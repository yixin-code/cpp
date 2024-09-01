TARGET=a.out

# TEMP=./语言/基础类型/global_variable.cpp
# TEMP=./linux/linux系统编程/线程/pthread_cond_timedwait.cpp
TEMP=./练习/test.cpp

# 当前目录下所有.cpp文件
# TEMP=$(wildcard *.cpp)
# 将.cpp替换成.o
SRC=$(patsubst %.cpp, %.o, $(TEMP))

G = g++

# FLAG=-Wall -std=c++11 -g -fsanitize=address -Werror -O0
# FLAG=-Wall -std=c++11 -g -O0
FLAG=-Wall -std=c++11 -g

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
	$(G) $< -c $(FLAG) -o $@

# make clean
# clean:
# 	rm -rf a.out

# 执行shell命令
# $(shell mkdir aaa)
