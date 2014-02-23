## primitive type interface

Writer와 Reader에는 기본적으로 버퍼에 넣고 뺄 수 있는 primitive type의 연산자들이 정의되어 있다. 만약 버퍼에 넣고자 하는 타입인데 연산자 정의가 추가되어 있지 않다면 기존의 연산자를 복사해 하나씩 더 넣어주면 된다. 

이렇게 하지 않고 `pod(plain old data)`인 타입을 일괄 지원할 수도 있지만, 그렇게 구현하지 않는다. 그러려면 template type argument가 pod인지를 식별하는 type traits을 사용해야 하고, 이것이 헤더의 구현을 읽기 어렵게 만든다고 판단했기 때문이다. 나는 wrapper 구현코드가 읽기 쉽게 유지되는 것이 더 낫다고 생각하고, 필요한 타입의 연산자를 추가 정의해 주는 것은 그리 어렵지 않은 작업이기에 지금의 방식을 채택했다. 

## header include

wrapper는 용도에 따라 다수의 클래스로 분할되어 있다(이를테면 Buffer, Writer, Reader, etc.). 이들 헤더를 모두 포함하는 하나의 헤더파일을 만들 수도 있지만, 지금은 어플리케이션 쪽에서 필요한 클래스만 직접 개별 includle하도록 한다.

```cpp
#include "msgpack_wrapper/Buffer.h"
#include "msgpack_wrapper/Reader.h"
#include "msgpack_wrapper/Writer.h"

//...

```

이것이 귀찮다면 그냥 wrapper 폴더 내의 모든 헤더파일을 인클루드해주는 하나의 `include.h` 같은 헤더를 하나 만들고 사용하면 된다.

## 본래 코드 `namespace msgpack`와의 의존도.

wrapper는 최대한 `namespace msgpack`을 내부 구현으로 숨기려고 노력하였다. 실제 어플리케이션에서 사용할 때는 직접적으로 `msgpack`에 접근할 필요는 없고, wrapper 코드 집합인 `namespace Msgpack`만을 이용하면 된다. 
하지만 현재 `Reader`, `ArrayReader`, `MapReader` 간에 값을 주고 받는 과정에서 몇몇 클래스들이 헤더로 노출되기 때문에, 어플리케이션에서는 `#include "msgpack.hpp"`가 필요하다. 어플리케이션 쪽에서는 stdafx.h 정도에 이를 인클루드 해주는 것이 좋다. 
