/****************************************************************************************************
Description:                    分离数据
Input parameters:               参数1：读出来的存放空间的地址；
                                参数2：需要一个environmental_data_t的结构体指针，用于存放各种信息
Output parameters:              
                                输出各种信息到结构体中。

Created by:                     彭梁    (2023-9-19)
Modified by:                            (2023-3-2): 修改原因
                                        (2023-3-3):     
*******************************************************************************************************/


#include "separate_data.h"


void separte_data(unsigned char *data,environmental_data_t *environmental_data)
{



    //七段数码管的是否显示，显示就把g_seven_led_status 设置为 0xffff,不显示的情况为0
    if (0x00 ==data[27])
    {
        g_seven_led_status = 0xffff;
    }
    else
    {
        g_seven_led_status = 0;
    }


    //蜂鸣器是否工作 ， 不工作为 0 ， 工作为 0xffff
    if (0x00 ==data[26])
    {
        g_buzzer_status =0;
    }
    else
    {
        g_buzzer_status = 0xffff;
    }


    //风扇是否工作，不工作为0 ，工作为0xffff
    if(0x00 ==data[25])
    {
        g_fan_status = 0;
    }
    else
    {
        g_buzzer_status = 0xffff;
    }



    //判断灯是否打开
    if(0x00 ==data[24])
    {
        g_led_status = 0;
    }
    else
    {
        g_led_status = 0xffff;
    }


    //填充各种信息
    environmental_data->tep_low  = data[4];
    environmental_data->tep_high = data[5];
    environmental_data->hum_low  = data[6];
    environmental_data->hum_high = data[7];
    environmental_data->acc_x    = data[8];
    environmental_data->acc_y    = data[9];
    environmental_data->acc_z    = data[10];
    environmental_data->adc_ch0  = data[12];
    environmental_data->adc_ch1  = data[16];
    environmental_data->light    = data[20];
}