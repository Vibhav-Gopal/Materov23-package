#include "motion_command_executer.h"
#include "thrustered_vehicle_motion_controller/thrustered_vehicle_motion_controller.h"
#include  "pid_controller/pid_controller.h"
#include  "motion_commands.h"
#include  "ros_functs.h"
#include  "ros/ros.h"

#include <thread>
#include <chrono>
#include <iostream>


int motion_command = FORWARD,surge_magnitude = 0,sway_magnitude = 0;
bool stopped = false,updated_thrusters = false;
ThrusteredVehicleMotionController cholan_motion_controller;
PIDController pid_yaw,pid_heave;
float target_yaw = 30, current_yaw = 0,current_pitch = 0, current_roll = 0, target_depth = 1, current_depth = 0;

int main(int argc, char** argv){

    
    ros_init(argc,argv);
    
    cholan_motion_controller.initializeThrusters();
    std::thread yaw_thread(yaw_thread_funct);
    std::thread heave_thread(heave_thread_funct);

 
    while (ros::ok())
    { 
        

        switch (motion_command)
        {
        case FORWARD:
            if (!stopped)
            {
                cholan_motion_controller.setSurge(surge_magnitude);
                
            }
            break;

        case BACKWARD:
            if (!stopped)
            {
                cholan_motion_controller.setSurge( - surge_magnitude);
               
            }
            break;

        case LEFT:
            if (!stopped)
            {
                //cholan_motion_controller.setSway(sway_magnitude);
               
            }
            break;
        
        case RIGHT:
            if (!stopped)
            {
                //cholan_motion_controller.setSway(- sway_magnitude);
                
            }
            break;


        case UP:
            target_depth += 0.1;
            break;

        case DOWN:
            target_depth -= 0.1;
            break;

        case YAW_LEFT:
            target_yaw += 10;
            break;

        case YAW_RIGHT:
            target_yaw -= 10;
            break;
        
        case STOP:
            cholan_motion_controller.stopAllThrusters();
            stopped = true;
            break;

        case RESUME:
            if (yaw_thread.joinable())
            {
                yaw_thread.join();
            }
             if (heave_thread.joinable())
            {
                heave_thread.join();
            }
            stopped    = false;
            
            yaw_thread.swap (* new  std::thread (yaw_thread_funct));
            heave_thread.swap( *new  std::thread (heave_thread_funct) );
            break;

            
        default:
            
            break;
        

        }

        cholan_motion_controller.updateThrusterValues();
        std::this_thread::sleep_for(std::chrono::seconds(1/REFRESH_RATE));
        cholan_motion_controller.resetSurge();
        cholan_motion_controller.resetSway();
        checkForCallBack();
    
    }

    yaw_thread.join();
    heave_thread.join();
    
}


void yaw_thread_funct(){
    int pid_output = 0;
     auto prev_time = std::chrono::high_resolution_clock::now(), current_time = std::chrono::high_resolution_clock::now();
     auto dt        = std::chrono::duration_cast<std::chrono::milliseconds> (current_time - prev_time);

     while (!stopped)
     {   
         current_time = std::chrono::high_resolution_clock::now();
         dt        = std::chrono::duration_cast<std::chrono::milliseconds> (current_time - prev_time);
        pid_output = pid_yaw.update(target_yaw,current_yaw,dt.count()/1000);

        cholan_motion_controller.setYaw(pid_output);

         prev_time   =  std::chrono::high_resolution_clock::now();
         std::this_thread::sleep_for(std::chrono::seconds(10));

     }
     
    
}

void heave_thread_funct(){

    int pid_output = 0;
    
     auto prev_time = std::chrono::high_resolution_clock::now(), current_time = std::chrono::high_resolution_clock::now();
     auto dt        = std::chrono::duration_cast<std::chrono::milliseconds> (current_time - prev_time);

     while (!stopped)
     {   
         current_time = std::chrono::high_resolution_clock::now();
         dt        = std::chrono::duration_cast<std::chrono::milliseconds> (current_time - prev_time);
        pid_output = pid_heave.update(target_depth,current_depth,dt.count()/1000);

         cholan_motion_controller.setHeave(pid_output);

         prev_time   =  std::chrono::high_resolution_clock::now();
         std::this_thread::sleep_for(std::chrono::seconds(10));

     }
     
    
}


