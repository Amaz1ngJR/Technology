# C++多线程

## 时间操作chrono库 C++11
#include< chrono >
### *时间长度
```c++
void demo() {
	//时间长度
	//chrono::hours               //小时
	//chrono::minutes             //分钟
	chrono::seconds t1(1);        //1秒
	chrono::milliseconds t2(1000);//1000毫秒
	chrono::microseconds t3(1000 * 1000);//1000*1000微秒
	chrono::nanoseconds t4(1000 * 1000 * 1000);//1000 * 1000 * 1000纳秒
	if (t1 == t2)cout << "t1==t2" << endl;
	cout << "t3 = " << t3.count() << endl;
	t1++;
	cout << "t1++ = " << t1.count() << endl;
}
```

### 系统时间
```c++
void demo() {
	//(1) 静态成员区数chrono::system_clock::now()用于获取系统时间 (C++时间)
	chrono::time_point <chrono::system_clock> now = chrono::system_clock::now();
	//(2) 静态成员函数chrono::system_clock::to_time_t()把系统时间转换成time_t (UTC时间)
	time_t t_now = chrono::system_clock::to_time_t(now);
	//(3) std::localtime()函数把time_t转换成本地时间
	// localtime()不是线程安全的,VS用localtimes_s代替,Linux用localtime_r代替
	tm* tm_now = std::localtime(&t_now);
	//(4)格式化输出tm结构体中的成员
	cout << put_time(tm_now, "%Y-%m-%d %H:%M:%S") << endl;
	cout << put_time(tm_now, "%Y-%m-%d") << endl;
	cout << put_time(tm_now, "%H:%M:%S") << endl;
}
```

## 线程库 thread库 C++11
#include< thread >
