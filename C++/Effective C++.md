# Effective C++
## 尽量以const、enum、inline替换#define
### 对于单纯常量 最好用const或enum替换#define
```c++
#define NUMBER 1234 //如果发生错误 编译器给出的信息是1234 而不是NUMBER 如果这部分不是自己写的 来自某个头文件 会很难发现错误
//使用constexpr来定义常量替换#define
constexpr NUMBER = 1234;
```
class专属常量 无法使用#define创建一个class专属常量 
```c++
class Players {
private:
	static constexpr int Number = 8; //常量声明式 位于头文件
	int a[Number];//使用该常量
};
//有些编译器必须要看到定义式 在实现(非头文件)文件下提供定义式:
constexpr int Players::Number; //常量定义式 由于声明获得初值 因此定义时不在设初值

//有些编译器不让在声明的时候获得初值 改成下面的形式
class Players {
private:
	static constexpr int Number; //常量声明式 位于头文件
	int a[Number];//使用该常量
};
constexpr int Players::Number = 8;//常量定义式 位于实现文件

//当编译器不允许 static整数型class常量完成 in class初值设定 可改用:
class Players {
private:
	enum { Number = 8 };//"the enum hack" 令Number成为5的一个记号
	int a[Number];
};
//取一个const的地址是合法的 取enum和一个#define的地址通常不合法 如果不想让别的指针或引用指向某个整数常量 可以使用enum
```
### 对于形似函数的宏 最好改用inline函数替换#define

## 尽可能使用const
```c++
class P{};
const P operator*(const P& a, const P& b);//函数返回值为const
//防止出现下面现象
P a, b, c;
//错误的将if(a * b == c)写成if (a * b = c)
//将使c赋值到a*b的结果中
```
