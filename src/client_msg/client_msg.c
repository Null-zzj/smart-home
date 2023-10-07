#include "../smart_lock/smart_lock.h"
#include "../tools/common.h"
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

static int monitor_flag;
void client_msg(char *buf)
{

    if ((u_char)*buf == 0xdd)
    {
        send_msg(uart_fd, buf);
    }
    else if ((u_char)*buf == 0xaa)
    {
        if ((u_char) * (buf + 1) == 0x1) // monitor
        {
            if (monitor_flag == 1)
            {
                return;
            }

            monitor_flag = 1;
        }
        else if ((u_char) * (buf + 1) == 0x2)
        {
            pthread_cancel(pid);
        }
    }

    write(uart_fd, buf, 36);
}