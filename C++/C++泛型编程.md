# C++泛型编程

## *模板

语法:
template< typename T>

函数声明或定义

template ---声明创建模板
typename ---表面其后面的符号是一种数据类型，可以用class代替

T --通用的数据类型，名称可以替换，通常为大写字母

查看模板参数数据类型typeid(T).name()

### **函数模板

```c++
//函数模板
template<typename T>//声明一个模板 告诉编译器后面的代码中紧跟着的T不要报错
void mySwap(T& a, T& b) {
	T temp = a;
	a = b;
	b = temp;
}
template<class T>
void func() {
	cout << "func函数模板调用" << endl;
}
void demo() {
	int a = 10, b = 20;
	float c = 1.1, d = 2.3;
	//两种方式使用函数模板
	//1、自动类型推导 根据传入的参数自动识别
	mySwap(a, b); mySwap(c, d);
	//mySwap(a, c); 自动类型推导 必须推导出一致的数据类型T才可以使用
	//2、显示指定类型
	mySwap<float>(c, d);

	//模板必须要确定出T的数据类型才可以使用
	//func();
	func<int>();
}
```

#### ***普通函数与函数模板的区别

普通函数调用时可以发生自动类型转换（隐式类型转换)；
函数模板调用时，如果利用自动类型推导，不会发生隐式类型转换，如果利用显示指定类型的方式，可以发生隐式类型转换；

```c++
int myAdd(int a, int b) {//普通函数
	return a + b;
}
template<typename T>
T _myAdd(T a, T b) {//函数模板
	return a + b;
}
void demo() {
	int a = 10;
	char c = 'c';
	cout << myAdd(a, c);//正确 将char类型的c隐式转换为int

	//cout << _myAdd(a, c);//错误 自动类型推导时 不会发生隐式转换
	cout << _myAdd<int>(a, c);//正确 显示指定类型 发生隐式转换
}
```

调用规则如下:

1.如果函数模板和普通函数都可以实现，优先调用普通函数

2.可以通过空模板参数列表来强制调用函数模板

3.函数模板也可以发生重载

4.如果函数模板可以产生更好的匹配,优先调用函数模板

```c++
_myAdd<>(a,b);//通过空模板参数列表来强制调用函数模板
```

#### ***模板的局限性

```c++
template<typename T>
void f(T a, T b) {//传入的是数组 就无法实现了
	a = b;
};

class Person {
public:
	string m_Name;
	int m_Age;
};
template<typename T>
bool myCompare(T a, T b) {//传入的是Person自定义数据类型 也无法实现
	if (a == b)return true;
	else return false;
};
//解决方法
//利用具体化Person的版本实现代码，具体化优先调用
template<> bool myCompare(Person& p1, Person& p2) {
	if (p1.m_Name == p2.m_Name && p1.m_Age == p2.m_Age) {
		return true;
	}
	else {
		return false;
	}
}
```

### **类模板

```c++
template<class NameType,class AgeType>
class Person {
public:
	NameType m_Name;
	AgeType m_Age;

	Person(NameType name, AgeType age) {
		this->m_Name = name;
		this->m_Age = age;
	}
};
```

#### ***类模板与函数模板的区别

类模板与函数模板区别主要有两点:

1 类模板没有自动类型推导的使用方式 只有显式指定类型

⒉类模板在模板参数列表中可以有默认参数

```c++
void demo() {
	//Person p("Amaz1ng", 18);//错误 无法使用自动类型推导
	Person<string, int>p("Amaz1ng", 18);//正确 只能显式指定类型
	//修改成template<class NameType, class AgeType = int>默认参数
	//可以直接写成Person<string>p("Amaz1ng", 18);
}
```

#### ***类模板与普通类创建成员函数时机的区别

类模板中成员函数和普通类中成员函数创建时机是有区别的:

普通类中的成员函数一开始就可以创建
类模板中的成员函数在调用时才创建

#### ***类模板对象做函数参数

类模板实例化出的对象，向函数传参的方式共有三种: 

1.指定传入的类型  ---直接显示对象的数据类型

```c++
void printPerson1(Person<string, int>& p) {}
```

2.参数模板化          ---将对象中的参数变为模板进行传递 

```c++
template<class T1,class T2>
void printPerson2(Person<T1, T2>& p) {
	cout << "T1的数据类型为: " << typeid(T1).name() << endl; 
	cout << "T2的数据类型为: " << typeid(T2).name() << endl; 
}
```

3.整个类模板化      ---将这个对象类型模板化进行传递

```c++
template<class T>
void printPerson3(T& p) {
	cout << "T的数据类型为: " << typeid(T).name() << endl; 
}
```

#### ***类模板与继承

当类模板碰到继承时，需要注意一下几点:

当子类继承的父类是一个类模板时，子类在声明的时候，要指定出父类中T的类型 如果不指定，编译器无法给子类分配内存

```c++
template<class T>
class Base {
	T m;
};
//class Son:public Base{}; //错误 必须知道父类T的类型
class Son:public Base<int>{};
```

如果想灵活指定出父类中T的类型，子类也需变为类模板

```c++
template<class T>
class Base {
	T m;
};
//如果想灵活指定出父类中T的类型，子类也需变为类模板
template<class T1,class T2>
class Son :public Base<T2> {
	T1 obj;
};
void demo() {
	Son<int, char> p;
}
```

#### ***类模板成员函数类外实现

```c++
template<class T1,class T2>
class Person {
public:
	T1 m_Name;
	T2 m_Age;
	Person(T1 name, T2 age);//类内声明
};
//类外实现
template<class T1, class T2>
Person<T1,T2>::Person(T1 name, T2 age) {
	this->m_Name = name;
	this->m_Age = age;
}

```

类模板分文件编写 .hpp

类模板中成员函数创建时机是在调用阶段，导致分文件编写时链接不到解决:
解决方式1:直接包含.cpp源文件 让编译器先去看.cpp的具体实现是用模板  .cpp中又包含了.h
解决方式2∶将声明和实现写到同一个文件中，并更改后缀名为.hpp，hpp是约定的名称，并不是强制

#### ***类模板与友元 类内实现 类外实现

全局函数类内实现-直接在类内声明友元即可

```c++
template<class T1, class T2>
class Person {
	//全局函数 类内实现
	friend void printPerson(Person<T1, T2>p) {
		cout << p.m_Age << p.m_Name;
	}
public:
	T1 m_Name;
	T2 m_Age;
	Person(T1 name, T2 age) {
		this->m_Name = name;
		this->m_Age = age;
	}
};
void demo() {
	Person<string, int>p("Amaz1ng", 18);
	printPerson(p);
}

```

全局函数类外实现–需要提前让编译器知道全局函数的存在

```c++
//提前让编译器知道Person类存在
template<class T1, class T2>
class Person;
//类外实现
template<class T1, class T2>
void printPerson(Person<T1, T2>p) {
	cout << p.m_Age << p.m_Name;
}
template<class T1, class T2>
class Person {
	//全局函数 类内声明 加上空模板参数列表
	//需要让编译器提前知道这个函数的存在 故类外实现写在上面
	friend void printPerson<>(Person<T1, T2>p);
public:
	T1 m_Name;
	T2 m_Age;
	Person(T1 name, T2 age) {
		this->m_Name = name;
		this->m_Age = age;
	}
};
void demo() {
	Person<string, int>p("Amaz1ng", 18);
	printPerson(p);
}
```

