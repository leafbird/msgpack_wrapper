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

