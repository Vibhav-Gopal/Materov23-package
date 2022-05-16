#ifndef THRUSTERS_CONTROLLER_H
#define THRUSTERS_CONTROLLER_H
#define THRUSTERS_COUNT 4
#define ZERO_THRUST_PWM 1500
#define MAX_THRUST_PWM  1900
#define MIN_THRUST_PWM  1100

void initThrusters();
void setThrustValues(int* values);
#endif