#pragma once

class Buffer
{
public:
	Buffer(int reserve = 1024);
	virtual ~Buffer();

	Buffer(const Buffer&) = delete;
	void operator=(const Buffer&) = delete;

	void write(const char* buf, unsigned int len);

private:
	class Impl;
	Impl* m_pImpl;
};