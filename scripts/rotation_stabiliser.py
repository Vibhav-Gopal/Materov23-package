#!/usr/bin/env python3
import sys
sys.path.append('/home/r2d2/mrov_ws/devel/lib/')
import motion_controller as m
import rospy
from std_msgs.msg import String,Float32
bot = m.ThrusteredVehicleMotionController()

bot.setHeaveControlMode(1)
bot.setSurgeControlMode(1)
bot.setYawControlMode(1)

bot.setYawControlMode(0)
bot.setRollControlMode(0)
bot.setPitchControlMode(0)

bot.resetAllThrusters()

# bot.setTargetYawAngle(0)
# bot.setTargetRollValue(0)
# bot.setTargetPitchValue(0)


angle_sensitivity = 2 
yaw_joystick:int
roll_joystick:int
pitch_joystick:int

current_angle_yaw = current_angle_roll = current_angle_pitch = 0 # values to rotate the bot to, input from joystick


#help(m)
def mul(x):
    return 100*x
def call(data):
    
    lis = data.data.split('_')
    lis = list(map(float,lis))
    lis = list(map(mul,lis))
    lis[5] = lis[5]+100
    lis[5]  = lis[5]/2
    lis[5] = round(lis[5])
    lis[5] = -1*lis[5]
    
    lis[4] = lis[4]+100
    lis[4]  = lis[4]/2
    lis[4] = round(lis[4])
    
    lis[1] = -1*lis[1]
    
    thrust = lis[4]+lis[5]
    surge = lis[1]
    yaw = lis[2]
    
    reset = lis[10]

    if(reset ==100):
        bot.resetAllThrusters()

    
    if int(thrust) >= -7 and int(thrust) <=7:
        thrust =0
        
    if int(surge) >= -7 and int(surge) <=7:
        surge =0
        
    if int(yaw) >= -7 and int(yaw) <=7:
        yaw =0
    bot.setHeaveThrust(thrust)
    bot.setSurgeThrust(surge)
    bot.setYawThrust(yaw)
    ## get yaw input from joystick
    ## put buffer on input values (zero from -7 to 7)
    current_angle_yaw += yaw_joystick*angle_sensitivity
    current_angle_roll += roll_joystick*angle_sensitivity
    current_angle_pitch += pitch_joystick*angle_sensitivity
    bot.setTargetYawAngle(current_angle_yaw)
    bot.setTargetRollAngle(current_angle_roll)
    bot.setTargetPitchAngle(current_angle_pitch)

    bot.updateThrustValues()
    bot.refresh()
    print("Thrust:",thrust,"Surge:",surge,"Yaw",yaw,"Reset-",reset)


    
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


rospy.init_node("Bot")
rospy.Subscriber('/joydata', String,call)
rospy.Subscriber('/yaw',Float32,rot_yaw)
rospy.Subscriber('/roll',Float32,rot_roll)
rospy.Subscriber('/pitch',Float32,rot_pitch)
rospy.spin()