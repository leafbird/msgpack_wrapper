#pragma once

class Reader;

class MapReader : public NonCopyable
{
public:
	MapReader(msgpack::object object, msgpack::zone* zone);
	virtual ~MapReader();

	template <typename T>
	MapReader& GetPair(const std::string& key, T& data) {
		Ready(key) >> data;
		return *this;
	}

	template <typename Key, typename Value>
	MapReader& GetPair(int index, Key& key, Value& value) {
		ReadyKey(index) >> key;
		ReadyValue(index) >> value;
		return *this;
	}

	size_t size() const;

private:
	Reader& Ready(const std::string& key);
	Reader& ReadyKey(size_t index);
	Reader& ReadyValue(size_t index);

	class Impl;
	Impl* impl_;
};