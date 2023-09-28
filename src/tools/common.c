#include "common.h"
#include <stdlib.h>
// 放置所有的全局变量
pthread_t pid;
int uart_fd;
Client client = {0, {-1}};
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
        return SENSOR;   // 来自m0的数据
    case 0xdd: 
        return CLIENT;   // 来自客户端发送给m0的数据
    case 0xaa:
        return CLIENT;
    
    default:
        return -1;
    }

}

SOCKINFO sockinit(char *ipaddr, unsigned short port)
{
    SOCKINFO sock;
    memset(&sock, 0, sizeof(SOCKINFO));
    sock.fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock.fd == -1)
    {
        perror("socket");
        exit(-1);
    }

    sock.addr.sin_addr.s_addr = INADDR_ANY;
    sock.addr.sin_family = AF_INET;
    sock.addr.sin_port = htons(port);

    int opt = 1;
    setsockopt(sock.fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)); // reuse address
    int ret = bind(sock.fd, (struct sockaddr *)&sock.addr, sizeof(sock.addr));
    if (ret == -1)
    {
        perror("bind");
        exit(-1);
    }
    ret = listen(sock.fd, 255);
    if (ret == -1)
    {
        perror("listen");
        exit(-1);
    }
    return sock;
}