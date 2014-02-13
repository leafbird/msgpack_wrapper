#pragma once

class Buffer;

class Writer : public NonCopyable
{
public:
	Writer(Buffer* buffer, size_t array_size, size_t map_size);
	Writer(Writer&& rhs);
	virtual ~Writer();

	const Writer& PutArray(size_t size) const;
	const Writer& PutMap(size_t size) const;

	template <typename T>
	const Writer& operator<<(const T& data) const
	{
		Put(*this, data);
		return *this;
	}

	const Writer& operator<<(const int& data) const;

private:
	class Impl;
	Impl* impl_;
};

