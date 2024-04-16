# 创建型模式

## 工厂模式
简单工厂模式（Simple Factory Pattern）：
简单工厂模式通过一个工厂类来创建对象，客户端只需要通过工厂类来获取对象，而不需要直接实例化对象。简单工厂模式适用于创建对象的逻辑相对简单的情况，但缺点是当需要添加新的产品时，需要修改工厂类的代码。
```c++
// 定义产品接口
class Product {
public:
	virtual ~Product() = default; //虚析构
	virtual void use() const = 0; // 具体产品的使用方法 常成员函数
};

// 具体产品A
class ProductA : public Product {
public:
	void use() const override {
		std::cout << "Using product A" << std::endl;
	}
};

// 具体产品B
class ProductB : public Product {
public:
	void use() const override {
		std::cout << "Using product B" << std::endl;
	}
};

// 工厂类（简单工厂）
class SimpleFactory {
public:
	static std::unique_ptr<Product> createProduct(const std::string& type) {
		if (type == "A") 
			return std::make_unique<ProductA>();
		else if (type == "B") 
			return std::make_unique<ProductB>();
		else throw ("Invalid product type");
	}
};

void demo() {
	auto product = SimpleFactory::createProduct("A");
	product->use();

	product = SimpleFactory::createProduct("B");
	product->use();
}
```
工厂方法模式（Factory Method Pattern）：
工厂方法模式定义了一个抽象的工厂接口，具体的产品创建逻辑由子类工厂来实现。每个具体的子类工厂负责创建特定的产品，客户端通过调用工厂方法来获取对象。工厂方法模式遵循了开闭原则，但需要客户端选择适合的具体工厂类。
```c++
// 产品接口
class Product {
public:
	virtual ~Product() = default;
	virtual void use() const = 0;
};

// 具体产品A
class ProductA : public Product {
public:
	void use() const override {
		std::cout << "Using product A" << std::endl;
	}
};

// 具体产品B
class ProductB : public Product {
public:
	void use() const override {
		std::cout << "Using product B" << std::endl;
	}
};

// 抽象工厂接口
class Factory {
public:
	virtual ~Factory() = default;
	virtual std::unique_ptr<Product> createProduct() const = 0;
};

// 具体工厂A
class FactoryA : public Factory {
public:
	std::unique_ptr<Product> createProduct() const override {
		return std::make_unique<ProductA>();
	}
};

// 具体工厂B
class FactoryB : public Factory {
public:
	std::unique_ptr<Product> createProduct() const override {
		return std::make_unique<ProductB>();
	}
};

void demo() {
	FactoryA factoryA;
	auto productA = factoryA.createProduct();
	productA->use();

	FactoryB factoryB;
	auto productB = factoryB.createProduct();
	productB->use();
}
```
抽象工厂模式（Abstract Factory Pattern）：
抽象工厂模式提供了一个接口，用于创建一系列相关或依赖对象的家族，而不需要指定具体的类。客户端通过使用抽象工厂接口来创建对象，从而可以创建一组相关的产品。抽象工厂模式提供了更高层次的抽象，但增加了系统的复杂性。
```c++
// 产品接口族：颜色
class Color {
public:
	virtual ~Color() = default;
	virtual void apply() const = 0;
};

// 具体产品：红色
class Red : public Color {
public:
	void apply() const override {
		std::cout << "Applying red color" << std::endl;
	}
};

// 具体产品：蓝色
class Blue : public Color {
public:
	void apply() const override {
		std::cout << "Applying blue color" << std::endl;
	}
};

// 产品接口族：形状
class Shape {
public:
	virtual ~Shape() = default;
	virtual void draw() const = 0;
};

// 具体产品：圆形
class Circle : public Shape {
public:
	void draw() const override {
		std::cout << "Drawing a circle" << std::endl;
	}
};

// 具体产品：正方形
class Square : public Shape {
public:
	void draw() const override {
		std::cout << "Drawing a square" << std::endl;
	}
};

// 抽象工厂接口
class AbstractFactory {
public:
	virtual ~AbstractFactory() = default;
	virtual std::unique_ptr<Color> createColor() const = 0;
	virtual std::unique_ptr<Shape> createShape() const = 0;
};

// 具体工厂：红色与圆形
class RedCircleFactory : public AbstractFactory {
public:
	std::unique_ptr<Color> createColor() const override {
		return std::make_unique<Red>();
	}

	std::unique_ptr<Shape> createShape() const override {
		return std::make_unique<Circle>();
	}
};

// 具体工厂：蓝色与正方形
class BlueSquareFactory : public AbstractFactory {
public:
	std::unique_ptr<Color> createColor() const override {
		return std::make_unique<Blue>();
	}

	std::unique_ptr<Shape> createShape() const override {
		return std::make_unique<Square>();
	}
};

void demo() {
	RedCircleFactory redCircleFactory;
	auto red = redCircleFactory.createColor();
	red->apply();
	auto circle = redCircleFactory.createShape();
	circle->draw();

	BlueSquareFactory blueSquareFactory;
	auto blue = blueSquareFactory.createColor();
	blue->apply();
	auto square = blueSquareFactory.createShape();
	square->draw();
}
```
## 单例模式(懒汉式、饿汉式)
一个类只创建一个唯一的对象，即一次创建多次使用

