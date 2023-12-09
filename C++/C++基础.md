# C++

## *字符

```c++
void demo() {
	char number0 = '0';
	char number9 = '9';
	char a = 'a';
	char z = 'z';
	char A = 'A';
	char Z = 'Z';
	cout << "0= " << int(number0) << " 9= " << int(number9) << " a= " << int(a)
		<< " z= " << int(z) << " A= " << int(A) << " Z= " << int(Z) << endl;
}
输出：‘0’=48 ‘9’=57 a=97 z=122 A=65 Z=90
大写变小写chara=char(int(chara)+32);
```

转义字符

```c++
//水平制表\t
cout << "aaaa\thelloworld" << endl;
cout << "aa\thellowor1d" << endl;
cout << "aaaaaa\thellowor1d" << endl;
//输出：
aaaa    helloworld
aa      hellowor1d
aaaaaa  hellowor1d
//垂直制表\v
cout << "aaaa\vhelloworld" << endl;
cout << "aa\vhellowor1d" << endl;
cout << "aaaaaa\vhellowor1d" << endl;
//输出：
aaaa
helloworld
aa
hellowor1d
aaaaaa
hellowor1d
```

```c++
//1、C风格字符串
//注意事项1  char 字符串名 []
//注意事项2  等号后面要用 双引号 包含起来字符串
char str[] = "hello world";
cout << str << endl;
//2、C++风格字符串
string str2 = "he1lo world";
cout << str2 << endl;

// 使用 c_str() 将 std::string 转换为 C 风格字符串
const char* str3 = str2.c_str();
```

```c++
char s1[] = "hello world";
char s2[] = " !";
strcpy(s2, s1);//复制s1到s2中
strcat(s1, s2);//连接s2到s1末尾等效于 s1+=s2;
strlen(s1);//返回s1的长度
int a = strcmp(s1, s2);//如果s1==s2 return 0 s1<s2 return小于0 s1>s2 return 大于0
char* b = strchr(s1, 'ab');//返回一个指针,指向字符串s1中‘ab'第一次出现的位置
char* c = strstr(s1, s2);//返回一个指针,指向字符串s1中s2第一次出现的位置
```

## *位运算

```c++
	//  &按二进制位进行"与"运算 运算规则:
	0 & 0 = 0;
	0 & 1 = 0;
	1 & 0 = 0;
	1 & 1 = 1;
	//  |按二进制位进行"或"运算 运算规则:
	0 | 0 = 0;
	0 | 1 = 1;
	1 | 0 = 1;
	1 | 1 = 1;
	//  ^按二进制位进行"异或"运算 运算规则:
	0 ^ 0 = 0;
	0 ^ 1 = 1;
	1 ^ 0 = 1;
	1 ^ 1 = 0;
	//  ~按二进制位进行"取反"运算 运算规则:
	~1 = -2;
	~0 = -1;
	//  <<将二进制位全部左移若干位 左侧舍弃右侧补0
	//  >>将二进制位全部右移若干位 右侧舍弃左侧正数补0负数补1
```
```c++
void demo() {
	int a = 10;//1010
	int b = 12;//1100
	int c = a & b;//1000->8
	int d = a | b;//1110->14
	int e = a ^ b;//0110
	int aa = ~a;//1...0101(补码(反码+1 取第一个1，后面取反0...1011)表示)->-11
	cout << "c= " << c << " d= "
		<< d << " e= " << e
                << " aa= " << aa << endl;
}
```
## cmath函数

