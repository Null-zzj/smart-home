/****************************************************************************************************
Description:                    控制led的打开和关闭
Input parameters:               参数1：是打开文件的返回的文件描述符；
                                参数2：需要一个led_ctl_cmd_t枚举类型控制led显示
Output parameters:              
                                写入数据使M0的led是否显示
Returned value:                 0:成功
                                -1: 失败
Created by:                     彭梁    (2023-9-19)
Modified by:                            (2023-3-2): 修改原因
                                        (2023-3-3):     
*******************************************************************************************************/

#include "led_ctl.h"



int led_ctl(int uart_fd,led_ctl_cmd_t led_ctl_cmd) 
{
    unsigned char write_ctl_cmd[36] ={0};

    write_head_bit(write_ctl_cmd);//写入头部数据


    //判断命令
    switch (led_ctl_cmd) 
    {
        case LED_1_ON:
            write_ctl_cmd[4] = LED_1_ON;
            break;
        case LED_1_OFF:
            write_ctl_cmd[4] = LED_1_OFF;
            break;
        default:
            printf("ERROR: Unknown LED\n");
            break;
    }

    if(write(uart_fd,write_ctl_cmd,sizeof(write_ctl_cmd)) < 0)
    {
        perror("led_ctl");
        return -1;
    }
    sleep(2);
    
    return 0;
}

