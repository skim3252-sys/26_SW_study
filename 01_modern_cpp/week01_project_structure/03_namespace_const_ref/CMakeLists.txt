cmake_minimum_required(VERSION 3.20)

project(VehicleStudy)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_library(Vehicle_lib STATIC
	src/Vehicle.cpp 
	src/VehicleController.cpp
)

target_include_directories(Vehicle_lib
	PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/include
)
add_executable(Vehicle_main
	src/main.cpp
)
target_link_libraries(Vehicle_main 
	PRIVATE
	Vehicle_lib
)