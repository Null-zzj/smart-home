/****************************************************************************************************
Description:                    设置七段数码管的显示
Input parameters:               参数1：是打开文件的返回的文件描述符；
                                参数2：需要一个seven_led_ctl_t枚举控制seven_led的命令，
Output parameters:              
                                写入数据使M0的七段数码管是否显示
Returned value:                 0:成功
                                -1: 失败
Created by:                     彭梁    (2023-9-19)
Modified by:                            (2023-3-2): 修改原因
                                        (2023-3-3):     
*******************************************************************************************************/



#include "seven_led_ctl.h"


int seven_led_ctl(int uart_fd, seven_led_ctl_t seven_led_ctl_cmd)
{
    unsigned char write_ctl_cmd[36]={0};

    write_head_bit(write_ctl_cmd);//设置头部数据



    //判断命令是哪一个
    switch (seven_led_ctl_cmd)
    {
        case SEVEN_LED_ON:
            write_ctl_cmd[4] = SEVEN_LED_ON;
            //写入zigbee中，并且根据返回的开关状态来判断是否打开了
            while(g_seven_led_status == 0)
            {
                if (write(uart_fd, write_ctl_cmd, sizeof(write_ctl_cmd))<0)
                {
                    perror("seven_led_ctl");
                    return -1;
                }
                g_seven_led_status = 0xffff;
                sleep(2);//每次睡眠2秒，用于判断是否打开或关闭
            }
            break;


        case SEVEN_LED_OFF:
            write_ctl_cmd[4] = SEVEN_LED_OFF;
            //写入zigbee中，并且根据返回的开关状态来判断是否打开了
            while(g_seven_led_status == 0xffff)
            {
                if (write(uart_fd, write_ctl_cmd, sizeof(write_ctl_cmd))<0)
                {
                    perror("seven_led_ctl");
                    return -1;
                }
                g_seven_led_status = 0xffff;
                sleep(2);//每次睡眠2秒，用于判断是否打开或关闭
            }
            break;
            

        default:
            printf("Unknown seven_led_ctl_cmd\n");
            return -1;

    }

    return 0;
}