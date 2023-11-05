# C++多线程

## 时间操作chrono库 C++11
#include< chrono >
### 时间长度
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

## 线程库 thread库 C++11
#include< thread >
