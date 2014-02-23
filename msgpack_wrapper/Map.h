#pragma once

#include "Writer.h"
#include "MapReader.h"

namespace Msgpack {

template <typename Key, typename Value>
void Put(Writer& writer, const std::map<Key, Value>& data)
{
	writer.PutMap(data.size());
	for (const auto& pr : data)
	{
		writer.PutPair(pr.first, pr.second);
	}
}

template <typename Key, typename Value>
void Get(Reader& reader, std::map<Key, Value>& data)
{
	MapReader map_reader = reader.GetMap();
	const size_t size = map_reader.size();
	for (int i = 0; i < size; i++)
	{
		std::pair<Key, Value> val;
		map_reader.GetPair(i, val.first, val.second);
		data.insert(val);
	}
}

} // Msgpack