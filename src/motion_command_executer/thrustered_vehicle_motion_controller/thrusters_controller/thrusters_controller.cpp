#include "thrusters_controller.h"
#include "ros_functs.h"
#include <iostream>
int pwm_values[THRUSTERS_COUNT];

void initThrusters(){

   int zero_thrust[THRUSTERS_COUNT] = {ZERO_THRUST_PWM,ZERO_THRUST_PWM,ZERO_THRUST_PWM,ZERO_THRUST_PWM};
   publishPWMValues(zero_thrust);




}

void setThrustValues(int* thrust_values){
      
     for(int i = 0; i<THRUSTERS_COUNT; i++){
         pwm_values[i] = ZERO_THRUST_PWM + ( thrust_values[i]/100 * (MAX_THRUST_PWM - ZERO_THRUST_PWM) );
         pwm_values[i] = pwm_values[i] <= MAX_THRUST_PWM ? pwm_values[i] : MAX_THRUST_PWM;
         pwm_values[i] = pwm_values[i] >= MIN_THRUST_PWM ? pwm_values[i] : MIN_THRUST_PWM;
     }

   publishPWMValues(pwm_values);


}