# 指定目标
TARGET = server

# 源文件
SRCS = ../processor.cpp ../server.cpp ../sqlor.cpp ../tcpConnect.cpp ../application.cpp
OBJS = $(SRCS:.c=.o)

# 指定编译器
CC = g++

# 添加库
LIBS =  -lpthread

# 编译参数 
CFLAGS = -Wall 

# 规则编译.o 
%.o: %.c 
	$(CC) $(CFLAGS) -c $< -o $@

# 链接目标
$(TARGET): $(OBJS) 
	$(CC) -o $(TARGET) $(OBJS) $(LIBS)

# 清理
clean:
	rm -f $(TARGET) $(OBJS)
