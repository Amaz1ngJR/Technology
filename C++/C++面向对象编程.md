# C++面向对象编程

C++面向对象的三大特征为：封装、继承、多态

C++面向对象：封装（相似的类型抽象为一个类来封装）、继承（子类继承父类，把父类中所有的属性和行为拿过来，不用再声明）、多态（一个函数名称有多个接口，都是一个名称，父类指针指向子类对象，对象不同，调用同一接口，产生不同的形态）

## *封装

### **成员权限									

属性： 成员属性 成员变量

行为： 成员方法 成员函数

类中的属性和行为 统一称为成员

class和struct的区别:class默认权限为私有 struct默认权限为公共

```c++
class Person {
public:     //公共权限 成员类内可以访问 类外可以访问
	string m_name;
protected:  //保护权限 成员类内可以访问 类外不可以访问 派生类可以访问基类的保护内容
	int m_id;
private:    //私有权限 成员类内可以访问 类外不可以访问 派生类不可以访问基类的私有内容
	//成员属性设为私有的好处： 可以自己控制读写权限 对于写权限 可以检测数据的有效性
	int m_age;
public:
	//m_name可读可写(m_name本身是公共权限可读可写,这里假设是私有的)
	void setName(string name) {//m_name可写
		m_name = name;
	}
	string get_name() {//m_name可读
		return m_name;
	}
	void setID(int id) {//m_id只写
		if (id < 0) {//对于写权限 检测数据的有效性
			cout << "id格式不正确" << endl;
			return;
		}
		m_id = id;
	}
	int get_age() {//m_age只读
		return m_age;
	}
};
void demo() {
	Person p;//实例化对象p
	p.setName("Amaz1ng");
	cout << p.m_name;
}
```

#### ***友元
友元函数不属于类的成员函数 不能被继承

```c++
class GoodFriend;
class Person {
	void func();
	void friendFunc();
};
class Building {
	//友元的三种实现
	friend void friendfunc(Building* p);//1、全局函数做友元
	friend void Person::friendFunc();   //2、成员函数做友元
	friend class GoodFriend;            //3、类做友元
public:
	string m_SittingRoom = "客厅";
protected:
	string m_BedRoom1 = "卧室1";
private:
	string m_BedRoom2 = "卧室2";
};

void friendfunc(Building* p) {
	cout << p->m_BedRoom1 << p->m_BedRoom2 << p->m_SittingRoom;
}
class GoodFriend {
	Building p;
	void visit() {
		cout << p.m_BedRoom1 << p.m_BedRoom2 << p.m_SittingRoom;
	}
};
void Person::func() {
	Building p;
	cout << p.m_SittingRoom;
}
void Person::friendFunc() {
	Building p;
	cout << p.m_BedRoom1 << p.m_BedRoom2 << p.m_SittingRoom;
}
```

### **成员

#### ***对象成员

类对象作为类成员 称为对象成员

```c++
class Per {
public:
	Per() {
		cout << "调用对象成员构造函数" << endl;
	}
	~Per() {
		cout << "调用对象成员析构函数" << endl;
	}
};
class Person {
public:
	Person() {
		cout << "调用构造函数" << endl;
	}
	~Person() {
		cout << "调用析构函数" << endl;
	}
	Per per;//类对象作为类成员 称为对象成员
};
输出：
调用对象成员构造函数
调用构造函数
调用析构函数
调用对象成员析构函数
```

#### ***静态成员

静态成员就是在成员变量和成员函数前加上关键字static

静态成员变量：
所有对象共享同一份数据;

在编译阶段分配内存;

类内声明，类外初始化;

```c++
class Person {
public:
	static int m_a;
private://静态成员变量也有访问权限
	static int m_b;
};

//类内声明，类外初始化; 非静态数据成员不能类外定义
int Person::m_a = 100;
int Person::m_b = 20;

void demo() {
	Person p1;
	Person p2;
	cout << p1.m_a << endl;
	p2.m_a = 10;//所有对象共享同一份数据;
	cout << p1.m_a << endl;
}
```

静态成员函数
所有对象共享同一个函数

静态成员函数只能访问静态成员变量

```c++
class Person {
public:
	static int m_a;
	int m_b;
	static void func() {
		cout << m_a << endl;
		//cout << m_b << endl; 不能访问非静态成员变量
	}
private://静态成员函数也有访问权限
	static void fun() {};
};
//类内声明，类外初始化;
int Person::m_a = 100;
```

### **对象模型

类内的成员变量和成员函数分开存储，只有非静态成员变量才属于类的对象

C++编译器会对每个空对象（class Person{};）也分配一个字节1B空间，是为了区分空对象占空间的位置;

```c++
class Person {
public:
	//成员变量和成员函数分开存储
	int m_a; //非静态成员变量 属于类的对象上
	static int m_b; //静态成员变量 不属于类对象上

	void func1() {} //非静态成员函数 不属于类对象上
	static void func2() {}//静态成员函数 不属于类对象上
};
```

