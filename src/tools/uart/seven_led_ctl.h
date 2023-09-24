#ifndef __SEVEN_LED_CTL_H__
#define __SEVEN_LED_CTL_H__

#include <unistd.h>
#include "device_status.h"
#include <stdio.h>
#include "write_head_bit.h"

typedef enum 
{
    SEVEN_LED_ON  = 0X09,    // turn on  打开七段数码管
    SEVEN_LED_OFF = 0X0A     // turn off 关闭七段数码管
}seven_led_ctl_t;

int seven_led_ctl(int uart_fd,seven_led_ctl_t seven_led_ctl_cmd); 


#endif // !__SEVEN_LED_CTL_
