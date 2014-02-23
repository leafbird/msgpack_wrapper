#include "stdafx.h"
#include "msgpack_wrapper/Buffer.h"
#include "msgpack_wrapper/Writer.h"
#include "msgpack_wrapper/Reader.h"
#include "msgpack_wrapper/Vector.h"
#include "msgpack_wrapper/Map.h"

using namespace Msgpack;

TEST(msgpack, primitive_stl_vector)
{
	std::vector<int> src, dst;
	src.push_back(10);
	src.push_back(20);
	src.push_back(30);

	EXPECT_NE(src, dst);
	Buffer buffer;
	buffer.Put() << src;
	buffer.Get() >> dst;
	EXPECT_EQ(src, dst);
}

TEST(msgpack, primitive_stl_map)
{
	std::map<std::string, int64_t> src, dst;
	src.insert(std::make_pair("aa", 10LL));
	src.insert(std::make_pair("ab", 20LL));
	src.insert(std::make_pair("ac", 30LL));

	EXPECT_NE(src, dst);
	Buffer buffer;
	buffer.Put() << src;
	buffer.Get() >> dst;
	EXPECT_EQ(src, dst);
}