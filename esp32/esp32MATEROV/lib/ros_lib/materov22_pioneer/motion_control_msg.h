#ifndef _ROS_materov22_pioneer_motion_control_msg_h
#define _ROS_materov22_pioneer_motion_control_msg_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace materov22_pioneer
{

  class motion_control_msg : public ros::Msg
  {
    public:
      typedef int8_t _command_type;
      _command_type command;
      typedef int8_t _yaw_angle_type;
      _yaw_angle_type yaw_angle;

    motion_control_msg():
      command(0),
      yaw_angle(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      union {
        int8_t real;
        uint8_t base;
      } u_command;
      u_command.real = this->command;
      *(outbuffer + offset + 0) = (u_command.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->command);
      union {
        int8_t real;
        uint8_t base;
      } u_yaw_angle;
      u_yaw_angle.real = this->yaw_angle;
      *(outbuffer + offset + 0) = (u_yaw_angle.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->yaw_angle);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      union {
        int8_t real;
        uint8_t base;
      } u_command;
      u_command.base = 0;
      u_command.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->command = u_command.real;
      offset += sizeof(this->command);
      union {
        int8_t real;
        uint8_t base;
      } u_yaw_angle;
      u_yaw_angle.base = 0;
      u_yaw_angle.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->yaw_angle = u_yaw_angle.real;
      offset += sizeof(this->yaw_angle);
     return offset;
    }

    virtual const char * getType() override { return "materov22_pioneer/motion_control_msg"; };
    virtual const char * getMD5() override { return "6e4b2c647661760c63b441e5975bea7d"; };

  };

}
#endif
