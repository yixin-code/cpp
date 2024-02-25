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
## 浮点数存储IEEE754标准
* float
    * 符号位1位 指数部分8位 小数部分23位
    * 4.5 可以完整的算出
    * 十六进制 0x40900000
    * 二进制 0 10000001 00100000000000000000000
    * 指数部分 10000001 -> 需要转成十进制然后减去127 -> 129 - 127 = 2(结果是2的几次幂) -> 4
    * 小数部分 00100000000000000000000 -> 前面有一个1 -> 1.001(2的0次幂 到 2的-3次幂) -> 1.125
    * 4 * 1.125 = 4.5
### 浮点数有效位
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