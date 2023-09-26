#include "common.h"


int g_buzzer_status = 0;
int g_led_status = 0;
int g_seven_led_status = 0;
int g_fan_status = 0;


int send_msg(int fd, const char* msg)
{
    int ret;
    ret = write(fd, msg, 36);
    if(ret != 36)
    {
        perror("send_msg");
        return -1;
    }
    return ret;
}


int recv_msg(int fd, char* msg)
{
    int ret;
    char *buf = msg;
    ret = read(fd, buf, 128);  // 尽可能的读取数据
    if(ret == -1)
    {
        perror("recv_msg");
        return -1;
    }
    if(ret == 0)
    {
        return  0;
    }
    
    if((u_char)*buf == 0xbb || (u_char)*buf == 0xdd || (u_char)*buf == 0xaa)
    {
        return -1;
    }

    switch ((u_char)*msg) {
    case 0xbb:
        return SENSOR;   // 来自mo的数据
    case 0xdd: 
        return CLIENT;   // 来自客户端发送给m0的数据
    case 0xaa: 
        return MONITOR;  // 来自客户端的监控请求
    default:
        return -1;
    }

}