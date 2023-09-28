/*===============================================
*   文件名称：camera.h
*   创 建 者： 张城    
*   邮箱：zhangc_cd@hqyj.com     
*   创建日期：2022年06月26日
*   描    述：
================================================*/
#ifndef __CAMERA_H__
#define __CAMERA_H__
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <linux/videodev2.h>
#include<stdio.h>
#include<stdlib.h>     
#include<unistd.h>     
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>      
#include<termios.h>    
#include<errno.h>      
#include<string.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/ioctl.h>
#include <signal.h>

#define	REQBUFS_COUNT	4
int camera_init(char *devpath, unsigned int *width, unsigned int *height, unsigned int *size, unsigned int *ismjpeg);
int camera_start(int fd);
int camera_dqbuf(int fd, void **buf, unsigned int *size, unsigned int *index);
int camera_eqbuf(int fd, unsigned int index);
int camera_stop(int fd);
int camera_exit(int fd);



#endif
