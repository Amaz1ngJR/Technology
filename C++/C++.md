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

转移字符

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
```

```c++
	char s1[] = "hello world";
	char s2[] = " !";
	strcpy(s2, s1);//复制s1到s2中
	strcat(s1, s2);//连接s2到s1末尾等效于 s1+=s2;
	strlen(s1);//返回s1的长度
	int a = strcmp(s1, s2);//如果s1==s2 return 0 s1<s2 return小于0 s1>s2 return 大于0
	char* b=strchr(s1, 'ab');//返回一个指针,指向字符串s1中‘ab'第一次出现的位置
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

## cmath函数

| 函数                                                         | 功能                                    |
| :----------------------------------------------------------- | --------------------------------------- |
| [abs(a)](https://www.nhooo.com/cpp/cpp-library-function-cmath-abs.html) | 返回参数a的绝对值                       |
| [acos()](https://www.nhooo.com/cpp/cpp-library-function-cmath-acos.html) | 返回反余弦数字                          |
| [acosh()](https://www.nhooo.com/cpp/cpp-library-function-cmath-acosh.html) | 返回数字的双曲余弦值                    |
| [asin()](https://www.nhooo.com/cpp/cpp-library-function-cmath-asin.html) | 返回反正弦值                            |
| [asinh()](https://www.nhooo.com/cpp/cpp-library-function-cmath-asinh.html) | 返回数字的双曲正弦值                    |
| [atan(实数)](https://www.nhooo.com/cpp/cpp-library-function-cmath-atan.html) | 返回反正切弧度制[-PI/2,PI/2]            |
| [atan2(y,x)](https://www.nhooo.com/cpp/cpp-library-function-cmath-atan2.html) | 返回坐标的反正切 弧度制角度 [-PI,PI]    |
| [atanh()](https://www.nhooo.com/cpp/cpp-library-function-cmath-atanh.html) | 返回数字的弧双曲正切                    |
| [cbrt()](https://www.nhooo.com/cpp/cpp-library-function-cmath-cbrt.html) | 计算数字的立方根                        |
| [ceil(x)](https://www.nhooo.com/cpp/cpp-library-function-cmath-ceil.html) | 返回数字x的向上取整                     |
| [floor(x)](https://www.nhooo.com/cpp/cpp-library-function-cmath-floor.html) | 返回数字x的向下取整                     |
| [copysign(x,y)](https://www.nhooo.com/cpp/cpp-library-function-cmath-copysign.html) | 它以y的符号返回x的大小。                |
| [cos(弧度)](https://www.nhooo.com/cpp/cpp-library-function-cmath-cos.html) | 返回参数的余弦                          |
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
| [log(a)](https://www.nhooo.com/cpp/cpp-library-function-cmath-log.html) | 返回数字的自然对数     ln(a)            |
| [log10(a)](https://www.nhooo.com/cpp/cpp-library-function-cmath-log10.html) | 返回数字的以10为底的对数 log(a)         |
| [log1p()](https://www.nhooo.com/cpp/cpp-library-function-cmath-log1p.html) | 返回x + 1的自然对数。                   |
| [log2(x)](https://www.nhooo.com/cpp/cpp-library-function-cmath-log2.html) | 它计算x的以2为底的对数。                |
| [logb(x)](https://www.nhooo.com/cpp/cpp-library-function-cmath-logb.html) | 返回\| x \|的对数                       |
| [lrint()](https://www.nhooo.com/cpp/cpp-library-function-cmath-lrint.html) | 使用当前舍入模式舍入参数                |
| [lround()](https://www.nhooo.com/cpp/cpp-library-function-cmath-lround.html) | 返回最接近参数的long int值              |
| [modf()](https://www.nhooo.com/cpp/cpp-library-function-cmath-modf.html) | 将数字分解为整数和小数部分              |
| [nan()](https://www.nhooo.com/cpp/cpp-library-function-cmath-nan.html) | 返回NaN值                               |
| [nearbyint](https://www.nhooo.com/cpp/cpp-library-function-cmath-nearbyint)() | 将参数舍入为使用当前舍入模式            |
| [nextafter()](https://www.nhooo.com/cpp/cpp-library-function-cmath-nextafter.html) | 它表示x在y方向上的下一个可表示值。      |
| [nexttoward()](https://www.nhooo.com/cpp/cpp-library-function-cmath-nexttoward.html) | 它表示x在y方向上的下一个可表示值。      |
| [pow(a,b)](https://www.nhooo.com/cpp/cpp-library-function-cmath-pow.html) | 计算幂 a的b次方                         |
| [restder(x,y)](https://www.nhooo.com/cpp/cpp-library-function-cmath-remainder.html) | 返回x / y的余数                         |
| [remquo(x,y)](https://www.nhooo.com/cpp/cpp-library-function-cmath-remquo.html) | 计算机余数并存储x / y的商               |
| [rint()](https://www.nhooo.com/cpp/cpp-library-function-cmath-rint.html) | 使用当前舍入模式舍入参数                |
| [round()](https://www.nhooo.com/cpp/cpp-library-function-cmath-round.html) | 返回最接近参数的整数值                  |
| [scalbln(x,n)](https://www.nhooo.com/cpp/cpp-library-function-cmath-scalbln.html) | 计算x和FLT_RADX乘以n的乘积。            |
| [scalbn(x,n)](https://www.nhooo.com/cpp/cpp-library-function-cmath-scalbn.html) | 计算x和FLT_RADX乘以n的乘积。            |
| [sin(弧度)](https://www.nhooo.com/cpp/cpp-library-function-cmath-sin.html) | 返回参数的正弦                          |
| [sinh()](https://www.nhooo.com/cpp/cpp-library-function-cmath-sinh.html) | 返回某个角度的双曲正弦                  |
| [sqrt(a)](https://www.nhooo.com/cpp/cpp-library-function-cmath-sqrt.html) | 计算数字a的算术平方根                   |
| [tan()](https://www.nhooo.com/cpp/cpp-library-function-cmath-tan.html) | 返回参数的切线                          |
| [tanh()](https://www.nhooo.com/cpp/cpp-library-function-cmath-tanh.html) | 返回角度的双曲正切                      |
| [trunc()](https://www.nhooo.com/cpp/cpp-library-function-cmath-trunc.html) | 截断数字的符号部分                      |

## *数据/变量类型

### **变量类型

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

使用typedef给类型改名

```c++
typedef int myint//将int改名为myint
myint distance;
```



### **存储类

#### auto

**auto** 关键字用于两种情况：声明变量时根据初始化表达式自动推断该变量的类型、声明函数时函数返回值的占位符

```c++
auto f=3.14;      //double
auto s("hello");  //const char*
auto z = new auto(9); // int*
auto x1 = 5, x2 = 5.0, x3='r';//错误，必须是初始化为同一类型
```

#### static

**static** 存储类指示编译器在程序的生命周期内保持局部变量的存在，而不需要在每次它进入和离开作用域时进行创建和销毁。因此，使用 static 修饰局部变量可以在函数调用之间保持局部变量的值。

static 修饰符也可以应用于全局变量。当 static 修饰全局变量时，会使变量的作用域限制在声明它的文件内。

在 C++ 中，当 static 用在类数据成员上时，会导致仅有一个该成员的副本被类的所有对象共享。

```c++
void func()
{
	static int i = 8; // 局部静态变量
	i++;
	std::cout << "变量 i 为 " << i << endl;
}
void demo() {
	int num = 5;
	while (num--)
	{
		func();
	}
}
//输出：
变量 i 为 9
变量 i 为 10
变量 i 为 11
变量 i 为 12
变量 i 为 13
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

### **右值引用

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

### **修饰指针

const修饰指针（按*和const出现的顺序命名，*是指针，const是常量）

1. const修饰指针--常量指针const*

const int * p 特点：指针的指向可以修改，但是指针指向的值不可以修改

2. const修饰常量--指针常量*const

int * const p = &a; 特点：指针的指向不可以修改，指针指向的值可以修改

3. const既修饰指针又修饰常量

const int * const p = &a; 特点：指针的指向以及指向的值都不能修改

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

## *智能指针

### **独占指针unique_ptr

unique_ptr 独享它指向的对象，同时只有一个unique_ptr指向同一个对象，当这个unique_ptr被销毁时，指向的对象也随即销毁。

基本用法

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

```c++
void demo() {
	unique_ptr<MyPrint> ptr1(new MyPrint("指针1"));
	ptr1.reset();//释放对象
	unique_ptr<MyPrint> p1(new MyPrint("指针1"));
	unique_ptr<MyPrint> p2(new MyPrint("指针2"));
	swap(p1, p2);//交换两个unique_ptr的控制权
	cout << p1.get()->m_name << endl;
}
```

unique_ptr也可像普通指针那样，当指向一个类继承体系的基类对象时，也具有多态性质，如同使用裸指针管理基类对象和派生类对象那样。

unique_ptr 不是绝对安全，如果程序中调用exit()退出，全局的unique_ptr可以自动释放，但局部的unique_ptr无法释放。

```c++
unique_ptr<MyPrint> ptr1(new MyPrint("全局"));
void demo() {
	unique_ptr<MyPrint> ptr1(new MyPrint("局部"));
	exit(0);
}
```

