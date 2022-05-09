#include "ros/ros.h"
#include "sensor_msgs/Joy.h"
#include "std_msgs/Float32.h"

std_msgs::Float32 ans;

    ros::Publisher pub;

void joyInput(const sensor_msgs::Joy::ConstPtr& i)
{
    ans.data = i->axes[0];

    pub.publish(ans);

}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "input");
 
    ros::NodeHandle nh;

    pub = nh.advertise<std_msgs::Float32>("input",1000);

    ros::Subscriber sub = nh.subscribe<sensor_msgs::Joy>("joy", 10, joyInput);

    ros::spin();

    return 0;

}

