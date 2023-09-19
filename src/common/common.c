#include "common.h"




int send_msg(int fd, const char* msg)
{
    int ret;
    ret = write(fd, &msg, 4);
    if(ret != 4)
    {
        perror("write err");
        return -1;
    }
    return ret;
}


int recv_msg(int fd, char* msg)
{
    int ret;
    ret = read(fd, msg, 36);
    
    if(0 == ret)
    {
        return 0;
    }
    if(ret != 36)
    {
        perror("read err");
        return -1;
    }
    return ret;
}