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

private:
	Reader& Ready(const std::string& key);

	class Impl;
	Impl* impl_;
};