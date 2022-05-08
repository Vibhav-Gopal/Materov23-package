#include "motion_command_executer.h"
#include "thrustered_vehicle_motion_controller/thrustered_vehicle_motion_controller.h"
#include  "pid_controller/pid_controller.h"
#include  "motion_commands.h"
#include  "ros_functs/ros_functs.h"

#include <thread>
#include <chrono>

int command,surge_magnitude,sway_magnitude;
bool stopped = false;
ThrusteredVehicleMotionController cholan_motion_controller;
PIDController pid_yaw,pid_heave;
float set_yaw, current_yaw,current_pitch, current_roll, set_depth, current_depth;

int main(int argc, char** argv){

    
    ros_init(argc,argv);
    std::thread yaw_thread(yaw_thread_funct);
    std::thread heave_thread(heave_thread_funct);

    

    while (true)
    {
        switch (command)
        {
        case FORWARD:
            if (!stopped)
            {
                cholan_motion_controller.doSurge(surge_magnitude);
                std::this_thread::sleep_for(std::chrono::seconds(1/REFRESH_RATE));
                cholan_motion_controller.stopSurge();
            }
            break;

        case BACKWARD:
            if (!stopped)
            {
                cholan_motion_controller.doSurge(surge_magnitude);
                std::this_thread::sleep_for(std::chrono::seconds(1/REFRESH_RATE));
                cholan_motion_controller.stopSurge();
            }
            break;

        case LEFT:
            if (!stopped)
            {
                cholan_motion_controller.doSway(sway_magnitude);
                std::this_thread::sleep_for(std::chrono::seconds(1/REFRESH_RATE));
                cholan_motion_controller.stopSurge();
            }
            break;
        
        case RIGHT:
            if (!stopped)
            {
                cholan_motion_controller.doSway(sway_magnitude);
                std::this_thread::sleep_for(std::chrono::seconds(1/REFRESH_RATE));
                cholan_motion_controller.stopSurge();
            }
            break;


        case UP:
            set_depth += 0.1;
            break;

        case DOWN:
            set_depth -= 0.1;
            break;

        case YAW_LEFT:
            set_yaw += 10;
            break;

        case YAW_RIGHT:
            set_yaw -= 10;
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

            /*yaw_thread =  new  std::thread (yaw_thread_funct);
            heave_thread = new  std::thread (heave_thread_funct);*/
            break;

            
        default:
            
            break;
        }
    
    }

    yaw_thread.join();
    heave_thread.join();
    
}


void yaw_thread_funct(){

     auto prev_time = std::chrono::high_resolution_clock::now(), current_time = std::chrono::high_resolution_clock::now();
     auto dt        = std::chrono::duration_cast<std::chrono::milliseconds> (current_time - prev_time);

     while (!stopped)
     {   current_time = std::chrono::high_resolution_clock::now();
         dt        = std::chrono::duration_cast<std::chrono::milliseconds> (current_time - prev_time);
         cholan_motion_controller.doYaw(pid_yaw.update(set_yaw,current_yaw,dt.count()*1000));

         prev_time   =  std::chrono::high_resolution_clock::now();
         std::this_thread::sleep_for(std::chrono::seconds(1/REFRESH_RATE));

     }
     
    
}

void heave_thread_funct(){

   
    
     auto prev_time = std::chrono::high_resolution_clock::now(), current_time = std::chrono::high_resolution_clock::now();
     auto dt        = std::chrono::duration_cast<std::chrono::milliseconds> (current_time - prev_time);

     while (!stopped)
     {   
         current_time = std::chrono::high_resolution_clock::now();
         dt        = std::chrono::duration_cast<std::chrono::milliseconds> (current_time - prev_time);

         cholan_motion_controller.doHeave(pid_heave.update(set_depth,current_depth,dt.count()*1000));
         prev_time   =  std::chrono::high_resolution_clock::now();
         std::this_thread::sleep_for(std::chrono::seconds(1/REFRESH_RATE));

     }
     
    
}


