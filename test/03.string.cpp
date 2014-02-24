#include "stdafx.h"
#include "msgpack_wrapper/Buffer.h"
#include "msgpack_wrapper/Writer.h"
#include "msgpack_wrapper/Reader.h"

using namespace Msgpack;

TEST(msgpack, raw_string)
{
	const char* src = "hello world";
	std::string dst;

	Buffer buffer;
	EXPECT_STRNE(src, dst.c_str());
	buffer.Put() << src;
	buffer.Get() >> dst;
	EXPECT_STREQ(src, dst.c_str());
}

TEST(msgpack, empty_string)
{
	const char* src = "";
	std::string dst("hello world");

	Buffer buffer;
	EXPECT_STRNE(src, dst.c_str());
	buffer.Put() << src;
	buffer.Get() >> dst;
	EXPECT_STREQ(src, dst.c_str());
}

TEST(msgpack, std_string)
{
	std::string src = "hello world";
	std::string dst;

	Buffer buffer;
	EXPECT_STRNE(src.c_str(), dst.c_str());
	buffer.Put() << src;
	buffer.Get() >> dst;
	EXPECT_STREQ(src.c_str(), dst.c_str());
}