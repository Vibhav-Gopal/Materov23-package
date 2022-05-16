#include "ros/ros.h"
#include "materov22_pioneer/motion_command_msg.h"

void callBack(const materov22_pioneer::motion_command_msg::ConstPtr& msg)
{
    
}

int main(int argc, char** argv)
{
    ros::init(argc,argv,"output");

    ros::NodeHandle nh;

    ros::Subscriber sub = nh.subscribe("/motion_command",100,callBack);

    ros::spin();

    return 0;
}