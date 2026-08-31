cmake_minimum_required(VERSION 3.20)

project(vehicle_cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#어떤 실행, 구현부 source files를 컴파일하고 링크할 지 지정
add_executable(vehicle_cmake
    src/main.cpp
)
#선언부 확인 위해 include 디렉토리 확인 요구
target_include_directories(vehicle_cmake
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)