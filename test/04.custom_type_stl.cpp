#include "stdafx.h"
#include "CustomType.h"
#include "msgpack_wrapper/Buffer.h"
#include "msgpack_wrapper/Writer.h"
#include "msgpack_wrapper/Reader.h"
#include "msgpack_wrapper/Vector.h"
#include "msgpack_wrapper/Map.h"

using namespace Msgpack;

TEST(msgpack, custom_array_stl_vector)
{
	std::vector<MyArray> src, dst;
	src.push_back(MyArray(10, 20.f, 30, 40, 50));
	src.push_back(MyArray(20, 30.f, 40, 50, 60));
	src.push_back(MyArray(30, 40.f, 50, 60, 70));

	EXPECT_NE(src, dst);
	Buffer buffer;
	buffer.Put() << src;
	buffer.Get() >> dst;
	EXPECT_EQ(src, dst);
}

TEST(msgpack, custom_array_stl_map)
{
	std::map<std::string, MyArray> src, dst;
	src.insert(std::make_pair("a", MyArray(10, 20.f, 30, 40, 50)));
	src.insert(std::make_pair("b", MyArray(20, 30.f, 40, 50, 60)));
	src.insert(std::make_pair("c", MyArray(30, 40.f, 50, 60, 70)));

	EXPECT_NE(src, dst);
	Buffer buffer;
	buffer.Put() << src;
	buffer.Get() >> dst;
	EXPECT_EQ(src, dst);
}


TEST(msgpack, custom_map_stl_vector)
{
	std::vector<MyMap> src, dst;
	src.push_back(MyMap(10, 20.f, 30, 40, 50));
	src.push_back(MyMap(20, 30.f, 40, 50, 60));
	src.push_back(MyMap(30, 40.f, 50, 60, 70));

	EXPECT_NE(src, dst);
	Buffer buffer;
	buffer.Put() << src;
	buffer.Get() >> dst;
	EXPECT_EQ(src, dst);
}

TEST(msgpack, custom_map_stl_map)
{
	std::map<std::string, MyMap> src, dst;
	src.insert(std::make_pair("a", MyMap(10, 20.f, 30, 40, 50)));
	src.insert(std::make_pair("b", MyMap(20, 30.f, 40, 50, 60)));
	src.insert(std::make_pair("c", MyMap(30, 40.f, 50, 60, 70)));

	EXPECT_NE(src, dst);
	Buffer buffer;
	buffer.Put() << src;
	buffer.Get() >> dst;
	EXPECT_EQ(src, dst);
}