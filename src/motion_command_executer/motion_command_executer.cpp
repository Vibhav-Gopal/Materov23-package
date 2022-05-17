#include "motion_command_executer.h"
#include "thrustered_vehicle_motion_controller/thrustered_vehicle_motion_controller.h"
#include  "pid_controller/pid_controller.h"
#include  "motion_commands.h"
#include  "ros_functs.h"
#include  "ros/ros.h"

#include <thread>
#include <chrono>
#include <iostream>



int motion_command = 20,surge_magnitude = 50,sway_magnitude = 50,heave_magnitude = 20, yaw_magnitude = 30;
bool stopped = false,updated_thrusters = false,pid_enabled = false;


ThrusteredVehicleMotionController cholan_motion_controller;
PIDController pid_yaw,pid_heave;

float target_yaw = 1, current_yaw = 0,current_pitch = 0, current_roll = 0, target_depth = 0.1, current_depth = 0;

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
            if(!stopped){
                if(pid_enabled){
                    target_depth += 0.1;
                }
                else{
                    if (heave_magnitude <= 90 && heave_magnitude >= -90)
                    {
                         heave_magnitude += 10;
                        cholan_motion_controller.setHeave(heave_magnitude);
                    }
                }  
                   
            
            }
            break;
            

        case DOWN:

            if(!stopped){
                if(pid_enabled){
                    target_depth -= 0.1;
                }
                else
                    if (heave_magnitude <= 90 && heave_magnitude >= -90)
                        {
                            heave_magnitude += 10;
                            cholan_motion_controller.setHeave(heave_magnitude);
                        }
            }
            break;

        case YAW_LEFT:

            if(!stopped){

                if(pid_enabled)
                    target_yaw += 0.1;
                else
                    cholan_motion_controller.setYaw(yaw_magnitude);
                
            }
            break;

        case YAW_RIGHT:

            if(!stopped){
                if(pid_enabled)
                    target_yaw -= 0.1;
                else
                    cholan_motion_controller.setYaw(-yaw_magnitude);
               
            }
            break;

        case SPRINT:

            if(!stopped){
                cholan_motion_controller.setSurge(80);    
            }
            break;
        case LIGHTS_ON:
            changeLEDState(true);
            break;

        case LIGHTS_OFF:
            changeLEDState(false);
            break;

        case STOP:
            stopped = true;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            cholan_motion_controller.stopAllThrusters();
            
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

        std::this_thread::sleep_for(std::chrono::milliseconds(1000/REFRESH_RATE));

        cholan_motion_controller.resetSurge();
        cholan_motion_controller.resetSway();
        checkForCallBack();
    
    }

    yaw_thread.join();
    heave_thread.join();
    
}


void yaw_thread_funct(){

    int pid_output = 0,dt;

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

     
     while ( (!stopped) && (pid_enabled) )
     {   
         
        end = std::chrono::steady_clock::now();

        dt = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();

        pid_output = pid_yaw.update(target_yaw,current_yaw,dt);

        std::cout<<pid_output<<std::endl;
        //cholan_motion_controller.setYaw(pid_output);

        begin = std::chrono::steady_clock::now();
        std::this_thread::sleep_for(std::chrono::milliseconds((100)));

     }
     
    
}

void heave_thread_funct(){

    int pid_output = 0,dt;

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

     
     while ((!stopped) && (pid_enabled))
     {   
         
        end = std::chrono::steady_clock::now();

        dt = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();

        pid_output = pid_heave.update(target_depth,current_depth, dt);
        
        //cholan_motion_controller.setHeave(pid_output);

        begin = std::chrono::steady_clock::now();
        std::this_thread::sleep_for(std::chrono::milliseconds((1000/REFRESH_RATE)));

     }
     
    
}


