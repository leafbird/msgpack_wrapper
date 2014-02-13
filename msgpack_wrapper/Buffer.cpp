#include "stdafx.h"
#include "Buffer.h"
#include "Writer.h"

class Buffer::Impl : public NonCopyable
{
public:
	Impl(int reserve);

	void write(const char* buf, unsigned int len);

public:
	size_t offset_;
	std::vector<char> vecData_;
};

Buffer::Impl::Impl(int reserve) : offset_(0LL)
{
	vecData_.reserve(reserve);
}

void Buffer::Impl::write(const char* buf, unsigned int len)
{
	vecData_.resize(offset_ + len);
	::memcpy_s(&vecData_[offset_], offset_ + len, buf, len);

	offset_ += len;
}


// --------------------------------------------------------

Buffer::Buffer(int reserve) : impl_(new Impl(reserve))
{
}


Buffer::~Buffer()
{
	Delete(impl_);
}

void Buffer::write(const char* buf, unsigned int len)
{
	impl_->write(buf, len);
}

const Writer Buffer::Put()
{
	return Writer(this, 0, 0);
}

const Writer Buffer::PutArray(size_t size)
{
	return Writer(this, size, 0);
}

const Writer Buffer::PutMap(size_t size)
{
	return Writer(this, 0, size);
}
