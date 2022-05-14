#include "ros_functs.h"
#include "ros/ros.h"
#include "../motion_commands.h"
#include "std_msgs/Float32MultiArray.h"
#include "std_msgs/Int8MultiArray.h"
#include "std_msgs/Float32.h"
#include "std_msgs/Int32.h"
#include "materov22_pioneer/motion_control_msg.h"
#include "materov22_pioneer/sensor_data_msg.h"


#include <iostream>


extern  float target_yaw,target_depth,current_yaw,current_pitch,current_roll,current_depth;
extern int motion_command;

ros::Subscriber sensor_data_sub,motion_command_sub;
ros::Publisher pwm_values_pub;

materov22_pioneer::motion_control_msg motion_control_g;
materov22_pioneer::sensor_data_msg    sensor_data_g;

ros:: NodeHandle* nh;


std_msgs::Int8MultiArray pwm_values_msg;



void motionCommandCallBack(const  materov22_pioneer::motion_control_msgConstPtr& motion_command_msg ){

    motion_command   = motion_command_msg->command;
    if (motion_command == TURN_TO_GIVEN_DIRECTION )
    {
       target_yaw = motion_command_msg->yaw_angle;
    }
    

}

void sensorDataCallBack(const materov22_pioneer::sensor_data_msgConstPtr& sensor_data_msg)
{
    current_depth = sensor_data_msg->depth;
    current_yaw   = sensor_data_msg->yaw;
    current_pitch = sensor_data_msg->pitch;
    current_roll  = sensor_data_msg->roll;

}

void ros_init(int argc, char** argv){
    ros::init(argc,argv,"motion_command_executer");

    nh = new ros::NodeHandle;

    
    motion_command_sub    = (*nh).subscribe("motion_command",1,motionCommandCallBack);
    
    pwm_values_pub = (*nh).advertise<std_msgs::Int16MultiArray>("pwm_values",5);
    pwm_values_msg.data.resize(6);

   

    
    


}


void publishPWMValues(int* pwm_values){

    for (int i = 0; i < 6; i++)
    {
        pwm_values_msg.data[i] = pwm_values[i];
    }
    
    pwm_values_pub.publish(pwm_values_msg);
}
