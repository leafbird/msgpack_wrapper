#pragma once

class Buffer;
class ArrayReader;

class Reader : public NonCopyable
{
public:
	Reader();
	Reader(const Buffer& buffer);
	Reader(Reader&& rhs);
	virtual ~Reader();

	template <typename T>
	Reader& operator>>(T& data)
	{
		Get(*this, data);
		return *this;
	}

	Reader& operator>>(int& data);

	void set_object(const msgpack::object& object);

	ArrayReader GetArray();

private:
	class Impl;
	Impl* impl_;
};