#### ***this指针

this指针(本质是一个指针常量 指针的指向不能修改 指向被调用的成员函数所属的对象) 隐含在每一个非静态成员函数内的一种指针 

```c++
class Person {
public:
	int m_a; 
	Person(int m_a) {//当形参和成员变量同名时 使用this指针区分
		this->m_a = m_a;//this指针指向被调用的成员函数所属的对象
        //this = nullptr;本质是一个指针常量 指针的指向不能修改
	}
	Person& PersonAddm_a(Person& p) {
		this->m_a += p.m_a;
		return *this;//this指针返回对象本身
	}
	void showm_a() {//空指针也是能够调用成员函数
		//当this指针传入的是空指针时,没有对象就没法访问对象里的m_a 会报错
		if (this == nullptr)return;//加一行判断提高代码健壮性
		cout << "m_a = " << m_a << endl;
	}
};
```

#### ***常函数和常对象

常函数:
成员函数后加const 我们称为这个函数为常函数

```c++
class Person {
public:
	void showPerson() const;//常函数
};
```

常对象:
声明对象前加const 称该对象为常对象

```c++
class Person {
public:
	int m_a = 10;
	mutable int m_b = 20;
	void showPerson() const {//常函数
		cout << m_a;
		//this->m_a = 20; 常函数内不可以修改成员属性
		this->m_b = 30;//成员属性声明时加关键字mutable后 可以修改
		//func();//常函数不能调用类的非常函数 因为非常函数可以修改类的成员变量
	}
	void func(){}//非 常函数
};

void demo() {
	const Person p;//声明对象前加const 称该对象为常对象
	p.showPerson();//常对象只能调用常函数
}
```

C++利用了构造函数和析构函数进行对象的初始化和清理，这两个函数将会被编译器自动调用。对象的初始化和清理工作是偏译器强制要我们做的事情，因此如果我们不提供构造和析构。编译器会提供。编译器提供的构造函数和析构函数是空实现。
构造函数:主要作用在于创建对象时为对象的成员属性赋值，构造函数由编译器自动调用，无须手动调用。

析构函数:主要作用在于对象销毁前系统自动调用，执行一些清理工作。

### **构造函数

构造函数语法:类名(){}

1.构造函数，没有返回值也不写void

2.函数名称与类名相同 

3.构造函数可以有参数，因此可以发生重载 

4.程序在调用对象时候会自动调用构造，无须手动调用,而且只会调用一次

```c++
class Person {
public:
	int m_age;
	int m_id;
	//Person() = default;//启用默认构造函数
	//~Person() = delete;//删除默认析构函数
	Person() { cout << "调用无参(默认)构造函数" << endl; }
	Person(int a) {
		m_age = a;
		cout << "调用有参构造函数" << endl;
	}
	Person(const Person& p) {
		m_age = p.m_age;
		cout << "调用拷贝构造函数" << endl;
	}
	Person(int a, int b) :m_age(a), m_id(b) { cout << "调用初始化列表" << endl; };
};

class Person2 {
public:
	int m_age;
	int m_id;
	explicit Person2(int a) {//避免隐式转换
		m_age = a;
		cout << "调用有参构造函数" << endl;
	}
};

void demo() {
	Person p1;//调用默认构造函数
	//Person p1(); 使用默认构造函数不要加(),编译器会认为这是一个函数声明 而不是创建对象

	//1、括号法
	Person p2(18);//调用有参构造函数
	Person p3(p2);//调用拷贝构造函数
	Person(18);//匿名对象 当前行执行结束后,系统会立即回收匿名对象

	//2、显示法
	Person p4 = Person(18);//调用有参构造函数
	Person p5 = Person(p4);//调用拷贝构造函数
	//Person(p3);//不要利用拷贝构造初始化匿名对象 编译器会认为Person(p3)===Person p3

	//3、隐式转换法
	Person p5 = 10;//等效于 Person p5 = Person(10);
	Person p6 = p5;//拷贝构造

	//避免隐式转换 构造函数前加explicit
	//Person2 p7 = 2;
}
```

默认情况下 编译器至少给一个类添加4个函数：
```c++
class Empty {};
//等效于
class Empty {
public:
	Empty();  //默认构造函数(无参，函数体为空)
	Empty(const Empty& rhs);  //默认拷贝构造函数(浅拷贝)
	~Empty();  //默认析构函数(无参，函数体为空)
	Empty& operator=(const Empty& rhs); //默认赋值运算符operator= 对属性进行值拷贝
};
```

当用户定义有参构造函数 编译器不提供默认无参构造函数

当用户定义拷贝构造函数 编译器不提供默认和拷贝构造函数

