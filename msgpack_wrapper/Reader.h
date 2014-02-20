#pragma once

class Buffer;
class ArrayReader;
class MapReader;

class Reader : public NonCopyable
{
public:
	Reader();
	Reader(const Buffer& buffer);
	Reader(const char* ptr, size_t size);
	Reader(Reader&& rhs);
	virtual ~Reader();

	template <typename T>
	Reader& operator>>(T& data)
	{
		Get(*this, data);
		return *this;
	}

	Reader& operator>>(int& data);
	Reader& operator>>(int64_t& data);
	Reader& operator>>(std::string& data);

	void set_object(const msgpack::object& object);
	bool HasData() const;

	ArrayReader GetArray();
	MapReader GetMap();

private:
	class Impl;
	Impl* impl_;
};

