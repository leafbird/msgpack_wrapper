#include "stdafx.h"
#include "ArrayReader.h"
#include "Reader.h"

class ArrayReader::Impl
{
public:
	Impl(msgpack::object object, msgpack::zone* zone);

	Reader& ReadyNext();
	size_t size() const;

public:
	size_t index_;
	msgpack::object object_;
	std::unique_ptr<msgpack::zone> mempool_;
	Reader reader_;
};

ArrayReader::Impl::Impl(msgpack::object object, msgpack::zone* zone)
: object_(object), mempool_(zone), index_(0)
{

}

Reader& ArrayReader::Impl::ReadyNext()
{
	assert(index_ < size());

	reader_.set_object(object_.via.array.ptr[index_++]);

	return reader_;
}

size_t ArrayReader::Impl::size() const
{
	return object_.via.array.size;
}


// ------------------------------------------------------------------------------

ArrayReader::ArrayReader(msgpack::object object, msgpack::zone* zone)
	: impl_(new Impl(object, zone))
{
}

ArrayReader::~ArrayReader()
{
	Delete(impl_);
}

Reader& ArrayReader::ReadyNext()
{
	return impl_->ReadyNext();
}

size_t ArrayReader::size() const
{
	return impl_->size();
}

