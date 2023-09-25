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
#define MONITOR 0x3
#define LOCK 0x4

typedef struct {
    int len;    // 编码长度
    char* buf;  // base编码
}data;

// 通用工具

// 数据传输


int send_msg(int fd, const char* buf);
int recv_msg(int fd, char* buf);



#endif