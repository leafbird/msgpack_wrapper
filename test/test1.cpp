#include "stdafx.h"
#include "msgpack_wrapper/interface.h"

TEST(msgpack, empty)
{
	Buffer buffer;
	{
		Reader reader = buffer.Get();
		EXPECT_FALSE(reader.HasData());
	}

	{
		buffer.Put() << "test";
		Reader reader = buffer.Get();
		EXPECT_TRUE(reader.HasData());
	}
}

TEST(msgpack, reader_indirect_buffer)
{
	{
		Reader reader(nullptr, 100);
		EXPECT_FALSE(reader.HasData());
	}
	{
		Reader reader("NEVER use it like this.", 0);
		EXPECT_FALSE(reader.HasData());
	}
}

TEST(msgpack, primitive)
{
	int src = 20, dst = 0;

	Buffer buffer;
	buffer.Put() << src;
	buffer.Get() >> dst;

	EXPECT_EQ(src, dst);
}

TEST(msgpack, primitive_stream)
{
	int src[3] = { 10, 20, 30 };
	int dst[3] = { 0 };

	Buffer buffer;
	buffer.Put() << src[0] << src[1] << src[2];
	buffer.Get() >> dst[0] >> dst[1] >> dst[2];

	for (int i = 0; i < 3; i++)
	{
		EXPECT_EQ(src[i], dst[i]);
	}
}

TEST(msgpack, primitive_array)
{
	int src[3] = { 10, 20, 30 };
	int dst[3] = { 0 };

	Buffer buffer;
	buffer.PutArray(3) << src[0] << src[1] << src[2];
	buffer.GetArray() >> dst[0] >> dst[1] >> dst[2];

	for (int i = 0; i < 3; i++)
	{
		EXPECT_EQ(src[i], dst[i]);
	}
}

TEST(msgpack, primitive_map)
{
	int src[3] = { 10, 20, 30 };
	int dst[3] = { 0 };

	Buffer buffer;
	buffer.PutMap(3)
		.PutPair("a", src[0])
		.PutPair("b", src[1])
		.PutPair("c", src[2]);

	buffer.GetMap()
		.GetPair("a", dst[0])
		.GetPair("b", dst[1])
		.GetPair("c", dst[2]);

	for (int i = 0; i < 3; i++)
	{
		EXPECT_EQ(src[i], dst[i]);
	}
}

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