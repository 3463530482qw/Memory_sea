#include <iostream>

// 1. 定义一个名为 Greeter 的类
class Greeter {
public:
    // 2. 在 public 区域定义一个成员函数
    void sayHello() {
        std::cout << "Hello World" << std::endl;
    }
};

int main() {
    // 3. 实例化对象（创建一个 Greeter 类的对象）
    Greeter myGreeter;

    // 4. 使用点操作符 (.) 调用对象的成员函数
    myGreeter.sayHello();

    return 0;
}
