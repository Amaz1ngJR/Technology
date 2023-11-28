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

### 创建动态库 lib_.so

## 文件IO

## 文件操作