当不想提供这四个函数的时候 一种方法是将它们放在private中
```c++
class Empty {
public:
	Empty();
	~Empty();
private:  //禁用默认的拷贝构造和拷贝赋值
	Empty(const Empty& rhs);
	Empty& operator=(const Empty& rhs);
};
```
但是成员函数、友元函数还是可以调用private下的默认的拷贝构造和拷贝赋值(但是会出现链接错误)

使用一个基类解决这个问题
```c++
class Uncopyable{
protected:
	Uncopyable();
	~Uncopyable();
private:  //禁用默认的拷贝构造和拷贝赋值
	Uncopyable(const Uncopyable& rhs);
	Uncopyable& operator=(const Uncopyable& rhs);
};

class Empty private:Uncopyable{};//不再声明拷贝构造和拷贝赋值
```
可以使用delete禁用 c++11(delete/default)
```c++
class Empty {
public:
	Empty() = delete;
	~Empty()= delete;
	Empty(const Empty& rhs) = delete;
	Empty& operator=(const Empty& rhs) = delete;
	Empty() = default;//启用默认构造函数
};
```
#### ***拷贝构造

##### 拷贝构造的调用时机

C++中拷贝构造函数调用时机通常有三种情况

```c++
//1、使用一个已经创建完毕的对象来初始化一个新对象
Person p1(18);
Person p2(p1);
```

```c++
//2、值传递的方式给函数参数传值
void func(Person p) {}
void demo() {
	Person p;
	func(p);
}
```

```c++
//3、以值方式返回局部对象
Person func() {
	Person p1;
	cout << (int*)&p1 << endl;
	return p1;
}
void demo() {
	Person p = func();
	cout << (int*)&p << endl;
}
```

##### 深拷贝和浅拷贝

编译器提供的拷贝构造是浅拷贝 带来的问题：堆区的内存重复释放

```c++
class Person {
public:
	int m_age;
	int* m_id;
	Person(int a,int b) {
		m_age = a;
		m_id = new int(b);
		cout << "调用有参构造函数" << endl;
	}
	Person(const Person& p) {
		m_age = p.m_age;
		//m_id = p.m_id;//浅拷贝 两个指针指向同一片内存 析构时内存重复释放
		m_id = new int(*p.m_id);//深拷贝 在堆区重新申请空间，进行拷贝操作
		cout << "调用拷贝构造函数" << endl;
	}
};
```

```c++
class Base {
public:
	int* m_data = nullptr;//数据成员 指向堆区资源的指针

	void copy() {//给数据成员m_data分配内存
		m_data = new int;//分配空间
		memset(m_data, 0, sizeof(int));//初始化已分配的内存
	}
	Base(const Base& p) {//拷贝构造函数
        cout << "调用拷贝构造函数" << endl;
		if (m_data == nullptr) copy();//如果没有分配内存 就分配
		memcpy(m_data, p.m_data, sizeof(int));//把数据从源对象中拷贝过来
	}
};
```

#### ***移动构造

移动构造函数语法：类名(类名&& 源对象){…}

```c++
class Base {
public:
	int* m_data = nullptr;
    
	Base(Base&& p) {//移动构造函数
		cout << "调用移动构造函数" << endl;
		if (m_data != nullptr)delete m_data;//如果已分配内存 先释放掉
		m_data = p.m_data;//把资源从源对象中转移过来
		p.m_data = nullptr;//把源对象中的指针置为空
	}
};
```

如果没有提供移动构造函数，只提供了拷贝函数，编译器就会使用拷贝构造函数

#### ***委托构造C++11

委托构造就是在一个构造函数的初始化列表中调用另一个构造函数。注意:
不要生成环状的构造过程。
一但使用委托构造，就不能在初始化列表中初始化其它的成员变量。

```c++
class Person {
public:
	int m_age;
	int m_id;
	int m_ID;
	Person(int a) {
		m_age = a;
		cout << "调用有参构造函数" << endl;
	}
	Person(int a, int b){
		m_id = a;
		m_ID = b;
	}
	Person(int a, int b, int c) :Person(a) {//委托构造
		cout << m_age;//一但使用委托构造，就不能在初始化列表中初始化其它的成员变量
	}
	Person(int a, int b, int c) :Person(a,b) {//委托构造
		cout << m_id << m_ID;
	}
};
```

#### ***继承构造C++11

```c++
class Person {
public:
	int m_age;
	Person(int a) {
		m_age = a;
		cout << "调用有参构造函数" << endl;
	}
};
class Per :public Person {
public:
	int m_id;
	Per(int a, int b) :Person(a) {//继承构造
		m_id = b;
		cout << m_age << m_id;
	}
};
```

### **析构函数

析构函数语法:~类名(){}
1.析构函数，没有返回值也不写void

2.函数名称与类名相同,在名称前加上符号~

3.析构函数不可以有参数，因此不可以发生重载

