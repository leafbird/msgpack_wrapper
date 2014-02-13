#include "stdafx.h"
#include "msgpack_wrapper/interface.h"

TEST(msgpack, primitive)
{
	int src = 20, dst = 0;

	Buffer buffer;
	buffer.Put() << src;
	//buffer.Get() >> dst;

	EXPECT_EQ(src, dst);
}

TEST(msgpack, primitive_array)
{
	int src[3] = { 10, 20, 30 };
	int dst[3] = { 0 };

	Buffer buffer;
	buffer.PutArray(3) << src[0] << src[1] << src[2];
	//buffer.Get() >> dst;

	EXPECT_EQ(src, dst);
}