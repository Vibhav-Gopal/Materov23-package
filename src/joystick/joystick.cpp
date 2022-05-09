#include "ros/ros.h"
#include "std_msgs/Int32.h"

int main(int argc, char** argv)
{
    ros::init(argc,argv,"joystick");

    ros::NodeHandle nh;
    
    std_msgs::Int32 command;

    command.data = 3;

    ros::Publisher pub = nh.advertise<std_msgs::Int32>("/motion_command",1000);

    ros::Rate loop_rate(5);

    while(ros::ok())
    {
        pub.publish(command);

        ros::spinOnce();

        loop_rate.sleep();
    }

    return 0;    
}