4.程序在对象销毁前会自动调用析构，无须手动调用,而且只会调用一次

```c++
class Per {
public:
	int* p;
	Per() {
		p = new int;
		cout << "调用构造函数" << endl;
	}
	~Per() {
		delete p;
		cout << "调用析构函数" << endl;
	}
};
```

## *继承

### **继承中的对象模型

语法： class 子类（派生类） : 继承方式 父类（基类）

继承方式：

公共public继承：父类的公共部分继承到子类公共部分 保护部分继承到子类保护部分 

保护protected继承：父类的公共部分和保护部分都继承到子类保护部分

私有private继承）：父类的公共部分和保护部分都继承到子类私有部分

父类的私有部分也继承下来了 只是被编译器隐藏了 访问不到

```c++
class Base {
public:
	int a;
protected:
	int b;
private:
	int c;
};
class Son :private Base {
public:
	int d;
};
void demo() {
	Base a;
	Son b;
	cout << "a.size= " << sizeof(a) << endl;
	cout << "b.size= " << sizeof(b) << endl;
}
输出：
a.size= 12
b.size= 16
```

1.打开VS开发人员命令提示符(Developer PowerShell for VS)

2.跳转盘符 

```c++
D:
```

3.cd到代码所在文件目录

```c++
 cd D:\MyCode\MyCode
```

4.输入cl /d1 reportSingleClassLayout类名 "文件名"

```c++
cl /d1 reportSingleClassLayoutBase "main.cpp"
```

### **继承中的同名成员处理方式

当子类与父类出现同名的成员。针对成员函数，子类会隐藏父类中的同名成员函数 包括重载
子类对象访问子类同名成员直接访问即可
子类对象访问父类同名成员需要加作用域

```c++
//同名非静态成员的处理方式
class Base {
public:
	int m_a = 10;
	void func() {
		cout << "Base下func()调用" << endl;
	}
	void func(int a) {
		m_a = a;
		cout << "Base下func(int)调用" << endl;
	}
};
class Son :public Base {
public:
	int m_a = 20;
	void func() {
		cout << "Son下func()调用" << endl;
	}
};
void demo() {
	//同名成员属性处理方式
	Son a;
	//访问子类同名成员直接访问即可
	cout << "a.m_a = " << a.m_a << endl;
	//访问父类同名成员需要加作用域
	cout << "Base 下的a.m_a = " << a.Base::m_a << endl;

	//同名成员函数处理方式
	Son b;
	b.func();
	//b.func(10);子类会隐藏父类中的所有同名成员函数 包括重载
	//通过加作用域来访问父类的成员函数
	b.Base::func();
	b.Base::func(10);
}
```

```c++
//同名静态成员的处理方式
class Base {
public:
	static int m_a;
	static void func() {
		cout << "Base下func()调用" << endl;
	}
};
int Base::m_a = 10;
class Son :public Base {
public:
	static int m_a;
	static void func() {
		cout << "Son下func()调用" << endl;
	}
};
int Son::m_a = 20;
void demo() {
	//同名静态成员属性处理方式
	Son a;
	//1、通过对象访问
	//访问子类同名成员直接访问即可
	cout << "a.m_a = " << a.m_a << endl;
	//访问父类同名成员需要加作用域
	cout << "Base 下的a.m_a = " << a.Base::m_a << endl;
	//2、通过类名访问
	cout << "a.m_a = " << Son::m_a << endl;
	cout << "Base 下的a.m_a = " << Son::Base::m_a << endl;

	//同名静态成员函数处理方式
	Son b;
	//1、通过对象访问
	b.func();
	b.Base::func();
	//2、通过类名访问
	Son::func();
	Son::Base::func();
}
```

### **多继承语法

C++允许一个类继承多个类
语法:class子类∶继承方式 父类1,继承方式 父类2...
多继承可能会引发父类中有同名成员出现，需要加作用域区分

#### ***菱形(钻石)继承问题

羊继承了动物的数据，驼同样继承了动物的数据，羊驼继承了羊和驼的数据。当羊驼使用数据时，就会产生二义性。羊驼继承自动物的数据继承了两份，其实我们应该清楚，这份数据我们只需要一份就可以。

#### ***虚继承

```c++
class Animal {
public:
	int m_age;
};
class Sheep1 :public Animal {};
class Tuo1 :public Animal {};
class SheepTuo1 :public Sheep1, public Tuo1 {};
//虚继承
class Sheep2 :virtual public Animal {};
class Tuo2 :virtual public Animal {};
class SheepTuo2 :public Sheep2, public Tuo2 {};
void demo() {
	SheepTuo1 a;
	//父类有相同的数据 加作用域区分
	a.Sheep1::m_age = 18;
	a.Tuo1::m_age = 20;
	cout << "a.Sheep1::m_age= " << a.Sheep1::m_age << endl;
	cout << "a.Tuo1::m_age= " << a.Tuo1::m_age << endl;
	//cout << "a.m_age= " << a.m_age << endl; 错误，a.m_age指代不明确

	//虚继承
	//父类继承之前加上 virtual 变成 虚继承
	//Animal类称为 虚基类
	SheepTuo2 b;
	b.Sheep2::m_age = 18;
	b.Tuo2::m_age = 20;
	cout << "b.Sheep2::m_age= " << b.Sheep2::m_age << endl;
	cout << "b.Tuo2::m_age= " << b.Tuo2::m_age << endl;
	cout << "b.m_age= " << b.m_age << endl;
}
```

