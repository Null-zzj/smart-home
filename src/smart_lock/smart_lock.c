#include "../tools/camera/camera.h"
#include "../tools/uart/fan_ctl.h"
#include "../tools/uart/led_ctl.h"
#include "../tools/uart/seven_led_ctl.h"
#include "face_recognition.h"
#include "../tools/common.h"
#include <pthread.h>
#include <unistd.h>



// 智能锁线程
void* smart_lock(void *str)
{

    // 初始化摄像头
    unsigned int width = 640, height = 480, size, ismjpeg, index;
    int fd = camera_init("/dev/video0", &width, &height, &size, &ismjpeg);
    if (fd == -1)
    {
        perror("camera open:");
        pthread_exit(NULL);
    }
    printf("smartlock init success\n");
    // 启动摄像头
    camera_start(fd);
    char *buf;
    while (1) 
    {

        camera_dqbuf(fd, (void **)&buf, &size, &index);

        int i = face_recognition(buf, size); // 返回
        
        if (i > 60)
        {
            fan_ctl(uart_fd, FAN_ON);
            printf("led_ctl success");
            sleep(2);
            fan_ctl(uart_fd, FAN_OFF);

        }   
        camera_eqbuf(fd, index);
        sleep(20);
    }
}