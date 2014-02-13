#pragma once

class Buffer;

class Writer
{
public:
	Writer(Buffer* buffer, size_t array_size, size_t map_size);
	Writer(Writer&& rhs);
	virtual ~Writer();

	Writer(const Writer&) = delete;
	void operator=(const Writer&) = delete;

	const Writer& PutArray(size_t size) const;
	const Writer& PutMap(size_t size) const;

	template <typename T>
	const Writer& operator<<(T& data) const
	{
		Put(*this, data);
		return *this;
	}

	const Writer& operator<<(int& data) const;

private:
	class Impl;
	Impl* impl_;
};