### **可变参数模板 C++11
参数包的展开方式：
1.模板特化+递归
2.模板特化+继承

#### 函数模板的可变参数

```c++
void show() {};//基本情况:当没有剩余参数时，终止递归

template<typename T, typename... Args> //... Args称为折叠参数
//thisArg用T来定义 表示递归取出来的已展开的参数 args用Args定义 表示尚未展开的参数包
void show(T thisArg, Args...args) {
	cout << thisArg << endl;//显示本次展开的参数
	cout << "还有" << sizeof...(args) << "个参数未展开" << endl;
	show(args...);//递归调用自身 继续展开参数
}

void demo() {
	show(2.12, 5, "hello", 'a');
}
```
如果一个函数要两个参数 第二个参数是可变参数 就用一个普通模板嵌套一个可变参数模板


#### 类模板的可变参数

```c++
// 基本情况：当没有剩余的参数时，停止递归
template <typename... Ts>
class Tuple {};

//第一个参数递归取出来的已展开的参数，剩余的参数为尚未展开的参数包
template <typename T, typename... Ts>
class Tuple<T, Ts...> {
private:
	T value; // 头部元素
	Tuple<Ts...> tail; // 尾部元组
public:
	// 构造函数，接受已展开的参数和剩余元素
	Tuple(T t, Ts... ts) : value(t), tail(ts...) {}
	// 获取已展开的参数的方法
	T getHead() const {
		return value;
	}
	// 获取参数包的方法
	Tuple<Ts...> getTail() const {
		return tail;
	}
};
void demo() {
	// 创建一个包含整数、浮点数和字符串的元组
	Tuple<int, double, std::string> myTuple(1, 3.14, "Hello");
	std::cout << "Head: " << myTuple.getHead() << std::endl;
	std::cout << "Tail Head: " << myTuple.getTail().getHead() << std::endl;
	std::cout << "Tail Tail Head: " << myTuple.getTail().getTail().getHead() << std::endl;
}
```

## *STL标准模板库

STL几乎所有的代码都采用了模板类或者模板函数

STL大体上分为6大组件:容器(container)、算法(algorithm)、迭代器(iterator)：扮演容器与算法之间的胶合剂 算法要通过迭代器才能访问到容器里的内容，每个容器都有专属的迭代器(类似指针)、仿函数(functors)、配接器(adapters)、空间配置器(allocators)


### **STL迭代器
每个容器都有自己专属的迭代器 迭代器的使用非常类似于指针
迭代器种类:

```c++
input_iterator输入迭代器 对数据的只读访问  只读，支持++、==、!=
output_iterator输出迭代器 对数据的只写访问  只写，支持++
forward_iterator前向迭代器 读写操作,并能向前推进迭代器  读写，支持++、==、!=
bidirectional_iterator双向迭代器 读写操作,并能向前和向后操作  读写，支持++、--
random_access_iterator随机访问迭代器 读写操作,可以以跳跃的方式访问任意数据  读写，支持++、--、[n]、 -n、<、<=、>、>=
```
“修饰迭代器”
```c++
void demo(){
	std::vector<int>v;
	const std::vector<int>::iterator it1 = v.begin(); //it1的作用像个 T* const
	*it1 = 10;//正确 指针指向的值可以修改
	//it1++;//错误 指针的指向不能修改
	std::vector<int>::const_iterator it2 = v.begin();//it2的作用像个const T*
	//*it2 = 10;//错误 指针指向的值不可修改
	it2++;//正确 指针的指向可以修改
	std::vector<int>::const_pointer ptr = v.data();//data()返回指向v第一个元素的指针 ptr类似T* const
	std::vector<int>::const_reference ref = v[0]; //ref类似const T&
}
```

### **STL常见容器

#### ***vector

#include< vector > #include< array > 单端数组 随机访问迭代器

vector与array非常相似，也称单端数组。但是array是静态空间的，vector可以动态扩展空间(配置原则：如果原大小为0，则配置1个元素大小，如果原大小不为0，则配置原大小的两倍)

动态扩展空间不是在原空间后面接续新空间，而是另外配置原大小两倍的空间，前面一半空间将原内容拷贝过来，后半部分准备构造新元素，然后释放原空间。

因此一旦引起空间重新配置，指向原vector的所有迭代器都失效了！！！

