## CMake Include Path

`#include "Vehicle.hpp"`는 사용할 헤더 파일 이름을 지정하지만,
컴파일러가 해당 파일의 위치를 자동으로 아는 것은 아니다.

현재 프로젝트 구조:

```text
02_cmake_build/
├─ include/
│  └─ Vehicle.hpp
└─ src/
   ├─ main.cpp
   └─ Vehicle.cpp
```

 ## CMake Target Visibility

CMake의 `PRIVATE`, `PUBLIC`, `INTERFACE`는 target의 설정이
다른 target으로 전파되는 범위를 결정한다.

# CMake 기초 정리

## Target

CMake에서 `target`은 빌드 대상이다.

주로:

- 실행 파일
- 라이브러리

가 target이 된다.

---

## Executable

```cmake
add_executable(vehicle_cmake_app
    src/main.cpp
)
```

`main.cpp`를 이용해 실행 파일 target을 만든다.

Windows에서는 최종적으로 `.exe` 파일이 생성된다.

---

## Library

```cmake
add_library(vehicle_cmake_lib
    src/Vehicle.cpp
)
```

`Vehicle.cpp`의 구현을 이용해 library target을 만든다.

정적 라이브러리는:

```cmake
add_library(vehicle_cmake_lib STATIC
    src/Vehicle.cpp
)
```
처럼 작성하며 Windows에서는 보통 `.lib` 파일이 생성된다.

동적 라이브러리는:
```cmake
add_library(vehicle_cmake_lib SHARED
    src/Vehicle.cpp
)
``` 
SHARED 를 넣어주며 Windows에서는 보통 `.dll` 파일이 생성된다.

빌드 시점에 코드를 묶어두는 것이 정적 라이브러리이고, 
- 실행 시점에 lib 없어도 문제 X

실행 때마다 코드를 묶어두는 것이 동적 라이브러리이다. 
- 실행 시점에 dll 필요, 대신 executable 파일 크기 작음
- visual_studio에서는 dll 을 실행 시점에 없으면 다시 빌드해줌

---

## Header와 Library

`Vehicle.hpp`

- 클래스와 함수의 선언
- 사용할 수 있는 인터페이스 제공

`Vehicle.cpp`

- 함수의 실제 구현

Library는 이 구현 코드를 묶어둔 빌드 결과물이다.

---

## include 경로 설정

```cmake
target_include_directories(vehicle_cmake_lib
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
```

컴파일러에게 `Vehicle.hpp`를 찾을 때 `include/` 폴더도 검색하도록 알려준다.

즉:

- `#include "Vehicle.hpp"` → 어떤 헤더를 사용할지 지정
- `target_include_directories()` → 그 헤더를 어디서 찾을지 지정

---

## PRIVATE / PUBLIC / INTERFACE

- `PRIVATE` : 현재 target만 사용
- `PUBLIC` : 현재 target + 이 target을 사용하는 쪽에도 전달
- `INTERFACE` : 사용하는 쪽에만 전달

현재 `vehicle_cmake_lib`은 `Vehicle.hpp`를 사용하고,
`vehicle_cmake_app`의 `main.cpp`도 `Vehicle.hpp`를 사용하므로 `PUBLIC`으로 설정한다.

---

## Library 연결

```cmake
target_link_libraries(vehicle_cmake_app
    PRIVATE
    vehicle_cmake_lib
)
```

`vehicle_cmake_app`이 `vehicle_cmake_lib`의 실제 구현을 사용하도록 연결한다.

전체 구조는 다음과 같다.

```text
Vehicle.hpp
    ↓ 선언

Vehicle.cpp
    ↓
vehicle_cmake_lib
    ↓ link

main.cpp
    ↓
vehicle_cmake_app
    ↓
vehicle_cmake_app.exe
```

---

## Compile Error와 Link Error

Header를 찾지 못하면:

- Compile Error

예:
`Vehicle.hpp`를 찾을 수 없음

Header 선언은 찾았지만 실제 구현을 연결하지 못하면:

- Link Error

예:
`Vehicle.cpp`를 빌드 대상에서 빼거나 library를 link하지 않은 경우

---

## 현재 CMakeLists.txt

```cmake
cmake_minimum_required(VERSION 3.20)

project(vehicle_cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(vehicle_cmake_lib
    src/Vehicle.cpp
)

target_include_directories(vehicle_cmake_lib
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(vehicle_cmake_app
    src/main.cpp
)

target_link_libraries(vehicle_cmake_app
    PRIVATE
    vehicle_cmake_lib
)
```

---

## CMake Cache

CMake는 이전 설정 결과를 cache에 저장한다.

설정을 수정했는데 이상한 오류가 계속 남거나,
CMake 생성 실패 메시지가 사라지지 않는다면 cache를 삭제하고 다시 구성한다.

기존 실행 파일이 남아 있으면 CMake 생성이 실패한 상태에서도
예전 `.exe`가 실행될 수 있으므로 실행 여부만으로 빌드 성공을 판단하면 안 된다.


## CMake add_subdirectory()

프로젝트가 커지면 하나의 `CMakeLists.txt`에서 모든 target을 관리하기보다,
기능별 폴더에 `CMakeLists.txt`를 나누어 관리할 수 있다.

예:

```text
02_cmake_build/
├─ CMakeLists.txt
├─ vehicle/
│  ├─ CMakeLists.txt
│  ├─ include/
│  │  └─ Vehicle.hpp
│  └─ src/
│     └─ Vehicle.cpp
└─ app/
   ├─ CMakeLists.txt
   └─ main.cpp
```

최상위 `CMakeLists.txt`:

```cmake
cmake_minimum_required(VERSION 3.20)

project(vehicle_cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(vehicle)
add_subdirectory(app)
```

`add_subdirectory()`는 해당 폴더의 `CMakeLists.txt`를 현재 빌드에 포함시킨다.

### vehicle/CMakeLists.txt

```cmake
add_library(vehicle_lib STATIC
    src/Vehicle.cpp
)

target_include_directories(vehicle_lib
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
```

### app/CMakeLists.txt

```cmake
add_executable(vehicle_app
    main.cpp
)

target_link_libraries(vehicle_app
    PRIVATE
    vehicle_lib
)
```

전체 관계:

```text
vehicle/
→ vehicle_lib target 생성

app/
→ vehicle_app target 생성
→ vehicle_lib 링크
```

`${CMAKE_CURRENT_SOURCE_DIR}`는 현재 처리 중인 `CMakeLists.txt`가 있는 폴더를 의미한다.

따라서 `vehicle/CMakeLists.txt`에서:

```cmake
${CMAKE_CURRENT_SOURCE_DIR}/include
```

는 `vehicle/include`를 가리킨다.