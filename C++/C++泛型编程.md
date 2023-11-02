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

#### ***可变参数模板 C++11

##### 函数模板的可变参数



```c++
void show() {};//基本情况:当没有剩余参数时，终止递归
template<typename T, typename... Args>
void show(T firstArg, Args...args) {
	cout << firstArg << endl;
	show(args...);
}
void demo() {
	show(2.12, 5, "hello", 'a');
}
```



##### 类模板的可变参数

![image](https://github.com/Amaz1ngJR/Technology/assets/83129567/a0a9d725-6bad-44bc-9f7b-b8e48c37203e)
