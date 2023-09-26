
/****************************************************************************************************
Description:                    初始化串口
Input parameters:               参数1：是打开文件的返回的文件描述符；
                                参数2：需要一个buzzer_ctl_cmd_t枚举控制蜂鸣器的命令
Output parameters:              
                                写入数据使M0的蜂鸣器是否打开
Returned value:                 0:成功
                                -1: 失败
Created by:                     彭梁    (2023-9-19)
Modified by:                            (2023-3-2): 修改原因
                                        (2023-3-3):     
*******************************************************************************************************/


#include "buzzer_ctl.h"


int buzzer_ctl(int uart_fd,buzzer_ctl_cmd_t buzzer_ctl_cmd)
{

    unsigned char write_ctl_cmd[36] ={0};


    write_head_bit(write_ctl_cmd);

    //判断命令
    switch (buzzer_ctl_cmd) 
    {
        case BUZZER_ON:
            write_ctl_cmd[4] = BUZZER_ON;//写入zigbee中，并且根据返回的开关状态来判断是否打开了
            while( g_buzzer_status ==  0)
            {
                if(write(uart_fd,write_ctl_cmd,sizeof(write_ctl_cmd)) < 0)
                {
                    perror("buzzer_ctl");
                    return -1;
                }
                sleep(2);
            }       
            break;
        case BUZZER_OFF:
            write_ctl_cmd[4] = BUZZER_OFF;
            while( g_buzzer_status ==  0xffff)//写入zigbee中，并且根据返回的开关状态来判断是否打开了
            {
                if(write(uart_fd,write_ctl_cmd,sizeof(write_ctl_cmd)) < 0)
                {
                    perror("buzzer_ctl");
                    return -1;
                }
                sleep(2);
            }      
            break;
        default:
            printf("unknown buzzer_ctl\n");
            return -1;
    }
    return 0;
}