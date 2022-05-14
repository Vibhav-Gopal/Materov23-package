#ifndef PWM_DRIVER_H
#define PWM_DRIVER_H
#define THRUSTER_PINS {0,1,2,3}
#define LED_PINS      {5,6}

void attachPWMPins();
void setThrustPWM(int* pwm_values);
void switchLEDS(bool turn_on);

#endif