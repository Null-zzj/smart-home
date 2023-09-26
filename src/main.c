#include "client_msg/client_msg.h"
#include "sensor_info/sensor_info.h"
#include "smart_lock/smart_lock.h"
#include "tools/common.h"
#include "tools/uart/uart.h"
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

typedef void (*module_function)(char *);
module_function modules_array[64]; // 模块函数指针数组
Client client = {0, {-1}};
int uart_fd;

SOCKINFO sockinit(char *ipaddr, unsigned short port);
void module_function_init();
int insert_client(int cfd); // 添加客户端
int del_client(int fd);
int uart_init();

int main()
{

    char buf[32];
    SOCKINFO cli_sock;
    bzero(&cli_sock, sizeof(SOCKINFO));
    SOCKINFO sock;
    sock = sockinit(IP, PORT);
    uart_init();

    int epfd = epoll_create(256);

    struct epoll_event tep, ep_arr[256];
    memset(ep_arr, 0, sizeof(ep_arr));
    tep.events = EPOLLIN;
    tep.data.fd = sock.fd;

    int ret = epoll_ctl(epfd, EPOLL_CTL_ADD, sock.fd, &tep);
    if (ret == -1)
    {
        perror("epoll_ctl");
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

                    client.client_array[client.count++] = cfd;

                    tep.events = EPOLLIN;
                    tep.data.fd = cfd;
                    ret = epoll_ctl(epfd, EPOLL_CTL_ADD, cfd, &tep);
                }
                else
                { // client send data
                    int len = recv_msg(ep_arr[i].data.fd, buf);
                    if (len == -1)
                    {
                        perror("main recv_msg");
                    }
                    else if (len == 0)
                    { // client close
                        ret = epoll_ctl(epfd, EPOLL_CTL_DEL, ep_arr[i].data.fd, NULL);

                        close(ep_arr[i].data.fd);
                        del_client(ep_arr[i].data.fd);
                        printf("client close\n");
                        // exit(0);
                    }
                    else if (len == 4)
                    {
                        modules_array[(u_int8_t)buf[0]](buf); // 函数指针
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

int uart_init()
{
    int uart_fd = open(UART_PATH, O_RDWR);
    if (uart_fd < 0)
    {
        perror("Error opening USB serial port");
        return -1;
    }
    if (init_uart(uart_fd, PREINSTALL_BAUD, PREINSTALL_DATA, PREINSTALL_STOP, PREINSTALL_PARITY, NULL) < 0)
    {
        return -1;
    }
    return uart_fd;
}

int insert_client(int cfd) // 添加客户端
{

    if (client.count == 255)
    {
        printf("已到达最大连接数");
        return -1;
    }
    int flag = 0;
    for (int i = 0; i < client.count; i++)
    {
        if (client.client_array[i] == -1)
        {
            client.client_array[i] = cfd;
            flag = 1;
            break;
        }
    }
    if (!flag)
    {
        client.client_array[client.count++] = cfd;
    }
    return 0;
}

int del_client(int fd)
{
    for (int i = 0; i < client.count; i++)
    {
        if (client.client_array[i] == fd)
        {
            client.client_array[i] = -1;
            client.count--;
            break;
        }
    }
    return 0;
}

void module_function_init()
{
    modules_array[CLIENT] = client_msg;
    modules_array[SENSOR] = sensor_info;
    modules_array[MONITOR] = 0;
    modules_array[LOCK] = smart_lock;
}