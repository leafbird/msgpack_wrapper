#include "stdafx.h"
#include "msgpack_wrapper/Buffer.h"
#include "msgpack_wrapper/Writer.h"
#include "msgpack_wrapper/Reader.h"
#include "msgpack_wrapper/Map.h"

TEST(msgpack, quick_example)
{
	std::map<std::string, int> src, dst;
	src.insert(std::make_pair("a", 10));
	src.insert(std::make_pair("b", 20));
	src.insert(std::make_pair("c", 30));

	Msgpack::Buffer buffer;
	buffer.Put() << src;

	std::stringstream stm;
	stm << buffer;
	EXPECT_STREQ(R"(0:{"a"=>10, "b"=>20, "c"=>30})", stm.str().c_str());

	EXPECT_NE(src.size(), dst.size());
	buffer.Get() >> dst;
	EXPECT_EQ(src.size(), dst.size());

	for (const auto& pr : src)
	{
		EXPECT_NE(end(dst), dst.find(pr.first));
		EXPECT_EQ(pr.second, dst[pr.first]);
	}
}
