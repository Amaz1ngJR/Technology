# Effective C++
## 尽量以const、enum、inline替换#define
```c++
#define NUMBER 1234 //如果发生错误 编译器给出的信息是1234 而不是NUMBER 如果这部分不是自己写的 来自某个头文件 会很难发现错误
//使用constexpr来定义常量替换#define
constexpr NUMBER = 1234;
```
