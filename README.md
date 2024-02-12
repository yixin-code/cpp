# 语言基础
## c和c++区别
### 命名空间
```cpp
    #include <iostream>
    namespace yixin
    {
        int num;
        namespace yixin2 // 可以嵌套
        {
            int num;
        }
    }
    yixin::num = 11;
    yixin::yixin2::num = 22;
```
## 指针 引用 数组 内存
## 输入输出
## 继承
### 虚继承 菱形继承
### 多态
#### 动态多态 静态多态
#### 虚函数 虚函数表 纯虚函数
#### 智能指针 智能指针原理
## static const volatile extern
## 类型转换
## stl
## 模板特化 偏特化 萃取traits
## 编译连接机制 内存布局 对象模型
## 新特性