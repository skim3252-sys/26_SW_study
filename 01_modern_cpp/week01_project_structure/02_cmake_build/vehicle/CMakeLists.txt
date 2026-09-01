add_library(vehicle_lib STATIC
    src/Vehicle.cpp
)

target_include_directories(vehicle_lib
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)