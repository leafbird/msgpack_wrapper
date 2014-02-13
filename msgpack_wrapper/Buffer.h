#pragma once

class Writer;

class Buffer : public NonCopyable
{
public:
	Buffer(int reserve = 1024);
	virtual ~Buffer();

	void write(const char* buf, unsigned int len);

	const Writer Put();
	const Writer PutArray(size_t size);
	const Writer PutMap(size_t size);

private:
	class Impl;
	Impl* impl_;
};