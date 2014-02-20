#pragma once

class MapReader : public NonCopyable
{
public:
	MapReader(msgpack::object object, msgpack::zone* zone);
	virtual ~MapReader();

	template <typename T>
	MapReader& GetPair(const std::string& key, T& data) {
		return *this;
	}

private:
	class Impl;
	Impl* impl_;
};