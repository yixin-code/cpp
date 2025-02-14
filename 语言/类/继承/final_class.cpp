#include <iostream>

class Parent final {
};

class Son : public Parent { // error 不能将final做基类
};