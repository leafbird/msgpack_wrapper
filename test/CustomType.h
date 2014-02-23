#pragma once

struct BaseType
{
	BaseType();
	BaseType(int int_, float float_, short short_, unsigned int uint_, int64_t int64_);

	int int_;
	float float_;
	short short_;
	unsigned int uint_;
	int64_t int64_;
};

struct MyStream : public BaseType {};
struct MyArray : public BaseType {};
struct MyMap : public BaseType {};

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