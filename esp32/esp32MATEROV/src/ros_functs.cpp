#include "ros_functs.h"
#include "ros_lib/ros.h"
#include "materov22_pioneer/sensor_data_msg.h"

ros::NodeHandle nh;
materov22_pioneer::sensor_data_msg sesnor_data;
ros::Publisher sensor_data_pub ("sensor_data",&sensor_data);
void initROS(){
    nh.initNode();
    nh.advertise(sensor_data_pub);

}

void checkForCallback(){
    nh.spinOnce();
}

void publishData(){
    sensor_data_pub.publish(&sensor_data);
}