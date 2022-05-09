add_executable(motion_command_executer  motion_command_executer.cpp      pid_controller/pid_controller.cpp
               ros_functs/ros_functs.cpp thrustered_vehicle_motion_controller/thrustered_vehicle_motion_controller.cpp
               thrustered_vehicle_motion_controller/thrusters_controller/thrusters_controller.cpp)

target_link_libraries( motion_command_executer  pthread ${catkin_LIBRARIES})


add_executable(joystick joystick/joystick.cpp)
    target_link_libraries(joystick
    ${catkin_LIBRARIES}
)

add_executable(input joystick/joystick_input.cpp)
    target_link_libraries(input
    ${catkin_LIBRARIES}
)