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

### *系统时间
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

### *计时器
```c++
void demo() {
	chrono::steady_clock::time_point start = chrono::steady_clock::now(); //计时开始
	for (int i = 0; i < 9999999; i++) {}
	std::this_thread::sleep_for(std::chrono::seconds(2)); // 等待2秒
	chrono::steady_clock::time_point end = chrono::steady_clock::now(); //计时结束
	auto dt = end - start;   //单位是纳秒
	cout << "take time " << (double)dt.count() / (1000 * 1000 * 1000) << "秒" << endl;
}
```

## 线程库 thread库 C++11
#include< thread >
### *线程的创建与管理
#### **创建线程
```c++
constexpr int NUM_THREADS = 5; //线程数量

void threadFunction(string ss, int threadID) {//线程函数
	cout << "调用" << ss << threadID << endl;
	this_thread::sleep_for(chrono::seconds(1));//休眠1秒
}

class MyThread {
public:
	void operator()() {
		cout << "Hello from thread!" << endl;
	}
};
void demo() {
	//join()等待子线程的退出 回收它的资源 如果子线程退出 join()函数立即返回 否则产生阻塞 直到子线程退出
	//detach()分离子线程 子线程退出时 系统自动回收资源 主程序不等待
	//joinable()判断子线程的分离状态 返回bool
	
	thread t;//默认构造 创建一个不代表任何线程的thread对象
	//t.join();// 试图等待一个不代表任何线程的线程将导致程序崩溃

	thread t1(threadFunction, "线程", 1);// 创建一个新线程 执行threadFunction函数 传递参数Args
	if (t1.joinable())t1.join();//joinable()函数检查线程对象是否已经被join()或者detach()

	//thread t2 = t1; // 尝试拷贝thread对象 会导致编译错误 (拷贝构造不可用)

	thread t2 = move(t1); // 使用移动构造函数将t1的所有权转移到t2
	if (t2.joinable())t2.join(); //t1 t2同时join()会出错

	MyThread myThread;
	thread t3(myThread); // 使用函数对象创建线程
	t3.join(); // 等待线程执行完毕

	thread t4([]() {
		cout << "Hello from Lambda thread!" << endl;
		}); // 使用Lambda表达式创建线程
	t4.join(); // 等待线程执行完毕

	thread threads[NUM_THREADS]; // 创建一个包含5个线程的数组
	for (int i = 0; i < NUM_THREADS; ++i) {// 创建并启动5个线程
		threads[i] = thread(threadFunction, "数组线程", i); // 将线程函数和该函数的参数传递给线程
	}
	for (int i = 0; i < NUM_THREADS; ++i) {//这段循环如果放到上面那个循环中 速度会变慢
		threads[i].join(); //等待线程结束
	}
}
```
#### ** this_thread全局函数

thread::get_id() thread::yield() thread::sleep_for() thread::sleep_until()
```c++
void thread_func(int a, const string& str) {//线程函数
	if (a == 1)this_thread::yield();//让线程主动让出自己抢到的CPU时间片
	std::thread::id thisThreadId = std::this_thread::get_id();//获得线程id
	cout << "第" << a << "个线程ID：" << thisThreadId << str << endl;
	auto now = std::chrono::system_clock::now();// 获取当前时间点
	auto sleepUntilTime = now + std::chrono::seconds(2); //定义要休眠到的时间点
	std::this_thread::sleep_until(sleepUntilTime);//使当前线程休眠直到指定的时间点
	for (int i = 0; i < 3; i++) {
		cout << "开始休眠" << endl;
		this_thread::sleep_for(chrono::seconds(1));//让线程休眠一秒
	}
}
void demo() {
	thread t1(thread_func, 1, "调用1");
	thread t2(thread_func, 2, "调用2");
	swap(t1, t2);//交换两个线程对象
	t1.join();
	t2.join();
}
```
