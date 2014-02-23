#pragma once

struct BaseType
{
	BaseType();

	int int_;
	float float_;
	short short_;
	unsigned int uint_;
	int64_t int64_;

	bool operator==(const BaseType& rhs) const;
	bool operator!=(const BaseType& rhs) const { return !operator==(rhs); }
};

struct MyStream : public BaseType
{
	MyStream() = default;
	MyStream(int int_, float float_, short short_, unsigned int uint_, int64_t int64_);
};

struct MyArray : public BaseType
{
	MyArray() = default;
	MyArray(int int_, float float_, short short_, unsigned int uint_, int64_t int64_);
};

struct MyMap : public BaseType
{
	MyMap() = default;
	MyMap(int int_, float float_, short short_, unsigned int uint_, int64_t int64_);
};


namespace Msgpack {

class Writer;
class Reader;

void Put(Writer& writer, const MyStream& data);
void Get(Reader& reader, MyStream& data);
void Put(Writer& writer, const MyArray& data);
void Get(Reader& reader, MyArray& data);
void Put(Writer& writer, const MyMap& data);
void Get(Reader& reader, MyMap& data);

} // Msgpack