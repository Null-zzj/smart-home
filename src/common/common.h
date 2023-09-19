#include <sys/types.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

#define CLIENT 0xcc
#define SENSOR 0xbb
// 通用工具

// 数据传输


int send_msg(int fd, const char* buf);
int recv_msg(int fd, char* buf);
