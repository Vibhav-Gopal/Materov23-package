#ifndef THRUSTERED_VEHICLE_MOTION_CONTROLLER_H
#define THRUSTERED_VEHICLE_MOTION_CONTROLLER_H
#include "vehicle_config.h"

class ThrusteredVehicleMotionController
{
private:
    int yaw_magnitude_,pitch_magnitude_,roll_magnitude_,surge_magnitude_,sway_magnitude_,heave_magnitude_ = 0;
    
    int yaw_vector_[THRUSTERS_NUMBER] = YAW_VECTOR, pitch_vector_[THRUSTERS_NUMBER] = PITCH_VECTOR, roll_vector_[THRUSTERS_NUMBER] = ROLL_VECOR,
    surge_vector_[THRUSTERS_NUMBER] = SURGE_VECTOR, sway_vector_[THRUSTERS_NUMBER] = SWAY_VECTOR,    heave_vector_[THRUSTERS_NUMBER] = HEAVE_VECTOR;

    int thruster_values_[THRUSTERS_NUMBER];
public:

    void initializeThrusters();
    
    void setYaw(int magnitude_in_percent);
    void doYaw(int magnitude_in_percent);
    void stopYaw();

    void setPitch(int magnitude_in_percent);
    void doPitch(int magnitude_in_percent);
    void stopPitch();
    
    void setRoll(int magnitude_in_percent);
    void doRoll(int magnitude_in_percent);
    void stopRoll();

    void setSurge(int magnitude_in_percent);
    void doSurge(int magnitude_in_percent);
    void stopSurge();
    
    void setSway(int magnitude_in_percent);
    void doSway(int magnitude_in_percent);
    void stopSway();
    
    void setHeave(int magnitude_in_percent);
    void doHeave(int magnitude_in_percent);
    void stopHeave();

    void stopAllThrusters();

private:
    void updateThrusterValues();
     
    
    
};


#endif