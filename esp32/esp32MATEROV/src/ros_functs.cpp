#include "ros_functs.h"
#include "ros.h"
#include "materov22_pioneer/sensor_data_msg.h"

ros::NodeHandle nh;
materov22_pioneer::sensor_data_msg sensor_data;
ros::Publisher sensor_data_pub ("sensor_data",&sensor_data);

void ThrustPWMValuesCallback( ){

}

void initROS(){
    nh.initNode();
    nh.advertise(sensor_data_pub);

}

void checkForCallback(){
    nh.spinOnce();
}

void publishData(float yaw, float roll, float pitch, float depth){
    sensor_data.yaw = yaw;
    sensor_data.roll = roll;
    sensor_data.pitch = pitch;
    sensor_data.depth = depth;
    sensor_data_pub.publish(&sensor_data);
}