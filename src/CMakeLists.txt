add_executable(motion_command_executer  motion_command_executer.cpp      pid_controller/pid_controller.cpp
               ros_functs/ros_functs.cpp thrustered_vehicle_motion_controller/thrustered_vehicle_motion_controller.cpp
               thrustered_vehicle_motion_controller/thrusters_controller/thrusters_controller.cpp)

target_link_libraries( motion_command_executer  pthread )