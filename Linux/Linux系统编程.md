# Linux系统调用/系统函数

## *gcc/g++编译 (检查语法错误)
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

## *gdb调试 (检查逻辑错误)
对gcc -g .c文件 生成的文件如hello进行调试
```bash
gdb hello
(gdb)l/list                 //显示代码
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
### 对父子进程的gdb调试
使用gdb调试的时候 gdb只能跟踪一个进程 可以在fork函数调用之前 通过指令设置gdb调试工具跟踪父进程(默认)或子进程
```bash
(gdb)set follow-fork-mode child #在fork之后跟踪子进程
(gdb)set follow-fork-mode parent #在fork之后跟踪父进程
(gdb)info inferiors #查看当前有哪些进程 以及你当前正在调试
(gdb)inferior 1   # 切换到父进程
(gdb)inferior 2   # 切换到子进程
```
## *静态库与动态库
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

## *文件相关 系统函数/调用

### 操作系统相关名词解释

#### 终端
终端(一系列输入输出设备的统称)文件 /dev/tty

#### 文件进制
```bash
od-tcx filename  //查看文件的16进制表示形式
od-tcd filename  //查看文件的10进制表示形式
```

#### 索引节点inode
其本质为结构体 存储文件的属性信息 如:权限、类型、大小、时间、用户、盘块位置·.····也叫作文件属性管理结构 
大多数的 inode 都存储在磁盘上 少量常用、近期使用的 inode会被缓存到内存中

#### 目录项dentry
其本质是结构体 重要成员变量有两个(文件名，inode，...) 而文件内容(data)保存在磁盘盘块中

![image](https://github.com/Amaz1ngJR/Technology/assets/83129567/488d5a66-77c6-4dfb-9c68-394325165bb7)

#### 文件描述符
是一个非负整数 它在进程中唯一标识打开的文件、套接字（socket）或其他I/O资源

文件描述符的三个标准值：
0：标准输入（stdin）
1：标准输出（stdout）
2：标准错误（stderr）

![v2-d3e534157323ffd5881150d9d8d9c734_r](https://github.com/Amaz1ngJR/Technology/assets/83129567/ffb90d35-118a-4484-b1a5-1f7b498c77e8)

#### 阻塞和非阻塞
阻塞和非阻塞是设备文件、网络文件的属性(常规文件无阻塞概念)

产生场景：读设备文件、网络文件

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
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
//查看errno错误
#include <errno.h>
#include <string.h>
#include <cstdlib> // C++ For exit
#include <cstring> // C++ For perror

int main() {
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

	return 0;
}
```

### read/write函数
函数原型
```c++
#include <unistd.h>

ssize_t read(int fd, void *buf, size_t count);  
ssize_t write(int fd, const void *buf, size_t count);  
//参数：fd 文件描述符 *buf:存/写 数据的缓冲区 count：缓冲区/写入 大小
//返回值：成功：读到的字节数 失败：-1 设置errno 如果errno=EAGIN或EWOULDBLOCK 说明不是read失败
//而是read以非阻塞的方式读一个设备文件、网络文件 并且文件无数据
```
通过read和write实现cp命令
```c++
//argc 表示命令行参数的数量 至少为1 因为程序的名称被算作一个参数
//argv 指向字符串数组的指针 每个字符串表示一个命令行参数
// ./demo test.txt newtest.txt argc=3 argv[] ={"./demo" ,"test.txt","newtest.txt"}
int main(int argc, char* argv[]) {
	int fd1, fd2, n = 0;
	char buf[1024];  //设置缓冲区的大小为1024
	fd1 = open(argv[1], O_RDONLY);
	if (fd1 == -1) {
		perror("open argv1 error");
		exit(1); //#include <stdlib.h> exit(0)表示正常终止 其他表示异常终止
	}
	fd2 = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, 0664);
	while ((n = read(fd1, buf, 1024)) != 0) {
		write(fd2, buf, n);
	}
	close(fd1); close(fd2);
	return 0;
}
```
系统函数read/write与库函数fputc的区别

fputc内置一个4096的缓冲区(预读入缓输出) 满了以后调用write系统函数

read/write称为unbuffered I/O（无用户级缓冲区）

