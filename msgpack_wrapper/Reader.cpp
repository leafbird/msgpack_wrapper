#include "stdafx.h"
#include "Reader.h"
#include "Buffer.h"

class Reader::Impl : public NonCopyable 
{
public:
	Impl();

	void Init(const Buffer& buffer);

public:
	std::unique_ptr<msgpack::zone> mempool_;
	msgpack::object object_;
};

Reader::Impl::Impl()
{
}

void Reader::Impl::Init(const Buffer& buffer)
{
	mempool_.reset(new msgpack::zone);
	msgpack::unpack(buffer.ptr(), buffer.size(), nullptr, mempool_.get(), &object_);
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
	impl_->object_ >> data;
	return *this;
}