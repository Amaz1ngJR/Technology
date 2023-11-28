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

## 文件

### 文件前置
```bash
od-tcx filename  //查看文件的16进制表示形式
od-tcd filename  //查看文件的10进制表示形式
```

inode
其本质为结构体 存储文件的属性信息 如:权限、类型、大小、时间、用户、盘块位置·.····也叫作文件属性管理结构 
大多数的 inode 都存储在磁盘上 少量常用、近期使用的 inode会被缓存到内存中

目录项dentry
其本质是结构体 重要成员变量有两个(文件名，inode，...) 而文件内容(data)保存在磁盘盘块中

![image](https://github.com/Amaz1ngJR/Technology/assets/83129567/488d5a66-77c6-4dfb-9c68-394325165bb7)
