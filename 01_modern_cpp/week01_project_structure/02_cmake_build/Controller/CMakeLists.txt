add_library(controller_lib STATIC
	src/VehicleController.cpp
)
target_include_directories(controller_lib
PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(controller_lib
	PUBLIC
    vehicle_lib
)
