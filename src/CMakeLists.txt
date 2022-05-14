

add_executable(input joystick/input.cpp joystick/joystick.cpp)

target_link_libraries(input pthread ${catkin_LIBRARIES})

add_subdirectory(motion_command_executer)