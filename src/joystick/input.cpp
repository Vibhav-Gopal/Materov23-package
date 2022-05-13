// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// Copyright Drew Noakes 2013-2016

#include "joystick.h"
#include <unistd.h>
#include"ros/ros.h"
#include"std_msgs/String.h"
#include<iostream>
#include<cmath>
#include<vector>
#include<sstream>
#define RAD2DEG 57.2975


int main(int argc, char** argv)
{
  ros::init(argc, argv, "input");

  ros::NodeHandle nh;

  ros::Publisher pub = nh.advertise<std_msgs::String>("/commands",1);

  std_msgs::String i;

//  std::vector<int>arr_2;

  std::vector<int>arr_3;

  std::vector<int>arr_4;
  
  float x,y;

  // Create an instance of Joystick
  Joystick joystick("/dev/input/js0");

  // Ensure that it was found and that we can use it
  if (!joystick.isFound())
  {
    printf("Joystick is not connected :(\n");
    exit(1);
  }

  while (true)
  {
    // Restrict rate
    usleep(1000);

    // Attempt to sample an event from the joystick
    JoystickEvent event;
    if (joystick.sample(&event))
    {
      if (event.isButton() && event.value != 0)
      {
        //L1 - Up
        if(event.number == 4)
        {
          i.data = "Up";

          pub.publish(i);
        }

        //R1 - Down
        else if(event.number == 5)
        {
          i.data = "Down";

          pub.publish(i);
        }

        //L2 - Yaw left
        else if(event.number == 6)
        {
          i.data = "Yaw Left";

          pub.publish(i);
        }

        //R2 - Yaw right
        else if(event.number == 7)
        {
          i.data = "Yaw Right";

          pub.publish(i);
        }

        //Button 1 - Speed_increase
        else if(event.number == 0)
        {
          i.data = "Speed Increase";

          pub.publish(i);
        }

        //Button 3 - Speed increase
        else if(event.number == 2)
        {
          i.data = "Speed Decrease";

          pub.publish(i);
        }

        //Button 2 - Start
        else if(event.number == 1)
        {
          i.data = "Start";

          pub.publish(i);
        }

        //Button 4 - Stop
        else if(event.number == 3)
        {
          i.data = "Stop";

          pub.publish(i);
        }

        //Button select - Lights on 
        else if(event.number == 8)
        {
          i.data = "Lights On";

          pub.publish(i);
        }

      }
      
      else if (event.isAxis())
      {
          if(event.number == 6)
          {
            //Backward is pressed
            if(event.value > 0)
            {
              i.data = "Backward";
              
              pub.publish(i);
            }
          
            //Forward is pressed
            if(event.value < 0)
            {
              i.data = "Forward";
              
              pub.publish(i);
            }
          }

          else if(event.number == 5)
          {
            //Right is pressed
            if(event.value > 0)
            {
              i.data = "Right";

              pub.publish(i);
            }
            //Left is pressed
            if(event.value < 0)
            {
              i.data = "Left";

              pub.publish(i);
            }
          }

          else if(event.number == 3)
          {
              arr_3.push_back(event.value);

              x = *max_element(arr_3.begin(), arr_3.end());
          }

          else if(event.number == 4)
          {
              arr_4.push_back(event.value);

              y = *min_element(arr_4.begin(), arr_4.end());
          }

          float angle;

          if(y!=0)
          {
            float an = -x/y;

            angle = atan(an) * RAD2DEG;
            
            std::ostringstream ss;

            ss << angle;

            std::string ang(ss.str()); 

            i.data = ang;
              
            pub.publish(i);

            arr_3.clear();

            arr_4.clear();
            
          }

          else if(x != 0 && y == 0)
          {
            i.data = "90.0";

            pub.publish(i);

            arr_3.clear();

            arr_4.clear();
          }

            
          }
          
      }
    }
  }

