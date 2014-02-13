#pragma once

class Buffer;

class Reader : public NonCopyable
{
public:
	Reader(const Buffer& buffer);
	Reader(Reader&& rhs);
	virtual ~Reader();

	template <typename T>
	const Reader& operator>>(T& data)
	{
		Get(*this, data);
		return *this;
	}

	const Reader& operator>>(int& data) const;

private:
	class Impl;
	Impl* impl_;
};

