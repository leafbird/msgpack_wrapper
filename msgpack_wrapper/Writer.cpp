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

const Writer& Writer::PutArray(size_t size) const
{
	impl_->packer_.pack_array(size);
	return *this;
}

const Writer& Writer::PutMap(size_t size) const
{
	impl_->packer_.pack_map(size);
	return *this;
}


const Writer& Writer::operator<<(int& data) const
{
	impl_->packer_ << data;
	return *this;
}
