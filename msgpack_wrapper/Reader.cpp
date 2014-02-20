#include "stdafx.h"
#include "Reader.h"
#include "Buffer.h"
#include "ArrayReader.h"
#include "MapReader.h"

class Reader::Impl : public NonCopyable 
{
public:
	Impl();

	void Init(const char* ptr, size_t size);
	void ReadyNext();

	template <typename T>
	void Get(T& data)
	{
		assert(enable_);
		object_ >> data;
		ReadyNext();
	}

	ArrayReader GetArray();
	MapReader GetMap();

public:
	bool enable_;
	msgpack::unpacker unpacker_;
	std::unique_ptr<msgpack::zone> mempool_;
	msgpack::object object_;
};

Reader::Impl::Impl() : enable_(false)
{
}

void Reader::Impl::Init(const char* ptr, size_t size)
{
	unpacker_.reserve_buffer(size);
	::memcpy(unpacker_.buffer(), ptr, size);
	unpacker_.buffer_consumed(size);

	ReadyNext();
}

void Reader::Impl::ReadyNext()
{
	msgpack::unpacked result;
	if (!unpacker_.next(&result))
	{
		enable_ = false;
		return;
	}

	object_ = result.get();
	mempool_.reset(result.zone().release());
	enable_ = true;
}

ArrayReader Reader::Impl::GetArray()
{
	return ArrayReader(object_, mempool_.release());
}

MapReader Reader::Impl::GetMap()
{
	return MapReader(object_, mempool_.release());
}

// --------------------------------------------------------

Reader::Reader() : impl_(new Impl)
{

}

Reader::Reader(const Buffer& buffer) : Reader()
{
	if (buffer.empty())
		return;

	impl_->Init(buffer.ptr(), buffer.size());
}

Reader::Reader(const char* ptr, size_t size) : Reader()
{
	if (ptr == nullptr || size == 0)
		return;

	impl_->Init(ptr, size);
}

Reader::Reader(Reader&& rhs) : impl_(rhs.impl_)
{
	rhs.impl_ = nullptr;
}

Reader::~Reader()
{
	Delete(impl_);
}

void Reader::set_object(const msgpack::object& object)
{
	impl_->object_ = object;
	impl_->enable_ = true;
}

Reader& Reader::operator>>(int& data)
{
	impl_->Get(data);
	return *this;
}

ArrayReader Reader::GetArray()
{
	return impl_->GetArray();
}

MapReader Reader::GetMap()
{
	return impl_->GetMap();
}

bool Reader::HasData() const
{
	return impl_->enable_;
}
