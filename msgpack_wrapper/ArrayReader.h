#pragma once

class Reader;

class ArrayReader
{
public:
	ArrayReader(msgpack::object object, msgpack::zone* zone);
	virtual ~ArrayReader();

	template <typename T>
	ArrayReader& operator>>(T& data)
	{
		ReadyNext() >> data;
		return *this;
	}

	size_t size() const;

private:
	Reader& ReadyNext();

	class Impl;
	Impl* impl_;
};

