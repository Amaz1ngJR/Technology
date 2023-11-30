# Linux系统调用/系统函数

## gcc/g++编译 (检查语法错误)
gcc 编译可执行程序四步骤：预处理、编译、汇编、链接
![image](https://github.com/Amaz1ngJR/Technology/assets/83129567/9849587b-2caf-4346-b4fb-1d5e7358d576)
链接阶段地址回填

![image](https://github.com/Amaz1ngJR/Technology/assets/83129567/dcaf018b-c6b9-457b-8d96-35550c951a63)
```bash
objdump -dS 二进制文件.o  //将机器代码转成汇编代码
```
```bash
gcc/g++
-v / -version 查看gcc版本号
-I目录 指定头文件目录 注意-I和目录之间没有空格
-c 只编译 生成.o文件 不进行链接
-g 包含调试信息 主要支持gdb调试
-On n=0~3 编译优化 n越大优化得越多
-Wa11 显示所有警告信息
-D<DEF> 编译时定义宏 注意-D和<DEF>之间没有空格
-E 生成预处理文件
-M 生成.c文件与头文件依赖关系 用于Makefile 包括系统库的头文件
-MM 生成.c文件与头文件依赖关系 用于Makefile 不包括系统库的头文件
```
g++与gcc的区别：

G++是GCC的C++编译器前端

1·标准库：g++会自动链接C++标准库 以支持C++语言的功能 如STL（标准模板库）等

2.编译选项：g++会自动启用C++语言的特性和默认编译选项
## gdb调试 (检查逻辑错误)
对gcc -g .c文件 生成的文件如hello进行调试
```bash
gdb hello
(gdb)list                 //显示代码
(gdb)b/break 3            //在行号为3处设置断点 也可根据函数名
(gdb)c/continue           //继续执行断点后续指令
(gdb)r/run                //运行程序 如果出现段错误 会报出
run argv[1] argv[2]       //调试时命令行传参
(gdb)n/next               //执行下一条(越过函数)
(gdb)s/step               //执行下一条(会进入函数)
(gdb)p/print i            //查看变量i的值
(gdb)d/delete             //删除断点 d breakpoints NUM
(gdb)i/info               //查看GDB内部局部变量的数值 info breakpoints
(gdb)finish               //结束当前函数 返回到函数调用点
(gdb)set                  //设置变量的值 set var n=100
(gdb)display/undisplay    //设置/取消观察变量
(gdb)enable/disable breakpoints   //启用/禁用断点
(gdb)x/nfu                //查看内存 n显示多少个元素 f表示显示的格式(进制) u 表示显示的单位 字/字节 1字=4字节
    x：十六进制格式
    d：有符号十进制格式
    u：无符号十进制格式
    o：八进制格式
    t：二进制格式
    a：地址格式
    c：字符格式
    s：字符串格式
    i：汇编指令格式

    b：字节
    h：半字（2个字节）
    w：字（4个字节）
    g：双字（8个字节）
    s：符号单位
    i：指令单位
(gdb)watch              //被设置观察点的变量发生修改时 打印显示
(gdb)i watch            //显示观察点
(gdb)q/quit             //退出gdb
```
## 静态库与动态库
静态库：对空间要求低 时间要求高的核心程序中 使用的时候直接复制到程序中
动态库：使用时全部调入到内存中 多个程序共享一份
### 创建静态库 lib_.a

将库中声明写到头文件下（一般库在lib下，头文件在inc下，头文件里是库中函数的声明和其他的include）

要创建一个静态库或将目标代码加入到已经存在的静态库中 使用下面命令
```bash
ar rcs libmylib.a file1.o file2.o
//r 将目标代码加入静态库中
//c 若libmylib.a不存在 会自动创建
//s 更新.a文件的索引 使之包含加入的.o文件
```
静态库制作以及使用步骤
```bash
1. 将.c生成.o
    g++ -c func.c -o func.o
2.使用ar工具制作静态库  
    ar rcs lib库名.a func1.o func2.o
3.编译静态库到可执行文件中
    g++ code.c lib库名.a -o code 
```
### 创建动态库 lib_.so
```bash
1.将.c生成.o文件（生成与位置无关的代码 参数 -fPIC）所有地址后面带有@plt（延迟绑定）
    gcc -c add.c -o add.o -fPIC
2.使用gcc -shared 制作动态库
	gcc -shared lib库名.so add.o
3.编译可执行程序时，指定所使用的动态库 所有的库名都以lib开头 链接的时候参数省略开头的lib
    gcc main.c -o main -lmylib -L./lib    //-l/L后直接带参数 没有空格
4.执行./main会出错
出错原因：
链接器：     工作于链接阶段 工作时需要-l和-L
动态链接器： 工作于程序运行阶段 工作时需要提供动态库所在目录位置
解决：需要将动态库加到环境变量LD_LIBRARY_PATH中并导出(参考环境变量部分)：
1.export LD_LIBRARY_PATH=./lib(临时设置)  
2.vi ~/.bashrc ->添加export LD_LIBRARY_PATH=./lib ->重启终端或者..bashrc或者source .bashrc(永久设置)
3.添加绝对路径到sudo vi /etc/ld.so.conf,并执行sudo ldconfig(永久设置)
4.拷贝到根目录下/lib：cd /.->cd lib->sudo cp libmylib.so /lib(永久设置)
```

## 操作系统名词解释

### 终端
终端(一系列输入输出设备的统称)文件 /dev/tty

### 文件进制
```bash
od-tcx filename  //查看文件的16进制表示形式
od-tcd filename  //查看文件的10进制表示形式
```

### 索引节点inode
其本质为结构体 存储文件的属性信息 如:权限、类型、大小、时间、用户、盘块位置·.····也叫作文件属性管理结构 
大多数的 inode 都存储在磁盘上 少量常用、近期使用的 inode会被缓存到内存中

### 目录项dentry
其本质是结构体 重要成员变量有两个(文件名，inode，...) 而文件内容(data)保存在磁盘盘块中

![image](https://github.com/Amaz1ngJR/Technology/assets/83129567/488d5a66-77c6-4dfb-9c68-394325165bb7)

### 文件描述符
是一个非负整数 它在进程中唯一标识打开的文件、套接字（socket）或其他I/O资源

文件描述符的三个标准值：
0：标准输入（stdin）
1：标准输出（stdout）
2：标准错误（stderr）

![v2-d3e534157323ffd5881150d9d8d9c734_r](https://github.com/Amaz1ngJR/Technology/assets/83129567/ffb90d35-118a-4484-b1a5-1f7b498c77e8)


### 进程控制块PCB
PCB(本质是结构体)中有一个指针* 指向文件描述符表 

文件描述符表中存放文件描述符(指针(实际是key)但是操作系统封装了 像个数组 只暴露出下标 所以一般用int整数)

关闭一个文件后 再打开一个文件 还是会按表中下标最小的位置存放

### 阻塞和非阻塞
阻塞和非阻塞是设备文件、网络文件的属性(常规文件无阻塞概念)

产生场景：读设备文件、网络文件

## 文件相关 系统函数/调用

### open/close函数

函数原型
```c++
int open(const char *pathname, int flags); //#include <fcntl.h>
int open(const char *pathname, int flags, mode_t mode); //#include <fcntl.h>、<sys/types.h>、<sys/stat.h>
//flags：
//	O_RDONLY: 只读方式打开文件
//	O_WRONLY: 只写方式打开文件
//	O_RDWR: 读写方式打开文件
//	O_CREAT: 如果文件不存在 就创建一个新文件 需要与mode参数一起使用 指定新文件的权限
//	O_EXCL: 与O_CREAT一起使用 用于确保创建新文件而不覆盖已存在的文件
//	O_TRUNC: 如果文件存在 并且以写方式打开 则清空文件内容
//	O_APPEND: 打开文件并定位到文件末尾 用于在文件末尾追加数据
//	O_NONBLOCK: 非阻塞模式打开文件 用于在读取或写入时不阻塞进程
//mode：mode是八进制的整型 表示文件的权限掩码
//	S_IRUSR (0400): 用户读权限
//	S_IWUSR (0200): 用户写权限
//	S_IXUSR (0100): 用户执行权限
//	S_IRGRP (0040): 组读权限
//	S_IWGRP (0020): 组写权限
//	S_IXGRP (0010): 组执行权限
//		S_IRUSR | S_IWUSR：表示用户具有读写权限
// 			文件权限 = mode & ~umask
//函数返回 int文件描述符

int close(int fd); //#include <unistd.h>
//fd 要关闭的文件描述符
//关闭成功返回0 关闭失败返回-1 并设置errno来指示错误的类型
```

```c++
#include <iostream>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
//查看errno错误
#include <errno.h>
#include <string.h>

void demo() {
	int fd = open("/home/yjr/mytest/test.txt", O_RDONLY);
	std::cout << "fd = " << fd << std::endl;
	int c = close(fd);
	std::cout << "c = " << c << std::endl;

	int fd2 = open("/home/yjr/NULL", O_RDONLY);
	std::cout << "fd2 = " << fd2 << std::endl;
	std::cout << "errno = " << strerror(errno) << std::endl;
	int c2 = close(fd2);
	std::cout << "c2 = " << c2 << std::endl;
	std::cout << "errno = " << strerror(errno) << std::endl;
}

int main(){
	demo();
	return 0;
}
```

### read/write函数
```c++
ssize_t read(int fd, void *buf, size_t count);  //#include <unistd.h>
ssize_t write(int fd, const void *buf, size_t count);  //#include <unistd.h>
//参数：fd 文件描述符 *buf:存/写 数据的缓冲区 count：缓冲区/写入 大小
//返回值：成功：读到的字节数 失败：-1 设置errno 如果errno=EAGIN或EWOULDBLOCK 说明不是read失败
//而是read以非阻塞的方式读一个设备文件、网络文件 并且文件无数据
```
通过read和write实现cp命令
```c++

```
### fcntl函数

### lseek函数

### 传入传出参数(都是指针)
传入参数：
```
1.	指针作为函数参数
2.	通常有const关键字修饰
3.	指针指向有效区域 在函数内部做读操作
```
传出参数：
```
1.	指针作为函数参数
2.	在函数调用之前 指针指向的空间可以无意义 但必须有效
3.	在函数内部 做写操作
4.	函数调用结束后 充当函数返回值
```
传入传出参数：
```
1.	指针作为函数参数
2.	在函数调用之前 指针指向的空间有实际意义
3.	在函数内部 先做读操作 后写操作
4.	函数调用结束后 充当函数返回值
```
