#pragma once

#include "Writer.h"
#include "ArrayReader.h"

namespace Msgpack {

template <typename T>
void Put(Writer& writer, const std::vector<T>& data)
{
	writer.PutArray(data.size());
	for (const auto& val : data)
	{
		writer << val;
	}
}

template <typename T>
void Get(Reader& reader, std::vector<T>& data)
{
	ArrayReader array_reader = reader.GetArray();
	const size_t size = array_reader.size();
	for (int i = 0; i < size; i++)
	{
		T val;
		array_reader >> val;
		data.push_back(val);
	}
}

} // Msgpack