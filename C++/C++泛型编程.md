# C++泛型编程

## *模板

语法:
template<typename T>

函数声明或定义

template ---声明创建模板
typename ---表面其后面的符号是一种数据类型，可以用class代替

T --通用的数据类型，名称可以替换，通常为大写字母

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

