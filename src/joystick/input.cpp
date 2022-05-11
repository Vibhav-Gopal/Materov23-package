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
#include"std_msgs/Int32.h"

int main(int argc, char** argv)
{
  ros::init(argc, argv, "input");

  ros::NodeHandle nh;

  ros::Publisher pub = nh.advertise<std_msgs::Int32>("/motion_command",1000);

  std_msgs::Int32 i;
  
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
          i.data = 4;

          pub.publish(i);
        }

        //R1 - Down
        else if(event.number == 5)
        {
          i.data = 5;

          pub.publish(i);
        }

        //L2 - Yaw left
        else if(event.number == 6)
        {
          i.data = 6;

          pub.publish(i);
        }

        //R2 - Yaw right
        else if(event.number == 7)
        {
          i.data = 7;

          pub.publish(i);
        }

        //Button 1 - Speed_increase
        else if(event.number == 0)
        {
          i.data = 8;

          pub.publish(i);
        }

        //Button 3 - Speed increase
        else if(event.number == 2)
        {
          i.data = 9;

          pub.publish(i);
        }

        //Button 2 - Resume
        else if(event.number == 1)
        {
          i.data = 11;

          pub.publish(i);
        }

        //Button 4 - Kill Switch
        else if(event.number == 3)
        {
          i.data = 10;

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
              i.data = 1;
              
              pub.publish(i);
            }
          
            //Forward is pressed
            if(event.value < 0)
            {
              i.data = 0;
              
              pub.publish(i);
            }
          }

          else if(event.number == 5)
          {
            //Right is pressed
            if(event.value > 0)
            {
              i.data = 3;

              pub.publish(i);
            }
            //Left is pressed
            if(event.value < 0)
            {
              i.data = 2;

              pub.publish(i);
            }
          }

      }
    }
  }
}
