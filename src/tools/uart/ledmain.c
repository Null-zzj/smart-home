#include "uart.h"
#include "device_status.h"
#include <stdio.h>
#include "seven_led_ctl.h"
#include "buzzer_ctl.h"
#include "fan_ctl.h"
#include "led_ctl.h"
#include "separate_data.h"
#include "write_head_bit.h"


#define USB_ZIGBEE_TYBE 36

int g_buzzer_status = 0;
int g_led_status = 0;
int g_seven_led_status = 0;
int g_fan_status = 0;



int main(int argc,char** argv)
{
    int uart_fd = open("/dev/ttyUSB0", O_RDWR);
    if (uart_fd < 0) 
    {
        perror("Error opening USB serial port");
        return -1;
    }
    if( init_uart( uart_fd , PREINSTALL_BAUD , PREINSTALL_DATA , PREINSTALL_STOP , PREINSTALL_PARITY , NULL ) < 0 )
    {
        return -1;
    }
    /*
    unsigned char buf[USB_ZIGBEE_TYBE]={0};

    environmental_data_t environmental_data;
    bzero(&environmental_data,sizeof(environmental_data));
    while(1)
    {
        sleep(2);
        int len = read( uart_fd,buf,USB_ZIGBEE_TYBE );
        if(len != USB_ZIGBEE_TYBE)
        {
            continue;
        }
        separte_data(buf,);
    }
*/
    fan_ctl(uart_fd,FAN_OFF);
    close(uart_fd);
    return 0;

}