优点
```
1.提供了对唯一实例的受控访问
2.由于在系统中只存在一个对象，因此可以节约系统资源，对于一些需要频繁创建和销毁的对象，单例模式无疑可以提高对系统的性能。
3.允许可变数目的实例
```
缺点
```
1.由于单例模式中没有抽象层，因此单例类的扩展有很大的困难。
2.单例类的指责过重，在一定程度上违背了“单一职责原则”。
3.滥用单例将带来一些负面问题，如为了节省资源将数据库连接池对象设计为单例类，可能会导致共享连接池对象的程序过多
而出现连接池溢出；如果实例化对象长时间不被利用，系统就会认为是垃圾而被回收，这将导致对象状态的丢失。
```
懒汉式（线程不安全）
```c++
class Singleton {
public:
	static Singleton& getInstance() {
		if (instance_ == nullptr) 
			instance_ = new Singleton();
		return *instance_;
	}
	//移除拷贝构造和拷贝赋值
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;
private:
	Singleton() = default;
	~Singleton() = default;
	static Singleton* instance_;//静态成员 类内声明
};
Singleton* Singleton::instance_ = nullptr;//静态成员 类外初始化
```
双检锁/双重校验锁（DCL，线程安全）
```c++
#include <mutex>
class Singleton {
public:
	static Singleton& getInstance() {
		if (instance_ == nullptr) {
			std::lock_guard<std::mutex> lock(mutex_);
			if (instance_ == nullptr) 
				instance_ = new Singleton();
		}
		return *instance_;
	}

	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;

private:
	Singleton() = default;
	~Singleton() = default;

	static Singleton* instance_;
	static std::mutex mutex_;
};

Singleton* Singleton::instance_ = nullptr;
std::mutex Singleton::mutex_;
```
C++11以后的版本
```c++
#include <mutex>

class Singleton {
public:
	static Singleton& getInstance() {
		std::call_once(initInstanceFlag_, &Singleton::createInstance);
		return *instance_;
	}
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;
private:
	Singleton() = default;
	~Singleton() = default;
	static void createInstance() {
		instance_.reset(new Singleton());
	}
	static std::unique_ptr<Singleton> instance_;
	static std::once_flag initInstanceFlag_;
};

std::unique_ptr<Singleton> Singleton::instance_{};
std::once_flag Singleton::initInstanceFlag_{};
```
利用静态局部变量的初始化来保证线程安全的版本
```c++
class Singleton {
public:
	static Singleton& getInstance() {
		static Singleton instance;
		return instance;
	}
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;

private:
	Singleton() = default;
	~Singleton() = default;
};

void demo() {
	auto& singleton1 = Singleton::getInstance();
	auto& singleton2 = Singleton::getInstance();

	// 假设 Singleton 类有一个输出标识的方法
	singleton1.identify();
	singleton2.identify();
}
```
# 结构型模式
## 外观模式（门面模式）
是指外部与子系统的通信必须通过一个统一的外观对象进行，为子系统中的一组接口提供一个一致的界面，定义一个高层接口，这个接口使得这一子系统更加容易使用

优点
```
1.简化客户端与子系统之间的交互，使得客户端更容易使用子系统
2.可以降低客户端与子系统之间的耦合度，使得客户端不需要直接与子系统交互
3.可以在不影响客户端的情况下改变子系统的实现
```
缺点
```
1.可能会限制客户端对子系统的访问，因为客户端只能通过外观类来访问子系统
2.如果设计不仔细，可能会成为一个庞大和复杂的类，难以维护
```
# 行为型模式
## 观察者模式
定义对象间一对多的依赖关系，当一个对象的状态发生改变时，所有依赖于它的对象都得到通知并被自动更新

优点
```
1.松散耦合：观察者模式提供了一种松散耦合的设计，使得当一个对象的状态发生变化时，它不需要知道其他对象是如何使用这些信息的。使得系统更容易扩展和维护
2.动态关联：观察者模式允许在运行时动态地添加或删除观察者，而无需修改主题或其他观察者的代码
3.抽象解耦：由于主题和观察者之间仅通过抽象接口进行通信，因此他们之间的耦合是抽象的，而不是具体的
```
缺点
```
1.可能导致意外的更新，如果一个观察者在接收到通知后执行了一些操作，这些操作又导致了主题状态的变化，那么就可能会导致意外的更新
2.可能导致性能问题，如果有大量的观察者需要更新，那么通知所有观察者可能会导致性能问题
3.可能增加复杂性，如果没有正确实现，观察者模式可能会增加系统的复杂性
```
```c++
// 观察者接口
class Observer {
public:
	virtual ~Observer() = default;
	virtual void update(const std::string& message) = 0;
};
// 具体观察者A
class ObserverA : public Observer {
public:
	void update(const std::string& message) override {
		std::cout << "Observer A received message: " << message << std::endl;
	}
};
// 具体观察者B
class ObserverB : public Observer {
public:
	void update(const std::string& message) override {
		std::cout << "Observer B received message: " << message << std::endl;
	}
};
// 主题接口
class Subject {
public:
	virtual ~Subject() = default;

	void attach(Observer* observer) {
		observers_.push_back(observer);
	}

	void detach(Observer* observer) {
		observers_.erase(std::remove(observers_.begin(), observers_.end(), observer), observers_.end());
	}

	virtual void notifyObservers(const std::string& message) = 0;

protected:
	std::vector<Observer*> observers_;
};
// 具体主题
class ConcreteSubject : public Subject {
public:
	void changeState(const std::string& newState) {
		state_ = newState;
		notifyObservers(state_);
	}

	void notifyObservers(const std::string& message) override {
		for (auto observer : observers_) {
			observer->update(message);
		}
	}

private:
	std::string state_;
};
void demo() {
	ConcreteSubject subject;
	ObserverA observerA;
	ObserverB observerB;

	subject.attach(&observerA);
	subject.attach(&observerB);

	subject.changeState("New state");
}
```
