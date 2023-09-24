
/****************************************************************************************************
Description:                    控制风扇的打开和关闭，风速设置等
Input parameters:               参数1：是打开文件的返回的文件描述符；
                                参数2：需要一个fan_ctl_cmd_t枚举控制风扇的命令，
Output parameters:              
                                写入数据使M0的风扇是否打开，和风速的设置
Returned value:                 0:成功
                                -1: 失败
Created by:                     彭梁    (2023-9-19)
Modified by:                            (2023-3-2): 修改原因
                                        (2023-3-3):     
*******************************************************************************************************/



#include "fan_ctl.h"


int fan_ctl(int uart_fd,fan_ctl_cmd_t fan_ctl_cmd)
{
    unsigned char write_ctl_cmd[36] ={0};

    write_head_bit(write_ctl_cmd);//头部数据的设置

    //判断命令
    switch (fan_ctl_cmd)
    {
        case FAN_ON:
            write_ctl_cmd[4] = FAN_ON;
            //写入zigbee中，并且根据返回的开关状态来判断是否打开了
            while(g_fan_status == 0)
            {
                if(write(uart_fd,write_ctl_cmd,sizeof(write_ctl_cmd)) < 0)
                {
                    perror("write");
                    return -1;
                }
                sleep(2);
            }
            break;


        case FAN_OFF:
            write_ctl_cmd[4] = FAN_OFF;
            //写入zigbee中，并且根据返回的开关状态来判断是否打开了
            while(g_fan_status == 0xffff)
            {
                if(write(uart_fd,write_ctl_cmd,sizeof(write_ctl_cmd)) < 0)
                {
                    perror("write");
                    return -1;
                }
                sleep(2);
            }
            break;


        default:
            write_ctl_cmd[4] = FAN_ON;   //如果风扇没有打开那就先打开后设置风扇速度
            //写入zigbee中，并且根据返回的开关状态来判断是否打开了
            while(g_fan_status == 0)
            {
                if(write(uart_fd,write_ctl_cmd,sizeof(write_ctl_cmd)) < 0)
                {
                    perror("write");
                    return -1;
                }
                sleep(2);
            }
            switch (fan_ctl_cmd)
            {
                case FAN_ON_LOW:
                    write_ctl_cmd[4] = FAN_ON_LOW;
                    break;


                case FAN_ON_MID:
                    write_ctl_cmd[4] = FAN_ON_MID;
                    break;


                case FAN_ON_HIGH:
                    write_ctl_cmd[4] = FAN_ON_HIGH;
                    break;
                default:
                    break;
            }

            //写入zigbee中，并且根据返回的开关状态来判断是否打开了
            while(g_fan_status == 0xffff)
            {
                if(write(uart_fd,write_ctl_cmd,sizeof(write_ctl_cmd)) < 0)
                {
                    perror("write");
                    return -1;
                }
                sleep(2);
            }
            break;   
    }

    return 0;
}