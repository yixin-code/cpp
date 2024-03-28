TARGET=./a.out

INCLUDE=-I ./_include

# SRC=./app/nginx.cpp ./app/ngx_conf.cpp ./app/ngx_func.cpp
SRC=./app/*.cpp

OBJ=$(SRC:.cpp=.o)
# OBJ=$(patsubst %.cpp, %.o, $(SRC))

G=g++

FLAG=-Wall -std=c++11 -g -fsanitize=address -Werror -O0

all:a.out

$(TARGET):$(OBJ)
	# $(G) $(OBJ) $(INCLUDE) $(FLAG) -o $(TARGET)
	$(G) $(OBJ) $(FLAG) -o $(TARGET)

%.o:%.cpp
	$(G) $< $(INCLUDE) -c -o $@