使用VS开发人员命令提示符查看 SheepTuo1和SheepTuo2的区别

```c++
class SheepTuo1 size(8)://继承了两份m_age 大小为8字节
        +---
 0      | +--- (base class Sheep1)
 0      | | +--- (base class Animal)
 0      | | | m_age
        | | +---
        | +---
 4      | +--- (base class Tuo1)
 4      | | +--- (base class Animal)
 4      | | | m_age
        | | +---
        | +---
        +---
            
class SheepTuo2 size(12)://继承两个父类的虚基类指针(每个大小为4B)和一个m_age
        +---
 0      | +--- (base class Sheep2)
 0      | | {vbptr}//虚基类指针
        | +---
 4      | +--- (base class Tuo2)
 4      | | {vbptr}//虚基类指针
        | +---
        +---
        +--- (virtual base Animal)
 8      | m_age
        +---

SheepTuo2::$vbtable@Sheep2@://虚基类表
 0      | 0
 1      | 8 (SheepTuo2d(Sheep2+0)Animal)//偏移量

SheepTuo2::$vbtable@Tuo2@://虚基类表
 0      | 0
 1      | 4 (SheepTuo2d(Tuo2+0)Animal)//偏移量
vbi:       class  offset o.vbptr  o.vbte fVtorDisp
          Animal       8       0       4 0            
```

## *多态

多态分为两类
静态多态:函数重载和运算符重载属于静态多态，复用函数名

动态多态:派生类和虚函数实现运行时多态

静态多态和动态多态区别:
静态多态的函数地址早绑定   编译阶段确定函数地址

动态多态的函数地址晚绑定   运行阶段确定函数地址

### **成员函数(常量性)重载

尽可能的使用const
```c++
class P{};
const P operator*(const P& a, const P& b);//函数返回值为const
//防止出现下面现象
P a, b, c;
//错误的将if(a * b == c)写成if (a * b = c)
//将使c赋值到a*b的结果中
```
```c++
class Text {
public:
	Text(string a) { this->text = a; }
	//注意重载的函数返回值都是char&而不是char
	const char& operator[](std::size_t position) const {
		cout << "调用 const" << endl;
		return text[position];
	}
	char& operator[](std::size_t position) {
		cout << "调用 non-const" << endl;
		return text[position];
	}
private:
	string text;
};
void demo() {
	Text p("hello");
	cout << p[0] << endl;//正确 读
	p[0] = 'H';//正确 写
	const Text q("hello");
	cout << q[0] << endl;//正确 读
	//q[0] = 'H';//错误 写
}
```
### **重载运算符
(.)(::)(?:)不能被重载

#### ***重载加号运算符

```c++
class Person {
public:
	int m_a = 10;
	int m_b = 20;
	int m_c = 30;

	//通过成员函数重载加号运算符
	Person operator+ (Person& p) {
		Person temp;
		temp.m_a = this->m_a + p.m_a;
		temp.m_b = this->m_b + p.m_b;
		temp.m_c = this->m_c + p.m_c;
		return temp;
	}
};
//通过全局函数重载加号运算符
Person operator+ (Person& p1, Person& p2) {
	Person temp;
	temp.m_a = p1.m_a + p2.m_a;
	temp.m_b = p1.m_b + p2.m_b;
	temp.m_c = p1.m_c + p2.m_c;
	return temp;
}
//重载
Person operator+ (Person& p1, int num) {
	Person temp;
	temp.m_a = p1.m_a + num;
	temp.m_b = p1.m_b + num;
	temp.m_c = p1.m_c + num;
	return temp;
}
void demo() {
	Person p1, p2;
	//使用成员函数重载加号运算符
	Person p3 = p1.operator+(p2);
	Person p3 = p1 + p2;//可以简化为这种形式 成员函数和全局函数都可以这样简化 注释掉其中一个
	//使用全局函数重载加号运算符
	Person p4 = operator+(p1, p2);
	Person p4 = p1 + p2;//可以简化为这种形式 
	//重载版本
	Person p5 = p1 + 2;
}
```

#### ***重载左移运算符