| 函数                                                         | 功能                                    |
| :----------------------------------------------------------- | --------------------------------------- |
| abs(a) | 返回参数a的绝对值                       |
| [acos()](https://www.nhooo.com/cpp/cpp-library-function-cmath-acos.html) | 返回反余弦数字                          |
| [acosh()](https://www.nhooo.com/cpp/cpp-library-function-cmath-acosh.html) | 返回数字的双曲余弦值                    |
| [asin()](https://www.nhooo.com/cpp/cpp-library-function-cmath-asin.html) | 返回反正弦值                            |
| [asinh()](https://www.nhooo.com/cpp/cpp-library-function-cmath-asinh.html) | 返回数字的双曲正弦值                    |
| [atan(实数)](https://www.nhooo.com/cpp/cpp-library-function-cmath-atan.html) | 返回反正切弧度制[-PI/2,PI/2]            |
| [atan2(y,x)](https://www.nhooo.com/cpp/cpp-library-function-cmath-atan2.html) | 返回坐标的反正切 弧度制角度 [-PI,PI]    |
| [atanh()](https://www.nhooo.com/cpp/cpp-library-function-cmath-atanh.html) | 返回数字的弧双曲正切                    |
| [cbrt()](https://www.nhooo.com/cpp/cpp-library-function-cmath-cbrt.html) | 计算数字的立方根                        |
| ceil(x)| 返回数字x的向上取整                     |
| floor(x)| 返回数字x的向下取整                     |
| copysign(x,y)| 它以y的符号返回x的大小。                |
| cos(弧度) | 返回参数的余弦                          |
| [cosh()](https://www.nhooo.com/cpp/cpp-library-function-cmath-cosh.html) | 返回某个角度的双曲余弦值                |
| [exp()](https://www.nhooo.com/cpp/cpp-library-function-cmath-exp.html) | 它计算升为幂x的指数e。                  |
| [exp2()](https://www.nhooo.com/cpp/cpp-library-function-cmath-exp2.html) | 它计算x的以2为底的指数。                |
| [expm1() ](https://www.nhooo.com/cpp/cpp-library-function-cmath-expm1.html) | 它计算出幂乘以x减一的指数。             |
| [fabs(f)](https://www.nhooo.com/cpp/cpp-library-function-cmath-fabs.html) | 返回浮点参数f的绝对值                   |
| [fdim(x,y)](https://www.nhooo.com/cpp/cpp-library-function-cmath-fdim.html) | 返回x和y之间的正差。                    |
| [fma(x,y,z)](https://www.nhooo.com/cpp/cpp-library-function-cmath-fma.html) | 它计算表达式x * y + z。                 |
| [fmax()](https://www.nhooo.com/cpp/cpp-library-function-cmath-fmax.html) | 返回传递的两个参数中最大的              |
| [fmin()](https://www.nhooo.com/cpp/cpp-library-function-cmath-fmin.html) | 返回两个给定参数中的最小值              |
| [fmod()](https://www.nhooo.com/cpp/cpp-library-function-cmath-fmod.html) | 计算除法浮点数的余数                    |
| [frexp()](https://www.nhooo.com/cpp/cpp-library-function-cmath-frexp.html) | 返回一个浮点数的尾数和指数。            |
| [hypot()](https://www.nhooo.com/cpp/cpp-library-function-cmath-hypot.html) | 返回参数平方和的平方根                  |
| [ilogb()](https://www.nhooo.com/cpp/cpp-library-function-cmath-ilogb.html) | 返回\| x \|的对数的整数部分             |
| [ldexp()](https://www.nhooo.com/cpp/cpp-library-function-cmath-ldexp.html) | 将x和2的乘积返回到幂e                   |
| [llrint()](https://www.nhooo.com/cpp/cpp-library-function-cmath-llrint.html) | 使用当前舍入模式舍入参数                |
| [llround()](https://www.nhooo.com/cpp/cpp-library-function-cmath-llround.html) | 将参数四舍五入到最接近的long long int值 |
| log(a) | 返回数字的自然对数     ln(a)            |
| log10(a) | 返回数字的以10为底的对数 log(a)         |
| [log1p()](https://www.nhooo.com/cpp/cpp-library-function-cmath-log1p.html) | 返回x + 1的自然对数。                   |
| log2(x) | 它计算x的以2为底的对数。                |
| logb(x) | 返回\| x \|的对数                       |
| [lrint()](https://www.nhooo.com/cpp/cpp-library-function-cmath-lrint.html) | 使用当前舍入模式舍入参数                |
| [lround()](https://www.nhooo.com/cpp/cpp-library-function-cmath-lround.html) | 返回最接近参数的long int值              |
| [modf()](https://www.nhooo.com/cpp/cpp-library-function-cmath-modf.html) | 将数字分解为整数和小数部分              |
| [nan()](https://www.nhooo.com/cpp/cpp-library-function-cmath-nan.html) | 返回NaN值                               |
| [nearbyint](https://www.nhooo.com/cpp/cpp-library-function-cmath-nearbyint)() | 将参数舍入为使用当前舍入模式            |
| pow(a,b) | 计算幂 a的b次方                         |
| [restder(x,y)](https://www.nhooo.com/cpp/cpp-library-function-cmath-remainder.html) | 返回x / y的余数                         |
| [remquo(x,y)](https://www.nhooo.com/cpp/cpp-library-function-cmath-remquo.html) | 计算机余数并存储x / y的商               |
| [rint()](https://www.nhooo.com/cpp/cpp-library-function-cmath-rint.html) | 使用当前舍入模式舍入参数                |
| [round()](https://www.nhooo.com/cpp/cpp-library-function-cmath-round.html) | 返回最接近参数的整数值                  |
| [sin(弧度)](https://www.nhooo.com/cpp/cpp-library-function-cmath-sin.html) | 返回参数的正弦                          |
| [sinh()](https://www.nhooo.com/cpp/cpp-library-function-cmath-sinh.html) | 返回某个角度的双曲正弦                  |
| sqrt(a)| 计算数字a的算术平方根                   |
| [tan()](https://www.nhooo.com/cpp/cpp-library-function-cmath-tan.html) | 返回参数的切线                          |
| [tanh()](https://www.nhooo.com/cpp/cpp-library-function-cmath-tanh.html) | 返回角度的双曲正切                      |
| [trunc()](https://www.nhooo.com/cpp/cpp-library-function-cmath-trunc.html) | 截断数字的符号部分                      |

## *变量类型

### **数据类型

| 类型               | 位            | 范围                                                         |
| ------------------ | ------------- | ------------------------------------------------------------ |
| char               | 1 个字节      | -128 到 127 或者 0 到 255                                    |
| unsigned char      | 1 个字节      | 0 到 255                                                     |
| signed char        | 1 个字节      | -128 到 127                                                  |
| int                | 4 个字节      | -2147483648 到 2147483647                                    |
| unsigned int       | 4 个字节      | 0 到 4294967295                                              |
| signed int         | 4 个字节      | -2147483648 到 2147483647                                    |
| short int          | 2 个字节      | -32768 到 32767                                              |
| unsigned short int | 2 个字节      | 0 到 65,535                                                  |
| signed short int   | 2 个字节      | -32768 到 32767                                              |
| long int           | 4 个字节      | -9,223,372,036,854,775,808 到 9,223,372,036,854,775,807      |
| signed long int    | 8 个字节      | -9,223,372,036,854,775,808 到 9,223,372,036,854,775,807      |
| unsigned long int  | 8 个字节      | 0 到 18,446,744,073,709,551,615                              |
| float              | 4 个字节      | 精度型占4个字节（32位）内存空间，+/- 3.4e +/- 38 (~7 个数字) |
| double             | 8 个字节      | 双精度型占8 个字节（64位）内存空间，+/- 1.7e +/- 308 (~15 个数字) |
| long double        | 16 个字节     | 长双精度型 16 个字节（128位）内存空间，可提供18-19位有效数字。 |
| wchar_t            | 2 或 4 个字节 | 1 个宽字符                                                   |

enum

类似bool都表示一组有限的离散值的数据类型

取一个const的地址是合法的 取enum和一个#define的地址通常不合法 如果不想让别的指针或引用指向某个整数常量 可以使用enum
```c++
enum Color {
    RED,
    GREEN,
    BLUE
};
void demo(){
	Color myColor = RED;
	if (myColor == RED) 
	        std::cout << "The color is red." << std::endl;
}
```
```c++
//枚举中的常量默认从0开始自动递增 也可以为它们指定特定的值
enum Color {
    RED = 1,
    GREEN = 2,
    BLUE = 4
};//RED=1 GREEN=2 BLUE=4
//or
enum Color {
    RED,
    GREEN = 2,
    BLUE
};//RED=0 GREEN=2 BLUE=3
```

使用typedef给类型改名

```c++
typedef int myint//将int改名为myint
myint distance;
```

**auto** 关键字用于两种情况：声明变量时根据初始化表达式自动推断该变量的类型、声明函数时函数返回值的占位符

```c++
auto f=3.14;      //double
auto s("hello");  //const char*
auto z = new auto(9); // int*
auto x1 = 5, x2 = 5.0, x3='r';//错误，必须是初始化为同一类型
```
### *关键字
#### const和constexpr
```c++
const修饰只读变量
constexpr修饰常量
```
用constexpr或enum替换#define常量
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
```

#### static

**static** 存储类指示编译器在程序的生命周期内保持局部变量的存在 而不需要在每次它进入和离开作用域时进行创建和销毁 因此 使用 static 修饰局部变量可以在函数调用之间保持局部变量的值

static 对象的寿命从构造出来直到程序结束为止 函数内的static对象称为local static对象

当 static 用在类数据成员上时 会导致仅有一个该成员的副本被类的所有对象共享

```c++
void func()
{
	static int i = 8; // 局部静态变量
	i++;
	std::cout << "变量 i 为 " << i << endl;
}
void demo() {
	int num = 3;
	while (num--){
		func();
	}
}
//输出：变量 i 为 9 变量 i 为 10 变量 i 为 11
```
c++对多个编译单元内的 non-local static 对象 的初始化次序无明确定义
```c++
//文件A下的类A
class A {
public:
	// ...
	int get_num()const;//成员函数
};
extern A a;//预备好的对象
```
```c++
//文件B下的类B
class B {
public:
	B() {
		//...
		int num = a.get_num();//调用A的成员函数来初始化B的对象
	}
};
B b;
```
除非a在b之前先初始化 否则b的初始化将使用未初始化的a

为免除"跨编译单元的初始化次序"问题 用local static对象替换non-local static 对象
```c++
//文件A下的类A
class A {
public:
	// ...
	int get_num()const;
};

A& get_a() { 
	static A a;
	return a;//返回一个指向local static 的引用
}
```
```c++
//文件B下的类B
class B {
public:
	B() {
		//...
		int num = get_a().get_num(); 
	}
};

B& get_b() {
	static B b;
	return b;
}
```
#### extern

**extern** 存储类用于提供一个全局变量的引用，全局变量对所有的程序文件都是可见的。当您使用 'extern' 时，对于无法初始化的变量，会把变量名指向一个之前定义过的存储位置。

当您有多个文件且定义了一个可以在其他文件中使用的全局变量或函数时，可以在其他文件中使用 *extern* 来得到已定义的变量或函数的引用。可以这么理解，*extern* 是用来在另一个文件中声明一个全局变量或函数。

extern 修饰符通常用于当有两个或多个文件共享相同的全局变量或函数

```c++
第一个文件：main.cpp
#include <iostream>
 
int count ;
extern void write_extern();
 
int main()
{
   count = 5;
   write_extern();
}
第二个文件：support.cpp
#include <iostream>
 
extern int count;
 
void write_extern(void)
{
   std::cout << "Count is " << count << std::endl;
}
输出:Count is 5
```

#### thread_local

使用 thread_local 说明符声明的变量仅可在它在其上创建的线程上访问。 变量在创建线程时创建，并在销毁线程时销毁。 每个线程都有其自己的变量副本。

thread_local 说明符可以与 static 或 extern 合并。

可以将 thread_local 仅应用于数据声明和定义，thread_local 不能用于函数声明或定义。

```c++
thread_local int x;  // 命名空间下的全局变量
class X
{
    static thread_local std::string s; // 类的static成员变量
};
static thread_local std::string X::s;  // X::s 是需要定义的
 
void foo()
{
    thread_local std::vector<int> v;  // 本地变量
}
```

### **类型限定符

| 限定符   | 含义                                                         |
| -------- | ------------------------------------------------------------ |
| const    | **const** 类型的对象在程序执行期间不能被修改改变。           |
| volatile | 修饰符 **volatile** 告诉编译器不需要优化volatile声明的变量，让程序可以直接从内存中读取变量。对于一般的变量编译器会对变量进行优化，将内存中的变量值放在寄存器中以加快读写效率。 |
| restrict | 由 **restrict** 修饰的指针是唯一一种访问它所指向的对象的方式。只有 C99 增加了新的类型限定符 restrict。 |

### **四大类型转换

#### 静态转换static_cast

```c++
int i = 10;
float f = static_cast<float>(i);//静态将int类型转换成float
//静态转换不进行任何运行时类型检查，可能会导致运行时错误
```

#### 动态转换dynamic_cast

```c++
class Base{
	virtual ~Base() {}  // 声明一个虚(析构)函数
};
class Son :public Base {};
void demo() {
	Base* base_ptr = new Base;
	//将基类指针或引用转换成派生类指针或引用(多态下)
	Son* son_ptr = dynamic_cast<Son*>(base_ptr);
	//动态转换进行运行时类型检查，如果不能进行转换则返回空指针或引发异常
}
```

#### 常量转换const_cast

```c++
const int i = 10;
//const_cast中的类型只能是指针或引用
int& j = const_cast<int&>(i); 
```

#### 重新解释转换reinterpret_cast

```c++
int i = 10;
float f = reinterpret_cast<float&>(i);//不进行任何类型转换
```

## *左值和右值

C++中，所有值不是左值就是右值。左值是表达式结束后依然存在的持久化对象，右值是表达式结束后就不再存在的临时对象；有名字的对象都是左值，右值没有名字；如果能对表达式取地址，则为左值，否则为右值。

C++11扩展了右值的概念，将右值分为了纯右值和将亡值：

纯右值：

a) 非引用返回的临时变量；如普通函数、lambda函数、类的成员函数以值的方式返回，都是纯右值。

b) 运算表达式产生的结果。

c) 字面常量(C风格字符串除外，它是地址)。

将亡值(学习移动语义、完美转发)：

a)与右值引用相关的表达式；如将要被移动的对象、T&&函数返回的值、std::move()的返回值、转换成T&&的类型的转换函数的返回值。

### **右值引用C++11

右值引用就是给右值取个别名，使用符号&&，右值有了名字后，就成了左值

左值引用只能绑定左值，右值引用只能绑定右值，但是常量左值引用除外

```c++
int func() {
	return 10;
}
void demo() {
	int a = 1;//a是左值，1是右值
	const int b = a + 1;//b是左值，a+1是右值
	const int& ra = a;//a是非常量左值
	const int& rb = b;//b是常量左值
	//常量左值引用 语法：数据类型&& 变量名=右值;
	const int&& c = 3;
	const int&& d = func();
	//C++11提供了std::move()方法来将左值转移成右值
	const int&& e = move(a);
	//引用右值的目的是实现移动语义
}
```

### **完美转发

1)如果模板中（包括类模板和函数模板）函数的参数书写成为T&&，那么，函数既可以接受左值引用，又可以接受右值引用。

2)提供了模板函数std::forward<T>(参数)，用于转发参数，如果参数是一个右值，转发之后仍是右值引用;如果参数是一个左值,转发之后仍是左值引用。

```c++
void func1(int& ii) {
	cout << "参数是左值=" << ii << endl;
}
void func1(int&& ii) {
	cout << "参数是右值=" << ii << endl;
}
template<typename TT>
void func(TT&& ii) {
	func1(forward<TT>(ii));
}
void demo() {
	int i = 3;
	func(i);//参数是左值=3
	func(3);//参数是右值=3
}
```

## *指针

指针就是地址，* 指针 是地址里存的数据

```c++
int a = 10;
int * p;
p = &a;
cout<<"a的地址为 "<<&a<<endl;
cout<<"指针p为 "<<p<<endl;

*p=100;
cout<<"a为 "<<a<<endl;
```



### **修饰指针

const修饰指针（按*和const出现的顺序命名，*是指针，const是常量）

1. const修饰指针--常量指针const*
```c++
int const * p = a;
const int * p = a;//特点：指针的指向可以修改，但是指针指向的值不可以修改
```
2. const修饰常量--指针常量*const
```c++
int * const p = &a;//特点：指针的指向不可以修改，指针指向的值可以修改
```
3. const既修饰指针又修饰常量
```c++
const int * const p = &a;//特点：指针的指向以及指向的值都不能修改
```

### **函数指针 回调函数

函数指针用来指向相同形式参数和返回值 但功能不同的函数

函数指针声明 ：函数返回类型 (*函数指针名)(函数参数)；

函数指针赋值：函数指针名=函数名；

函数指针使用：函数指针名（函数参数）；/(*函数指针名)(函数参数)

```c++
int sum(int a, int b) {
	return a + b;
}
int dif(int a, int b) {
	return a - b;
}
int fun(int(*func_ptr)(int, int), int x, int y) {
	//函数指针作为函数参数 
	//通过函数指针调用的函数称为回调函数
	return func_ptr(x, y);
}
void demo() {
	int a = 10, b = 5;
	int (*func_ptr)(int, int);//函数指针声明
	func_ptr = sum;
	cout << "sum函数地址  = " << sum << endl;
	cout << "函数指针地址 = " << func_ptr << endl;
	cout << "a+b= " << sum(a, b) << endl;
	cout << "a+b= " << func_ptr(a, b) << endl;
	cout << "a+b= " << fun(func_ptr, a, b) << endl;
	cout << "a+b= " << fun(sum, a, b) << endl;
}
```

### **引用

引用的本质在C++内部实现的是一个指针常量(指针的指向不能更改)
引用与指针之间有三个主要的不同:

1、不存在空引用 引用必须连接到—块合法的内存

2、引用一旦被初始化为一个对象 就不能被指向到另一个对象 指针可以在任何时候指向到另一个对象。

3、引用必须在创建时被初始化 指针可以在任何时间被初始化

```c++
void func(int& ref) {
	ref = 100;//ref是引用,转换成 *ref=100;
}
void demo() {
	//引用基本语法
	//数据类型 &别名 = 原名
	int a = 10;
	//自动转换为 int* const b=&a;
	int& b = a;//一旦初始化就不能更改指向
	b = 20; cout << b;
	func(b); cout << b;
	//int &c;  //错误，不存在空引用
    	//int &c = 10;//错误,引用本身需要一个合法的内存空间
    	//使用常量引用
    	const int &c = 10;//编译器优化代码:int temp=10;const int& c = temp;
}
```

#### ***引用做函数返回值

```c++
int& func() {//返回静态变量引用
	static int a = 100;
	return a;
}
void demo() {
	int& b = func();
	cout << b;//b=100
	//如果函数做左值,那么必须返回引用
	func() = 1;
	cout << b;//b=1
}
```

###  **空指针和野指针
空指针是不会指向有效数据的指针 空指针（null和内存编号为0-255）无法直接访问 如任何 *p 操作
以前c/c++用0表示空指针 这带来一些问题 0既可以表示指针常量 又可以表示整型常量
NULL是宏 可能是int也可能是long 取决于各个平台的实现 
如果有两个重载函数func(int) func(int *) 函数调用func(NULL)和func(0)会优先调用前者

C++11新增了nullptr来表示空指针 它是指针类型 但为了向后兼容 nullptr==0仍为true

野指针是指一个指针变量持有一个内存地址 但该地址并未被有效地分配给该指针指向的对象 
当程序试图使用一个野指针访问对象或者释放它指向的内存时 会导致未定义的行为

野指针出现的情况：

1、指针变量没有初始化

2、指针指向的对象被delete释放 但之后该指针没有置为nullptr 这种野指针也叫悬挂指针

3、指针超出作用域
```c++
int *demo() {
	int x = 10;
	return &x; //x在函数返回后被销毁 返回的是野指针/悬挂指针
}
```
避免野指针的方法：

1、始终在声明指针变量后初始化 可以初始化为nullptr

2、释放内存后，将指针置为nullptr

3、指针超出作用域前 避免将指针地址传递到超出其作用域的范围

4、使用智能指针

## *智能指针

普通指针需要程序员来释放内存，使用智能指针#include<memory>来管理指针的释放
智能指针是类模板，不是指针 在栈上创建智能指针对象，将普通指针交给智能指针对象，智能指针对象过期时，调用析构函数释放普通指针的内存。
智能指针有四类：auto_ptr(C++17已弃用)、unique_ptr 、shared_ptr、weak_ptr
一般使用unique_ptr，shared_ptr、weak_ptr用于多线程。

为了正确使用智能指针，必须坚持一些基本规范:

1、不使用相同的内置指针值初始化(或reset)多个智能指针

2、不delete get()返回的指针

3、不使用get()初始化或reset另一个智能指针

4、如果你使用get()返回的指针 记住当最后一个对应的智能指针销毁后 你的指针就变为无效了

5、如果你使用智能指针管理的资源不是new分配的内存 记住传递给它一个删除器

### **独占指针unique_ptr

unique_ptr 独享它指向的对象 同时只有一个unique_ptr指向同一个对象 当这个unique_ptr被销毁时 指向的对象也随即销毁



unique_ptr初始化

```c++
class MyPrint {
public:
	string m_name;
	MyPrint() {//构造函教
		cout << m_name << "调用无参构造函数MyPrint" << endl;
	}
	MyPrint(const string& name) :m_name(name) {
		cout << m_name << "调用有参构造函数MyPrint" << m_name << endl;
	}
	~MyPrint() {
		cout << "调用析构函数" << endl;
	}
};

void demo() {
	//初始化1:使用已经存在的地址初始化
	MyPrint* p = new MyPrint("指针1");//定义原始指针p，分配内存
	unique_ptr<MyPrint> p1(p);//创建智能指对象，管理原始指针p
	//错误示例:不能把普通指针直接赋值给智能指针
	//unique_ptr<MyPrint>p1 = p;
	//unique_ptr<MyPrint>p1 = new MyPrint("指针1");
	cout << "裸指针的值是" << p << endl;
	cout << "p1的值是    " << p1 << endl;
	cout << "p1.get() =  " << p1.get() << endl;
	cout << "p1的地址是  " << &p1 << endl;

	//初始化2:分配内存并初始化
	unique_ptr<MyPrint>p2(new MyPrint("指针2"));
	//错误示例:不能用其他智能指针拷贝构造 不能用=对unique_ptr进行赋值 独占指针!
	//用于函数的参教时 传引用 因为unique_ptr没有拷贝构造函数
	//unique_ptr<MyPrint>p2 = p1;

	//初始化3:使用C++14标准
	unique_ptr<MyPrint>p3 = make_unique<MyPrint>("指针3");
}
```

使用技巧

```c++
unique_ptr<MyPrint> Create_ptr() {
	unique_ptr<MyPrint>pp(new MyPrint("指针3"));
	return pp;
}

void demo() {
	//将一个unique_ptr赋给另一方时，如果源unique_ptr是一个临时右值，编译器允许这么做；
	unique_ptr<MyPrint> p1(new MyPrint("指针1"));
	unique_ptr<MyPrint> p2;
	//p2 = p1;//如果源unique_ptr将存在一段时间，编译器禁止这么做。
	p2 = unique_ptr<MyPrint>(new MyPrint("指针2"));//用匿名对象赋值
	cout << "开始调用Create_ptr函数" << endl;
	p2 = Create_ptr();
	cout << "结束调用Create_ptr函激" << endl;
	//使用nullptr给unique_ptr赋值 将释放对象
	unique_ptr<MyPrint> p3(new MyPrint("指针4"));
	cout << "赋值之前" << endl;
	if (p3 != nullptr) cout << "p3不是空的" << endl;
	p3 = nullptr;
	cout << "赋值之后" << endl;
	if (p3 == nullptr) cout << "p3是空的" << endl;
}
```

```c++
// func1需要一个指针但不会对这个指针负责
void func1(const MyPrint* a) {
	cout << a->m_name << "func1()" << endl;
}
// func2需要一个指针并会对这个指针负责
void func2(const MyPrint* a) {
	cout << a->m_name << "func2()" << endl;
	delete a;
}
// func3需要一个unique_ptr不会对这个unique_ptr负责
void func3(const unique_ptr<MyPrint>& a) {
	cout << a->m_name << "func3()" << endl;
}
// func4需要一个unique_ptr并会对这个unique_ptr负责
void func4(unique_ptr<MyPrint> a) {
	cout << a->m_name << "func4()" << endl;
}

void demo() {
	unique_ptr<MyPrint> ptr1(new MyPrint("指针1"));
	cout << "开始调用函数func1" << endl;
	func1(ptr1.get());
	cout << "结束调用函数func1" << endl;
	//release()释放对原始指针的控制权 将unique_ptr置为空 返回裸指针
	//(可用于把unique_ptr传递给子函数 子函数将负责释放对象)
	cout << "开始调用函教func2" << endl;
	func2(ptr1.release());
	cout << "结束调用函教func2" << endl;
	unique_ptr<MyPrint> ptr2(new MyPrint("指针2"));
	cout << "开始调用函数func3" << endl;
	func3(ptr2);
	cout << "结束调用函数func3" << endl;
	//std::move()可以转移对原始指针的控制权
	//（可用于把unique_ptr传递给子函数 子函数形参也是unique_ptr）
	cout << "开始调用函数func4" << endl;
	func4(std::move(ptr2));
	cout << "结束调用用函数func4" << endl;
}
```

reset()和swap()

```c++
void demo() {
	unique_ptr<MyPrint> ptr1(new MyPrint("指针1"));
	ptr1.reset();//释放ptr1指向的对象
    	ptr1.reset(nullptr);//释放对象
    	//ptr1.reset(q);//如果提供了内置指针q，指向q
	unique_ptr<MyPrint> p1(new MyPrint("指针1"));
	unique_ptr<MyPrint> p2(new MyPrint("指针2"));
	swap(p1, p2);//交换两个unique_ptr的控制权
	cout << p1.get()->m_name << endl;
}
```

unique_ptr也可像普通指针那样 当指向一个类继承体系的基类对象时 也具有多态性质 如同使用裸指针管理基类对象和派生类对象那样

unique_ptr 不是绝对安全 如果程序中调用exit()退出 全局的unique_ptr可以自动释放 但局部的unique_ptr无法释放

```c++
unique_ptr<MyPrint> ptr1(new MyPrint("全局"));
void demo() {
	unique_ptr<MyPrint> ptr1(new MyPrint("局部"));
	exit(0);
}
```

unique_ptr提供了支持数组的具体化版本 数组版本的unique_ptr 重载了操作符[] 操作符[]返回的是引用 可以作为左值使用

```c++
void demo() {
	unique_ptr<MyPrint[]>parr2(new MyPrint[2]);//unique_ptr数组
	unique_ptr<MyPrint[]>parr2(new MyPrint[2]{ string("指针1"),string("指针2") });
	parr2[0].m_name = "指针1";
}
```

### **共享/计数指针shared_ptr

shared_ptr共享它指向的对象 多个shared_ptr可以指向(关联)相同的对象 在内部采用计数机制来实现 
当新的shared_ptr与对象关联时 引用计数增加1 当shared_ptr超出作用域时 引用计数减1 当引用计数变为0时 则表示没有任何shared_ptr与对象关联 则释放该对象

初始化shared_ptr

```c++
void demo() {
	shared_ptr<MyPrint> p1(new MyPrint("指针1"));//方法1：分配内存并初始化
	shared_ptr<MyPrint> p2 = make_shared<MyPrint>("指针2");//方法2：C++11
	MyPrint* p = new MyPrint("指针3");
	shared_ptr<MyPrint>p3(p);//方法3：用已存在的地址初始化
	shared_ptr<MyPrint>p4 = p3;//p4(p3)//方法4：用已存在的shared_ptr初始化，计数+1
	cout << p4.use_count();//返回计数器的值
	if (p1.unique())cout << "计数为1" << endl;//如果计数器为1,返回true
	p3.get();
}
```

使用技巧

```c++
void demo() {
	shared_ptr<MyPrint> p1(new MyPrint("指针1"));
	shared_ptr<MyPrint> p2 = p1;
	p1 = nullptr;//使用nullpter给shared_ptr赋值 计数减1,如果计数为0,将释放对象
	unique_ptr<MyPrint>p3(new MyPrint("指针2"));
	//std::move()可以转移对原始指针的控制权。还可以将unique_ptr转移成shared_ptr(反之不行)
	shared_ptr<MyPrint>p4 = move(p3);
	swap(p2, p4);
	p2.reset(new MyPrint("新指针"));
}
```

shared_ptr也可像普通指针那样，当指向一个类继承体系的基类对象时，也具有多态性质，如同使用裸指针管理基类对象和派生类对象那样。

shared_ptr 不是绝对安全，如果程序中调用exit()退出，全局的shared_ptr可以自动释放，但局部的shared_ptr无法释放。

shared_ptr 提供了支持数组的具体化版本。数组版本的shared_ptr ，重载了操作符[]，操作符[]返回的是引用，可以作为左值使用。

shared_ptr的线程安全性:

shared_ptr的引用计数本身是线程安全（引用计数是原子操作)。

多个线程同时读同一个shared_ptr对象是线程安全的。
如果是多个线程对同一个shared_ptr对象进行读和写，则需要加锁。
多线程读写shared_ptr所指向的同一个对象，不管是相同的 shared_ptr对象，还是不同的shared_ptr对象，也需要加锁保护。如果unique_ptr能解决问题，就不要用shared_ptr。unique_ptr的效率更高，占用的资源更
少。

### **弱指针 weak_ptr

```c++
weak_ptr没有重->和*操作符，不能直接访问资源。
有以下成员函数:
1) operator=();//把shared_ptr或 weak_ptr赋值给weak_ptr
2) expired();//判断它指资源是否已过期(已经被销毁)。
3) lock();//提升为shared_ptr(线程安全的)，如果资源已过期，返回空的shared_ptr
4) reset();//将当前weak_ptr指针置为空
5) swap();//交换。
```

### **智能指针删除器

在默认情况下，智能指针过期的时候，用delete原始指针;释放它管理的资源。
程序员可以自定义删除器，改变智能指针释放资源的行为。
删除器可以是全局函数、仿函数和Lambda表达式，形参为原始指针。

```c++
void deletefunc(MyPrint* a) {//函数作为删除器
	cout << "自定义删除器(全局函数)" << endl;
	delete a;
}
struct deleteclass {//仿函数作为删除器
	void operator() (MyPrint* a) {
		cout << "自定义删除器(仿函数)" << endl;
		delete a;
	}
};
auto deletelambda = [](MyPrint* a) {//lambda表达式作为删除器
	cout << "自定义删除器(lambda表达式)" << endl;
	delete a;
};
void demo() {
	shared_ptr<MyPrint> p1(new MyPrint("指针1"));//默认用缺省的删除器 delete
	shared_ptr<MyPrint> p2(new MyPrint("指针2"), deletefunc);//函数作为删除器
	shared_ptr<MyPrint> p3(new MyPrint("指针3"), deleteclass());//仿函数作为删除器
	shared_ptr<MyPrint> p4(new MyPrint("指针4"), deletelambda);//lambda表达式作为删除器

	unique_ptr<MyPrint, decltype(deletefunc)*>p5(new MyPrint("指针5"), deletefunc);//函数作为删除器
	unique_ptr<MyPrint, void(*)(MyPrint*)>p5(new MyPrint("指针5"), deletefunc);//函数作为删除器 传函数指针
	unique_ptr<MyPrint, deleteclass>p6(new MyPrint("指针6"), deleteclass());//仿函数作为删除器
	unique_ptr<MyPrint, decltype(deletelambda)>p7(new MyPrint("指针7"), deletelambda);//lambda表达式作为删除器
}
```

## *结构体

```c++
struct student {
	string name;
	int age;
	int score;
};
```



### **结构体数组

```c++
//创建结构体数组
	struct student stuArray[3] =
	{
		{"张三",18, 100},
		{"李四",28 , 99 },
		{"王五", 38, 66}
	};

//给结构体数组中的元素赋值
	stuArray[2].name = "赵六";
```

### **结构体指针

```c++
student s = { "张三",18, 100 };
student* p = &s;
p->name
```

### **结构体嵌套结构体

```c++
struct student {
	string name;
	int age;
	int score;
};

struct teacher {
	int id;
	string name;
	struct student stu;
};

void demo() {
	teacher t1;
	t1.name = "a";
	t1.stu.name = "b";
	t1.stu.score = 100;
}
```

### **结构体作为函数参数

```c++
void printstudent1(student stu) {
	cout << stu.name << " " << stu.age << endl;
}
void printstudent2(student* stu) {
	stu->age = 19;
	cout << stu->name << " " << stu->age << endl;
}
void printstudent3(student& stu) {
	stu.age = 19;
	cout << stu.name << " " << stu.age << endl;
}
void demo() {
	student stu = { "张三",18, 100 };
	printstudent1(stu);//值传递 形参不修饰实参
	printstudent2(&stu);//地址传递 形参修饰实参
	printstudent3(stu);//引用传递 形参修饰实参
}
```

## *函数

占位参数和默认参数

```c++
void func1(int, int);//占位参数
//如果某个位置有默认参数，那这个位置之后都是默认参数
void func(int a, int b = 10, int c = 100);//默认参数b,c
void func(int a, int b, int c) {};//函数声明和实现中,只能有一处有默认值 防止歧义
```

### **函数重载

作用:函数名可以相同，提高复用性
函数重载满足条件:

1.同一个作用域下

2.函数名称相同

3.函数参数类型不同或者个数不同或者顺序不同

注意:函数的返回值不可以作为函数重载的条件

两个成员函数如果只是常量性不同 可以被重载(详见C++面向对象-多态)

```c++
//函数重载需要函数在同一个作用域下
void func(int a, int b);
//int func(int a, int b);//错误 函数返回值不作为函数重载条件
void func(double a, int b);
void func(int a, double b);
void func(double a, int b = 10);//默认参数
void func(int a, int b, int c);
//引用作为重载的条件
void func(const int& a);//const int& a=10;合法
//void func(int& a);//int& a=10;不合法
```

### **内联函数inline

在函数的声明、实现前加上关键字inline;

应用：正常程序执行到函数时，会发生函数调用，程序需要跳转到函数代码的位置，来回跳转是有开销的。使用内联函数，相当于在这个位置复制了这个函数的副本，程序不会跳转位置。好处是提高了运行速度，坏处是占用了更多的内存。

适用：代码执行时间很短

不适用：内联函数不能递归

对于形似函数的宏 最好改用inline函数替换#define

### **lambda表达式 匿名函数

 实现了函数里面定义函数

语法[ ] ( )->{}：[捕获列表] （参数列表）mutable noexcept函数选项 ->返回值 {函数体}

#### ***捕获列表

通过捕获列表，lambda函数可以访问的父作用域中的非静态局部变量（静态局部变量可以直接访问)。
捕获列表书写在[]中，与函数参数的传递类似，捕获方式也可以是值或者引用。

```c++
[]//空捕获列表 lambda不能使用所在函数中的变量
[names]//names是一个逗号分隔的名字列表 这些名字都是lambda所在函数的局部变量 默认情况下是值捕获
[=]//隐式捕获列表，采用值捕获方式
[&]//隐式捕获列表，采用引用捕获方式 
[&, identifier_list]//identifier_list变量采用值捕获方式 其他都采用引用捕获
[=, &identifier_list]//identifier_list变量采用引用捕获方式 不能包括this 名字前加& 其他都采用值捕获
void demo() {
	int a = 1, b = 2, c = 3;
	auto f1 = [] {cout << "hello" << endl; };
	auto f2 = [a, b] {cout << a + b; };
	auto f3 = [=] {cout << a + b + c; };
	auto f4 = [&] {cout << a++ << b++ << c++; };
	auto f5 = [=, &b] {cout << b++; };
	auto f6 = [&, b] {cout << a++ << b << c++; };
    	//显式捕获的变量必须使用和默认捕获不同的方式捕获;
	//如果希望修改捕获的值，加上mutable,但是lambda函数外部,这个值不会变
	auto f7 = [=]()mutable {cout << a++; };
}

```

#### ***参数列表

```c++
参数列表是可选的，类似普通函数的参数列表，如果没有参数列表，()可以省略不写。
与普通函数的不同:
lambda函数不能有默认参数;
所有参数必须有参数名;
不支持可变参数;
```

#### ***返回类型

用后置的方法书写返回类型，类似于普通函数的返回类型，如果不写返回类型，编译器会根据函数体中的代码推断出来。
如果有返回类型，建议显式的指定，自动推断可能与预期不一致。

```c++
void demo() {
	auto f1 = [] {return; };//void
	auto f2 = [] {return 1; };//int
	auto f3 = [] {return true; };//bool
	auto f4 = [] {return 1.0; };//double
}
```

#### ***函数包装

一般使用 auto f=[](){};来包装lambda表达式，但是当表达式里面递归调用表达式的时候，不允许。

解决方法#include< functional> std::function<return type()> f=[](){};

std::function是C++标准库中的一个类模板，用于包装可以调用的实体（函数、函数指针、成员函数指针、Lambda表达式等等）

```c++
void demo() {
	std::function<int(int, int)>dfs =
		[&](int a, int b)->int {
		dfs(a-1, b-2);//递归调用dfs
	};
}
```

## *内存管理

### **内存四区

C++程序在执行时，将内存大方向划分为4个区域

一、代码区：存放函数体的二进制代码，由操作系统进行管理

二、全局区:存放全局变量是和静态变量以及常量

三、栈区:由编译器自动分配释放,存放函数的参数值,局部变量等四、堆区:由程序员分配和释放,若程序员不释放,程序结束时由操作系统回收

内存四区意义:不同区域存放的数据，赋予不同的生命周期,给我们更大的灵活编程

```c++
                  程序运行前
在程序编译后，生成了exe可执行程序，未执行该程序前分为两个区域
                      
代码区:
存放CPU执行的机器指令;
代码区是共享的，共享的目的是对于频繁被执行的程序，只需要在内存中有一份代码即可;
代码区是只读的，使其只读的原因是防止程序意外地修改了它的指令;

全局区:
全局变量和静态变量存放在此;
全局区还包含了常量区,字符串常量和其他常量也存放在此;
该区域的数据在程序结束后由操作系统释放;
```

```c++
                  程序运行后
栈区:
由编译器自动分配释放存放函数的参数值,局部变量等
注意事项:不要返回局部变量的地址，栈区开辟的数据由编译器自动释放
int* func() {
	int a = 10;//局部变量 存在栈区 栈区的数据在函数执行完后自动释放
	return &a;//返回局部变量的地址
}
void demo() {
	int* p = func();
	cout << *p << endl;//第一次可以正确打印，因为编译器做了保留
	cout << *p << endl;//不再保留
}
堆区:
由程序员分配释放,若程序员不释放,程序结束时由操作系统回收在C++中主要利用new在堆区开辟内存 指针本质也是局部变量，放在栈上，指针保存的数据放在堆上
```



### **new、delete和malloc、free

```c++
void demo() {
	int* p = new int(10);//new返回的是该数据类型的指针
	delete p;
	int* arr = new int[10];
	delete[] arr;//释放数组的时候 加[]
}
```

new和malloc的区别

```c++
int *p=new int(10); //int *p=(int*)malloc(sizeof(int));
malloc按字节分配内存，大小自己定或sizeof()计算，返回类型是void* (使用时强制转换)指向已分配内存的指针，申请失败返回空指针
new根据对象类型自动计算分配内存大小，然后使用构造函数对内存初始化，返回指向对象的指针，申请失败抛出bad_alloc类型异常 new可以重载
```

delete和free的区别

```c++
free只释放内存
delete先调用析构函数，再释放内存，留下一个野指针 delete可以重载
void demo() {
	int* p = new int(10);
	cout << "p = " << p << endl;
	delete p;
	if (p != nullptr)cout << "p是野指针" << endl;
	cout << "p = " << p << endl;
	int a = 100;
	p = &a;
	cout << "p = " << p << endl;
}
```

## *文件操作

### **文本文件ASCII码

```c++
	写文件写文件步骤如下:
1.包含头文件#include <fstream>
2.创建流对象ofstream ofs;
3.打开文件ofs.open("文件路径,打开方式1|打开方式2|...);
    打开方式:
    ios::in 为读文件而打开文件
    ios:out 为写文件而打开文件
    ios:ate 初始位置:文件尾
    ios:app 追加方式写文件
    ios:trunc 如果文件存在先删除，再创建
    ios::binary 二进制方式
4.写数据ofs <<"写入的数据";
5.关闭文件ofs.close();
void m_write() {
	//创建流对象
	ofstream ofs;//或者fstream ofs;
	ofs.open("D:/test.txt", ios::out); //指定打开方式
	// 写内容
	ofs << "姓名" << endl;
	ofs << "年龄" << endl;
	ofs.close();//关闭文件
}          
```

```c++
              读文件与写文件步骤相似，但是读取方式相对于比较多
    读文件步骤如下:
1.包含头文件#include <fstream>
2.创建流对象ifstream ifs;
3.打开文件并判断文件是否打开成功ifs.open("文件路径".打开方式);
4.读数据四种方式读取
5.关闭文件ifs.close();
void m_read() {
	//创建流对象
	ifstream ifs;//或者fstream ifs;
	//打开文件并且判断是否打开成功
	ifs.open("D:/test.txt", ios::in);
	if (!ifs.is_open()) {
		cout << "打开文件失败" << endl;
		return;
	}
	//读数据
	//第一种
	/*char buf[1024] = { 0 };
	while (ifs >> buf){
		cout<< buf << endl;
	}*/
	//第二种
	/*char buf[1024] = { 0 };
	while (ifs.getline (buf, sizeof (buf))) {
		cout << buf << endl;
	}*/
	//第三种
	/*string buf;
	while (getline(ifs, buf)) {
		cout << buf << endl;
	}*/
	//第四种
	char c;
	while ((c = ifs.get()) != EOF) {//EOF end of file
		cout << c;
	}
	ifs.close();//关闭文件
}
```

### **二进制文件

打开方式要指定为 ios::binary

```c++
二进制方式写文件主要利用流对象调用成员函数write
函数原型:ostream& write(const char * buffer,int len) 
参数解释:指针buffer指向内存中一段存储空间 len是读写的字节数
class Person {
public:
	char m_name[64];
	int m_age;
};
void m_write() {
	//创建流对象
	//ofstream ofs;//或者fstream ofs;
	//ofs.open("D:/test.txt", ios::out | ios::binary); //指定打开方式
	//上面两行写成一行
	ofstream ofs("D:/test.txt", ios::out | ios::binary);
	//写内容
	Person p = { "张三",18 };
	ofs.write((const char*)&p, sizeof(Person));
	ofs.close();//关闭文件
}
```

```c++
二进制方式读文件主要利用流对象调用成员函数read
函数原型:istream& read(char *buffer,int len);
参数解释:指针buffer指向内存中一段存储空间。len是读写的字节数
void m_read() {
	//创建流对象
	ifstream ifs("D:/test.txt", ios::in | ios::binary);
	if (!ifs.is_open()) {
		cout << "打开文件失败" << endl;
		return;
	}
	//读文件
	Person p;
	ifs.read((char*)&p, sizeof(Person));
	cout << "姓名 " << p.m_name << endl;
	ifs.close();//关闭文件
}
```

### **批处理文件

```c++
//获取文件后缀类型
string get_file_extension(const string& file_path) {
	size_t pos = file_path.find_last_of('.');
	if (pos == string::npos) {
		return "";
	}
	else {
		return file_path.substr(pos + 1);
	}
}
```

```c++
//移动文件（复制完删除）
void removeFile(const std::string& sourcePath, const std::string& destinationPath) {
	std::ifstream sourceFile(sourcePath, std::ios::binary);
	std::ofstream destinationFile(destinationPath, std::ios::binary);

	destinationFile << sourceFile.rdbuf();

	sourceFile.close();
	destinationFile.close();
	std::cout << "将" << sourcePath << "转移到" << destinationPath << endl;
	std::remove(sourcePath.c_str());
}
```

```c++
//处理一个文件夹下的.obj文件
int deal_files() {
	// 指定文件夹路径
	string folder_path = "D:/MyCode/source";//指定文件夹
	string out__path = "D:/MyCode/target";//指定输出文件夹
	DIR* dir = opendir(folder_path.c_str());
	if (dir == NULL) {
		cout << "Failed to open folder." << endl;
		return 0;
	}
	// 读取文件夹下的所有文件
	dirent* entry;
	while ((entry = readdir(dir)) != NULL) {
		// 排除特殊条目 "." 和 ".."
		if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
			continue;
		}
		// 拼接文件的完整路径
		string file_path = folder_path + "/" + entry->d_name;
		std::string filename = entry->d_name;
		std::string basename = filename.substr(0, filename.find_last_of("."));
		string out_path = out__path + "/" + basename + ".vtk";//修改输出格式
		//判断该路径是否为文件
		struct stat statbuf;//见linux stat函数
		if (stat(file_path.c_str(), &statbuf) == 0 && S_ISREG(statbuf.st_mode)) {
			// 打开文件并读取文件内容
			ifstream file(file_path);
			string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
			// 在此处处理文件内容，例如打印输出;
			file.close(); // 关闭文件流
			string file_ext = get_file_extension(file_path);// 获取文件后缀
			if (file_ext == "obj") {
				cout << "打开" << file_path << "  " << endl;
				file.close(); // 关闭文件流
				/*stringstream ss;
				ss << "D:/MyCode/source" << entry->d_name;
				string destinationFilePath = ss.str();
				removeFile(file_path, destinationFilePath);*/
				VtkToObj(file_path, out_path);
				cout << "----------------------done--------------------" << endl;
			}
		}
	}
}
```

## *异常
```c++
void demo(int a) {
	try {//try里是可能抛出异常的代码
		if (a == 1)cout << "程序正常进行" << endl;
		else if (a == 2)throw"出现异常";//抛出C风格字符串char*异常
		else if (a == 3)throw 'a';// 抛出字符char异常
		else throw 1;//抛出int 异常
	}
	catch (const char* e) { // 捕获C风格字符串异常
		std::cerr << "捕获到异常: " << e << std::endl;
	}
	catch (char e) { // 捕获字符异常
		std::cerr << "捕获到异常: " << e << std::endl;
	}
	catch (int e) { // 捕获整数异常
		std::cerr << "捕获到异常: " << e << std::endl;
	}
	catch (...) { // 捕获其他类型异常
		std::cerr << "捕获到未知类型异常" << std::endl;
	}
}
```
