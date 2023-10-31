# C++面向对象编程

C++面向对象的三大特征为：封装、继承、多态

C++面向对象：封装（相似的类型抽象为一个类来封装）、继承（子类继承父类，把父类中所有的属性和行为拿过来，不用再声明）、多态（一个函数名称有多个接口，都是一个名称，父类指针指向子类对象，对象不同，调用同一接口，产生不同的形态）

## *类

### **成员权限									

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

