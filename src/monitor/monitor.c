#include "monitor.h"

void* monitor(void* arg)
{
    int clifd;
    
    // 初始化摄像头
    unsigned int width = 640, height = 480, size, ismjpeg, index;
    int fd = camera_init("/dev/video0", &width, &height, &size, &ismjpeg);
    if (fd == -1)
    {
        perror("camera open:");
        pthread_exit(NULL);
    }
    // 启动摄像头
    camera_start(fd);
    char *buf;
    while (1)
    {

        // camera_dqbuf(fd, (void **)&buf, &size, &index);

        // send()
        
        // camera_eqbuf(fd, index);
        // usleep(700000);
    }
    
}