#include "ros/ros.h"
#include "materov22_pioneer/motion_command_msg.h"

ros::Publisher pub;

void callBack(const materov22_pioneer::motion_command_msg::ConstPtr& msg)
{
    pub.publish(msg);
}

int main(int argc, char** argv)
{
    ros::init(argc,argv,"output");

    ros::NodeHandle nh;

    ros::Subscriber sub = nh.subscribe("/motion_command",100,callBack);

    pub = nh.advertise<materov22_pioneer::motion_command_msg>("/motion_command",1000);

    ros::spin();

    return 0;
}