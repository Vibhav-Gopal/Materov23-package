

add_executable(input joystick/input.cpp joystick/joystick.cpp)
add_executable(output joystick/output.cpp)

target_link_libraries(input pthread ${catkin_LIBRARIES})
target_link_libraries(output pthread ${catkin_LIBRARIES})

add_subdirectory(motion_command_executer)