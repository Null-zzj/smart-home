#include <sys/types.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>


#ifndef __COMMON_H__
#define __COMMON_H__

#define CLIENT 0x0
#define SENSOR 0x1
#define LOCK 0x2
#define MONITOR 0x3

#define IP "0.0.0.0"
#define PORT 12000
#define UART_PATH "/dev/ttyUSB0"

typedef struct
{
    int fd;
    struct sockaddr_in addr;
    socklen_t addrlen;
} SOCKINFO;


typedef struct {
    int len;    // 编码长度
    char* buf;  // base编码
}data;


// client 保存所有连接上的客户端
// count保存位置最大的客户端
typedef struct
{
    int count;
    int client_array[255];
} Client;
extern Client client;
// 通用工具

// 数据传输
extern pthread_t pid;
extern int uart_fd;


int send_msg(int fd, const char* buf);
int recv_msg(int fd, char* buf);
SOCKINFO sockinit(char *ipaddr, unsigned short port);




#endif