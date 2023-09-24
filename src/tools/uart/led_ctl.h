#ifndef __LED_CTL_H__
#define __LED_CTL_H__

#include <stdio.h>
#include "device_status.h"
#include <unistd.h>
#include "write_head_bit.h"

typedef enum
{
    LED_1_ON =0x00,       //开led1灯
    LED_1_OFF,            //关led1灯
}led_ctl_cmd_t;


int led_ctl(int uart_fd,led_ctl_cmd_t led_number);


#endif // !__LED_
