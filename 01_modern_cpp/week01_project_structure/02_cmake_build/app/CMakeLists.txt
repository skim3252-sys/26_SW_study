add_executable(vehicle_app
    main.cpp
)

target_link_libraries(vehicle_app
    PRIVATE
    controller_lib
)