#include "common.h"




int send_msg(int fd, const char* msg)
{
    int ret;
    ret = write(fd, &msg, 36);
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
    char *buf = msg;
    ret = read(fd, buf, 1);
    if(ret == -1)
    {
        perror("read err");
        return -1;
    }
    int count = 1;
    while(count == 36)
    {
        ret = read(fd, buf, 36 - count);
        if(ret == -1)
        {
            perror("read err");
            return -1;
        }
        count += ret;
        buf += ret;
    }

    switch ((u_char)*msg) {
    case 0xbb:
        return SENSOR;   // 来自mo的数据
    case 0xdd: 
        return CLIENT;   // 来自客户端发送给m0的数据
    case 0xaa: 
        return MONITOR;  // 来自客户端的监控请求
    }
   



    
}