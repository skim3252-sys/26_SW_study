cmake_minimum_required(VERSION 3.20)

project(vehicle_cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(vehicle_cmake_lib SHARED
    src/Vehicle.cpp
)
# Windows에서 이 DLL의 외부에서 사용할 수 있는 심볼들을 자동으로 export
set_target_properties(vehicle_cmake_lib PROPERTIES
    WINDOWS_EXPORT_ALL_SYMBOLS ON
)

# vehicle_cmake_lib을 컴파일할 때 include/를 헤더 검색 경로에 추가하고,
# 이 라이브러리를 사용하는 target에도 해당 경로를 전달
target_include_directories(vehicle_cmake_lib 
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# main.cpp를 이용해 실행 파일 target 생성
add_executable(vehicle_cmake_app
    src/main.cpp
)

# vehicle_cmake_app이 Vehicle의 실제 구현이 들어 있는
# vehicle_cmake_lib을 링크하도록 설정
target_link_libraries(vehicle_cmake_app
    PRIVATE
    vehicle_cmake_lib
)