```c++
class Person {
public:
	int m_a = 10;
	int m_b = 20;
	//利用成员函数重载左移运算符 p.operator<<(cout)简化版本 p<<cout
	//不会利用成员函数重载<<运算符 因为无法实现cout在左侧
	//void operator<<(cout)
};
//只能通过全局函数重载左移运算符
void operator<<(ostream& cout, Person& p) {//本质 operator<<(cout,p); 简化 cout<<p;
	cout << "m_a= " << p.m_a << " m_b= " << p.m_b;
}
void demo() {
	Person p1, p2;
	operator<<(cout, p1);//本质
	cout << p1; //简化
}
//想在cout<<p后面加上<<endl;
ostream& operator<<(ostream& cout, Person& p) {//本质 operator<<(cout,p); 简化 cout<<p;
	cout << "m_a= " << p.m_a << " m_b= " << p.m_b;
	return cout;
}
void demo() {
	Person p1, p2;
	operator<<(cout, p1) << endl;//本质
	cout << p1 << endl; //简化
}
```

#### ***重载递增运算符

​                         前置返回 引用，后置返回 值

```c++
class MyInteger {
public:
	int m_a;
	MyInteger() {
		m_a = 10;
	}
	//前置++ 返回引用
	MyInteger& operator++() {
		//先++
		m_a++;
		//再返回
		return *this;
	}
	//后置++ 返回的是值 因为后置中使用了temp局部变量(存放在栈区的数据在函数执行完后自动释放)
	MyInteger operator++(int) {//用占位参数int来实现函数重载 且只能用int
		MyInteger temp = *this;//先记录当前本身的值
		m_a++;//后递增
		return temp;
	}
};
ostream& operator<<(ostream& cout, MyInteger p) {
	cout << "m_a= " << p.m_a;
	return cout;
}
void demo() {
	MyInteger p1, p2;
	cout << p1 << endl;
	cout << p1++ << endl;
	cout << p1 << endl;
	cout << p2 << endl;
	cout << ++p2 << endl;
	cout << p2 << endl;
}
```

#### ***重载赋值运算符

##### 拷贝赋值

拷贝构造是创建一个新对象，拷贝赋值是更新一个已存在的对象

```c++
class Base {
public:
	int* m_data = nullptr;//数据成员 指向堆区资源的指针

	void copy() {//给数据成员m_data分配内存
		m_data = new int;//分配空间
		memset(m_data, 0, sizeof(int));//初始化已分配的内存
	}
	Base() { m_data = new int(10); }//默认构造函数
	Base& operator=(const Base& p) {//拷贝赋值函数
		cout << "调用了拷贝赋值函数" << endl;
		if (this == &p)return *this;//避免自我赋值
		if (m_data != nullptr) {
			delete m_data;
			m_data = nullptr;
		}
		if (m_data == nullptr) copy();
		memcpy(m_data, p.m_data, sizeof(int));
		return *this;
	}
};
void demo() {
	Base p1, p2;
	int* p = new int(20);
	p1.m_data = p;
	p2 = p1;//调用拷贝赋值函数
}
```



##### 移动赋值

移动赋值函数语法:类名& operator=(类名&& 源对象){…}

```c++
class Base {
public:
	int* m_data = nullptr;//数据成员 指向堆区资源的指针
	Base() = default;
	Base(Base&& p) {//移动构造函数
		cout << "调用移动构造函数" << endl;
		if (m_data != nullptr)delete m_data;//如果已分配内存 先释放掉
		m_data = p.m_data;//把资源从源对象中转移过来
		p.m_data = nullptr;//把源对象中的指针置为空
	}
	Base& operator=(Base&& p) {//移动赋值函数
		cout << "调用了移动赋值函数" << endl;
		if (this == &p)return *this;//避免自我赋值
		if (m_data != nullptr) {//如果已分配内存 先释放掉
			delete m_data;
			m_data = nullptr;
		}
		m_data = p.m_data;
		p.m_data = nullptr;
		return *this;
	}
};
Base func() {
	Base p;
	return p;
}
void demo() {
	Base p1;
	p1 = func();//移动赋值
	Base p2 = func();//移动构造
}
```

#### ***重载关系运算符

```c++
class Person {
public:
	string m_Name;
	int m_Age;

	bool operator==(Person& p) {//重载关系运算符==
		if (this->m_Name == p.m_Name && this->m_Age == p.m_Age) {
			return true;
		}
		else
		{
			return false;
		}
	}
};
```

#### ***重载函数调用运算符() 仿函数

由于重载后使用的方式非常像函数(本质是一个类)的调用，因此称为仿函数

仿函数没有固定写法，非常灵活

```c++
class Myprint {
public:
	void operator()(string text) {
		cout << text << endl;
	}
};
void demo() {
	Myprint p;
	p("hello");
}
```

### **虚函数

C++中，基类将类型相关的函数与派生类不做改变直接继承的函数区分对待，对于前者，基类希望它的派生类各自定义适合自身的版本，此时将这些函数声明成虚函数。一旦某个函数被声明成虚函数，在所有的派生类中，它都是虚函数。

