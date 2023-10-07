
#ifndef __SEQARATE_DATA_H__
#define __SEQARATE_DATA_H__

#include <stdio.h>
#include "device_status.h"

typedef struct
{
    char hum_high;         //湿度信息的高位
    char hum_low;          //湿度信息的低位
    char tep_high;         //温度信息的高位
    char tep_low;          //温度信息的低位
    char acc_x;            //x方向的加速度
    char acc_y;            //y方向的加速度
    char acc_z;            //z方向的加速度
    char adc_ch0;          //adc
    char adc_ch1;          //adc
    char light;            //强度

}environmental_data_t;



void separte_data(char *data,environmental_data_t *environmental_data);


#endif // !__SEQARATE_DATA_

