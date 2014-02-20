#include "stdafx.h"
#include "Writer.h"
#include "Buffer.h"

class Writer::Impl : public NonCopyable
{
public:
	Impl(Buffer* parent);

public:
	msgpack::packer<Buffer> packer_;
};

Writer::Impl::Impl(Buffer* parent) : packer_(parent)
{

}

// --------------------------------------------------------

Writer::Writer(Buffer* buffer, size_t array_size, size_t map_size)
: impl_(new Impl(buffer))
{
	assert(array_size == 0 || map_size == 0);

	if (array_size > 0)
	{
		PutArray(array_size);
	}
	else if (map_size > 0)
	{
		PutMap(map_size);
	}
}

Writer::Writer(Writer&& rhs) : impl_(rhs.impl_)
{
	rhs.impl_ = nullptr;
}

Writer::~Writer()
{
	Delete(impl_);
}

Writer& Writer::PutArray(size_t size)
{
	impl_->packer_.pack_array(size);
	return *this;
}

Writer& Writer::PutMap(size_t size)
{
	impl_->packer_.pack_map(size);
	return *this;
}


Writer& Writer::operator<<(const int& data)
{
	impl_->packer_ << data;
	return *this;
}

Writer& Writer::operator<<(const int64_t& data)
{
	impl_->packer_ << data;
	return *this;
}

Writer& Writer::operator<<(const std::string& data)
{
	impl_->packer_ << data;
	return *this;
}

Writer& Writer::operator<<(const char* data)
{
	return operator<<(std::string(data));
}

