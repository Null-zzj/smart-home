#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <termios.h>
#include <string.h>
#include <sys/ioctl.h>

/*第一部分代码*/
//根据具体的设备修改
const char default_path[] = "/dev/ttyUSB0";
// const char default_path[] = "/dev/ttySTM3";


int main(int argc, char *argv[])
{
   int fd;
   int res;
   char *path;
   
   u_char buf[1024] = {0xdd, 0x07, 0x24, 0x00, 0x02, 0x00};

   /*第二部分代码*/

   //若无输入参数则使用默认终端设备
   if (argc > 1)
      path = argv[1];
   else
      path = (char *)default_path;

   //获取串口设备描述符
   printf("This is tty/usart demo.\n");
   fd = open(path, O_RDWR);
   if (fd < 0) {
      printf("Fail to Open %s device\n", path);
      return 0;
   }

   /*第三部分代码*/
   struct termios opt;

   //清空串口接收缓冲区
   tcflush(fd, TCIOFLUSH);
   // 获取串口参数opt
   tcgetattr(fd, &opt);

   //设置串口输出波特率
   cfsetospeed(&opt, B115200);
   //设置串口输入波特率
   cfsetispeed(&opt, B115200);
   //设置数据位数
   opt.c_cflag &= ~CSIZE;
   opt.c_cflag |= CS8;
   //校验位
   opt.c_cflag &= ~PARENB;
   opt.c_iflag &= ~CSTOPB;
   //设置停止位
   opt.c_cflag &= ~CSTOPB;
   
   //更新配置
   tcsetattr(fd, TCSANOW, &opt);
   perror("");
   printf("Device %s is set to 115200bps,8N1\n",path);

   /*第四部分代码*/


   int ret = write(fd, buf, 36);
   printf("%d", ret);
   perror("write");
   // do {
      
   //    res = read(fd, buf, 36);
   //    perror("read:");

   //    if (res >0 ) {
   //    //给接收到的字符串加结束符
      
   //    buf[res] = '\0';
   //    }
   //    for(int i = 0; i < 36; i++)
   //    {
   //       printf("%#x", buf[i]);
   //    }
   //    printf("\n");
   // } while (res >= 0);

   

   close(fd);
   return 0;
}