#### ***动态多态

动态多态满足条件:1.有继承关系2.子类重写父类的虚函数
动态多态的使用:父类的指针或者引用执行子类对象

```c++
//基类
class Animal {
public:
	void _speak() {//普通函数 地址早绑定 在编译阶段确定函数地址
		cout << "动物在说话" << endl;
	}
	virtual void speak() {//虚函数 地址晚绑定 在运行阶段确定函数地址
		cout << "动物在说话" << endl;
	}
};
//派生类
class Cat : public Animal {
	void _speak() {//普通函数
		cout << "猫在说话" << endl;
	}
	//重写:函数返回值类型函数名参数列表都相同称为重写
	//子类重写虚函数
	void speak() {//虚函数
		cout << "猫在说话" << endl;
	}
};

//动态多态满足条件:1.有继承关系2.子类重写父类的虚函数
//动态多态的使用:父类的指针或者引用执行子类对象
void doSpeak(Animal& animal) { //Animal &animal = cat;父类的引用执行子类对象
	animal._speak();//"动物在说话"
	animal.speak();//"猫在说话"
}
void demo() {
	Cat cat;
	doSpeak(cat);
}
```

#### ***多态原理剖析

使用VS开发人员命令提示符剖析多态

虚函数表vtable(**属于类的**)：在编译阶段 当编译器遇到一个拥有虚函数的类时 会为该类生成一个虚函数表 
虚函数表是一个存储指向虚函数的指针数组 每个虚函数在表中有一个对应的指针 当派生类覆盖(override)基类的虚函数时 会用自己的函数指针替换虚函数表中的对应项

虚函数表指针vptr(**属于对象的**)：当对象被创建时 会在对象中添加一个指向虚函数表的指针 对象地址的**前4个字节**存储着指向虚表的指针；

在派生类实例化对象时，程序会自动调用构造函数，在构造函数中创建虚表，并对虚表初始化。在构造派生类的对象时，会先调用基类的构造函数，此时编译器只“看到了”基类，并且为基类对象初始化虚表指针，令它指向基类的虚表；当调用派生类的构造函数时，接着为派生类对象初始化虚表指针，令它指向派生类的虚表

当派生类对基类的虚函数没有覆盖（override），派生类的虚表指针直接指向基类的虚表；当派生类对基类的虚函数有覆盖时，派生类的虚表指针指向自己的虚表；当派生类中有自己的虚函数时，将该虚函数地址添加在自己的虚表里面

```c++
class Animal {
public:
	void speak() {//普通函数
		cout << "动物在说话" << endl;
	}
};
class Animal    size(1)://空类
        +---
        +---
```

```c++
class Animal {
public:
	virtual void speak() {//改为虚函数
		cout << "动物在说话" << endl;
	}
};

class Animal    size(4)://类大小为一个虚函数表指针(简称虚表指针)大小(4B)
        +---
 0      | {vfptr}//虚表指针 指向虚函数表
        +---

Animal::$vftable@://虚函数表
        | &Animal_meta
        |  0
 0      | &Animal::speak//表内记录了虚函数地址

Animal::speak this adjustor: 0
```

```c++
class Cat : public Animal {};//子类直接继承

class Cat       size(4):
        +---
 0      | +--- (base class Animal)
 0      | | {vfptr}
        | +---
        +---

Cat::$vftable@:
        | &Cat_meta
        |  0
 0      | &Animal::speak//子类的虚表复制父类内容
```

```c++
class Cat : public Animal {//子类重写虚函数
	void speak() {//虚函数
		cout << "猫在说话" << endl;
	}
};

class Cat       size(4):
        +---
 0      | +--- (base class Animal)
 0      | | {vfptr}
        | +---
        +---

Cat::$vftable@:
        | &Cat_meta
        |  0
 0      | &Cat::speak//子类将虚函数覆盖成&Cat::speak

Cat::speak this adjustor: 0
```

当父类的指针或者引用指向子类对象的时候Animal &animal = cat;，发生多态

#### ***override与final C++11

使用override来说明派生类中的虚函数。让编译器帮我们检测这个被override标记的函数有没有覆盖已存在的虚函数。防止程序员在重写虚函数的时候，不小心写错了形参列表，导致没有覆盖掉虚函数；将虚函数标记为final后，不允许这个类的后续的直接或者间接的派生类再覆盖这个虚函数。

