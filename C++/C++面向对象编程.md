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

## *对象的初始化和清理

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

#### ***拷贝构造

默认情况下，编译器至少给一个类添加3个函数：

默认构造函数(无参，函数体为空)

默认析构函数(无参，函数体为空)

默认拷贝构造函数(浅拷贝)

当用户定义有参构造函数 编译器不提供默认无参构造函数

当用户定义拷贝构造函数 编译器不提供默认和拷贝构造函数

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
	int* m_data = nullptr;

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