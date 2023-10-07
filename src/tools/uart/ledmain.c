#include "buzzer_ctl.h"
#include "client_msg.h"
#include "device_status.h"
#include "fan_ctl.h"
#include "led_ctl.h"
#include "separate_data.h"
#include "seven_led_ctl.h"
#include "uart.h"
#include "write_head_bit.h"
#include <stdio.h>
#include <unistd.h>

#define USB_ZIGBEE_TYBE 36

int g_buzzer_status = 0;
int g_led_status = 0;
int g_seven_led_status = 0;
int g_fan_status = 0;

int main(int argc, char **argv)
{
    int uart_fd = open("/dev/ttyUSB0", O_RDWR);
    if (uart_fd < 0)
    {
        perror("Error opening USB serial port");
        return -1;
    }
    if (init_uart(uart_fd, PREINSTALL_BAUD, PREINSTALL_DATA, PREINSTALL_STOP, PREINSTALL_PARITY, NULL) < 0)
    {
        return -1;
    }
    client_msg_queue_t queue;

    char buf[128] = {0};
    while (1)
    {
        read(uart_fd, buf, 128);
        for (int i = 0; i < 36; i++)
        {
            printf("%d ", buf[i]);
        }
        puts("");
        sleep(2);
    }

    close(uart_fd);
    return 0;
}
