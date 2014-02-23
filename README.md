msgpack_wrapper
===============

wrapping interface of msgpack 0.5.8 - for VC++ 12.0(visual studio 2013).

### quick example

see [test/00.basic.cpp](test/00.basic.cpp) and other test codes.

```cpp
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
```

### other document

* [About Design](doc/About Design.md)
