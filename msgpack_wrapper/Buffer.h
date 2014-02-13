#pragma once

class Writer;

class Buffer
{
public:
	Buffer(int reserve = 1024);
	virtual ~Buffer();

	Buffer(const Buffer&) = delete;
	void operator=(const Buffer&) = delete;

	void write(const char* buf, unsigned int len);

	const Writer Put();
	const Writer PutArray(size_t size);
	const Writer PutMap(size_t size);

private:
	class Impl;
	Impl* m_pImpl;
};