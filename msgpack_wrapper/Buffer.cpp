#include "stdafx.h"
#include "Buffer.h"

class Buffer::Impl
{
public:
	Impl(int reserve);

	Impl(const Impl&) = delete;
	void operator=(const Impl&) = delete;

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

Buffer::Buffer(int reserve) : m_pImpl(new Impl(reserve))
{
}


Buffer::~Buffer()
{
	delete m_pImpl;
	m_pImpl = nullptr;
}

void Buffer::write(const char* buf, unsigned int len)
{
	m_pImpl->write(buf, len);
}