![image](https://github.com/Amaz1ngJR/Technology/assets/83129567/dd027f7e-ca5f-4d50-a1fb-837b634b9686)
同样将buf设为1 由于库函数有内置的缓冲区 比write要快

### fcntl函数
函数原型
```c++
//改变一个 已经打开 的文件的 访问控制属性
int fcntl(int fd, int cmd, ... /* arg */ ); //#include <unistd.h> #include <fcntl.h>
//fd 是文件描述符
//cmd 是控制命令
//	获取文件状态： F_GETFL
//	设置文件状态： F_SETFL
//	复制文件描述符：F_DUPFD
//	获取文件锁信息：F_GETLK
//	设置文件锁：F_SETLK
//	阻塞设置文件锁：F_SETLKW
//参数3 如果是一个被占用的文件描述符 则返回最小的可以的 否则返回=参数3的文件描述符
```
```c++
int main() {
	int fd = open("/home/yjr/mytest/test.txt", O_RDWR);
	int flags = 0;
	flags = fcntl(fd, F_GETFL); //获取stdin属性信息
	if (flags == -1) {
		perror("fcnt; error");
		exit(1);
	}
	flags |= O_NONBLOCK; //添加非阻塞标志
	int ret = fcntl(fd, F_SETFL, flags);
	if (ret == -1) {
		perror("fcnt; error");
		exit(1);
	}
	return 0;
}
```

### lseek函数
函数原型
```c++
off_t lseek(int fd, off_t offset, int whence); //#include <unistd.h>
// fd：文件描述符 iffset：偏移字节数 whence：偏移起始位置(SEEK_SET/SEEK_CUR/SEEK_END)
//返回值是以文件的开头作为偏移起始位置的偏移量
```
在文件里写入一段字符再读出 注意文件的读和写使用同一偏移位置
```c++
int main(){
	int fd = open("test.txt", O_RDWR | O_CREAT, 0644);
	if (fd < 0) {
		perror("open error");
		exit(1);
	}

	char buf[] = "test for lseek";
	write(fd, buf, sizeof(buf)); //写到文件末尾
	lseek(fd, 0, SEEK_SET);      //将偏移量改到开头，归位

	char ch; int n;
	while (n = read(fd, &ch, 1)) {   //读和写使用同一个偏移位置
		if (n < 0) {
			perror("open error");
			exit(1);
		}
		write(STDOUT_FILENO, &ch, n);//写入到标准输出(终端)
	}
	close(fd);
	return 0;
}
```
使用lseek获取文件大小
```c++
int main() {
	int fd = open("test.txt", O_RDWR | O_CREAT, 0644);
	int len = lseek(fd, 0, SEEK_END);
	cout<<"len = "<<len<<endl;
	close(fd);
	return 0;
}
```
使用lseek拓展文件大小
```c++
lseek(fd,要拓展的大小-1,SEEK_END);
write(fd,”/0”,1);//要想使文件大小真正拓展 必须引起IO操作

int ret=truncate(filepath,要拓展大小);//使用truncate也可以拓展文件大小

```

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
```c++
int func(int* a, struct student* b, double* c) {...} 
void demo() {
	int* a;
	struct student* b;
	double* c;
	int d = 0;
	d = func(a, b, c);//d为函数返回值 a b c都是传出参数
}
```
传入传出参数：
```
1.	指针作为函数参数
2.	在函数调用之前 指针指向的空间有实际意义
3.	在函数内部 先做读操作 后写操作
4.	函数调用结束后 充当函数返回值
```

### stat/lstat函数
函数原型
```c++
#include <sys/types.h> 包含在#include <unistd.h>
#include <sys/stat.h>

int stat(const char *pathname, struct stat *statbuf);  //能够穿透符号链接
int lstat(const char *pathname, struct stat *statbuf); //不能穿透符号链接
//成功返回0 失败-1
```
```c++
//struct stat中有个成员st_mode可以用来判断文件类型
int main(int argc, char *argv[]){
	struct stat sb;
	int ret =stat(argv[1],&sb);
	if(ret==-1){
		perror("stat error");
		exit(1);
	}
	if(S_ISREG(sb.st_mode))
		std::cout<<"普通文件"<<std::endl;
	else if(S_ISDIR(sb.st_mode))
		std::cout<<"目录文件"<<std::endl;
	else if(S_ISFIFO(sb.st_mode))
		std::cout<<"管道"<<std::endl;
	else if(S_ISLNK(sb.st_mode))
		std::cout<<"软链接"<<std::endl;

	return 0;
}
```
### link/unlink函数
函数原型
```c++
#include <unistd.h>

int link(const char *oldpath, const char *newpath);
int unlink(const char *pathname);
//成功返回0 失败-1

//Linux下删除文件的机制：不断将st_nlink -1 直至为0
//使用unlink将文件的硬链接数降至0后 没有dentry与之对应
//该文件不会马上被释放 要等到所有打开该文件的进程关闭了该文件 系统才会择机释放(隐式回收系统资源)
```
使用link/unlink实现mv改名
```c++
link(argv[1],argv[2]);
unlink(argv[1]);
```
使用readlink函数或命令可以 读取符号链接文件本身的内容 得到链接所指向的文件名

### opendir/closedir/readdir 库函数
函数原型
```c++
#include <dirent.h>
DIR *opendir(const char *name);
DIR *fdopendir(int fd);
int closedir(DIR *dirp);
struct dirent *readdir(DIR *dirp);
//	struct dirent {  //目录项
//               ino_t          d_ino;       /* Inode number */
//               off_t          d_off;       /* Not an offset; see below */
//               unsigned short d_reclen;    /* Length of this record */
//               unsigned char  d_type;      /* Type of file; not supported
//                                              by all filesystem types */
//               char           d_name[256]; /* 去掉"/0"文件名最大255字节 */
//	};
```
```c++
string path = "/home/yjr/test";
DIR* dir;
struct dirent* entry;
if ((dir = opendir(sourceFolderPath.c_str())) != nullptr){
	while ((entry = readdir(dir)) != nullptr) {
		string subfolderName = entry->d_name;
		if (subfolderName != "." && subfolderName != ".."){
			string sourceFilePath = sourceFolderPath + "/" + subfolderName + "/raw_model.obj";
			struct stat fileInfo;
			if (stat(sourceFilePath.c_str(), &fileInfo) == 0 && S_ISREG(fileInfo.st_mode)) {
			//todo...
			}
		}
	}
	closedir(dir);
}
```

### dup/dup2重定向函数
```c++
#include <unistd.h>

int dup(int oldfd);//输入已有的文件描述符 返回新的文件描述符(拷贝一份oldfd)
int dup2(int oldfd, int newfd); //返回newfd (将oldfd拷贝到newfd 让newfd指向oldfd)
```
将终端输出的东西拷贝到文件里 而终端不显示
```c++
int main(int argc, char *argv[]){
	int fd = open(argv[1],O_RDWR);
	int fdret =dup2(fd,STDOUT_FILENO);
	std::cout<<"fdret = "<<fdret<<std::endl;
	std::cout<<"---------------"<<std::endl;
	return 0;
}
```

## *进程相关 系统函数/调用

### 操作系统相关名词解释

#### 进程控制块PCB
PCB本质是结构体 里面含进程id 进程的状态 进程切换时保存的CPU寄存器 虚拟内存信息 当前的工作目录  文件描述符 会话和进程组等

文件描述符表中存放文件描述符(指针(实际是key)但是操作系统封装了 像个数组 只暴露出下标 所以一般用int整数)

关闭一个文件后 再打开一个文件 还是会按表中下标最小的位置存放

进程的状态有5种：初始态、就绪态、运行态、挂起态与终止态(初始态为进程准备阶段 常与就绪态结合)
![bf436d541a109a5b17bc6ffbfceec4c3](https://github.com/Amaz1ngJR/Technology/assets/83129567/1e86794c-5148-419c-bc7b-c8d3f76901a8)

#### 虚拟地址到物理地址的映射
在32位操作系统中 一个进程通常具有4GB(可用)的虚拟地址空间 如下图所示 有1G的内核空间和3G的用户空间 内核区映射回物理地址是同一片区域(也是进程通信能够实现的原因)

![665567ea583a121297b7ba8262c59ec8](https://github.com/Amaz1ngJR/Technology/assets/83129567/dbc3b923-0457-495c-a655-f05f4307fcd7)

#### 进程共享
fork之后 父子进程的不同之处：进程ID、fork返回值、父进程ID、进程运行时间、闹钟(定时器)、未决信号集  

子进程似乎复制了父进程的用户空间的内容以及PCB(pid不同) 但子进程并不是将父进程的用户空间 完全拷贝一份

父子进程之间真正共享的是**文件描述符(打开文件的结构体)**
父子进程间遵循 **读时共享** **写时复制** 的原则 
```c++
int global_val = 100;
int main(int argc, char* argv[]) {
	pid_t pid = fork();
	if (pid == -1) {
		perror("fork error");
		exit(1);
	}
	else if (pid > 0) {
		global_val = 200; 
		std::cout << "父进程" << getpid() << "的global_val为" << global_val << std::endl;
		sleep(1);
	}
	else if (pid == 0) {
		//global_val = 50;  //此行验证写时复制
		std::cout << "由进程" << getppid() << "创建的子进程"
			<< getpid() << "的global_val为" << global_val << std::endl;
	}
	std::cout << "---done---" << std::endl;
	return 0;
}
```
#### 孤儿进程和僵尸进程
父进程先于子进程结束 则子进程成为孤儿进程 子进程的父进程成为init进程 称init进程领养孤儿进程

子进程终止 父进程(比如是死循环)尚未回收 子进程残留资源(PCB)存放在内核中 变成僵尸进程 僵尸进程无法使用kill命令清除(因为进程已经终止了)

清理僵尸进程的方法：kill父进程

### fork函数
函数原型
```c++
#include <sys/types.h> 包含在#include <unistd.h>

pid_t fork(void);  //创建一个子进程 无参数 
//内部是当程序Base执行到fork() 会在内存复制一份作为子进程Son
//子进程的fork返回给父进程一个0表示子进程创建成功 失败为-1
//父进程的fork返回子进程的pid (只调用了父进程的fork 但是父子进程的fork都有返回)
//父子进程继续执行fork后的指令
pid_t getpid(void);//获取当前进程的PID  getuid：当前用户id getgid：当前用户组id
pid_t getppid(void);//获取父进程的PID

```
```c++
int main(int argc, char *argv[]){
	std::cout << "创建子进程之前的指令" << std::endl;
	pid_t pid = fork();
	if (pid == -1) {
		perror("fork error");
		exit(1);
	}
	else if (pid == 0) {//子进程返回给父进程0 当前进程为子进程
		std::cout << "子进程成功被创建" << std::endl;
		std::cout << "进程" << getpid() << "被" <<getppid() << "创建" <<std::endl; 
	}
	else if (pid > 0) {//父进程返回子进程的pid 当前进程为父进程
		//#include <sys/wait.h> 等待子进程结束
		//wait(NULL); //防止进程成为孤儿进程
		sleep(1);//睡眠1秒 防止进程成为孤儿进程
		std::cout << "进程" << getpid() << "创建了子进程" << pid << std::endl;
	}
	std::cout << "---end---" << std::endl;
	return 0;
}
```
循环创建N个子进程
```c++
int main(int argc, char* argv[]) {
	//循环创建5个子进程
	int i;
	for (i = 0; i < 5; i++) {
		if (fork() == 0) {//当前进程为子进程
			break;
		}
	}
	if (i == 5) {
		sleep(1);
		std::cout << "父进程" << getpid() << std::endl;
	}
	else {
		sleep(i);
		std::cout << "第" << i + 1 << "个子进程" << std::endl;
	}

	return 0;
}
```
c语言中printf和c++cout在fork上的区别
```c++
int demo(){
	//c++ 输出 a
	std::cout<<"a"<<std::endl;
	pid_t pid = fork();
	return 0;
	//c语言 输出aa
	printf("a");
	pid_t pid = fork();
	return 0;
	//printf 只把数据输出到缓存区 return 0 程序终止退出后才将缓存区的内容输出到显示器
	//子进程可以继承父进程的缓存区 而父进程没有刷新缓存 所以会输出两个a
}
```
### exec库函数族 
fork创建子进程后 子进程执行的是和父进程相同的程序(可以通过if(pid==0?)来执行不同的代码分支) 

子进程往往调用exec函数来执行另一个程序 当进程调用exec函数时 该进程的用户空间代码和数据被新的程序替换

调用exec并不创建新进程 所以调用exec前后 该进程的id并不改变

在bash中执行的程序都是bash的子程序 用exec执行
函数原型
```c++
#include <unistd.h>
extern char **environ;

int execl(const char *pathname, const char *arg, ...
	       /* (char  *) NULL */);
int execlp(const char *file, const char *arg, ...  //file为文件名 则在$path中寻找对应命令 为目录 则在传入目录中找命令
	       /* (char  *) NULL */);  //仅在出错的时候返回-1
int execle(const char *pathname, const char *arg, ...
	       /*, (char *) NULL, char *const envp[] */);
int execv(const char *pathname, char *const argv[]);
int execvp(const char *file, char *const argv[]); //加载一个进程 使用自定义环境变量env
int execvpe(const char *file, char *const argv[],
	       char *const envp[]);
exec l(list)命令行参数列表 p(path)搜索file时使用path变量 v(vector)使用命令行参数数组 e(environment)使用环境变量数组
execve 是真正的系统调用 
```
execlp函数 加载一个进程 借助path环境
```c++
int main(int argc, char* argv[]) {
	pid_t pid = fork();
	if (pid == 0) { //子进程
		//execlp("ls", "-l", "-h", NULL);//错误写法 第二个参数是从argv[0]开始计算
		execlp("ls", "ls", "-l", "-h", NULL);//成功无返回值
		perror("exec error");
		exit(1);
	}
	return 0;
}
```
execl函数 同一个目录下有一个test可执行程序
```c++
int main(int argc, char* argv[]) {
	pid_t pid = fork();
	if (pid == 0) { //子进程
		//execlp("/bin/ls", "ls", NULL);//成功无返回值
		execlp("./test", "./test", NULL);//成功无返回值
		perror("exec error");
		exit(1);
	}
	return 0;
}
```
### wait/waitpid函数
函数原型
```c++
#include <sys/types.h> 包含在#include <unistd.h>
#include <sys/wait.h>

pid_t wait(int *wstatus);
//功能：1、阻塞等待子进程退出 2、回收子进程残留资源 3、获取子进程结束状态(退出原因)
//参数：传出参数 借助宏可以查看子进程结束状态 返回值： 成功返回子进程pid 失败返回-1 
pid_t waitpid(pid_t pid, int *wstatus, int options);
//参数1 指定回收某个进程 传-1 就和wait回收一样 可以回收分离出去的子进程
//传0 回收和当前调用waitpid一个进程组的所有子进程(也就是没有分离出去的所有子进程)
//传<-1回收指定进程组内的任意子进程 如果子进程分离单独是一个进程组可以传负的该子进程的pid表示回收这个进程组
//参数3 设置非阻塞 不设置传0       返回值 比wait多一个 0:函数调用时 参数3指定了WNOHANG(不阻塞)并且没有子进程结束

//一次wait、waitpid函数调用 只能回收一个子进程 对于wait 由于没有指定哪个子进程 当存在多个子进程的时候 回收第一个结束的子进程
```
使用宏 查看子进程退出值和异常终止信号
```c++
int main(int argc, char* argv[]) {
	pid_t pid, wpid;
	int status;
	pid = fork();
	if (pid == 0) {
		std::cout << "子进程" << getpid() << "going to sleep 5s" << std::endl;
		sleep(5);
		std::cout << "子进程死亡" << std::endl;
		return 2;//返回一个正常终止的值
	}
	else {
		wpid = wait(&status);  //可以传NULL表示不关心子进程结束原因
		if (WIFEXITED(status)) {//若为真 说明进程正常终止
			std::cout << "子进程正常退出返回" << WEXITSTATUS(status) << std::endl;//返回2
		}
		if (WIFSIGNALED(status)) {//若为真 说明进程异常终止
			std::cout << WTERMSIG(status) << "信号导致子进程异常退出" << std::endl;
		}
		if (WIFSTOPPED(status)) {//若为真 说明进程处于暂停状态
			std::cout << WSTOPSIG(status) << "信号导致子进程暂停" << std::endl;
			if (WIFCONTINUED(status)) std::cout << "子进程暂停后已继续运行" << std::endl;
		}
		std::cout << "父进程等待子进程" << wpid << "结束" << std::endl;
	}
	return 0;
}
```
## *进程通信(IPC)

进程之间不能相互访问 要交换数据必须通过内核 进程A在内核开辟一块缓冲区(默认4096B)后 将数据从用户空间拷贝过去 进程B再从缓冲区中读走数据 这种机制称为进程间通信(IPC)

常用的IPC方法有：1、管道(使用最简单 要有血缘关系 父子或兄弟)2、信号(开销最小)3、共享映射区(无血缘关系)4、本地套接字(最稳定) 此外还有 文件、共享内存、消息队列
### 管道pipe(伪文件)
管道的原理:管道实为内核使用环形队列(fifo)机制 借助内核缓冲区(4k)实现

管道的特质:

1.其本质是一个伪文件(管道、字符、块、套接字)实为内核缓冲区

2.由两个文件描述符引用 一个表示读端 一个表示写端

3.规定数据从管道的写端流入管道 从读端流出

管道的局限性:

1.数据不能进程自己写 自已读

2.管道中数据不可反复读取 一旦读走 管道中不再存在

3.采用半双工通信方式 数据只能在单方向上流动

可以有一个写端 多个读端 或多个写端 一个读端
#### pipe函数
函数原型
```c++
#include <unistd.h>
//成功返回0失败返回-1 参数pipedf[0]表示读端 [1]表示写端
int pipe(int pipefd[2]); //创建并自动打开管道 需要手动关闭管道
```
```c++
int main() {
	int fd[2];
	pid_t pid;
	const char* str = "hello";
	char buf[1024];
	//创建完管道是同时有读和写的 fork后子进程也是
	//要让父进程关闭读端 子进程关闭写端
	pipe(fd);
	pid = fork();
	if (pid > 0) {
		close(fd[0]);  //关闭读端  
		write(fd[1], str, strlen(str));  //写入管道
		sleep(1);
		close(fd[1]); //手动关闭写端
	}
	else if (pid == 0) {
		close(fd[1]);  //关闭写端
		int ret = read(fd[0], buf, sizeof(buf));  //读走管道
		write(STDOUT_FILENO, buf, ret);//向终端写管道内容
		close(fd[0]); //手动关闭读端
	}
	return 0;
}
```
父子进程实现管道符操作 ls | wc -l
```c++
int main() {
	int fd[2];

	pipe(fd);//创建一个管道
	pid_t pid = fork();
	if (pid == 0) {
		close(fd[0]);  //关闭读端  
		dup2(fd[1], STDOUT_FILENO);//将标准输出 改到写端
		execlp("ls", "ls", NULL);
	}
	else if (pid > 0) {
		close(fd[1]);  //关闭写端
		dup2(fd[0], STDIN_FILENO);  //将标准输入 改到读端
		execlp("wc", "wc", "-l", NULL);
	}
	return 0;
}
```
兄弟进程实现管道符操作 ls | wc -l
```c++
int main() {
	int fd[2], i;
	pipe(fd);//创建一个管道
	//循环创建两个子进程
	for (i = 0; i < 2; i++) {
		if (fork() == 0)break;
	}
	if (i == 2) {//父进程
		close(fd[0]);//关闭读端
		close(fd[1]);//关闭写端
		for (i = 0; i < 2; i++)wait(NULL);
	}
	else if (i == 0) {//兄进程
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		execlp("ls", "ls", NULL);
	}
	else if (i == 1) {//弟进程
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		execlp("wc", "wc", "-l", NULL);
	}
	return 0;
}
```
#### 命名管道FIFO(文件)
解决没有血缘关系的进程间通信 是文件且能阻塞

mkfifo命令创建命名管道
```bash
mkfifo 管道名
```
使用库函数mkfifo
```c++
#include <sys/types.h> 包含在#include <unistd.h>
#include <sys/stat.h>

int mkfifo(const char *pathname, mode_t mode);
//成功返回0 失败返回-1 参数：管道名 权限
//本质还是创建一个文件(FIFO) 一个以open(fd,O_WRONLY)->write 另一个open(fd,O_RDONLY)->read
```

#### 普通文件实现进程间通信
使用普通文件test.txt文件实现两个进程间的通信
```c++
//进程1
int main(int argc, char* argv[]) {
	char buf[1024];
	char* s = "---------1write------";  //要写入的信息
	int fd = open("test.txt", O_RDWR | O_TRUNC | O_CREAT, 0644);
	write(fd, s, strlen(s));  //将信息写入到test.txt文件中
	std::cout << "1写入完毕" << std::endl;
	sleep(5);  //睡眠5秒 让进程2去读取信息并再写入信息

	lseek(fd, 0, SEEK_SET);  //将偏移量移动到文件开头 再去读test.txt里的内容
	int ret = read(fd, buf, sizeof(buf));
	ret = write(STDOUT_FILENO, buf, ret);
	close(fd);
	return 0;
}
```
```c++
//进程2
int main(int argc, char* argv[]) {
	char buf[1024];
	char* s = "---------2write------"; //要写入的信息
	sleep(2);//先睡眠2秒 让进程1写完信息

	int fd = open("test.txt", O_RDWR);
	int ret = read(fd, buf, sizeof(buf));
	write(STDOUT_FILENO, buf, ret);//将读到的信息打印的终端
	write(fd, s, strlen(s));//接着往文件里面写入信息s
	std::cout << "2读完并写完了" << std::endl;
	close(fd);
	return 0;
}
```
### 存储映射I/O
存储映射I/O(Mempry-mapped I/O) 使一个磁盘文件与内存空间中的一个缓冲区相映射 于是当从缓冲区中取数据 
就相当于读文件中的相应字节 于此类似 将数据存入缓冲区 则相应的字节就自动写入文件 
这样就可在不使用 read 和 write 函数的情况下 使用地址(指针)完成I/O操作

#### mmap函数
函数原型
```c++
#include <sys/mman.h>
//使用文件描述符 创建共享内存映射
void *mmap(void *addr, size_t length,
	int prot, int flags,int fd, off_t offset);
//参数 addr：指定映射区的首地址 通常传NULL 表示让系统自动分配
//1ength：共享内存映射区的大小 (<=文件的实际大小)
//prot：共享内存映射区的读写属性 PROT_READ、PROT_WRITE、PROTREAD|PROT_WRITE
//flags：标注共享内存的共享属性 MAP_SHARED、MAP_PRIVATE(对内存的修改不会映射到磁盘)
//MAP_ANON、MAP_ANONYMOUS用来创建匿名映射区(无需一个文件)
//fd：用于创建共享内存映射区的那个文件的 文件描述符
//offset：偏移位置 必须是page大小(4K)的整数倍 默认是0 表示映射文件的全部
//返回值void*(通用的指针类型) 成功返回映射区的首地址 失败返回MAP_FAILED

//释放映射区
int munmap(void *addr, size_t length);
//addr：mmap的返回值 length：映射区的大小 返回值 成功0失败-1
```
使用mmap在不使用 read 和 write 函数的情况下 使用地址(指针)完成I/O操作
```c++
void sys_err(const std::string& s) {
	perror(s.c_str());
	exit(1);
}
int main(int argc, char* argv[]) {
	int fd = open("test.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)perror("open error");

	/*lseek(fd, 9, SEEK_END);
	write(fd, "a", 1);*/
	ftruncate(fd, 10);
	int len = lseek(fd, 0, SEEK_END);

	char* p = (char*)(mmap(nullptr, len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0));
	if (p == MAP_FAILED)sys_err("mmap error");
	close(fd);  //创建完映射区 即可关闭文件
	//使用p对文件进行读写操作
	strcpy(p, "hello-----------");
	std::cout << "--" << p << std::endl;

	int ret = munmap(p, len);
	if (ret == -1)sys_err("munmap error");

	return 0;
}
```
使用mmap的注意事项(出错率高 一定检查返回值)：
```
1.用于创建映射区的文件大小为 0 实际指定非0大小创建映射区 出 总线错误
2.用于创建映射区的文件大小为 0 实际指定0大小创建映射区 出 无效参数 
3.用于创建映射区的文件读写属性为只读 映射区属性为读写 出 无效参数
4.创建映射区需要read权限 mmap的读写权限 <= 文件的open权限 只写不行
5.文件描述符fd 在mmap创建映射区完成即可关闭 后续访问文件用 地址访问
6.offset 必须是4096(页大小)的整数倍 (MMU 映射的最小单位为一页)
7.对申请的映射区内存 不能越界访问
8.munmap用于释放的地址必须是mmap申请返回的地址 杜绝指针++操作
```
保险调用mmap：
1.open(O_RDWR)
2.MMAP(NULL,有效文件大小,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);

mmap父子进程间通信
```c++
int var = 100;
int main(int argc, char* argv[]) {
	int fd = open("test.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)perror("open error");
	int ret = unlink("test.txt");
	if (ret == -1)sys_err("unlink error");
	ftruncate(fd, 4);

	//int* p = (int *)(mmap(nullptr,4 , PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0));
	int* p = (int *)(mmap(nullptr,4 , PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0));  //改为私有
	if (p == MAP_FAILED)sys_err("mmap error");
	close(fd);  //创建完映射区 即可关闭文件

	int pid = fork();
	if (pid == 0) {//子进程
		*p = 50;   //写共享内存
		var = 200;//修改全局变量
		std::cout << "子进程：*p = " << *p << "var = " << var << std::endl;
	}
	if (pid > 0) {
		sleep(1);
		std::cout << "父进程：*p = " << *p << "var = " << var << std::endl;
		wait(NULL);

		int ret = munmap(p, 4);  //释放映射区
		if (ret == -1)sys_err("munmap error");
	}

	return 0;
}
```
改为匿名映射(非血缘关系不能使用)
```c++
int main(int argc, char* argv[]) {
	//改成匿名映射后 无需open文件 文件大小任意设置 文件描述符传-1
	int* p = (int*)(mmap(nullptr, 10, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0));
	if (p == MAP_FAILED)sys_err("mmap error");

	int pid = fork();
	if (pid == 0) {//子进程
		*p = 50;   //写共享内存
		var = 200;//修改全局变量
		std::cout << "子进程：*p = " << *p << "var = " << var << std::endl;
	}
	if (pid > 0) {
		sleep(1);
		std::cout << "父进程：*p = " << *p << "var = " << var << std::endl;
		wait(NULL);

		int ret = munmap(p, 4);  //释放映射区
		if (ret == -1)sys_err("munmap error");
	}

	return 0;
}
Linux下两个特殊文件： /dev/zero 摇钱树 可以读很多空洞 /dev/null 文件黑洞 写不满
当MAP_ANON无法使用的时候 使用open("/dev/zero", 权限) mmap中文件大小也可以任意设置 (非血缘关系也不能使用)
```
mmap非血缘关系进程间通信 

【针对非血缘关系进程间通信 mmap和FIFO的区别】mmap(数据可以重复读取 数据在内存上)FIFO(数据只能一次读取 读完管道就清空了)
```c++
struct student {
	int id;
	char name[10];//使用固定大小的字符数组 不能是std::string
 	//mmap映射的内存区域必须是固定大小的 而string是动态分配的内存
	int age;
};
//进程A
int main(int argc, char* argv[]) {
	int fd = open("test.txt", O_RDWR | O_CREAT | O_TRUNC);
	if (fd == -1)sys_err("open error");
	student stu = { 1,"n_m",18 };
	ftruncate(fd, sizeof(stu));
	struct student* p = (struct student*)mmap(NULL, sizeof(stu), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	close(fd);
	if (p == MAP_FAILED)sys_err("mmap error");
	int i = 5;
	while (i) {
		memcpy(p, &stu, sizeof(stu));
		stu.id++;
		sleep(1);
		i--;
	}
	munmap(p, sizeof(stu));
	return 0;
}
//进程B
int main(int argc, char* argv[]) {
	int fd = open("test.txt", O_RDONLY);
	if (fd == -1)sys_err("open error");
	student stu;
	struct student* p = (struct student*)mmap(NULL, sizeof(stu), PROT_READ, MAP_SHARED, fd, 0);
	close(fd);
	if (p == MAP_FAILED)sys_err("mmap error");
	int i = 5;
	while (i) {
		std::cout << "id = " << p->id << " name = " << p->name << " age = " << p->age << std::endl;
		sleep(1);
		i--;
	}
	munmap(p, sizeof(stu));
	return 0;
}
```
### 信号
信号的共性：1、简单2、不能携带大量信息3、满足某个特设条件才发送

信号的机制：A向B发送信号 B收到信号之前执行自己的代码 收到信号后 不管执行到程序的什么位置 都要暂停运行去处理信号 
处理完毕再继续执行 与硬件中断类似一一异步模式 但信号是软件层面上实现的中断 早期常被称为"软中断" (每个进程收到的所有信号 都是由内核负责产生发送并处理的)

信号的特质：由于信号是通过软件方法实现 其实现手段导致信号有很强的延时性 但对用户来说 这个延迟时间非常短 不易察觉

与信号相关的事件和状态：

产生信号：
```
1.按键产生 如:Ctrl+c(中断终止)、Ctrl+z(暂停到后台可以通过命令fg恢复)、Ctrl+\(退出终止并生成core转储文件 用于调试程序崩溃的原因)
2.系统调用产生 如: kill、raise、abort
3.软件条件产生 如:定时器 alarme
4.硬件异常产生 如:非法访问内存(段错误)、除0(浮点数例外)、内存对齐出错(总线错误)
5.命令产生，如: kill 命令
```
递达:信号从内核产生后发送到进程 未决:信号产生后还没到达进程的状态(主要由阻塞(屏蔽)导致)

信号的处理方式：1、执行默认动作2、忽略(丢弃)3、捕捉(调用用户处理函数 类似catch)

使用命令kill -l查看所有信号
```bash
kill -l
```
信号的四要素：1、编号2、名称3、事件4、默认处理动作 使用man 7 signal 查看

#### kill函数
函数原型
```c++
#include <sys/types.h>
#include <signal.h>

int kill(pid_t pid, int sig); //发送信号给有权限发送的进程
```
```c++
int main(int argc, char* argv[]) {
	pid_t pid = fork();
	if (pid > 0) {
		std::cout << "父进程:" << getpid() << std::endl;
		while (1);
	}
	else if (pid == 0) {
		std::cout << "子进程：" << getpid() << "form" << getppid() << std::endl;
		sleep(2);
		kill(getppid(), SIGKILL);
	}
	return 0;
}
```
循环创建5个子进程 父进程用kill函数终止任一子进程
```c++

```
#### alarm函数(使用自然计时法)
每个进程有且仅有一个定时器

函数原型
```c++
#include <unistd.h>
//定时发送信号给当前进程
unsigned int alarm(unsigned int seconds); //返回0或者剩余的秒数(无失败)
```
取消定时器alarm(0);   
```
alarm(5); //定时为5秒
//过了3秒
alarm(4)；//返回2秒 重置定时器为4秒
//过了5秒
alarm(5); //返回0秒 重置定时器为5秒
alarm(0); //返回5秒
```
使用time ./demo 查看下面代码的实际时间=用户时间+系统时间+等待时间
```c++
int main(int argc, char* argv[]) {
	int i;
	alarm(1);
	for (i = 0;; i++)std::cout << i << std::endl;
	return 0;
}
```
#### setitimer/getitimer函数
函数原型
```c++
#include <sys/time.h>

int getitimer(int which, struct itimerval *curr_value);
int setitimer(int which, const struct itimerval *new_value,
                     struct itimerval *old_value);
//成功返回0 失败返回-1
//which:指定定时方式
//1、【自然计时】ITIMER_REAL(14):计算自然时间 同alarm 发送SIGALRM信号
//2、【虚拟空间计时(用户空间)】ITIMER_VIRTUAL(26):只计算进程占用cpu的时间 发送SIGVTALRM信号
//3、【运行时计时(用户+内核)】ITIMER_PROF(27):计算占用cpu及执行系统调用的时间 发送SIGPROF信号
//new_value：同alarm的seconds old_value同alarm的返回值
struct itimerval {
	struct timeval it_interval; /* 用来设定两次定时任务之间的间隔时间 */
	struct timeval it_value;    /* 定时的时长 */
};

struct timeval {
	time_t      tv_sec;         /* seconds */
	suseconds_t tv_usec;        /* microseconds */
};
```
```c++
void func(int sig) {
	std::cout << "hello" << std::endl;
}

int main(int argc, char* argv[]) {
	struct itimerval it, oldit;
	signal(SIGALRM, func);//SIGALRM信号的捕捉函数

	it.it_value.tv_sec = 2;//设置定时时长2秒
	it.it_value.tv_usec = 0;//0微妙

	it.it_interval.tv_sec = 5;//设定两次定时任务之间的间隔为5秒
	it.it_interval.tv_usec = 0;

	//一次设置两个闹钟 do while do定时2秒 while定时5秒
	if (setitimer(ITIMER_REAL, &it, &oldit) == -1)sys_err("setitimer error");
	while (1);
	return 0;
}
```
### 信号集
阻塞信号集/信号屏蔽字(位图):将某些信号加入集合 对他们设置屏蔽(屏蔽信号只是将信号处理延后执行 而忽略表示丢弃这个信号) 当屏蔽x信号后 再收到该信号 该信号的处理将推后(解除屏蔽后)

未决信号集(位图):1.信号产生未决信号集中描述该信号的位立刻翻转为1 表信号处于未决状态 当信号被处理 对应位翻转回为0 这一时刻往往非常短暂
2.信号产生后由于某些原因(主要是阻塞)不能抵达 这类信号的集合称之为未决信号集 在屏蔽解除前 信号一直处于未决状态

通过操作阻塞信号集来间接改变未决信号集(不能直接操作)
#### 信号集操作 库函数 修改自己的set
函数原型
```c++
#include <signal.h>

sigset_t set;//自定义信号集

int sigemptyset(sigset_t *set);//将集合(二进制)都置为0
int sigfillset(sigset_t *set);//将集合(二进制)都置为1
int sigaddset(sigset_t *set, int signum);//将信号signum置为1
int sigdelset(sigset_t *set, int signum);//将信号signum置为0
int sigismember(const sigset_t *set, int signum);//查看signum是否在集合中
```
#### sigprocmask/sigpending函数 通过自己的set修改阻塞信号集mask/查看未决信号集pending
函数原型
```c++
#include <signal.h>
//用来屏蔽信号、解除信号 本质是读取或修改进程的信号屏蔽字(PCB中)
int sigprocmask(int how, const sigset_t *set, sigset_t *oldset);
//参数 how: 1、SIG_BLOCK：阻塞(位或mask=mask|set) 2、SIG_UNBLOCK：解除阻塞(取反再位与mask=mask&~set)  3、SIG_SETMASK：设置屏蔽集(mask=set)
//*set 传入参数 *oldset传出参数

//读取当前进程的未决信号集pending
int sigpending(sigset_t *set);//set传出参数 pending

//成功返回0 失败返回-1
```
#### signal/sigaction函数
signal函数原型
```c++
#include <signal.h>

typedef void (*sighandler_t)(int); //函数指针 指向返回值为空 参数为int
//注册一个信号捕捉函数 捕获是操作系统内核做的 而不是这个函数
sighandler_t signal(int signum, sighandler_t handler);
//返回一个函数指针 
```
```c++
void sig_catch(int sig) {
	std::cout << "捕获信号" << sig << std::endl;
}
int main(int argc, char* argv[]) {
	signal(SIGINT, sig_catch);
	while (1);

	return 0;
}
```
sigaction函数原型
```c++
#include <signal.h>

int sigaction(int signum, const struct sigaction *act,
                     struct sigaction *oldact);

struct sigaction {
	//......
	void     (*sa_handler)(int);  //函数指针 类似signal的第二个参数
	sigset_t   sa_mask; //不同于阻塞信号集mask作用域为整个进程存活时间 它仅作用于当前信号捕捉函数
	int        sa_flags; //一般传0 表示屏蔽这个信号本身
};
```
信号捕捉特性：

特性1、进程正常运行时 默认PCB中有一个信号屏蔽字 假定为mask 它决定了进程自动屏蔽哪些信号 当注册了某个信号A捕捉函数 捕捉到信号A以后 要调用该函数 而该函数有可能执行很长时间 在这期间所屏蔽的信号是由masksa_mask和mask共同来指定的 调用完信号A处理函数后再恢复为mask

特性2、A信号捕捉函数执行期间 A信号自动被屏蔽

特性3、阻塞的常规信号不支持排队 产生多次只记录一次(后 32 个实时信号支持排队)
```c++
void sig_catch(int sig) {
	std::cout << "捕获信号" << sig << std::endl;
	sleep(10);//10秒内屏蔽sig信号 特性3
}
int main(int argc, char* argv[]) {
	struct sigaction act, oldact;
	act.sa_handler = sig_catch;  //设置回调函数
	sigemptyset(&act.sa_mask);   //清空sa_mask屏蔽字 只在sig_catch工作时有效
	act.sa_flags = 0;	
	sigaction(SIGINT, &act, &oldact);
	while (1);
	return 0;
}
```
内核实现信号的捕获过程
![image](https://github.com/Amaz1ngJR/Technology/assets/83129567/471db1b5-5248-43f3-a14c-0c9d02f5c5c6)

#### SIGCHLD信号
产生条件(子进程状态改变就会产生)：子进程终止时、子进程接收到SIGSTOP信号停止时、子进程处在停止态接受到SIGCONT后唤醒时

借助SIGCHLD信号回收子进程
```c++
void catch_child(int sig) {
	pid_t pid;
	while ((pid = wait(NULL)) != -1) {//循环回收 这里不用while的话 会有僵尸进程
		std::cout << "回收子进程" << pid << std::endl;
	}
}
int main(int argc, char* argv[]) {
	pid_t pid;
	//设置阻塞 防止父进程的信号捕捉函数还没有注册完 子进程先死了
	sigset_t set;
	sigemptyset(&set);
	sigaddset(&set, SIGCHLD);
	sigprocmask(SIG_BLOCK, &set, nullptr);
	int i;
	for (i = 0; i < 5; i++) {
		if ((pid = fork()) == 0) break;
	}
	if (i == 5) {
		struct sigaction act;
		act.sa_handler = catch_child;
		sigemptyset(&act.sa_mask);
		act.sa_flags = 0;
		sigaction(SIGCHLD, &act, nullptr);
		//父进程注册完信号捕捉函数 解除阻塞
		sigprocmask(SIG_UNBLOCK, &set, nullptr);
		std::cout << "父进程" << getpid() << std::endl;
		while (1);
	}
	else std::cout << "创建子进程" << getpid() << std::endl;

	return 0;
}
```
## *中断系统调用
系统调用可分为两类:慢速系统调用和其他系统调用

1.慢速系统调用：可能会使进程永远阻塞的一类(如read、writepause、wait...) 如果在阻塞期间收到一个信号 该系统调用就被中断 不再继续执行(早期);也可以设定系统调用是否重启 (可修改sa_flags参数来设置被信号中断后系统调用是否重启 SA_INTERRURT不重启 SA_RESTART重启)

2.其他系统调用:getpid、getppid、fork....
 
## *进程组(作业)和会话
多个进程形成一个进程组 多个进程组形成一个会话
```
当父进程创建子进程的时候 默认子进程与父进程属于同一进程组 进程组D==第一个进程D(组长进程) 所以 组长进程的标识为 进程组ID==进程ID
可使用kill -SIGKILL -进程组id(负数)来将整个进程内的进程全部杀死
进程组的生存期为 进程组创建到最后一个进程离开 一个进程可以为自己或子进程设置进程组ID
```
创建一个会话需要注意以下几点注意事项:
```
1.调用进程不能是进程组组长 
2.该进程变成新会话首进程(session header)、成为一个新进程组的组长进程
3.需有root 权限 (ubuntu 不需要)
4.新会话丢弃原有的控制终端 该会话没有控制终端 无法完成交互 
5.建立新会话时 先调用fork 父进程终止 子进程调用 setsid
```
### getsid/setsid函数
函数原型
```c++
#include <unistd.h>

pid_t getsid(pid_t pid); //获取进程所属会话ID pid为0表示查看当前进程sessionID
pid_t setsid(void);//创建一个会话 并以自己的ID设置进程组ID 同时也是新会话的ID (非进程组组长的话 返回值等于getpid)

//成功返回调用进程的会话id 失败返回-1
```
```c++
int main(int argc, char* argv[]) {
	pid_t pid;
	if ((pid = fork()) < 0) sys_err("fork error");
	else if (pid == 0) {
		std::cout << "子进程的PID：" << getpid() << std::endl;
		std::cout << "子进程的组ID：" << getpgid(0) << std::endl;
		std::cout << "子进程的会话ID：" << getsid(0) << std::endl;
		sleep(2);
		setsid();  //子进程非组长进程 将其成为新会话首进程 成为组长进程
		std::cout << "发生改变" << std::endl;
		std::cout << "子进程的PID：" << getpid() << std::endl;
		std::cout << "子进程的组ID：" << getpgid(0) << std::endl;
		std::cout << "子进程的会话ID：" << getsid(0) << std::endl;
	}

	return 0;
}
```
### 守护进程
Daemon(精灵)进程 是Linux 中的后台服务进程 通常独立于控制终端并且周期性地执行某种任务或等待处理某些发生的事件 一般采用以d 结尾的名字

Linux 后台的一些系统服务进程 没有控制终端 不能直接和用户交互 不受用户登录、注销的影响 一直在运行着 他们都是守护进程 如:预读入缓输出机制的实现;ftp 服务器;nfs 服务器等

创建守护进程 最关键的一步是调用 setsid 函数创建一个新的 Session 并成为 Session Leader

创建守护进程模型
```
1.创建子进程 父进程退出:所有工作在子进程中进行形式上脱离了控制终端
2.在子进程中创建新会话:setsid()函数 使子进程完全独立出来 脱离控制
3.改变当前目录:chdir()函数 防止占用可卸载的文件系统
4.重设文件权限掩码:umask()函数 防止继承的文件创建屏蔽字拒绝某些权限 增加守护进程灵活性
5.关闭文件描述符(或将0、1、2重定向到/dev/null):继承的打开文件不会用到 浪费系统资源 无法卸载

6.开始执行守护进程核心工作 守护进程退出处理程序模型
```
```c++
int main(int argc, char* argv[]) {
	pid_t pid = fork();
	if (pid > 0)exit(0);//父进程终止
	pid = setsid(); //创建新会话
	if (pid == -1)sys_err("setsid error");

	int ret = chdir("/home/yjr/"); //改变工作目录位置
	if (ret == -1)sys_err("chdir error");
	umask(0022);  //改变文件访问权限掩码

	close(STDIN_FILENO);//关闭文件描述符0
	int fd = open("/dev/null", O_RDWR);//fd ---> 0
	if (fd == -1)sys_err("open error");
	dup2(fd, STDOUT_FILENO);//重定向文件描述符1
	dup2(fd, STDERR_FILENO);//重定向文件描述符2

	while (1);//模拟守护进程业务 

	return 0;
}
```

## *线程相关

### 线程概念 
进程和线程的区别(内核眼中 二者相同)
```
进程:独立地址空间 拥有 PCB·
线程(LWP:轻量级进程 在linux环境下本质还是进程):有独立的 PCB 但没有独立的地址空间(共享)
区别:在于是否共享地址空间
Linux下 线程是最小的执行单位 进程是最小分配资源单位 可看成是只有一个线程的进程
```
使用 ps -Lf 进程id 得到线程号(不是线程ID) 线程号是给cpu用来分配时间的 线程ID是给进程识别线程的

线程共享：
```
1.文件描述符
2.每种信号的处理方式(信号和线程最好不要同时使用)
3.当工作目录
4.用户ID 和组ID
5.内存地址空间 (.text/.data/.bss/heap/共享库  线程间共享全局变量(errno除外) 而进程不共享全局变量 只能借助mmap)
```
线程不共享：
```
1.线程id
2.处理器现场和栈指针(内核栈)
3.独立的栈空间(用户空间栈)
4.errno变量(全局变量)
5.信号屏蔽字
6.调度优先级
```
线程ID：可以使用pthread_self(void)查看线程ID同getpid 是进程内部的识别标志(两个进程间的线程ID允许相同)

### pthread_create库函数 
函数原型
```c++
#include <pthread.h>

int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
	void *(*start_routine) (void *), void *arg); 
//参数: *thread传出参数 新创建线程的线程ID  *attr描述线程属性 *start_routine函数指针 *arg函数参数
//成功返回0 失败返回-1 编译和链接的时候加 -lpthread
```
循环创建多个子线程
```c++
void sys_err(const int& ret) {//线程中的error 不能再使用perror了
	std::cout << "error:" << strerror(ret) << std::endl;
	exit(1);
}

void* func(void* arg) {
	int i = *((int*)arg);
	sleep(i);
	std::cout << "第" << i + 1 << "个线程" << "pid = "
		<< getpid() << " tid = " << pthread_self() << std::endl;
	delete static_cast<int*>(arg); // 释放内存
	return nullptr;//返回函数调用者
}
int main(int argc, char* argv[]) {
	std::cout << "main: pid = " << getpid() << " tid = " << pthread_self() << std::endl;
	int ret, i; pthread_t tid;
	for (i = 0; i < 5; i++) {//循环创建5个线程
		int* arg = new int(i); // 为每个i的值分配内存
		ret = pthread_create(&tid, nullptr, func, static_cast<void*>(arg));
		if (ret)sys_err(ret);
	}
	pthread_exit((void *)0);
}
```
验证线程间共享全局变量
```c++
int var = 100;//主、子线程共享全局变量
void* func(void* arg) {
	var = 200;
	std::cout << "thread" << std::endl;
	return nullptr;
}
int main(int argc, char* argv[]) {
	std::cout << "var = " << var << std::endl;
	pthread_t tid;//线程ID pthread_create传出参数
	pthread_create(&tid, nullptr, func, nullptr);
	sleep(1);
	std::cout << "after pthread_create, var = " << var << std::endl;
	return 0;
}
```
### pthread_exit/pthread_join库函数
exit：退出当前进程
return: 返回到调用者
pthread_exit：退出当前线程

函数原型
```c++
#include <pthread.h>

void pthread_exit(void *retval);
int pthread_join(pthread_t thread, void **retval);// void **retval传出参数
```
```c++
struct thrd {
	int var;
	char str[256];
};

void* func(void* arg) {
	thrd* tval = new(thrd);
	tval->var = 100;
	strcpy(tval->str, "hello");
	return (void*)tval;
}
int main(int argc, char* argv[]) {
	pthread_t tid;//线程ID pthread_create传出参数
	thrd* retval;
	int ret = pthread_create(&tid, nullptr, func, nullptr);
	if (ret)sys_err(ret);
	ret = pthread_join(tid, (void**)&retval);
	if (ret)sys_err(ret);
	std::cout << "var = " << retval->var << " str = " << retval->str << std::endl;
	pthread_exit(nullptr);
}
```

### pthread_cancel库函数
杀死(取消)线程 对应于kill函数 对线程的取消并不是实时的 而是需要等待线程到达某个取消点
函数原型
```c++
#include <pthread.h>
int pthread_cancel(pthread_t thread); 杀死线程ID为thread的线程 需要取消点 成功返回0失败-1
```
```c++
void* func1(void* arg) {
	std::cout << "thread 1 returning" << std::endl;
        std::cout << "func1:pid = " << getpid() << " tid = " << pthread_self() << std::endl;
	return (void*)111;  //使用return取消线程
}

void* func2(void* arg) {
	std::cout << "thread 2 returning" << std::endl;
	pthread_exit((void*)222);  //使用pthread_exit
}

void* func3(void* arg) {
	while (1) {
		// std::cout << "thread 3 going to die in 3 seconds" << std::endl;
		// sleep(1);
		
		pthread_testcancel();//添加取消点 可以进内核的函数
	}
	return (void*)666;//在主函数中通过pthread_cancel退出
}
int main(int argc, char* argv[]) {
	pthread_t tid;//线程ID pthread_create传出参数
	void* ptr = nullptr;
	std::cout << "main:pid = " << getpid() << " tid = " << pthread_self() << std::endl;

	int ret = pthread_create(&tid, nullptr, func1, nullptr);
	if (ret)sys_err(ret);
	pthread_join(tid, &ptr);
	std::cout << "thread 1 exit code = " << (long)ptr << std::endl;

        pthread_create(&tid, nullptr, func2, nullptr);
	pthread_join(tid, &ptr);
	std::cout << "thread 2 exit code = " << (long)ptr << std::endl;

	pthread_create(&tid, nullptr, func3, nullptr);
	sleep(3);
	pthread_cancel(tid);
	pthread_join(tid, &ptr);
	std::cout << "thread 3 exit code = " << (long)ptr << std::endl;

	pthread_exit(nullptr);
}
```
### pthread_detach库函数
函数原型
```c++
#include <pthread.h>
int pthread_detach(pthread_t thread);//成功返回0 失败-1
```
```c++
int main() {
	pthread_t tid;//线程ID pthread_create传出参数

	int ret = pthread_create(&tid, nullptr, func1, nullptr);
	if (ret)sys_err(ret);
	ret = pthread_detach(tid);//分离子线程 线程结束会自动清理PCB 无需回收 
	if (ret)sys_err(ret);
	sleep(1);//让子进程先结束
	ret = pthread_join(tid, nullptr);//等待回收子线程
	std::cout << "join ret = " << ret << std::endl;
	if (ret)sys_err(ret);

	pthread_exit(nullptr);
}
```

### 线程和进程控制原语对比
| ------------------ | --------------- |
|   线程控制原语    |  进程控制原语     |
|   pthread_create()  |   fork()   |
|   pthread_self()    |   getpid()   |
|   pthread_exit()    |   exit()   |
|   pthread_join()    |   waitpid()   |
|   pthread_cancel()  |   kill()   |
|   pthread_detach    |  NULL  |








