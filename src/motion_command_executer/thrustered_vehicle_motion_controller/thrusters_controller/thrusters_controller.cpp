#include "thrusters_controller.h"
#include "ros_functs.h"
#include <iostream>


void initThrusters(){

   int zero_thrust[THRUSTERS_COUNT] = {ZERO_THRUST_PWM,ZERO_THRUST_PWM,ZERO_THRUST_PWM,ZERO_THRUST_PWM,ZERO_THRUST_PWM,ZERO_THRUST_PWM};
   publishPWMValues(zero_thrust);




}

void setThrustValues(int* thrust_values){
      

     publishPWMValues(thrust_values);


}