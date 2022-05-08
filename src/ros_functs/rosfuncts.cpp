#include "ros_functs.h"
#include "ros/ros.h"
#include "std_msgs/Float32MultiArray.h"
#include "std_msgs/Float32.h"
#include "std_msgs/Int32.h"



extern  float target_yaw,current_yaw,current_pitch,current_roll;
extern int motion_command;
ros::Subscriber current_orientation_sub, motion_command_sub,target_yaw_sub;
ros::Publisher thrust_values_pub;

void currentOrientationCallBack(const std_msgs::Float32MultiArrayConstPtr&  current_orientation_msg ){

    current_yaw = current_orientation_msg.data[0];
    current_pitch = current_orientation_msg.data[1];
    current_roll = current_orientation_msg.data[2];

}
void TargetYawCallBack(const std_msgs::Float32ConstPtr&  target_yaw_msg ){

    target_yaw    = target_yaw_msg.data;

}

void TargetYawCallBack(const std_msgs::Int32ConstPtr&  motion_command_msg ){

    motion_command   = motion_command_msg.data;

}

void ros_init(int argc, char** argv){

    ros::init(argc,argv,"motion_command_executer");
    ros:: NodeHandle nh;

    current_orientation_sub    = nh.subscribe("current_orientation",1,currentOrientationCallBack);
    target_yaw_sub    = nh.subscribe("target_yaw",1,currentOrientationCallBack);
    motion_command_sub    = nh.subscribe("motion_command",1,motionCommandCallBack);
    
    thrust_values_pub = nh.advertise<std_msgs::Float32MultiArray>("thrust_values",5);
    


}