#ifndef __BUZZER_CTL_H__
#define __BUZZER_CTL_H__

#include <stdio.h>
#include <unistd.h>
#include "device_status.h"
#include "write_head_bit.h"


typedef enum {
    BUZZER_ON =  0x02,      //开蜂鸣器    
    BUZZER_OFF              //关蜂鸣器

}buzzer_ctl_cmd_t;


int buzzer_ctl(int uart_fd, buzzer_ctl_cmd_t buzzer_ctl_cmd);

#endif // !__BUZZER_CTL_


