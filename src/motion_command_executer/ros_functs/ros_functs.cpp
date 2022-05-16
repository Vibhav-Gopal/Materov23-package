#include "ros_functs.h"
#include "ros/ros.h"
#include "motion_commands.h"
#include "materov22_pioneer/pwm_values_msg.h"
#include "materov22_pioneer/motion_command_msg.h"
#include "materov22_pioneer/sensor_data_msg.h"
#include "std_msgs/Bool.h"
#include <iostream>



extern  float target_yaw,target_depth,current_yaw,current_pitch,current_roll,current_depth;
extern int motion_command;

ros::Subscriber sensor_data_sub,motion_command_sub;
ros::Publisher pwm_values_pub,led_state_pub;

materov22_pioneer::motion_command_msg motion_command_msg;
materov22_pioneer::sensor_data_msg    sensor_data_msg;
std_msgs::Bool     led_state_msg;

ros:: NodeHandle* nh;
materov22_pioneer::pwm_values_msg pwm_values_msg;



void motionCommandCallBack(const  materov22_pioneer::motion_command_msgConstPtr& motion_command_msg ){

    motion_command   = motion_command_msg->command;
    if (motion_command == TURN_TO_GIVEN_DIRECTION )
    {
       target_yaw = motion_command_msg->angle;
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

    
    motion_command_sub    = (*nh).subscribe("motion_command",10,motionCommandCallBack);
    sensor_data_sub       = (*nh).subscribe("sensor_data",10,sensorDataCallBack);
    
    pwm_values_pub = (*nh).advertise<materov22_pioneer::pwm_values_msg>("pwm_values",5);
    led_state_pub  = (*nh).advertise<std_msgs::Bool>("led_state",1);

   

    
    


}


void publishPWMValues(int* pwm_values){

    for (int i = 0; i < 4; i++)
    {
        pwm_values_msg.values[i] = pwm_values[i];
    }
    
    pwm_values_pub.publish(pwm_values_msg);
} 

void changeLEDState(bool on_or_off){
    led_state_msg.data = on_or_off;
    led_state_pub.publish(led_state_msg);

}

void checkForCallBack(){
    ros::spinOnce();
}