```c++
class Base {
	virtual void fun1(int num);
	virtual void fun2();
	void fun3(int num);
};
class Son1 :Base {
	void fun1(int num) override;//正确
	void fun2(int num) override;//错误! Base中没有f2(int)版的虚函数
	void fun3(int num) override;//错误! fun3不是虚函数
};
class Son2 :Base {
	void fun1(int num) override;//正确
	void fun2() final;//不允许后续的直接或者间接派生类重写覆盖fun2
};
class Grandson1 :Son1 {
	void fun1(int num) override;//虚函数即使被重写了 依然是虚函数
	void fun2() override; //虚函数即使被重写了 依然是虚函数
};
class Grandson2 : Son2 {
	void fun20 override; //错误! 不允许重写final后的的虚函数
};
class Grandson3 :Grandson2 {
	void fun2() override;//!不允许重写final后的的虚函教
};
```

#### ***纯虚函数和抽象类

在多态中，通常父类中虚函数的实现是毫无意义的，主要都是调用子类重写的内容
因此可以将虚函数改为纯虚函数
纯虚函数语法:virtual 返回值类型 函数名 (参数列表)  = 0;

含纯虚函数（纯虚析构等）的类为抽象类，无法实例化对象

抽象类的子类必须重写父类的纯虚函数 否则也属于抽象类

```c++
//纯虚函数和抽象类
class Base {//含纯虚函数 为抽象类
public:
	//纯虚函数
	virtual void func() = 0;
};
void demo() {
	//1.抽象类无法实例化对象
	//Base a;    //new Base;
	//2.抽象类的子类必须要重写父类中的纯虚函数，否则也属于抽象类
	class Son1 :public Base {};
	// Son1 a;
	class Son2 : public Base {
	public:
		virtual void func() {
			cout << "func()函数调用" << endl;
		}
	};
	Base* base = new Son2;
	base->func();
}
```

##### 虚析构和纯虚析构

多态使用时，如果子类中有属性开辟到堆区，那么父类指针在释放时无法调用到子类的析构代码 导致内存泄漏

虚析构和纯虚析构用来解决通过父类释放子类对象的，如果子类中没有堆数据，可以不写虚析构和纯虚析构

纯虚构函数 需要声明也需要实现
虚析构语法：virtual ~类名(){}

纯虚析构语法:
virtual ~类名() = 0;
纯虚析构函数，需要声明也需要实现
类名::~类名(){}

```c++
class Animal {
public:
	Animal() {
		cout << "Animal构造函数调用" << endl;
	}
	virtual void speak() {//虚函数
		cout << "动物在说话" << endl;
	}
	~Animal() {
		cout << "Animal析构函数调用" << endl;
	}
};
class Cat : public Animal {
public:
	int* a;
	Cat(int a) {
		cout << "Cat构造函数调用" << endl;
		this->a = new int(a);//子类将数据开辟到堆区
	}
	~Cat() {
		cout << "Cat析构函数调用" << endl;
		if (a != nullptr) {
			delete a;
			a = nullptr;
		}
	}
	void speak() {//虚函数
		cout << "猫在说话" << endl;
	}
};
void doSpeak(Animal& animal) { //Animal &animal = cat;父类的引用执行子类对象
	animal.speak();
}
void demo() {
	Animal* animal = new Cat(2);
	animal->speak();
	delete animal;
}
输出://父类指针在释放时无法调用到子类的析构代码 导致内存泄漏
Animal构造函数调用
Cat构造函数调用
猫在说话
Animal析构函数调用
```

将Animal的析构函数改成虚析构函数后

```c++
virtual ~Animal() {cout << "Animal析构函数调用" << endl;}
输出：
Animal构造函数调用
Cat构造函数调用
猫在说话
Cat析构函数调用
Animal析构函数调用
```

也可以将析构函数改成纯虚析构函数

```c++
virtual ~Animal() = 0;//纯虚析构函数声明
//纯虚析构函数 需要声明也需要实现
//类外实现
Animal::~Animal() { cout << "Animal纯虚析构函数调用" << endl; }

class Animal    size(4):
        +---
 0      | {vfptr}
        +---

Animal::$vftable@:
        | &Animal_meta
        |  0
 0      | &Animal::speak//虚函数
 1      | &Animal::{dtor}//表示(纯)虚析构地址

Animal::speak this adjustor: 0
Animal::{dtor} this adjustor: 0
Animal::__delDtor this adjustor: 0
Animal::__vecDelDtor this adjustor: 0
```
#### ***不适合当虚函数的函数
并不是所有函数都应该被声明为虚函数

1.构造函数：构造函数不能是虚函数 构造函数在对象创建时被调用 而此时虚表还未构建 虚函数的机制依赖于虚表 因此在构造函数中使用虚函数没有意义

2.静态函数：静态函数与类关联 而不是与类的实例（对象）关联 虚函数的调用是通过类的实例进行的
静态成员函数理论上可以继承 但静态成员函数是编译时确定的 无法动态绑定 不支持多态 因此不能被重写

3.内联函数：内联函数通常在类定义中定义 而且通常比较简单 编译器在编译时会将其内联展开 而虚函数是为了实现多态 是运行时绑定的

4.非成员函数 ：不能被继承
