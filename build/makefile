# 指定目标
TARGET = server

# 源文件
C_SRCS = ../src/client_msg/client_msg.c \
			../src/tools/common.c \
			../src/sensor_info/sensor_info.c \
			../src/smart_lock/smart_lock.c \
			../src/tools/uart/led_ctl.c \
			../src/tools/uart/uart.c \
			../src/tools/uart/fan_ctl.c \
			../src/tools/uart/seven_led_ctl.c \
			../src/tools/uart/buzzer_ctl.c \
			../src/tools/uart/write_head_bit.c \
			../src/tools/uart/separate_data.c \
			../src/tools/camera/camera.c \
			../src/main.c \

CPP_SRCS = ../src/smart_lock/face_recognition.cpp \
			../src/tools/base64/base64.cpp

C_OBJS = $(C_SRCS:.c=.o)
CPP_OBJS = $(CPP_SRCS:.cpp=.o)

# 指定编译器
CC = gcc
CPP = g++
# 添加库
LIBS =  -lpthread -lcurl -lstdc++ -ljsoncpp

# gcc编译参数 
CFLAGS = -Wall 

#


# 规则编译.o 
%.o: %.c 
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.cpp 
	$(CPP) $(CFLAGS) -c $< -o $@

# 链接目标
$(TARGET): $(C_OBJS) $(CPP_OBJS)
	$(CC) -o $(TARGET) $(C_OBJS) $(CPP_OBJS) $(LIBS) $(LDFLAGS)

# 清理
clean:
	rm -f $(TARGET) $(C_OBJS)  $(CPP_OBJS)
