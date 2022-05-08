#include "ros_functs.h"
#include "ros/ros.h"

#include "std_msgs/Float32MultiArray.h"
#include "std_msgs/Int16MultiArray.h"
#include "std_msgs/Float32.h"
#include "std_msgs/Int32.h"

#include <iostream>


extern  float target_yaw,current_yaw,current_pitch,current_roll;
extern int motion_command;

ros::Subscriber current_orientation_sub, motion_command_sub,target_yaw_sub;
ros::Publisher pwm_values_pub;

std_msgs::Int16MultiArray pwm_values_msg;

void currentOrientationCallBack(const std_msgs::Float32MultiArrayConstPtr&  current_orientation_msg ){

    current_yaw = current_orientation_msg -> data[0];
    current_pitch = current_orientation_msg -> data[1];
    current_roll = current_orientation_msg ->data[2];

}
void TargetYawCallBack(const std_msgs::Float32ConstPtr&  target_yaw_msg ){

    target_yaw    = target_yaw_msg->data;

}

void motionCommandCallBack(const std_msgs::Int32ConstPtr&  motion_command_msg ){

    motion_command   = motion_command_msg-> data;

}


void ros_init(int argc, char** argv){
    ros::init(argc,argv,"motion_command_executer");
    ros:: NodeHandle nh;

    current_orientation_sub    = nh.subscribe("current_orientation",1,currentOrientationCallBack);
    target_yaw_sub    = nh.subscribe("target_yaw",1,currentOrientationCallBack);
    motion_command_sub    = nh.subscribe("motion_command",1,motionCommandCallBack);
    
    pwm_values_pub = nh.advertise<std_msgs::Int16MultiArray>("pwm_values",5);
    pwm_values_msg.data.resize(6);

   

    
    


}


void publishPWMValues(int* pwm_values){

    for (int i = 0; i < 6; i++)
    {
        pwm_values_msg.data[i] = pwm_values[i];
    }
    
    pwm_values_pub.publish(pwm_values_msg);
}
