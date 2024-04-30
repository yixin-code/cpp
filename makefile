TARGET=a.out

# TEMP=./linux/linux系统编程/信号/信号阻塞.cpp
# TEMP=./语言/可变参数/cpp可变参数.cpp
# TEMP=./练习/三个有序数组相同元素.cpp
TEMP=./linux/linux网络编程/服务端.cpp

# 当前目录下所有.cpp文件
# TEMP=$(wildcard *.cpp)
# 将.cpp替换成.o
SRC=$(patsubst %.cpp, %.o, $(TEMP))

G = g++

FLAG=-Wall -std=c++11 -g -fsanitize=address -Werror -O0
# FLAG=-Wall -std=c++11 -g

# 动态库
# -fPIC -shared

# 返回值不进行优化
# -fno-elide-constructors

# 警告是为错误
# -Werror

# make如果有多个目标的时候会自动编译 clean如果写在此处会每次都执行
all:a.out

$(TARGET):$(SRC)
	$(G) $(SRC) $(FLAG) -o $(TARGET)

%.o:%.cpp
	$(G) $< -c -o $@

# make clean
# clean:
# 	rm -rf a.out

# 执行shell命令
# $(shell mkdir aaa)
