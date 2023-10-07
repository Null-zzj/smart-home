#include "../tools/common.h"
#include <strings.h>
#include "../tools/uart/separate_data.h"

extern Client client;
extern environmental_data_t environmental_data;

void *sensor_info(void *arg)
{
    char buf[128] = {0};
    while (1)
    {
        bzero(buf, 128);
        read(uart_fd, buf, 128);
        separte_data(buf,&environmental_data);
        for (int i = 0; i < client.count; i++)
        {
            send_msg(client.client_array[i], buf);
        }
        sleep(2);
    }
}