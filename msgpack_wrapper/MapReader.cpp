#include "stdafx.h"
#include "MapReader.h"
#include "Reader.h"

class MapReader::Impl : public NonCopyable {
public:
	Impl(msgpack::object object, msgpack::zone* zone);

	Reader& Ready(const std::string& key);
public:
	msgpack::object object_;
	std::unique_ptr<msgpack::zone> mempool_;
	Reader reader_;
};

MapReader::Impl::Impl(msgpack::object object, msgpack::zone* zone)
: object_(object), mempool_(zone)
{
	assert(object_.type == msgpack::type::MAP);
}

Reader& MapReader::Impl::Ready(const std::string& key)
{
	msgpack::object_kv* p = object_.via.map.ptr;
	msgpack::object_kv* pend = object_.via.map.ptr + object_.via.map.size;
	for (; p != pend; p++)
	{
		std::string data_key;
		p->key >> data_key;
		if (data_key == key)
		{
			reader_.set_object(p->val);
			return reader_;
		}
	}

	assert(false);
	return reader_;
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

Reader& MapReader::Ready(const std::string& key)
{
	return impl_->Ready(key);
}
