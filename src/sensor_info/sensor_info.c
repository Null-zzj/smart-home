#include "../tools/common.h"

extern Client client;

void sensor_info(char* buf)
{
    for(int i = 0; i < client.count; i++)
    {
        send_msg(client.client_array[i], buf);
    }
}