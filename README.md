# c语言
## 编译步骤
* 预处理
    * 生成预处理文件
* 编译
    * 生成汇编文件
* 汇编
    * 生成目标文件
* 连接
    * 连接库 系统引导 生成可执行程序
## ![内存分区](./资源/内存分区.png)
## 常量
* 整型 1 2 3
* 浮点型 1.1 2.2 3.3
* 字符型 'a' 'b' 'c'
* 字符串型 "a" "b" "c"
### 常量表达式
* 编译期间可以直接求值的表达式
### [宏函数](./语言基础/宏/宏函数.cpp)
* 提高效率，普通函数调用会造成额外开销
```cpp
    #define func(x) ((x) * (x) + 11)

    #define print() do { \
    printf("hello "); \
    printf("world\n"); \
    }while(0)

    int i = 2;
    int num = func(++i); // 会加两次
    std::cout << num << "\n"; // 4 * 4 + 11 = 27
    print(); // hello world
```
## 输入输出
### printf格式化输出
* %d：输出十进制整数。 
* %f：输出浮点数。 
* %c：输出字符。 
* %s：输出字符串。 
* %p：输出指针地址。 
* %x：输出十六进制整数。0x开头 
* %o：输出八进制整数。0开头
* %u：输出无符号十进制整数。 
* %e：输出科学计数法表示的浮点数。 
* %g：根据实际情况选择%f或%e格式输出浮点数。
* printf("%05.3f\n");
    * 宽度为5 填充0 显示点后3位小数
### scanf匹配
* [当scanf中有空白字符时，可以匹配0个或多个](./语言基础/输入输出/scanf.cpp)
```cpp
    // 输入 num    =   11  ,  num2   =   22
    // num2会匹配失败','前没有空格所以无法匹配后续
    scanf("num   = %d, num2 =   %d", &num, &num2);
    printf("num = %d, num2 = %d\n", num, num2);
```
* [数值匹配时会忽略数值前面的空白字符](./c语言/输入输出/scanf2.cpp)
```cpp
    // 输入:    11    22     33
    scanf("%d%d%d", &num, &num2, &num3);
    printf("num = %d, num2 = %d, num3 = %d\n", num, num2, num3);
```
* [%c不会忽略前面的空白字符](./c语言/输入输出/scanf3.cpp)
```cpp
    char ch = 0;

    scanf("%c", &ch); // 输入：   a
    printf("[%c]", ch); // [ ]

    while(getchar() != '\n');

    // 空白字符可以匹配0个或多个
    scanf(" %c", &ch); // 输入：   a
    printf("[%c]", ch); // [a]
```
### scanf输入返回值
* 返回成功匹配的次数
### 读写字符getchar/putchar
```cpp
    char ch = getchar();
    putchar(ch);
```
#### 舍弃剩余字符
```cpp
    while (getchar() != '\,');
```
## sscanf 通配符
* 格式化从字符串中输入
* %*s或%*d 跳过数据
* %[width]s 读取指定宽度数据
* %[a-z] 匹配a到z
* %[^a-z] 不匹配a到z
* 条件必须逐一匹配否则直接退出
## [整形运算默认是int](./c语言/基础类型/整型运算.cpp)
```cpp
    // 0000 0000 0000 0000 0000 0000 1001 1001
    // 000 0000 0000 0000 0000 0000 1001 1001 0
    // 0000 0000 0000 0000 0000 0000 1001 1001
    unsigned char num = 0x99 << 1 >> 1; // 99
    printf("%x\n", num);

    // 1001 1001
    // 0011 0010 -> 0x32
    // 0001 1001 -> 0x19
    unsigned char num2 = 0x99 << 1;
    num2 = num2 >> 1;
    printf("%x\n", num2); // 19
```
## 浮点数存储IEEE754标准
* float
    * 符号位1位 指数部分8位 小数部分23位
    * 4.5 可以完整的算出
    * 十六进制 0x40900000
    * 二进制 0 10000001 00100000000000000000000
    * 指数部分 10000001 -> 需要转成十进制然后减去127 -> 129 - 127 = 2(结果是2的几次幂) -> 4
    * 小数部分 00100000000000000000000 -> 前面有一个1 -> 1.001(2的0次幂 到 2的-3次幂) -> 1.125
    * 4 * 1.125 = 4.5
### 浮点数有效位(第一个不为0的数开始)
    > 0.0001 1位有效数字
    > 1.0001 5位有效数字
* float 有效位 6-7
* double 有效位 15-16
* long double 有效位 18-19
## ascii码: A 65, a 97, space 32
## 字符控制 c中需要加头文件ctype.h c++中无需加头文件
* 转大写 toupper(int)
* 转小写 tolower(int)
* 是否为数字 isdigit(int)
* 是否为字母 isalpha(int)
* 是否为字母或数字 isalnum(int)
* 是否为大写字母 isupper(int)
* 是否为小写字母 islower(int)
* 是否是空白字符 isspace(int)
## bool类型 stdbool.h
```cpp
    printf("sizeof(bool): %ld\n", sizeof(bool)); // 1    
```
## 隐式类型转换
> char -> short -> int -> long -> long long -> float -> double
* short, char 运算会隐式转换成int
    > 计算机在运算int类型数据最快
    > int 运算注意 int 越界
* 有符号, 无符号 运算会隐式转换成 无符号
    > 有无符号不要一起进行运算
## typedef
* 基础类型
    * typedef int_type int
