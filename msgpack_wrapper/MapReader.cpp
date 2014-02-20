#include "stdafx.h"
#include "MapReader.h"
#include "Reader.h"

class MapReader::Impl : public NonCopyable {
public:
	Impl(msgpack::object object, msgpack::zone* zone);

public:
	msgpack::object object_;
	std::unique_ptr<msgpack::zone> mempool_;
	Reader reader_;
};

MapReader::Impl::Impl(msgpack::object object, msgpack::zone* zone)
: object_(object), mempool_(zone)
{

}

// ------------------------------------------------------------------------------

MapReader::MapReader(msgpack::object object, msgpack::zone* zone)
: impl_(new Impl(object, zone))
{
}


MapReader::~MapReader()
{
	Delete(impl_);
}
