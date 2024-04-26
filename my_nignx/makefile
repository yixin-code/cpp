all:a.out

TARGET=./a.out

INCLUDE=-I ./_include

SRC=./app/nginx.cpp ./app/ngx_conf.cpp ./app/ngx_func.cpp ./app/ngx_log.cpp ./app/ngx_printf.cpp ./app/ngx_set_process_title.cpp

OBJ=$(SRC:.cpp=.o)

G=g++

FLAG=-Wall -std=c++11 -fsanitize=address -Werror -O0
# FLAG=-Wall -std=c++11

$(TARGET):$(OBJ)
	$(G) $(OBJ) $(FLAG) -o $(TARGET)

%.o:%.cpp
	$(G) $< $(INCLUDE) -c -g -o $@

clean:
	rm -rf ./app/*.o