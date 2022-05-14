cmake_minimum_required(VERSION 3.0.2)
project(materov22_pioneer)


find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  message_generation
)

add_message_files(
   FILES
   MotionCommand.msg
   PWMValues.msg
   SensorData.msg
 )

 generate_messages(
  
  
)

include_directories(include 

   ${catkin_INCLUDE_DIRECTORIES}
)

add_subdirectory(src)