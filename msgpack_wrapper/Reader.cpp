#include "stdafx.h"
#include "Reader.h"
#include "Buffer.h"

class Reader::Impl : public NonCopyable 
{
public:
	Impl();

	void Init(const Buffer& buffer);
	void ReadyNext();

	template <typename T>
	void Get(T& data)
	{
		assert(enable_);
		object_ >> data;
		ReadyNext();
	}

public:
	bool enable_;
	msgpack::unpacker unpacker_;
	std::unique_ptr<msgpack::zone> mempool_;
	msgpack::object object_;
};

Reader::Impl::Impl() : enable_(false)
{
}

void Reader::Impl::Init(const Buffer& buffer)
{
	unpacker_.reserve_buffer(buffer.size());
	::memcpy(unpacker_.buffer(), buffer.ptr(), buffer.size());
	unpacker_.buffer_consumed(buffer.size());

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


// --------------------------------------------------------

Reader::Reader(const Buffer& buffer) : impl_(new Impl)
{
	impl_->Init(buffer);
}

Reader::Reader(Reader&& rhs) : impl_(rhs.impl_)
{
	rhs.impl_ = nullptr;
}


Reader::~Reader()
{
	Delete(impl_);
}


const Reader& Reader::operator>>(int& data) const
{
	impl_->Get(data);
	return *this;
}