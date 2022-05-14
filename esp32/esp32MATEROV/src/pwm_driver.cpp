#include <Arduino.h>
#include <ESP32Servo.h>

int thruster_pins[4], led_pins[2];
Servo thrusters[4],leds[2];
void attachPWMPins(){

    for (int i = 0; i < 4; i++)
    {
        thrusters[i].attach(thruster_pins[i]);
    }

     for (int i = 0; i < 2; i++)
    {
        leds[i].attach(led_pins[i]);
    }
    
}
void setThrustersPWM(int* pwm_values){
    
    for (int i = 0; i < 4; i++)
    {
        thrusters[i].writeMicroseconds(pwm_values[i]);
    }

}
void switchLEDs(bool turn_on){
    if (turn_on)
    {
        leds[0].writeMicroseconds(1900);
        leds[1].writeMicroseconds(1900);

    }
    else
    {  leds[0].writeMicroseconds(0);
        leds[1].writeMicroseconds(0);
    }
    
    

}