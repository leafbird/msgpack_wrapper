#pragma once

namespace Msgpack {

class Writer;
class Reader;
class ArrayReader;
class MapReader;

class Buffer : public NonCopyable
{
public:
	Buffer(int reserve = 1024);
	virtual ~Buffer();

	void write(const char* buf, unsigned int len);

	Writer Put();
	Writer PutArray(size_t size);
	Writer PutMap(size_t size);

	Reader Get() const;
	ArrayReader GetArray() const;
	MapReader GetMap() const;

	const char* ptr() const;
	size_t size() const;
	bool empty() const;

private:
	class Impl;
	Impl* impl_;
};

} // Msgpack