/****************************************************************************************************
Description:                    初始化串口
Input parameters:               参数1：是打开文件的返回的文件描述符；
                                参数2：需要的设置的波特率的大小，有默认值为115200，只需要传入PREINSTALL_BAUD即可；
                                参数3：需要设置的数据位的大小，默认值为8位的数据位，只需要传入PREINSTALL_DATA即可；
                                参数4：需要设置的停止位的大小，默认值为1位的停止位，只需要传入PREINSTALL_STOP即可；
                                参数5：需要设置的校验位，默认值为无校验，只需要传入PREINSTALL_PARITY即可；
                                参数6：是否保存上一个串口的状态，无需保存就传入NULL即可，要保存则需要传入struct termios结构体的指针。
Output parameters:              
                                参数6输出上一个的串口状态。
Returned value:                 0:成功
                                -1: 失败
Created by:                     彭梁    (2023-9-19)
Modified by:                            (2023-3-2): 修改原因
                                        (2023-3-3):     
*******************************************************************************************************/


#include "uart.h"

int init_uart( int uart_fd , BaudRate_t baud_rate , DataBits_t data_bits , 
                StopBits_t stop_bits , Parity_t parity , struct termios *old_termios_settings ) 
{
    if( old_termios_settings != NULL )
    {
        if( tcgetattr( uart_fd , old_termios_settings ) !=0 )
	    {
		    perror("get old_termios_settings error");
		    return -1;
	    }
    }
    struct termios new_termios_settings;
    bzero(&new_termios_settings,sizeof(new_termios_settings)); //清空
    //CREAD开启串行数据接收，CLOCAL打开本地连接模式
	new_termios_settings.c_cflag |= (CLOCAL|CREAD);
	new_termios_settings.c_cflag &= ~CSIZE;//设置数据位
    //恢复串口为阻塞状态
	if( fcntl( uart_fd , F_SETFL , 0 ) < 0 )
	{
		perror("set F_SETFL failed!");
		return -1;
	}

    //设置波特率
    //set baud rate
    switch (baud_rate) 
    {
        case BAUD_300:
            cfsetispeed(&new_termios_settings,B300);
			cfsetospeed(&new_termios_settings,B300);
            break;
        case BAUD_600:
            cfsetispeed(&new_termios_settings,B600);
			cfsetospeed(&new_termios_settings,B600);
            break;
        case BAUD_1200:
            cfsetispeed(&new_termios_settings,B1200);
			cfsetospeed(&new_termios_settings,B1200);
            break;
        case BAUD_2400:
            cfsetispeed(&new_termios_settings,B2400);
			cfsetospeed(&new_termios_settings,B2400);
            break;
        case BAUD_4800:
            cfsetispeed(&new_termios_settings,B4800);
			cfsetospeed(&new_termios_settings,B4800);
            break;
        case BAUD_9600:
            cfsetispeed(&new_termios_settings,B9600);
			cfsetospeed(&new_termios_settings,B9600);
            break;
        case BAUD_19200:
            cfsetispeed(&new_termios_settings,B19200);
			cfsetospeed(&new_termios_settings,B19200);
            break;
        case BAUD_38400:
            cfsetispeed(&new_termios_settings,B38400);
			cfsetospeed(&new_termios_settings,B38400);
            break;
        case BAUD_57600:
            cfsetispeed(&new_termios_settings,B57600);
			cfsetospeed(&new_termios_settings,B57600);
            break;
        case BAUD_115200:
            cfsetispeed(&new_termios_settings,B115200);
			cfsetospeed(&new_termios_settings,B115200);
            break;
        default:
            cfsetispeed(&new_termios_settings,B115200);
			cfsetospeed(&new_termios_settings,B115200);
            break;
    }



    //设置数据位
    //set data bits
    switch (data_bits) 
    {
        case DATA_BITS_8:
            new_termios_settings.c_cflag |= CS8;
            break;
        case DATA_BITS_7:
            new_termios_settings.c_cflag |= CS7;
            break;
        case DATA_BITS_6:
            new_termios_settings.c_cflag |= CS6;
            break;
        default:
            new_termios_settings.c_cflag |= CS8;
            break;
    }





    //设置停止位
    // set stop bits
    switch (stop_bits) 
    {
        case STOP_BITS_1:
            new_termios_settings.c_cflag &= ~CSTOPB;
            break;
        case STOP_BITS_2:
            new_termios_settings.c_cflag |= CSTOPB;
            break;
        default:
            new_termios_settings.c_cflag &= ~CSTOPB;
        break;
    }




    //设置校验位
    // Set parity
    switch (parity) 
    {
        case PARITY_NONE:
            new_termios_settings.c_cflag &= ~PARENB; // 禁用校验位
            break;
        case PARITY_EVEN:
            new_termios_settings.c_cflag |= PARENB;  // 启用校验位
            new_termios_settings.c_cflag &= ~PARODD; // 设置为偶校验
            break;
        case PARITY_ODD:
            new_termios_settings.c_cflag |= PARENB;  // 启用校验位
            new_termios_settings.c_cflag |= PARODD;  // 设置为奇校验
            break;
        default:
            new_termios_settings.c_cflag &= ~PARENB; // 默认禁用校验位
            break;
    }


    //设置最少字符和等待时间，对于接收字符和等待时间没有特别要求时
	new_termios_settings.c_cc[VTIME]=0;//非规范模式读取时的超时时间
	new_termios_settings.c_cc[VMIN]=0;//非规范模式读取时的最小字符数


	tcflush(uart_fd,TCIFLUSH);
    //tcflush清空终端未完成的输入/输出请求及数据；
	//TCIFLUSH表示清空正收到的数据，且不读去出来


	//激活配置使其生效
	if(( tcsetattr( uart_fd , TCSANOW , &new_termios_settings )) != 0)
	{
		perror("uart set error");
		return -1;
	}
	return 0;


}


