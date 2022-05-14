#include "thrustered_vehicle_motion_controller.h"
#include "thrusters_controller/thrusters_controller.h"

void ThrusteredVehicleMotionController::initializeThrusters(){
    initThrusters();
}



void ThrusteredVehicleMotionController::doYaw(int yaw_magnitude_in_percent){
    yaw_magnitude_ = yaw_magnitude_in_percent;
    updateThrusterValues();

}

void ThrusteredVehicleMotionController::stopYaw(){
    doYaw(0);

}

void ThrusteredVehicleMotionController::doPitch(int pitch_magnitude_in_percent){
    pitch_magnitude_ = pitch_magnitude_in_percent;
    updateThrusterValues();

}

void ThrusteredVehicleMotionController::stopPitch(){
    doPitch(0);

}


void ThrusteredVehicleMotionController::doRoll(int roll_magnitude_in_percent){
    roll_magnitude_ = roll_magnitude_in_percent;
    updateThrusterValues();

}

void ThrusteredVehicleMotionController::stopRoll(){
    doRoll(0);

}


void ThrusteredVehicleMotionController::doSurge(int surge_magnitude_in_percent){
    surge_magnitude_ = surge_magnitude_in_percent;
    updateThrusterValues();

}

void ThrusteredVehicleMotionController::stopSurge(){
    doSurge(0);

}

void ThrusteredVehicleMotionController::doSway(int sway_magnitude_in_percent){
    sway_magnitude_ = sway_magnitude_in_percent;
    updateThrusterValues();

}

void ThrusteredVehicleMotionController::stopSway(){
    doSway(0);

}

void ThrusteredVehicleMotionController::doHeave(int heave_magnitude_in_percent){
    heave_magnitude_ = heave_magnitude_in_percent;
    updateThrusterValues();

}

void ThrusteredVehicleMotionController::stopHeave(){
    doHeave(0);

}

void ThrusteredVehicleMotionController::stopAllThrusters(){
    heave_magnitude_ = surge_magnitude_ = sway_magnitude_ = pitch_magnitude_ = roll_magnitude_ = yaw_magnitude_ = 0;
    updateThrusterValues();
}

void ThrusteredVehicleMotionController::updateThrusterValues(){
    for (int i = 0; i < THRUSTERS_NUMBER; i++)
    {
        thruster_values_[i] = yaw_magnitude_*yaw_vector_[i] + pitch_magnitude_*pitch_vector_[i] + roll_magnitude_*roll_vector_[i] + surge_magnitude_*surge_vector_[i] + sway_magnitude_*sway_vector_[i] + heave_magnitude_*heave_vector_[i];
        thruster_values_[i] = thruster_values_[i] <= 100 ? thruster_values_[i] : 100;
        thruster_values_[i] = thruster_values_[i] >= -100 ? thruster_values_[i] : -100;
    }
    
    setThrustValues(thruster_values_);
}
