#include "stdafx.h"
#include "CustomType.h"

BaseType::BaseType()
: int_(0)
, float_(0.f)
, short_(0)
, uint_(0U)
, int64_(0LL)
{
}

bool BaseType::operator==(const BaseType& rhs) const
{
	return this->int_ == rhs.int_
		&& std::abs(this->float_ - rhs.float_) < 0.01f
		&& this->short_ == rhs.short_
		&& this->uint_ == rhs.uint_
		&& this->int64_ == rhs.int64_;
}


MyStream::MyStream(int int_, float float_, short short_, unsigned int uint_, int64_t int64_)
{
	this->int_ = int_;
	this->float_ = float_;
	this->short_ = short_;
	this->uint_ = uint_;
	this->int64_ = int64_;
}

MyArray::MyArray(int int_, float float_, short short_, unsigned int uint_, int64_t int64_)
{
	this->int_ = int_;
	this->float_ = float_;
	this->short_ = short_;
	this->uint_ = uint_;
	this->int64_ = int64_;
}

MyMap::MyMap(int int_, float float_, short short_, unsigned int uint_, int64_t int64_)
{
	this->int_ = int_;
	this->float_ = float_;
	this->short_ = short_;
	this->uint_ = uint_;
	this->int64_ = int64_;
}

#include "msgpack_wrapper/Writer.h"
#include "msgpack_wrapper/Reader.h"
#include "msgpack_wrapper/ArrayReader.h"
#include "msgpack_wrapper/MapReader.h"

namespace Msgpack {

void Put(Writer& writer, const MyStream& data)
{
	writer
		<< data.int_
		<< data.float_
		<< data.short_
		<< data.uint_
		<< data.int64_;
}

void Get(Reader& reader, MyStream& data)
{
	reader
		>> data.int_
		>> data.float_
		>> data.short_
		>> data.uint_
		>> data.int64_;
}

void Put(Writer& writer, const MyArray& data)
{
	writer.PutArray(5)
		<< data.int_
		<< data.float_
		<< data.short_
		<< data.uint_
		<< data.int64_;
}

void Get(Reader& reader, MyArray& data)
{
	reader.GetArray()
		>> data.int_
		>> data.float_
		>> data.short_
		>> data.uint_
		>> data.int64_;
}

void Put(Writer& writer, const MyMap& data)
{
	writer.PutMap(5)
		.PutPair("int_", data.int_)
		.PutPair("float_", data.float_)
		.PutPair("short_", data.short_)
		.PutPair("uint_", data.uint_)
		.PutPair("int64_", data.int64_);
}

void Get(Reader& reader, MyMap& data)
{
	reader.GetMap()
		.GetPair("int_", data.int_)
		.GetPair("float_", data.float_)
		.GetPair("short_", data.short_)
		.GetPair("uint_", data.uint_)
		.GetPair("int64_", data.int64_);
}

} // Msgpack