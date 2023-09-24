#ifndef __UART_H__
#define __UART_H__




#include <stdio.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <sys/epoll.h>





//波特率的枚举
typedef enum 
{
    BAUD_300,    //300  
    BAUD_600,
    BAUD_1200,
    BAUD_2400,
    BAUD_4800,
    BAUD_9600,
    BAUD_19200,
    BAUD_38400,
    BAUD_57600,  //57600
    BAUD_115200, //115200
    PREINSTALL_BAUD
} BaudRate_t;



//数据位的枚举
typedef enum 
{
    DATA_BITS_8, //8
    DATA_BITS_7, //7
    DATA_BITS_6, //6
    PREINSTALL_DATA
} DataBits_t;



//停止位的枚举
typedef enum 
{
    STOP_BITS_1,//停止位 为1
    STOP_BITS_2, //停止位 为2
    PREINSTALL_STOP
} StopBits_t;


//校验的枚举
typedef enum 
{
    PARITY_NONE,//无校验
    PARITY_EVEN,//偶校验
    PARITY_ODD, //奇校验
    PREINSTALL_PARITY
} Parity_t;


//串口初始化函数
int init_uart(int uart_fd,BaudRate_t baud_rate, DataBits_t data_bits, 
                StopBits_t stop_bits, Parity_t parity,struct termios *old_termios_settings);


#endif // !__UART_H