* 数组
    * typedef int arr_type[11];
* 函数指针
    * typedef void (*p_func_type)();
## sizeof 编译时期确定 得到的结果是一个常量表达式
## 运算符
### 算术运算符
* 取模运算不能用于浮点数
    * a % b 符号和a相同
### 赋值运算符可能会发生隐式类型转换
### 自增自减运算符
```cpp
    // 都是未定义行为
    i = i++;
    j = (i++) + (i++);
    arr[i] = arr2[i++];
    // 会产生临时值 在赋值
    j = i++;        i = i++;
    temp = i;       temp = i;
    j = temp;       i = temp;
    i = i + 1;      i = i + 1;
```
### 关系运算符 > < 从左向右
### 逻辑运算符 &&(优先级高于或) || 会发生短路现象 从左到右
---
---
---
---
---
# 计算机
## 补码
* 十进制补码存储源码显示
* 内存中根据符号位判断正负
* 减法变加法运算
> 2 - 3
> 0000 0010, 2 正数源码补码一样
> 1111 1101, -3 源码 1000 0011
> 1111 1111, 补码
> 0000 0001, 源码
## linux目录作用
* usr 用户安装的软件、库文件、头文件等资源
    * bin 用户安装的可执行文件
    * sbin 用户安装的系统管理工具和系统服务的可执行文件
    * lib 用户安装的库文件
    * include 存放头文件
    * share 程序资源文件，文档 帮助文件 等
    * local 用户安装的软件
## linux命令
### 压缩解压缩
* 压缩 tar -czvf xxx.tar.gz file1 file2
* 解压缩 tar -xzvf xxx.tar.gz
---
---
---
---
---
# GDB
## 下一步
* n 不进入函数
* s 进入函数
## 继续执行
* c
## 打印信息
* p num
* ptype num 显示类型
## 查看内存中的值
* x/16xw 0x01 查看以0x01开始，16个单元每个单元4字节
    * x 16进制，d 10进制，u 无符号，t2进制
    * b 1字节，h 2字节，w 4字节，g 8字节
## 查看反汇编
* disassemble /m 地址或函数名
## 设置变量值
* set var num=11
* set args aaa 设置命令行参数
## 段错误 调试core文件
* 查看用户资源限定
    * umilit -a
    * 设置无限制
        * umilit -c unlimited 
    * 调试
        * gdb core文件名
        * 查看函数调用栈
            * bt 
## 调试正在运行的程序
    * ps -ef | grep ./a.out
    * gdb ./a.out -p 进程编号
---
---
---
---
---
# nginx
* web服务器，反向代理，负载均衡，邮件代理等
* 轻量级服务器，运行是系统资源消耗少
* 并发处理百万级TCP连接，稳定，热部署(运行时可升级)，高度模块化设计(每个模块间耦合性很低)，开源可以开发模块
* nginx采用epoll技术高并发，只需要占用更多内存
    * 其中包含：内存池，线程池，进程池，事件驱动等等
## nignx环境搭建
* 需要的库
    * pcre库：解析正则表达式
    * zlib库：压缩解压缩
    * openssl库：ssl功能，网站加密通讯
    * 官网 www.nignx.org
        * mainline 主线版 更新快稳定性略差
        * stable 稳定版
        * legacy 往期版
    * wget 连接
### 编译安装
* 执行 ./configure
    * 生成中间文件 objs 其中 ngx_modules.c 包含哪些模块会编译到nginx中
* 执行 make 编译
* 执行 sudo make install 安装
### 源码目录
* auto 编译相关脚本
    * cc 检查编译器脚本
    * lib 检查依赖库脚本
    * os 检查操作系统脚本
    * type 检查平台类型脚本
* CHANGES 修复功能说明
* conf 默认配置文件
* configure 执行生产中间文件
* contrib 脚本工具，vi语法高亮
* html 欢迎 错误 的html页面
* man 帮助文件
* src 源码目录
    * core 核心代码
    * event 事件模块相关代码
    * http web服务相关代码
    * mail 邮件模块相关代码
    * os 操作系统模块相关代码
    * stream 流处理模块相关代码
## 使用
* 可执行程序在 /usr/local/nginx/sbin/nginx
### nginx整体结构
* 一个 master 进程，一个到多个 worker 进程(为master进程的子进程)
    * master 监控进程
    * worker 工作进程
* master和worker之间通讯可以使用信号 共享内存
    * worker 如果挂掉 master 会立刻 fork() 一个新的 worker
* worker 需要几个
    * 多核情况下，将每个worker配置在单独内核上，最大程度减少cup进程切换成本
        * lscpu 查看cpu
            * therads 2 和 cores 6 相乘
---
---
---
---
---
# 软件
## 微信
* yay -Sy wechat-uos
## QQ
* yay -Sy linuxqq
## vscode
* yay -Sy visual-studio-code-bin
## lazygit
* yay -Sy lazygit
## onlyoffice 办公
* yay -Sy onlyoffice-bin
## warpd 键盘控制鼠标
* yay -Sy warpd
    > super + meat + x
    > v 选中拖拽
## virtualbox 虚拟机
* sudo pacman -S virtualbox virtualbox-guest-iso
* sudo gpasswd -a yixin vboxusers
* sudo systemctl enable vboxweb.service
* yay -S rdesktop
* sudo systemctl enable vboxweb.service
* sudo systemctl start vboxweb.service
* sudo /sbin/rcvboxdrv setup