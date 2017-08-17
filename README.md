msgpack_wrapper
===============

wrapping interface of msgpack 0.5.8 - for VC++ 12.0(visual studio 2013).

### 왜 wrapper를 사용하는가
msgpack은 기본으로 다양한 기능을 가진 c++ 인터페이스가 제공되고, [github에 오픈](https://github.com/msgpack/msgpack-c)되어 있다. 기본 제공되는 인터페이스를 이용해도 User-defined type을 직렬화할 순 있으나, 대상 타입의 선언 내에 intrusive하게 수정을 가해야 한다는 제약을 가진다. 
```cpp
class myclass {
private:
    std::string m_str;
    std::vector<int> m_vec;
public:
    MSGPACK_DEFINE(m_str, m_vec); // 난 이게 싫다. I hate this.
};
```
위의 방식은 세 가지 정도가 마음에 안드는데,

1. 일단 serialize 시키려면 타입 선언 헤더를 고쳐야 하는 것 자체도 마음에 안들지만
2. 3rd party코드를 가져와서 부득이하게 타입 선언을 수정할 수 없다면 답도 없거니와
3. `MSGPACK_DEFINE` 매크로가 헤더에서 참조되어야 하기 때문에 msgpack의 헤더파일이 넓은 범위에서 참조될 수밖에 없다.

### wrapper를 사용한 User-defined type의 직렬화

그래서, non-intrusive하게 User-defined type을 직렬화할 수 있도록 wrapper 인터페이스를 만들어 보았다. `msgpack_wrapper`를 사용하면 user-defined type의 직렬화 방식을 정의하는 Msgpack::Put, Msgpack::Get 헬퍼 메소드를 작성해주면 된다.

```cpp
class myclass { // 타입의 선언은 건드리지 않는다.
private:
    std::string m_str;
    std::vector<int> m_vec;
};

// 아래 헬퍼 함수를 만들어주면 된다. 필요에 따라 서로 다른 헤더 파일로 구분해 작성해도 무방하다.
namespace Msgpack {
class Writer;
class Reader;

void Put(Writer& writer, const myclass& data);
void Get(Reader& reader, myclass& data);
} // namespace Msgpack
```

### quick example

see [test/00.quick_example.cpp](test/00.quick_example.cpp) and other test codes.

### other document

* [About Design](doc/About%20Design.md)
* ...and others...