底层是由三个指针实现的，分别是头指针(表示目前使用空间的开头)、尾指针(表示目前使用空间的末尾)、可用空间尾指针(预留空间的末尾)
![image](https://github.com/Amaz1ngJR/Technology/assets/83129567/86a50249-2a08-476f-95ac-fc72e545ade2)


##### vector构造函数

```c++
void demo() {
	vector<int>a = { 1,2,3,4,5 };//初始化列表
	vector<int>a{ 1,2,3,4,5 };//初始化列表
    
	vector<int>v0;//默认构造
	vector<int>v1(3);//构造一个大小为3的v1
	vector<int>v2(v1.begin(), v1.end());//将v1[)区间中元素拷贝给v2
	vector<float>v3(3, 6.66);//将3个6.66拷贝给v3
	vector<float>v4(v3);//拷贝构造函数
}
```

##### vector赋值操作

```c++
void demo() {
	vector<int>v1, v2;
	//赋值
	//operator=
	v1 = v2;//将v2赋值给v1
	//assign
	v1.assign(v2.begin(), v2.end());//将v2[)区间赋值给v1
	v1.assign(3, 6);//将3个6赋值给v1 如果v1的大小大于3 那么大于部分元素清空(这是和resize的区别)
}
```

##### vector容量、大小操作

```c++
void demo() {
	vector<int>v1;
    	v1.reserve(10);// 预留10个元素的内存空间 容量 用来减少动态扩展的次数 
    	//cout << v1[5] << endl;//预留位置不初始化 元素不可访问
	if (v1.empty()) {
		cout << "v1是空的" << endl;
	}
	cout << "v1的容量为 " << v1.capacity() << endl;
	cout << "v1中的元素个数为 " << v1.size() << endl;
	v1.resize(20);//重新指定容器长度为20 若容器变长 以默认值填充新位置 变短则删除超出部分
	v1.resize(20, 100);//将填充的默认值修改成100
}
void demo() {//区分vector<int>v(size) v.resize(size)和v.reserve(size)
	vector<int>v1(10), v2;
	v2.resize(10);//分配内存 并用默认值初始化
	cout << "v1的大小为 " << v1.size() <<
		" v2的大小为 " << v2.size() << endl;
	//v1的大小为 10 v2的大小为 10 
	for (int i = 0; i < 10; i++) {
		v1.emplace_back(i);
		v2.push_back(i);
	}
	cout << "v1的大小为 " << v1.size() <<
		" v2的大小为 " << v2.size() << endl;
	//v1的大小为 20 v2的大小为 20
	for (auto it = v1.begin(); it != v1.end(); it++) {
		cout << *it;//能够访问前面10个元素 都为0
	}

	vector<int>v3;
	v3.reserve(10);//只分配内存
	for (int i = 0; i < 10; i++) {
		v3.emplace_back(i);
	}
	cout << "v3的大小为 " << v3.size();//v3的大小仍为10
}
```

由于vector是动态扩容的 预留容量会随着插入次数的增多而变大

当vector缩小长度的时候 预留容量不会跟着缩小  

可以通过swap巧妙收缩内存

```c++
void demo() {
	vector<int>v1;
	for (int i = 0; i < 100000; i++) {
		v1.emplace_back(i);
	}
	//由于vector是动态扩容的 预留容量会随着插入次数的增多而变大
	cout << "v1的大小为" << v1.size() << "; v1的容量为" << v1.capacity() << endl;
	v1.resize(10);//将v1大小缩小至10 但是预留的容量不会跟着缩小
	cout << "v1的大小为" << v1.size() << "; v1的容量为" << v1.capacity() << endl;
	//使用swap巧妙收缩内存
	vector<int>(v1).swap(v1);//匿名对象
	cout << "v1的大小为" << v1.size() << "; v1的容量为" << v1.capacity() << endl;
}
```



##### vector插入、删除和去重

```c++
void demo() {
	struct person {
		int age;
		int id;
		person(int a, int b) :age(a), id(b) {}
	};
	vector<person>v1;
	person p1(18, 123);
	//插入
	v1.push_back(p1);//容器尾部插入
	//emplace_back较于push_back可以直接在容器内部进行构造 避免了拷贝构造或者移动构造 如果插入的是构造好的对象等同于push_back
	v1.emplace_back(18, 123);//容器尾部插入
	v1.insert(v1.begin(), p1);//在迭代器指向位置插入
	v1.insert(v1.begin(), 2, p1);//插2个进去
	v1.emplace(v1.begin(), p1);//类比emplace_back
	//删除
    	v1.pop_back();//容器尾部删除
	v1.erase(v1.begin());//删除迭代器指向的元素
	v1.erase(v1.begin(), v1.end());//删除[)区间
	v1.clear();//清空
}
```
emplace_back/emplace
```c++
void demo() {
	vector<vector<int>>v;
	v.emplace_back(1, 2);//调用vector<int>(1,2)
	v.emplace_back(3, 4);//调用vector<int>(3,4)
	for (const auto& vv : v) {//输出2;4,4,4;
		for (const int& vvv : vv) 
			cout << vvv << " ";
		cout << endl;
	}
	v.clear();
	//initializer_list<>初始化列表模板
	v.emplace_back(initializer_list<int>{1, 2});
	v.emplace_back(initializer_list<int>{3, 4});
	//v.emplace_back(vector<int>{3, 4});
	//v.push_back({3, 4});
	for (const auto& vv : v) {//输出1,2;3,4
		for (const int& vvv : vv)
			cout << vvv << " ";
		cout << endl;
	}
}
```
去重
```c++
void demo() {
	vector<vector<int>>test;
	test.emplace_back(initializer_list<int>{ 8,8,8,8 });
	test.emplace_back(initializer_list<int>{ 6,6,6 });
	test.emplace_back(initializer_list<int>{ 8,6,6,6 });
	test.emplace_back(initializer_list<int>{ 8,8,8,8 });
	test.emplace_back(initializer_list<int>{ 8,8,8,8,1 });
	sort(test.begin(), test.end());//先排序
	//unique将相邻的重复元素放到容器末尾并返回一个新的end迭代器
	auto newend = unique(test.begin(), test.end());
	test.erase(newend, test.end());//删除容器末尾的多余重复元素
	for (const auto& v : test) {
		for (const auto& vv : v) {
			cout << vv << " ";
		}
		cout << endl;
	}
}
```



##### vector数据访问及使用迭代器遍历

```c++
//数据访问
void demo() {
	vector<int>a = { 1,2,3,4,5 };
	for (int i = 0; i < a.size(); i++) {
		//如果使用a[i]来访问一个越界的元素 
		//可能会访问到未知的内存区域 
		//这可能引发程序崩溃或产生不可预测的结果
		cout << a[i] << endl;
        //cout << a[6] << endl;
		//使用成员函数at()来访问容器元素更安全
		//与a[i]不同 a.at(i)会进行边界检查
		//如果尝试访问越界的元素 会抛出一个std::out_of_range异常
		cout << a.at(i) << endl;
        //cout << a.at(6) << endl;//分别解注释这行和a[6]看一下区别
	}
	cout << "容器中的第一个元素为" << a.front() << endl;
	cout << "容器中的最后一个元素为" << a.back() << endl;
}
```

```c++
//使用迭代器遍历
void demo() {
	vector<int>v = { 1,2,3,4,5 };
	//第一种遍历方式
	vector<int>::iterator itBegin = v.begin();//指向容器第一个元素的位置
	vector<int>::iterator itEnd = v.end();//指向容器最后一个元素的下一个位置
	while (itBegin != itEnd) {
		cout << *itBegin;
		itBegin++;
	}
	//第二种遍历方式
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++) {
		cout << *it;
	}
	//逆序遍历
	for (vector<int>::reverse_iterator it = v.rbegin(); it != v.rend(); it++) {
		cout << *it;
	}
	//第三种遍历方式#include<algorithm>标准算法头文件
	for_each(v.begin(), v.end(), [](int val) {cout << val; });
}
```

```c++
class Person {
public:     
	string m_name;
	int m_age;
};
void demo() {
	vector<Person>v1;
	for (vector<Person>::iterator it = v1.begin(); it != v1.end(); it++) {
		cout << (*it).m_name << (*it).m_age;
		cout << it->m_name << it->m_age;
	}
	vector<Person*>v2;
	for (vector<Person*>::iterator it = v2.begin(); it != v2.end(); it++) {
		cout << (*it)->m_name << (*it)->m_age;
	}
}
```

#### ***list

#include< list >双向循环链表 双向迭代器  #include< forward_list >单向链表 前向迭代器

list的插入insert和接合splice不会使迭代器失效

![image](https://github.com/Amaz1ngJR/Technology/assets/83129567/393abe92-98a4-4f87-86ea-f0c978f3e166)


##### list构造函数

```c++
void demo() {
	list<int> p;//默认构造
	list<int> p1(p.begin(), p.end());//将p[)区间中元素拷贝给p1
	list<int> p2(3);//构造一个大小为3的v1
	list<int> p3(3, 6);//将3个6拷贝给p3
	list<int> p4(p3);//拷贝构造函数
}
```

##### list赋值和交换

```c++
void demo() {
	list<int> p1, p2;
	vector<int>v = { 1,2,3 };
	//赋值
	//operator=
	p1 = p2;//将v2赋值给v1
	//assign
	p1.assign(v.begin(), v.end());//将v[)区间赋值给p1
	for (const auto& l : p1) {
		cout << l;
	}
	p1.assign(3, 6);//将3个6赋值给p1
	p2.swap(p1);//互换 p1 p2
}
```

##### list大小操作

```c++
void demo() {
	list<int>p1;
	if (p1.empty()) {
		cout << "p1是空的" << endl;
	}
	cout << "p1中的元素个数为 " << p1.size() << endl;
	p1.resize(20);//重新指定容器长度为20 若容器变长 以默认值填充新位置 变短则删除超出部分
	p1.resize(20, 100);//将填充的默认值修改成100
}
```

##### list插入和删除

```c++
void demo() {
	list<int>p1;
	vector<int>v1;
	//插入
	p1.push_back(1);//容器尾部插入
	p1.emplace_back(1);//容器尾部插入
	p1.push_front(1);//容器开头插入
	p1.emplace_front(1);//容器开头插入
	p1.insert(p1.begin(), 1);//在迭代器指向位置插入 返回新数据的位置
	p1.insert(p1.begin(), 2, 1);//插2个1进去 无返回值
	p1.insert(p1.begin(), v1.begin(), v1.end());//在迭代器指向位置插入[)数据 无返回值
	p1.emplace(p1.begin(), 1);//类比emplace_back
	//删除
	p1.pop_back();//容器尾部删除
    	p1.pop_front();//容器开头删除
	p1.erase(p1.begin());//删除迭代器指向的元素
	p1.erase(p1.begin(), p1.end());//删除[)区间
	p1.remove(1);//将容器中所有是1的元素移动到容器末尾 并返回新end 后续使用erase真正删除这些元素
	p1.clear();//清空
}
```

##### list数据访问

```c++
void demo() {
	list<int>p1;
	p1.front();//返回第一个元素
	p1.back();//返回最后一个元素
}
```

#### ***string

\#include< string > 随机访问迭代器

##### string构造函数

```c++
void demo() {
	const char* str = "hello";
	string str1;//默认构造 创建一个空字符串
	string str2(str);//使用字符串(const char* s)初始化
	string str3(str1);//使用(const string& s)初始化
	string str4(3, 'a');//使用3个char a初始化
}
```

##### string赋值操作

```c++
void demo() {
	string str1;
	string str2;
	const char* a = "a";
	//赋值操作
	str1 = "a";
	str1 = 'a';
	str1 = a;
	str2 = str1;
	str2.assign(a);
	str2.assign("abc");
	str1.assign("abcdklg", 4);//将"abcdklg"的前4个字符赋值给str1
	str1.assign(str2);
	str1.assign(3, 'a');//将3个字符'a'赋值给str1
}
```

##### string随机访问和比较

```c++
void demo() {
	string str = "abcd";
	cout << str[2] << str.at(1);
    
}
```

```c++
void demo() {
	string a = "a";
	string b = "b";
	int ans = a.compare(b);
	if (ans == 0) cout << "a=b";
	else if (ans == 1)cout << "a>b";
	else if (ans == -1)cout << "a<b";
}
```

##### string拼接与截取

```c++
//拼接
void demo() {
	string str1 = "我";
	//拼接
	str1 += "爱玩";//+string
	str1 += ':';//+char
	string str2 = "GTA5 Battlefield1";
	str1 += str2;
	cout << "str1 = " << str1 << endl;
	string str3 = "I";
	str3.append(" love play");//把参数string拼接到str3后面
	str3.append("games abcde", 5);//从"games abcde"中截取前5个字符拼接到str3后面
	str3.append(str2, 5, 12);//从str2中下标5开始截取前12个字符
	str3.append(3, '!')//末尾插入3个char
	cout << "str3 =" << str3 << endl;
}
```

```c++
//截取
void demo() {
	string str = "789123";
	cout << str.substr(3, 3);//截取str下标3开始(包含3)的3个字符
	cout << srt.subsrt(3);//截取str下标3开始（包含3）的后缀字符
	//提取由空格分割的单词words
	string words = "I have a big plan";
	string word; vector<string> all;
	istringstream iss(words); //#include<sstream>
	while (iss >> word) {
		all.emplace_back(word);
	}
	//提取由,分割的汉字Words
	string Words = "我,爱,C++";
	istringstream sstream(Words);
	while (getline(sstream, word, ',')) {
		cout << "字" << word << endl;
	}
	//提取字符串中不同类型的数据
	string inputString = "42 3.14 hello";
	istringstream isss(inputString);
	int intValue; double doubleValue; string stringValue;
	isss >> intValue >> doubleValue >> stringValue;
	if (isss.fail()) {//输入与预期不符，使用fail()函数检查流的状态
		std::cout << "Failed to parse input." << std::endl;
	}
	else cout << intValue << " " << doubleValue << " " << stringValue;
}
```

##### string查找和替换

```c++
void demo() {
	string str = "Amaz1ng";
    	if(!str.empty())cout<<"不空";
	//find从左向右查找 
	int ans = str.find("az1");//从下标0开始查找"az1"第一次出现的位置
	ans = str.find('1', 2);//从下标2开始查找'1'第一次出现的位置
	//rfind是从右向左查找 用法类比find
	ans = str.rfind("az1", 6);//从下标6开始向右查找"az1"最后一次出现的位置
	//替换
	str.replace(1, 3, "1A");//从下标1开始3个字符替换成"1A"
	cout << str;

	 // 检查是否以 "Ama" 开头
	if (str.starts_with("Ama")) {
		std::cout << "The string starts with 'Ama'\n";
	}
	// 检查是否以单个字符'A'开头
	if (str.starts_with('A')) {
		std::cout << "The string starts with 'A'\n";
	}
}
```

##### string插入和删除

```c++
void demo() {
	string str = "Amaz1ng";
	//插入
	str.insert(7, "!!!");//下标7插入"!!!"
	str.insert(0, 3, '!');//下标0开始插入3个字符'!'
	str.push_back('!');

	cout << str;
	//删除
	str.pop_back();//删除末尾元素
	str.erase(0, 1);//删除下标0开始的1个元素

	cout << str;
}
```

##### string与数字的相互转换

```c++
//将int ,double 等类型转成字符串to_string C++11
void demo() {
	double number = 12345.5;
	//使用to_string C++11
	string strnumber = to_string(number);
	cout << strnumber << endl;
	//使用字符串流std::stringstream
	stringstream ss;
	ss << number;
	string strnumber1 = ss.str();
	cout << strnumber1 << endl;
}
```

```c++
void demo() {
	//将字符串转成数字(10进制， 转成2进制的话stoi(s, nullptr, 2) )
	//如果字符串中没有数字的话，将会抛出"invalid_argument"的异常；
	//如果字符串中的数字转换后超过int/float/double的范围，将会抛出"out_of_range"的异常
	string pi = "-3.14";
	int a = stoi(pi);//-3
	float b = stof(pi);//-3.14
	double c = stod(pi);//-3.14
	cout << a << " " << b << " " << c;
	string str = "98745";
	if (stoi(str.substr(1, 2)) == 87)cout << "从下标1开始截取的两个字符组成的数字为87";
	//将字符转成数字
	int num = stoi(string(1, str[2]));//7
}
```

#### ***deque

\#include< deque > 双端数组 随机访问迭代器

![image](https://github.com/Amaz1ngJR/Technology/assets/83129567/3c3de878-905c-4ea2-89e7-8fe486bfec73)
![image](https://github.com/Amaz1ngJR/Technology/assets/83129567/3b4a7465-f068-40c6-98de-db522c2c2055)

中控器是一个双向链表 里面存的是数组

##### deque构造函数

```c++
void demo() {
	deque<int> deque1;// 默认构造函数
	deque<int> deque2(5); // 包含5个默认初始化的int元素
	deque<int> deque3(3, 42); // 包含3个值为42的int元素
	deque<int> deque4(deque3.begin(), deque3.end());//区间[)拷贝
	deque<int> deque5(deque4);// 拷贝构造函数
	deque<int> deque6(move(deque5));// 移动构造函数C++11
}
```

##### deque赋值操作

```c++
void demo() {
	deque<int> d1, d2;
	//赋值
	d1 = d2;
	d1.assign({ 1,2,3 });
	d1.assign(d2.begin(), d2.end());//区间[)赋值
	d1.assign(3, 4);//赋值3个4
}
```

##### deque大小操作

```c++
void demo() {
	//同vector
	deque<int> d1;
	if (!d1.empty()) {
		cout << d1.size();
	}
	d1.resize(10);
	d1.resize(10, -1);
}
```

##### deque插入和删除

```c++
//基本同vector
void demo() {
	deque<int> d1;
	//插入
	d1.push_back(1);
	d1.emplace_back(1);
	d1.push_front(1);
	d1.emplace_front(1);
	d1.insert(d1.begin(), 1);//在迭代器指向位置插入
	d1.insert(d1.begin(), 2, 1);//插2个进去
	d1.emplace(d1.begin(), 1);//类比emplace_back
	//删除
	d1.pop_back();
	d1.pop_front();
	d1.erase(d1.begin());//删除迭代器指向的元素
	d1.erase(d1.begin(), d1.end());//删除[)区间
	d1.clear();//清空
}
```

##### deque数据访问

```c++
void demo() {
	deque<int> d1 = { 1,2,3,4 };
	cout << d1[1] << d1.at(2);
	cout << d1.front() << d1.back();
}
```

#### ***stack

栈#include< stack > 没有迭代器

![image](https://github.com/Amaz1ngJR/Technology/assets/83129567/db939b7c-4484-4bb5-adff-1ece912a478b)


```c++
//栈的所有操作
void demo() {
	stack<int> s1;//默认构造
	stack<int>s2(s1);//拷贝构造
	s1.swap(s2);//交换
	if (!s1.empty()) {//非空
		cout << s1.size();//大小
	}
	// 入栈操作
	s1.push(1);
	s1.emplace(1);
	// 获取栈顶元素
	cout << s1.top();
	// 出栈操作
	s1.pop();
}
```

#### ***queue

\#include< queue > 队列

![image](https://github.com/Amaz1ngJR/Technology/assets/83129567/670f3411-10fa-4346-9391-7d80569ac0be)


```c++
//队的所有操作
void demo() {
	queue<int> q1;//默认构造
	queue<int>q2(q1);//拷贝构造
	q1.swap(q2);//交换
	if (!q1.empty()) {//非空
		cout << q1.size();//大小
	}
	// 入队操作 在队尾
	q1.push(1);
	q1.emplace(1);
	// 出队操作 在队头
	q1.pop();
	//返回元素
	q1.front();//队头元素
	q1.back();//队尾元素
}
```

##### priority_queue优先队列

```c++
//优先队列所有操作
void demo() {
	vector<int>nums;
	priority_queue<int> q, q1;//默认大根堆底层容器为vector top是最大的
	priority_queue<int, vector<int>, std::greater<int>> q2;//改成小根堆 top是最小的
	priority_queue<int, std::deque<int>>q3;//底层容器改为双端数组
	priority_queue<int>q4(nums.begin(), nums.end());//从容器中构造优先队列
	q1.swap(q);
	if (!q1.empty()) {
		cout << q1.size();
	}
	q1.emplace(1); //入堆
	q1.push(1); //入堆
	q1.pop();//弹出队首
	q1.top();//返回队首
}
```

#### ***set族

#include< set >  双向迭代器    #include< unordered_set >  #include< unordered_multiset > 前向迭代器

| 集合               | 底层实现 | 是否有序 | 数值是否可以重复 | 能否更改数值 | 查询效率 | 增删效率 |
| ------------------ | -------- | -------- | ---------------- | ------------ | -------- | -------- |
| std::set           | 红黑树   | 有序     | 否               | 否           | O(log n) | O(log n) |
| std::multiset      | 红黑树   | 有序     | 是               | 否           | O(logn)  | O(logn)  |
| std::unordered_set | 哈希表   | 无序     | 否               | 否           | O(1)     | O(1)     |

```c++
//set常用操作
void demo() {
	set<int> s1, s2;//默认构造
	set<int>s3(s1);//拷贝构造
	s1 = s2;//赋值
	s1.swap(s2);//交换
	if (!s1.empty())cout << s1.size();
	//插入操作
	//set/unordered_set有一个插入的重载版本会返回一个pair<插入位置的迭代器,bool是否插入成功>
	auto it = s1.insert(1).first; cout << *it<<" ==1";
	if (s1.emplace(2).second)cout << "成功插入";
	//删除操作
	s1.erase(s1.begin());
	s1.erase(s1.begin(), s1.end());
	s1.erase(1);//删除元素值为1的元素
	s1.clear();
	//查找操作
	s1.find(1);//基于二分的O(log n)查找1是否存在 存在返回迭代器 不存在返回s1.end()
	s1.count(1);//对于set 只能是0/1
}
```
哈希表相关知识

哈希映射方式
```
直接寻址法：如果键的范围较小且密集，则可以使用一个数组，其中键作为索引，值作为存储的数据。这种方法简单高效，但仅适用于键集非常有限的情况。
除留余数法：这是最常用的哈希方法之一，通过取键值除以表大小的余数来确定键在哈希表中的位置。选择合适的表大小（通常为质数）对于减少冲突非常重要。
折叠法：将键分成几部分，然后把这些部分加在一起（或者进行其他运算），用所得结果作为哈希值。
平方取中法：先对键求平方，然后取中间几位作为哈希值。这种方法试图利用数字分布更均匀的部分。
基数转换法：将键看作是某种基数下的数，然后转换成另一个基数下的数，并取该数的一部分作为哈希值。
```
处理哈希冲突的方法
```
链地址法（Separate Chaining）【STL中的哈希表使用该方法来解决哈希冲突】：每个哈希表条目实际上是指向一个链表（或其他数据结构如红黑树）的指针/桶（bucket）。所有哈希到同一位置的元素都存储在这个链表中。查找、插入和删除操作需要遍历相应的链表。

开放定址法（Open Addressing）：
	线性探测（Linear Probing）：当发生冲突时，检查哈希表中的下一个位置（或之前的位置），直到找到空位为止。
	二次探测（Quadratic Probing）：与线性探测类似，但跳过的间隔按照二次方增长（如 1, 4, 9, 16...）。
	双重哈希（Double Hashing）：使用第二个哈希函数来决定在遇到冲突时应跳过的步长。
再哈希法（Rehashing）：当哈希表变得过于拥挤时，创建一个新的更大规模的哈希表，并使用新的哈希函数重新插入所有元素。
公共溢出区法：除了主哈希表外，还维护一个单独的溢出区域来存放所有发生冲突的元素。
```
扩容机制
```
创建新的存储桶数组：新数组的大小通常是当前存储桶数组大小的两倍（或者更大的质数倍，具体取决于实现）。
重新哈希所有现有元素：由于存储桶的数量改变了，所有现有的元素都需要根据新的存储桶数量重新计算哈希值，并被放置到正确的位置上。
更新负载因子（哈希表中存储的元素数量/哈希表的桶数量）阈值：扩容后，负载因子降低，这有助于保持良好的性能特性。
	std::unordered_map<int, int> umap;
	// 获取当前负载因子
	float current_load_factor = umap.load_factor();
	std::cout << "Current Load Factor: " << current_load_factor << std::endl;
	// 设置最大负载因子
	umap.max_load_factor(0.7f);
```

#### ***map族

\#include< map > 双向迭代器     #include< unordered_map >  #include< unordered_multimap > 前向迭代器

| 映射               | 底层实现 | 是否有序 | 数值是否可以重复 | 能否更改数值 | 查询效率 | 增删效率 |
| ------------------ | -------- | -------- | ---------------- | ------------ | -------- | -------- |
| std::map           | 红黑树   | key有序  | key不可重复      | key不可修改  | O(logn)  | O(logn)  |
| std::multimap      | 红黑树   | key有序  | key可重复        | key不可修改  | O(log n) | O(log n) |
| std::unordered_map | 哈希表   | key无序  | key不可重复      | key不可修改  | O(1)     | O(1)     |

```c++
//map常见操作
void demo() {
	map<int,int> s1, s2;//默认构造
	map<int,int>s3(s1);//拷贝构造
	s1 = s2;//赋值
	s1.swap(s2);//交换
	if (!s1.empty())cout << s1.size();
	//插入操作
	s1.insert(pair<int, int>(1, 2));
	s1.insert(make_pair(2, 1));
	s1.insert(map<int, int>::value_type(3, 2));
	s1[4] = 3;//不建议使用 插错了还是会创建的
	s1.emplace(1, 3);
	//删除操作
	s1.erase(s1.begin());
	s1.erase(s1.begin(), s1.end());
	s1.erase(1);//删除元素值为1的元素
	s1.clear();
	//查找操作
	s1.find(1);//基于二分的O(log n)查找1是否存在 存在返回迭代器 不存在返回s1.end()
	s1.count(1);//对于map 查找的是key 也只能是0/1 
}
```
```c++
//unordered_map动态扩容 默认采用std::hash作为哈希函数 使用链地址法解决哈希冲突
struct PairHash {
	template <class T1, class T2>
	std::size_t operator () (const std::pair<T1, T2>& p) const {
		auto hash1 = std::hash<T1>{}(p.first);
		auto hash2 = std::hash<T2>{}(p.second);
		return hash1 ^ hash2;
	}
};
struct PairEqual {
	template <class T1, class T2>
	bool operator () (const std::pair<T1, T2>& lhs, const std::pair<T1, T2>& rhs) const {
		return lhs.first == rhs.first && lhs.second == rhs.second;
	}
};
unordered_map<pair<double, double>, int, PairHash, PairEqual>um;

auto pairHash = [](const auto& p) {
	auto hash1 = std::hash<decltype(p.first)>{}(p.first);
	auto hash2 = std::hash<decltype(p.second)>{}(p.second);
	return hash1 ^ hash2;
};
auto pairEqual = [](const auto& lhs, const auto& rhs) {
	return lhs.first == rhs.first && lhs.second == rhs.second;
};
std::unordered_map<std::pair<double, double>, int, decltype(pairHash), decltype(pairEqual)> um(10, pairHash, pairEqual);//10为初始化桶数 为预期元素数量的 1.0 到 1.5 倍
```
### **STL函数对象(仿函数)

重载函数调用操作符的类。其对象常称为函数对象

函数对象使用重载的()时，行为类似函数调用，也叫仿函数

函数对象(仿函数)是一个类，不是一个函数

#### ***仿函数的特点:

```c++
// 1、函数对象在使用时，可以像普通函数那样调用,可以有参数,可以有返回值
class MyAdd {
public:
	int operator()(int v1, int v2) {
		return v1 + v2;
	}
};
void demo() {
	MyAdd myAdd;
	cout << myAdd(12, 10) << endl;
}
```

```c++
// 2、函数对象可以有自己的状态
class MyPrint{
public:
	MyPrint() {
		count = 0;
	}
	void operator() (string test) {
		cout << test << endl;
		count++;//统计使用次数
	}
	int count; //内部自己的状态
};
void demo() {
	MyPrint myPrint;
	myPrint("hello world"); myPrint("hello world"); myPrint("hello world");
	cout << "myPrint调用次数为:" << myPrint.count << endl;
}
```

```c++
// 3、函数对象可以作为参数传递
void doprint(MyPrint & mp, string test) {
	mp(test);
}
void demo() {
	MyPrint myPrint;
	doprint(myPrint, "Hello C++");
}
```

#### ***谓词

返回bool型的仿函数称为谓词

 含一个参数称为一元谓词

```c++
// 一元谓词
class GreaterFive {
public:
	bool operator()(int val) {
		return val > 5;
	}
};
void demo() {
	vector<int> v;
	for (int i = 0; i < 10; i++) {
		v.push_back(i);
	}
	//查找容器中有没有大于5的数字
	//GreaterFive()匿名函数对象
	vector<int>::iterator it = find_if(v.begin(), v.end(), GreaterFive());
	if (it == v.end())cout << "没找到" << endl;
	else cout << "找到了大于5的数字为:" << *it << endl;
}
```

 两个参数为二元谓词

```c++
// 二元谓词
class Mysort {
public:
	bool operator()(int a,int b) {
		return a > b;
	}
};
void demo() {
	vector<int> v;
	sort(v.begin(), v.end(), Mysort());//从大到小排序
}
```

#### ***内建算术仿函数

```c++
void demo() {
	//#include< functional >
	negate<int> n;//取反仿函数
	cout << n(50);
	plus<int>p;//加法仿函数 二元仿函数 写一个int 
	cout << p(1, 2);
	minus<int> m;// 减法仿函数(二元仿函数)
	cout << m(5, 3);
	multiplies<int> mult;// 乘法仿函数(元仿函数)
	cout << mult(4, 6);
	divides<int> div;// 除法仿函数（二元仿函数）
	cout << div(10, 2);
	modulus<int> mod;// 求模仿函数（二元仿函数）
	cout << mod(13, 5);
}
```

#### ***内建关系仿函数

```c++
void demo() {
	//#include< functional >
	std::equal_to<int> equalTo;// 等于仿函数(二元仿函数)
	bool isEqual = equalTo(3, 3);
	std::cout << "Is 3 equal to 3? " << isEqual << std::endl;

	std::not_equal_to<int> notEqualTo;// 不等于仿函数(二元仿函数)
	bool isNotEqual = notEqualTo(2, 5);
	std::cout << "Is 2 not equal to 5? " << isNotEqual << std::endl;

	std::greater<int> greaterThan;// 大于仿函数(二元仿函数)
	bool isGreaterThan = greaterThan(6, 4);
	std::cout << "Is 6 greater than 4? " << isGreaterThan << std::endl;

	std::less<int> lessThan;// 小于仿函数(二元仿函数)
	bool isLessThan = lessThan(2, 8);
	std::cout << "Is 2 less than 8? " << isLessThan << std::endl;

	std::greater_equal<int> greaterOrEqual;// 大于等于仿函数(二元仿函数)
	bool isGreaterOrEqual = greaterOrEqual(5, 5);
	std::cout << "Is 5 greater than or equal to 5? " << isGreaterOrEqual << std::endl;

	std::less_equal<int> lessOrEqual;// 小于等于仿函数(二元仿函数)
	bool isLessOrEqual = lessOrEqual(7, 3);
	std::cout << "Is 7 less than or equal to 3? " << isLessOrEqual << std::endl;
}
```

#### ***内建逻辑仿函数

```c++
void demo() {
	//#include< functional >
	std::logical_and<bool> logicalAnd;	// 逻辑与仿函数(二元仿函数)
	bool resultAnd = logicalAnd(true, true);
	std::cout << "Logical AND result: " << resultAnd << std::endl;

	// 逻辑或仿函数(二元仿函数)
	std::logical_or<bool> logicalOr;
	bool resultOr = logicalOr(true, false);
	std::cout << "Logical OR result: " << resultOr << std::endl;

	// 逻辑非仿函数(一元仿函数)
	std::logical_not<bool> logicalNot;
	bool resultNot = logicalNot(true);
	std::cout << "Logical NOT result: " << resultNot << std::endl;
}
```

### **STL常用算法

#include < algorithm > < functional > < numeric >

#### ***常用遍历算法

##### for_each

//遍历容器(begin(),end(),_func);

```c++
void print01(int val) {//普通函数
	cout << val << endl;
}//仿函数
class print02 {
public:
	void operatorO(int val) {
		cout << val << endl;
	}
};
void demo() {
	vector<int>v;
	for (int i = 0; i < 3; i++) v.push_back(i);
	for_each(v.begin(),v.end(), print01);//普通函数
	for_each(v.begin(),v.end(),print02());//仿函数
}
```

##### transform

//搬运容器到另一个容器中(source.begin(),source.end(),target.begin(),_func)

```c++
class Transform {
public:
	int operator()(int v) {
		return v * v;
	}
};
void demo() {
	vector<int>v;//原容器
	for (int i = 0; i < 3; i++) v.push_back(i);
	vector<int>w;//目标容器
	w.resize(v.size());//目标容器需要提前开辟空间
	transform(v.begin(), v.end(), w.begin(), Transform());//仿函数或者函数
	for_each(w.begin(), w.end(), print01());
}
```

##### remove/remove_if
//移动满足条件的元素到容器末尾std::remove(begin(),end(), value); std::remove_if(begin(),end(), _pre);
```c++
void demo() {
	std::vector<int> numbers = { 1, 2, 3, 2, 4, 5 };
	// 移除值为 2 的元素
	auto new_end1 = std::remove(numbers.begin(), numbers.end(), 2);
	// 移除奇数元素
	auto new_end2 = std::remove_if(numbers.begin(), numbers.end(), [](int x) { return x % 2 != 0; });
	// 使用 erase 方法真正删除元素
	numbers.erase(new_end1, numbers.end());
}
```
##### remove_copy/remove_copy_if
//std::remove_copy(begin(),end(), result, value);std::remove_copy_if(begin(),end(), result, _pre);
```c++
void demo() {
	std::vector<int> numbers = { 1, 2, 3, 2, 4, 5 };
	std::vector<int> res;//使用back_inserter不用预分配空间#include <iterator>
	std::remove_copy(numbers.begin(), numbers.end(), std::back_inserter(res), 2);
	std::cout << res.size() << std::endl;
	for (const int& v : res) { std::cout << v << " "; }
	
	std::vector<int> res2(numbers.size());//预分配空间
	auto new_end = std::remove_copy_if(numbers.begin(), numbers.end(),
		res2.begin(), [](int x) { return x % 2 == 0; });
	std::cout << res2.size() << std::endl;
	for (const int& v : res2) { std::cout << v << " "; }
	res2.erase(new_end, res2.end());//删除多余的预分配空间
	std::cout << std::endl << res2.size() << std::endl;
}
```
##### unique
将【相邻的】重复的元素移到序列的末尾 并返回一个迭代器 指向去除重复元素后的范围的末尾位置
```c++
void demo() {
	std::vector<int> numbers = { 4, 2, 4, 1, 3, 2, 5, 4 };
	// 先对容器进行排序
	std::sort(numbers.begin(), numbers.end());
	auto new_end = std::unique(numbers.begin(), numbers.end());
	// 使用新的逻辑末尾迭代器来获取去除重复元素后的范围
	numbers.erase(new_end, numbers.end());
	for (const int& num : numbers) std::cout << num << " ";
}
```
##### lexicographical_compare
比较两个容器v1、v2的字典序 如果v1小于v2返回true
```c++
void demo() {
	vector<int>a = { 1,3,4,5,6 };
	vector<int>b = { 1,3,4,4,6 };
	if (lexicographical_compare(begin(a), end(a), begin(b), end(b)))
		cout << "a的字典序小于b" << endl;
	else cout << "b的字典序小于a" << endl; //执行这个语句
}
```
#### ***常用查找算法

##### find

(begin(),end(),val)         返回迭代器

```c++
void demo() {
	vector<int>v;
	//查找指定元素1是否存在 存在返回该位置迭代器 v.end()
	find(v.begin(), v.end(), 1);
}
```

##### find_if 

(begin(),end(),_pred)      返回迭代器

//基本等同find只不过第三个参数变成了谓词或函数

```c++
//查找内置数据类型
class CreaterTwo {
public:
	bool operator()(int val) {
		return val > 2;
	}
};
void demo() {
	vector<int>v;
	for (int i = 0; i < 5; i++) v.push_back(i);
	vector<int>::iterator it = find_if(v.begin(), v.end(), GreaterTwo());
	if (it == v.end()) cout << "没找到" << endl;
	else cout << "找到:" << *it << endl;
}
```

```c++
//查找自定义数据类型
class Person {
public:
	string m_Name;
	int m_Age;

	Person(string name, int age) {
		this->m_Name = name;
		this->m_Age = age;
	}
	//重载--让后续find能够认识
	bool operator==(const Person& p) {
		if (this->m_Name == p.m_Name && this->m_Age == p.m_Age)
			return true;
		else return false;
	}
};
class Greater20 {
public:
	bool operator()(Person& p) {
		return p.m_Age > 20;
	}
};
void demo() {
	vector<Person> v;
	Person p1("aaa", 10);
	Person p2("bbb",20);
	Person p3("ccc", 30);
	v.push_back(p1);
	v.push_back(p2);
	v.push_back(p3);
	vector<Person>::iterator it = find_if(v.begin(), v.end(), Greater20());
	if (it == v.end())cout << "没找到" << endl;
	else cout << "找到:" << it->m_Name << endl;
}
```

##### adjacent_find

//查找相邻重复元素   返回相邻元素的第一个位置的迭代器

(begin(),end())

```c++
void demo() {
	vector<int>v;
	vector<int>::iterator it = adjacent_find(v.begin(),v.end());
	if (it == v.end()) {
		cout << "找不到!" << endl;
	}	
}
```

##### binary_search 

//二分查找(begin(),end(),val) 注意无序序列不可用     返回bool

```c++
void demo() {
	vector<int>v;
	if (!binary_search(v.begin(), v.end(), 1)) {
		cout << "找不到!" << endl;
	}	
}
```

##### lower/upper_bound

//lower_bound在已排序的容器中二分查找第一个大于或等于给定值的元素的位置    返回一个迭代器
//upper_bound在已排序的容器中二分查找第一个大于给定值的元素的位置 返回一个迭代器
```c++
void demo() {
	std::vector<int> vec = { 1,2,4,4,5,6,7,8,9 };
	int target = 5;

	auto it = std::lower_bound(vec.begin(), vec.end(), target);
	if (it != vec.end()) {
		std::cout << "第一个大于等于 " << target << " 的元素的位置是："
			<< std::distance(vec.begin(), it) << std::endl;
	}
	else std::cout << "容器中没有不小于 " << target << " 的元素。" << std::endl;
	
	auto it2 = std::upper_bound(vec.begin(), vec.end(), target);
	if (it2 != vec.end()) {
		std::cout << "第一个大于 " << target << " 的元素的位置是："
			<< std::distance(vec.begin(), it2) << std::endl;
	}
	else std::cout << "容器中没有大于 " << target << " 的元素。" << std::endl;
}
```

##### equal_range

在已排序的容器中查找等于给定值的元素范围 返回一个 pair 其中包含两个迭代器 分别指向容器中等于给定值的元素的起始位置和结束位置[)

```c++
void demo() {
	vector<int>vec = { 1, 2, 2, 2, 2, 3 };
	int target = 2;
	auto range = std::equal_range(vec.begin(), vec.end(), target);
	std::cout << "等于 " << target << " 的元素范围是："
		<< std::distance(vec.begin(), range.first) << " 到 "
		<< std::distance(vec.begin(), range.second) << std::endl;
}
```

##### max/min/mimmax_element

```c++
void demo() {
	vector<int>v = { 3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5 };
	auto max_v = std::max_element(std::begin(v), std::end(v));
	std::cout << "最大值是：" << *max_v << ",位于索引: " << std::distance(v.begin(), max_v) << std::endl;
	auto min_v = std::min_element(std::begin(v), std::end(v));
	std::cout << "最小值是: " << *min_v << ",位于索引: " << std::distance(v.begin(), min_v) << std::endl;
	auto minmaxPair = std::minmax_element(std::begin(v), std::end(v));
	std::cout << "最小值是: " << *minmaxPair.first << ",位于索引: " << std::distance(std::begin(v), minmaxPair.first) << std::endl;
	std::cout << "最大值是: " << *minmaxPair.second << ",位于索引: " << std::distance(std::begin(v), minmaxPair.second) << std::endl;
}
```
### ***常用计数算法

##### count

返回元素出现的次数(begin(),end(),val)        返回int

```c++
void demo() {
	vector<int>v;
	int number = count(v.begin(), v.end(), 1);
}
```

##### count_if

类比find_if (begin(),end(),_pred)

##### distance

计算两个指针或迭代器之间元素的个数

```c++
void demo() {
	std::vector<int> vec = { 1,2,3,4,5,6,7,8,9 };
	auto first = vec.begin();
	auto last = vec.end();
	//ptrdiff_t 是一个有符号整数类型 通常用于表示两个指针（或迭代器）之间的距离
	//在不同的系统上，指针的大小可能不同 因此使用 ptrdiff_t 类型可以提高代码的可移植性
	std::ptrdiff_t dist = std::distance(first, last);
	std::cout << "容器中的元素个数是：" << dist << std::endl;
}
void demo() {
	int array[] = { 1, 2, 3, 4, 5 };
	int* first = array;
	int* last = array + 7;//不会发现越界
	std::ptrdiff_t distance = last - first;
	std::cout << "两个指针之间的距离是：" << distance << std::endl;
}
```

#### ***常用排序算法
##### iota
//给元素递增赋值(source.begin(),source.end(),star)
```c++
void demo() {
	vector<int> a(10);
	iota(a.begin(), a.end(), 1);
	/*for (int i = 0; i < 10; i++)
		a[i] = i + 1;*/
	//用法：不改变二维数组q的位置 得到q排序后的位置
	vector<vector<int>>q;
	vector<int>qid(q.size());
	iota(qid.begin(), qid.end(), 0);
	//返回二维数组q按第一个元素从大到小排序后位置结果
	sort(qid.begin(), qid.end(), [&](int i, int j) {
		return q[i][0] > q[j][0];});
}
```

##### sort

(begin(),end(),_pred)//第三个参数不填默认快排实现升序排列

```c++
void demo() {
	std::vector<int>v = { 3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5 };
	std::sort(v.begin(), v.end());

	//c20 #include <ranges>
	std::ranges::sort(v);//直接对容器中的元素进行升序排序 其他用法与std::sort一样
        //take使用注意事项：
	//如果原始范围的大小小于指定的截取数量 则截取视图将包含整个原始范围的元素
	//返回的视图是只读的 因此无法通过视图修改原始范围中的元素
	//对返回的视图进行迭代时 它会迭代原始范围中的元素 直到达到截取数量为止
	auto view = v | std::views::take(3);//返回的对象是惰性求值(不会立即计算结果 而是在需要时才执行)的
	std::ranges::sort(view);//对前3个数排序
	for (int& t : v)cout << t << " ";
}
```

##### random_shuffle

（begin(),end()）指定区间元素随机调整次序

```c++
void demo() {
	vector<int>v;
	srand((unsigned int)time(NULL));//#include<ctime> 使得每次运行都不一样
	random_shuffle(v.begin(), v.end());
}
```

##### merge

将两个同序容器合并到一个新目标容器中(begin1(),end()1,begin2(),end2(),target.begin())

```c++
void demo() {
	vector<int>v1, v2, target;
	target.resize(v1.size() + v2.size());
	merge(v1.begin(), v1.end(), v2.begin(), v2.end(), target.begin());
}
```

##### reverse

逆置区间 (begin(),end())

```c++
void demo() {
	vector<int>v1;
	reverse(v1.begin(), v1.end());
}
```

#### ***常用拷贝、替换算法

##### copy

拷贝(begin(),end(),target.begin())

```c++
void demo() {
	std::vector<int>v1, target;
	target.resize(v1.size());//预分配空间
	std::copy(v1.begin(), v1.end(), target.begin());
	//使用back_inserter在容器的末尾插入元素#include <iterator>
	std::copy(v1.begin(), v1.end(), std::back_inserter(target));//使用back_inserter不用预分配空间
}
```

##### replace

将区间中old替换成new(begin(),end(),old,new)

```c++
void demo() {
	vector<int>v;
	replace(v.begin(), v.end(), -1, 1);
}
```

##### replace_if

类比find_if(begin(),end(),_pred,new)

##### swap

互换

```c++
void demo() {
	vector<int>v1,v2;
	swap(v1, v2);
}
```

#### ***常用算术生成算法

##### accumulate 

从初始val开始累加区间(begin(),end(),val)

```c++
void demo() {
	vector<int>v;
	accumulate(v.begin(), v.end(), 6);//从初始值6开始累加v中元素
}
```
##### partial_sum
计算前缀和
```c++
void demo() {
	std::vector<int>v = { 1, 2, 3, 4 };
	std::vector<int>pre(v.size() + 1);
	std::partial_sum(v.begin(), v.end(), pre.begin() + 1);
	for (const int& p : pre)std::cout << p << " ";
}
```
##### fill

区间push_back (begin(),end(),val)

```c++
void demo() {
	vector<int>v;
	fill(v.begin(), v.end(), 6);//区间填充为6
}
```

#### ***常用集合算法

两个集合必须是有序序列

##### set_intersection 

交集(begin1(),end()1,begin2(),end2(),target.begin())

```c++
void demo() {
	vector<int>v1 = { 1,2,3,4,5,6 };
	vector<int>v2 = { 4,5,6,7,8,9,10 };
	vector<int>target;
	target.reserve(min(v1.size(), v2.size()));
	vector<int>::iterator it =
		set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), target.begin());
}
```

##### set_union

并集(begin1(),end()1,begin2(),end2(),target.begin())

```c++
void demo() {
	vector<int>v1 = { 1,2,3,4,5,6 };
	vector<int>v2 = { 4,5,6,7,8,9,10 };
	vector<int>target;
	target.reserve(v1.size() + v2.size());
	vector<int>::iterator it =
		set_union(v1.begin(), v1.end(), v2.begin(), v2.end(), target.begin());
}
```

##### set_difference 

差集v1-v2(begin1(),end()1,begin2(),end2(),target.begin())

```c++
void demo() {
	vector<int>v1 = { 1,2,3,4,5,6 };
	vector<int>v2 = { 4,5,6,7,8,9,10 };
	vector<int>target;
	target.reserve(max(v1.size(), v2.size()));
	vector<int>::iterator v12 =
		set_difference(v1.begin(), v1.end(), v2.begin(), v2.end(), target.begin());
	vector<int>::iterator v21 =
		set_difference(v2.begin(), v2.end(), v1.begin(), v1.end(), target.begin());
}
```

