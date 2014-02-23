#pragma once

namespace Msgpack {
	
class Buffer;

class Writer : public NonCopyable
{
public:
	Writer(Buffer* buffer, size_t array_size, size_t map_size);
	Writer(Writer&& rhs);
	virtual ~Writer();

	Writer& PutArray(size_t size);
	Writer& PutMap(size_t size);

	template <typename T>
	Writer& operator<<(const T& data)
	{
		Put(*this, data);
		return *this;
	}

	template <typename Key, typename Value>
	Writer& PutPair(const Key& key, const Value& value)
	{
		return (*this) << key << value;
	}

	Writer& operator<<(const int& data);
	Writer& operator<<(const float& data);
	Writer& operator<<(const short& data);
	Writer& operator<<(const unsigned int& data);
	Writer& operator<<(const int64_t& data);
	Writer& operator<<(const std::string& data);
	Writer& operator<<(const char* data);

private:
	class Impl;
	Impl* impl_;
};

} // Msgpack