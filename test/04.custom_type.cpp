#include "stdafx.h"
#include "CustomType.h"
#include "msgpack_wrapper/Buffer.h"
#include "msgpack_wrapper/Writer.h"
#include "msgpack_wrapper/Reader.h"
#include "msgpack_wrapper/Vector.h"
#include "msgpack_wrapper/Map.h"

using namespace Msgpack;

TEST(msgpack, custom_stream)
{
	MyStream src(10, 20.f, 30, 40, 50), dst;

	EXPECT_NE(src, dst);
	Buffer buffer;
	buffer.Put() << src;
	buffer.Get() >> dst;
	EXPECT_EQ(src, dst);
}

TEST(msgpack, custom_array)
{
	MyArray src(10, 20.f, 30, 40, 50), dst;

	EXPECT_NE(src, dst);
	Buffer buffer;
	buffer.Put() << src;
	buffer.Get() >> dst;
	EXPECT_EQ(src, dst);
}

TEST(msgpack, custom_map)
{
	MyMap src(10, 20.f, 30, 40, 50), dst;

	EXPECT_NE(src, dst);
	Buffer buffer;
	buffer.Put() << src;
	buffer.Get() >> dst;
	EXPECT_EQ(src, dst);
}
