#!/usr/bin/env python3
import sys
sys.path.append('/home/r2d2/mrov_ws/devel/lib/')
import motion_controller as m
import rospy
from std_msgs.msg import String,Float32
bot = m.ThrusteredVehicleMotionController()
reset=0
bot.setHeaveControlMode(1)
bot.setSurgeControlMode(1)
bot.setSwayControlMode(1)

bot.setYawControlMode(0)
bot.setRollControlMode(0)
bot.setPitchControlMode(0)

bot.resetAllThrusters()

bot.setTargetYawAngle(0)
bot.setTargetRollValue(0)
bot.setTargetPitchValue(0)


angle_sensitivity_yaw = 2 
angle_sensitivity_roll = 2 
angle_sensitivity_pitch = 2 

yaw_joystick:int
roll_joystick:int
pitch_joystick:int

multiplier_heave = 1
multiplier_sway = 1
multiplier_surge = 1

buffer_multiplier = 0.07
current_angle_yaw = current_angle_roll = current_angle_pitch = 0 # values to rotate the bot to, input from joystick


#help(m)
def mul(x):
    return 100*x
def call(data):
    
    # lis = data.data.split('_')
    # lis = list(map(float,lis))
    # lis = list(map(mul,lis))
    # lis[5] = lis[5]+100
    # lis[5]  = lis[5]/2
    # lis[5] = round(lis[5])
    # lis[5] = -1*lis[5]
    
    # lis[4] = lis[4]+100
    # lis[4]  = lis[4]/2
    # lis[4] = round(lis[4])
    
    # lis[1] = -1*lis[1]
    
    # thrust = lis[4]+lis[5]
    # surge = lis[1]
    # yaw = lis[2]
    
    # reset = lis[10]

## Left joy front - forward
## Left joy left - translate left
## Right joy front - pitch down
## Right joy left - yaw left

    heave_up = data.right_trigger #right trigger moves bot upwards towards surface
    heave_down = data.left_trigger
    heave = heave_up - heave_down
    
    sway = data.vals.ax0 

    surge = data.vals.ax1

    yaw_joystick = data.vals.ax2

    pitch_joystick = data.vals.ax3

    if(reset ==1):
        bot.resetAllThrusters()

    

    heave*=multiplier_heave
    sway*=multiplier_sway
    surge*=multiplier_surge

## Within 7% of the signal, the response is zero, so stick drift can be avoided (not the best way)
    if (heave) >= -(buffer_multiplier*multiplier_heave) and (heave) <=(buffer_multiplier*multiplier_heave):
        heave =0
        
    if (surge) >= (buffer_multiplier*multiplier_surge) and (surge) <= (buffer_multiplier*multiplier_surge):
        surge =0
        
    if (sway) >= (buffer_multiplier*multiplier_sway) and (sway) < (buffer_multiplier*multiplier_sway):
        sway =0

## TODO 
## Change below code to buffer angle values
    # if (heave) >= -(buffer_multiplier*multiplier_heave) and (heave) <=(buffer_multiplier*multiplier_heave):
    #     heave =0
        
    # if (surge) >= (buffer_multiplier*multiplier_surge) and (surge) <= (buffer_multiplier*multiplier_surge):
    #     surge =0
        
    # if (sway) >= (buffer_multiplier*multiplier_sway) and (sway) < (buffer_multiplier*multiplier_sway):
    #     sway =0


    bot.setHeaveThrust(heave)
    bot.setSurgeThrust(surge)
    bot.setSwayThrust(sway)

    ## put buffer on input values

    current_angle_yaw += yaw_joystick*angle_sensitivity_yaw
    current_angle_roll += roll_joystick*angle_sensitivity_roll
    current_angle_pitch += pitch_joystick*angle_sensitivity_pitch

    bot.setTargetYawAngle(current_angle_yaw)
    bot.setTargetRollAngle(current_angle_roll)
    bot.setTargetPitchAngle(current_angle_pitch)

    bot.updateThrustValues()
    bot.refresh()
    print("Thrust:",heave,"Surge:",surge,"Sway",sway,"Reset-",reset)


    
    pass
def rot_yaw(data):
    bot.updateCurrentYawAngle(data.data)
    bot.updateThrustValues()
    bot.refresh()

def rot_roll(data):
    bot.updateCurrentRollAngle(data.data)
    bot.updateThrustValues()
    bot.refresh()


def rot_pitch(data):
    bot.updateCurrentPitchAngle(data.data)
    bot.updateThrustValues()
    bot.refresh()

# TODO
# refractor code to have yaw roll pitch updating in same method

rospy.init_node("Bot")
rospy.Subscriber('/joydata', String,call)
rospy.Subscriber('/yaw',Float32,rot_yaw)
rospy.Subscriber('/roll',Float32,rot_roll)
rospy.Subscriber('/pitch',Float32,rot_pitch)
rospy.spin()
