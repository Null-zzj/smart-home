# 指定目标
TARGET = server

# 源文件
C_SRCS = ../src/client_msg/client_msg.c \
			../src/common/common.c \
			../src/sensor_info/sensor_info.c \
			../src/smart_lock/smart_lock.c \
			../src/main.c
CPP_SRCS = ../src/smart_lock/face_recognition.cpp \
			../src/smart_lock/base64.cpp

C_OBJS = $(C_SRCS:.c=.o)
CPP_OBJS = $(CPP_SRCS:.cpp=.o)

# 指定编译器
CC = gcc
CPP = g++
# 添加库
LIBS =  -lpthread -lcurl -lstdc++

# gcc编译参数 
CFLAGS = -Wall 

# 规则编译.o 
%.o: %.c 
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.cpp 
	$(CPP) $(CFLAGS) -c $< -o $@

# 链接目标
$(TARGET): $(C_OBJS) $(CPP_OBJS)
	$(CC) -o $(TARGET) $(C_OBJS) $(CPP_OBJS) $(LIBS)

# 清理
clean:
	rm -f $(TARGET) $(C_OBJS)  $(CPP_OBJS)
