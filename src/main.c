#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include "common/common.h"
#include "client_msg/client_msg.h"
#include "sensor_info/sensor_info.h"

#define IP "0.0.0.0"
#define PORT 12000

typedef struct
{
    int fd;
    struct sockaddr_in addr;
    socklen_t addrlen;
} SOCKINFO;

SOCKINFO sockinit(char *ipaddr, unsigned short port);
void module_function_init();

void sys_err(char *str)
{
    perror(str);
}

typedef void (*module_function)(char*);
module_function modules_array[64];   // 模块函数指针数组

int main()
{
    
    char buf[32];
    SOCKINFO cli_sock;
    bzero(&cli_sock, sizeof(SOCKINFO));
    SOCKINFO sock;
    sock = sockinit(IP, PORT);
    module_function_init();

    int epfd = epoll_create(256);

    struct epoll_event tep, ep_arr[256];
    memset(ep_arr, 0, sizeof(ep_arr));
    tep.events = EPOLLIN;
    tep.data.fd = sock.fd;

    int ret = epoll_ctl(epfd, EPOLL_CTL_ADD, sock.fd, &tep);
    if(ret == -1)
    {
        perror("error");
    }
    while (1)
    {
        epoll_wait(epfd, ep_arr, 256, -1);
        for (int i = 0; i < 256; i++)
        {
            if (ep_arr[i].events & EPOLLIN)
            {
                if (ep_arr[i].data.fd == sock.fd)
                { // new client  connection request
                    struct sockaddr_in cli_addr;
                    socklen_t cli_len = sizeof(cli_addr);
                    int cfd = accept(sock.fd, (struct sockaddr *)&cli_addr, &cli_len);

                    printf("client connect succsee  ip: %s, port: %d\n", inet_ntoa(cli_addr.sin_addr),
                           ntohs(cli_addr.sin_port));
                    tep.events = EPOLLIN;
                    tep.data.fd = cfd;
                    ret = epoll_ctl(epfd, EPOLL_CTL_ADD, cfd, &tep);
                }
                else
                { // client send data
                    // int len = recv_msg(ep_arr[i].data.fd, buf);
                    int len = read(ep_arr[i].data.fd, buf, 36);
                    if (len == -1)
                    {
                        sys_err("read err");
                    }
                    else if (len == 0)
                    { // client close
                        ret = epoll_ctl(epfd, EPOLL_CTL_DEL, ep_arr[i].data.fd, NULL);

                        close(ep_arr[i].data.fd);
                        printf("client close\n");
                    }
                    else if(len == 4)
                    {    


                        // write(STDOUT_FILENO, buf, 4);
                        modules_array[(u_int8_t)buf[0]](buf);   // 函数指针
                    }
                }
            }
        }
    }

    return 0;
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

void module_function_init()
{
    modules_array[CLIENT] = client_msg;
    modules_array[SENSOR] = sensor_info;
}