#ifndef __FAN_CTL_H__
#define __FAN_CTL_H__

#include <stdio.h>
#include <unistd.h>
#include "device_status.h"
#include "write_head_bit.h"

typedef enum
{
    FAN_ON = 0x04,         //开风扇
    FAN_ON_LOW,            //风扇小风速
    FAN_ON_MID,            //风扇中风速
    FAN_ON_HIGH,           //风扇高风速
    FAN_OFF                //关风扇
}fan_ctl_cmd_t;


int fan_ctl(int uart_fd,fan_ctl_cmd_t fan_ctl_cmd);

#endif // !__FAN_CTL_
