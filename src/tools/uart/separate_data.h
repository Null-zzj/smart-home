
#ifndef __SEQARATE_DATA_H__
#define __SEQARATE_DATA_H__

#include <stdio.h>
#include "device_status.h"

typedef struct
{
    unsigned char hum_high;         //湿度信息的高位
    unsigned char hum_low;          //湿度信息的低位
    unsigned char tep_high;         //温度信息的高位
    unsigned char tep_low;          //温度信息的低位
    unsigned char acc_x;            //x方向的加速度
    unsigned char acc_y;            //y方向的加速度
    unsigned char acc_z;            //z方向的加速度
    unsigned char adc_ch0;          //adc
    unsigned char adc_ch1;          //adc
    unsigned char light;            //强度

}environmental_data_t;



void separte_data(unsigned char *data,environmental_data_t *environmental_data);


#endif // !__SEQARATE_DATA_

