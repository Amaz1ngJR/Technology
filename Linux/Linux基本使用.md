# *配置

```
Win + R： mstsc 远程连接
```
```
Host 508
    HostName 10.1.115.92
Host 606
    HostName 10.1.21.164
    User yjr
    port 22
```
## 用户和权限
### 切换用户
su [ 选项 ]  [ 用户名 ]
```bash
su  //用户名省略切换到root
su - // - 表示重新加载新用户的环境变量
su -c 'ls /root' // c 表示允许在切换用户时指定要执行的命令
```
普通用户切换其他用户需要输入密码 root用户切换到其他用户 无需密码
### 配置sudo认证
切换到root用户 执行
```bash
visudo  //会自动通过vi编辑器打开/etc/sudoers
```
在文件的最后添加 并wq保存
```
yjr ALL=(ALL:ALL)         NOPASSWD:ALL
```
### 用户和用户组
参看系统中的用户和用户组
```bash
getent passwd  //查看当前系统中有哪些用户
//输出：  用户名：密码(x)：用户ID：组ID：描述信息：HOME目录：执行终端(默认bash)
getent group  //查看当前系统中有哪些用户组
//输出：  组名称：组认证(x)：组ID
```
增、删、改、查 用户和用户组(root用户下)
```bash
useradd [-g -d] 用户名  //创建用户
//-g指定用户的组(已经存在的组) 不指定会创建同名组并自动加入 如已存在同名组 必须使用-g
//-d指定用户HOME路径 不指定HOME目录默认在: /home/用户名
groupadd 用户组名       //创建用户组

userdel [-r] 用户名    //删除用户 -r删除用户的HOME目录
groupdel 用户组名      //删除用户组

usermod -aG 用户组 用户名 //将指定用户加入指定用户组

id [用户名]         //查看用户所属组 不提供用户名则查看自身
```
### 权限控制信息
```
ll  //参看详细的权限控制信息
-表示文件 d表示文件夹 l表示软链接 r表示读/查看权限 w表示写/修改权限 x表示执行/CD进入权限
```
![image](https://github.com/Amaz1ngJR/Technology/assets/83129567/7e44ca43-cc66-4dfc-ae40-ff97118cf509)
权限的数字序号：权限可以用3位数字代表 分别表示用户权限、用户组权限、其他用户权限

r记为4 w记为2 x记为1

0：无任何权限 即 ---

1：仅有x权限 即 --x

2：仅有w权限 即 -w-

3：有w和x权限 即 -wx

4：仅有r权限 即 r--

5：有r和x权限 即 r-w

6：有r和w权限 即 rw-

7：全部权限 即 rwx

修改权限信息
```bash
chmod u=rwx,g=rx,o=x test.txt  //将文件test.txt的权限修改为rwxr-x--x
chmod 751 test.txt //使用权限的数字序号
chmod -R 权限 文件夹名   //将文件夹以及文件夹内的全部内容的权限设置

chown [-R] [用户] [:][用户组] 文件或文件夹名   //root用户下 修改文件、文件夹的所属用户、用户组
```
## 日期与时间
date查看日期 日期计算
```bash
date  //查看系统的时间
date -d [+格式化字符串]  //-d 按照给定的字符串显示日期
%Y 年
%y 年份后两位 00-99
%m 月
%d 日
%H 时
%M 分
%S 秒
date -d "-1 day" // 一般用于日期计算
```
timedatectl 时区相关
```bash
timedatectl  //查看当前时区
timedatectl list-timezones  //列出所有可用的时区
sudo timedatectl set-timezone Asia/Shanghai  //设置时区
```
使用ntp程序自动校准系统时间
```bash
sudo apt install ntp  //安装ntp
systemctl start ntpd //启动
systemctl enable ntpd //开机自启
```

## IP地址与主机名
```bash
ping [-c num(检查次数)] ip或主机名  //检查指定的网络服务器是否联通
nmap 被查看IP  //使用nmap(需要安装)查看一个IP地址的对外端口
netstat -anp|grep 端口号  //查看指定端口的IP占用（安装net-tools）
```
```bash
ifconfig //查看本机的ip地址
hostname //查看主机名
hostnamectl set-hostname 主机名  //root下修改主机名
```
## 主机状态监控
### 查看CPU、内存使用情况

PID: 进程id

USER: 进程所属用户

PR:进程优先级，越小越高

NI: 负值表示高优先级，正表示低优先级

VIRT:进程使用虚拟内存，单位KB

RES:进程使用物理内存，单位KB

SHR:进程使用共享内存，单位KB

S:进程状态(S休眠,R运行Z僵死状态,N负数优先级,空闲状态)

TIME+:进程使用CPU时间总计 单位10毫秒

COMMAND:进程的命令或名称或程序文件路径
```bash
top  // 查看CPU、内存使用情况 
-p：只显示某个进程的信息
-d：设置刷新时间默认是5秒
-n：指定刷新次数 刷新完后退出
-i：不显示闲置或无用的进程
-c：显示产生进程的完整命令 默认是进程名
-u：查找特定用户启动的程序
-b：以非交互非全屏模式运行

//交互模式下
//按q退出
//按Shift + P 按CPU使用率对进程进行排序
//按Shift + M 按内存使用率对进程进行排序
//按m 切换显示内存信息
//按t 切换显示CPU信息
//按i/c 等同于-i/-c
```

### 查看显卡使用情况
```bash
nvtop
```
### 进程管理
```bash
ps [-e -f] //查看Linux系统中的进程信息 后续配合|grep tail
//-e 显示全部的进程 -f 以完全格式化的形式展示信息
//-a 显示终端上所有进程 包括其他用户的进程
//-u 显示进程的详细状态 -x 显示没有控制终端的进程

ps aux  //显示当前系统的所有进程

kill [-9] 进程ID //关闭进程 -9表示强制关闭
```
### 查看磁盘信息使用情况
```bash
df[-h] //-h 以更人性化的单位显示
```

安装sysstat
```bash
sudo apt install sysstat
```
### 查看CPU、磁盘的相关信息
```bash
iostat [-x][num1][num2]  // -x:显示更多信息 num1：刷新间隔 num2：刷新几次
```
### 网络状态监控
```bash
sar -n DEV num1 num2  //-n:查看网络 DEV：查看网络接口 num1：刷新间隔 num2：查看次数
```

## 下载、压缩、服务
### 软件下载安装x
mac上
```
brew install x
```
Linux上
```
sudo apt update
sudo apt install x
apt install x
```


CentOS:yum 和Ubuntu:apt 完全一致 需要root权限或者sudo 需要联网
```bash
yum [-y] [install | remove | search] 软件名称
-y 自动确认 install 安装 remove 卸载 search 搜索
```
```bash
sudo yum update  //更新所有已安装的软件包
sudo yum update package-name  //更新特定软件包
yum list installed  //列出已安装的软件包
yum info package-name  //查看软件包信息
sudo yum clean all  //清理缓存
yum deplist package-name  //查找依赖关系
```
### 网络文件下载
```bash
wget [-b] url(下载链接) //下载网络文件 -b 后台下载
curl url  //发送http网络请求 可用于下载文件、获取信息
curl -O http://example.com/file.zip  //保存下载的文件
curl -o localfile.zip http://example.com/file.zip //指定保存的文件名
```
### 压缩与解压缩
针对.tar/.gz/.bz2的压缩包
```bash
tar[-c|-x -z|-j -v -f -C] 参数1 参数2…
-c 创建压缩文件 用于压缩模式 -x 解压模式 -v查看压缩、解压进度
(-z表示gzip -j表示bzip2不使用默认tarball格式)
-f 要创建的文件 或要解压的文件 必须在所有选项的最后一个
-C 选择解压的目的地(单独使用) 不加表示解压到当前目录

tar -xvf test.tar -C /home/yjr    //将test.tar解压至/home/yjr
tar --delete -f test.tar file1   //将test.tar中的file1删除
tar -rvf test.tar newfile     //将newfile加入到test.tar中
```
针对.zip的压缩包
```bash
zip [-r] 参数1，参数2，…  //压缩 -r:被压缩的包含文件夹
zip test.zip newfile    //将newfile加入到test.zip中
zip -d test.zip file1 file2 ...  //将test.zip中的file1 file2 ...删除

unzip [-d] 压缩包名 //解压 -d(不同于zip)选择解压的目的地
```
### 服务
Linux系统很多软件能够被systemctl管理
```bash
systemctl start | stop | restart | status | enable | disable 服务名  //启动|停止|重启|查看状态|开机自启|开机不自启 一个服务
systemctl list-units --type=service  //列出所有正在运行的服务
systemctl is-enabled mysql  //查看服务mysql是否开机启动
```
## vim配置

Linux 没有盘符，只有一个根目录/，所有文件都在它下面

默认路径/etc/vim/vimrc,可以在~/路径下创建.vimrc进行配置 vim ~/.vimrc

```bash
set ai/ autoindent        "自动缩进，与上一行保持一致的自动空格
set cindent               "以C/C++模式缩进
set smartindent           "为c程序提供自动缩进
syntax enable
set syntax=on             "自动语法高亮
set tabstop=4             "设置Tab长度为4
set softtabstop =4        "统一缩进为4
set shiftwidth=4          "统一缩进为4
set number                "左侧显示行号
set showmatch             "显示括号配对，并高亮显示相匹配的括号
set matchtime=1           "匹配括号高亮的时间
set smarttab              "在行和段开始处使用制表符
set history=1000          "历史记录数
set ic/ ignorecase        "在查询模型与匹配模式下忽略大小写
set incsearch             "搜索逐字符高亮
set laststatus=2          "总是显示状态行
set ruler                 "显示状态栏标尺
set showmode              "文本输入模型下，加亮显示模式指示器
set showcmd               "在状态栏显示所执行的指令，未完成的指令片段
set warn                  "长行显示自动折行 自动换行显示
set scrolloff=6           "设置光标离窗口上下6行时窗口自动滚动
set noexpandtab           "不使用空格代替制表符
set nocompatible          "不使用vi的键盘模式，而是vim自己的
set nobackup              "禁止生成临时文件
set noswapfile            "禁止生成临时文件
set confirm               "在处理未保存或者只读文件的时候 弹出确认

"编码设置
set enc=utf-8
set fencs=utf-8,ucs-bom,shift-jis,gbk,gb2312,cp936,gb18030

"语言设置
set langmenu=zh_CN.UTF-8
set helplang=cn
```

## Byobu使用

安装byobu

```bash
sudo apt-get install byobu 
```

登录启动

```
byobu-enable 表示Byobu窗口管理器将在每次文本登录时自动启动
byobu-disable 表示Byobu窗口管理器将不再在登录时自动启动
```

```
F1/F9 配置菜单
F2新建窗口 
F3回到上一个窗口 
F4跳到下一个窗口
窗口操作：
F5重新加载文件
F6释放该次对话
F7进入复制/回滚模式(按q退出)
Ctrl+D 删除当前窗口
```
## man手册
```bash
man 1 用户命令
man 2 系统调用/函数
man 3 C标准库函数
man 4 设备和特殊文件
man 5 配置文件、数据文件和其他文件格式和约定
man 6 游戏
man 7 宏包和协议等杂项
man 8 只能由系统管理员运行的系统管理命令和守护进程
```
# *Linux基本指令

## ls 列出当前目录下的内容
```bash
ls              //仅列出当前目录下的文件和子目录
ls -l           //以详细列表格式显示文件和目录的信息 包括文件权限、所有者、文件大小、修改时间等
ls -h ->ls -lh  //必须搭配-l使用 以易于阅读的格式显示文件大小 例如 KB、MB、GB 等 
ls -a           //显示所有文件 包括以点(.)开头的隐藏文件 在 Linux 中 以点开头的文件被视为隐藏文件
ls -t           //按修改时间排序 最新修改的文件或目录显示在前面
ls -r           //反向排序 按字母顺序的相反顺序列出文件和目录
ls -R           //递归列出所有子目录的内容
ls -i           //显示每个文件或目录的 inode 号码 用于唯一标识文件系统中的每个对象
ls -S           //按文件大小排序 最大的文件显示在前面
ls -d           //仅显示目录本身，而不显示其内容。
ls --color      //以不同的颜色显示不同类型的文件。这需要终端支持颜色。
```
## stat 查看文件、目录的详细信息
```bash
stat [-c|-t|-l] name
```
## cd/pwd 切换/查看当前目录
```bash
cd                    //返回用户的home目录
cd [ 目录路径 ]        //进入指定目录
cd ..                 //返回上一级目录
cd ~/[ 子目录 ]        //进入home下的子目录
cd ../[ 相对路径 ]     //进入相对于当前的工作目录的路径
cd /path/to/directory  //进入绝对路径
pwd                    //显示当前工作目录
```
## touch/mkdir/mkfifo 创建文件/文件夹/管道
```bash
touch/mkdir filename          //创建文件/文件夹
touch/mkdir file1 file2 file3 //创建多个文件/文件夹
touch/mkdir /path/to/filename //特定(相对、绝对、特殊)路径下创建文件/文件夹
mkdir -p Dir/dir3/dir2/dir1   //递归在Dir下创建dir3 dir3下创建dir2 ...
```
## 硬链接和软链接
```
硬链接：
物理链接： 硬链接创建了一个与原始文件完全相同的新链接 它们共享相同的 inode 和磁盘空间
无法跨文件系统： 硬链接不能在不同的文件系统之间创建 因为 inode 号在不同文件系统之间通常不一致
文件删除： 当原始文件或其硬链接之一被删除时 实际的数据并不会被删除 直到所有链接都被删除
没有权限独立性： 所有硬链接都指向同一份数据 因此它们共享相同的权限和属性

硬链接用途：
节省磁盘空间：多个硬链接可以共享相同的数据块
备份：可以通过硬链接创建文件的备份 备份的文件共享相同的数据块 从而节省空间

软链接：
逻辑链接： 软链接创建了一个包含目标文件路径的独立文件 通过该文件可以找到目标文件
可以跨文件系统： 软链接可以在不同的文件系统之间创建 因为它们不依赖于 inode 号。
文件删除： 如果原始文件被删除或移动 软链接就会失效 称为“悬空链接”
有权限独立性： 软链接和目标文件有不同的 inode 号 因此它们可以有不同的权限和属性

软链接用途：
跨文件系统引用：软链接可以引用其他文件系统中的文件
简化文件路径：软链接可以创建一个简短的路径 指向较长或深层次的目标路径
更新和版本控制：在软链接中引用的文件可以轻松更换或更新
```

删除硬链接的时候 只是删除硬链接计数 当计数为0时 才”删除（别的文件可以覆盖这里 并不会物理上删除）”这个文件
```bash
ln 文件/文件夹名 链接名  //创建硬链接
ln test.txt test
stat test.txt
stat test
```
```bash
ln -s 参数1：文件/文件夹 参数2：要链接去的目的地   //创建软链接
//为了保证这个软链接在任意目录下都能使用 参数1写绝对路径 软链接大小为路径大小
ln -s /etc/yum ~/yum
ls -l //展示创建的链接
```
```bash
readlink t.soft  //看链接本身
```
## rm/rmdir 删除文件/文件夹
```bash
rm filename              //删除文件
rm file1 file2 file3     //删除多个文件
rmdir dirname            //删除空文件夹
rm -r dirname            //递归删除文件夹及其内容
rm -f filename           //强制删除而不询问
rm -i filename           //交互式删除 删除之前询问确认
rm -v filename           //详细显示进行的步骤
```
rm支持通配符* 来做模糊匹配
```bash
test*    //表示匹配任何以test开头的内容
*test    //表示匹配任何以test结尾的内容
*test*   //表示匹配任何包含test的内容
```
## cp 复制文件、文件夹
```bash
cp source /path/to/dir/         //将source文件复制到dir下
cp file1 file2  /path/to/dir/  //将多个文件复制到dir下
cp -r sourcedir /path/to/      //递归将文件夹及其内容复制到另一个目录下
cp -f source target/           //-f强制覆盖 不询问 如果要复制的地方已存在文件 会询问是否覆盖
cp -v source target/           //显示详细的复制过程
```
## mv 移动/改名文件、文件夹
```bash
mv old_name new_name           //改名
mv source /path/to/target/     //将source文件移动到target下   
mv source /path/to/target/new_name //将source文件移动到target下并改名
mv -f source target/           //-f强制覆盖 不询问 如果要移动的地方已存在文件 会询问是否覆盖

mv dir1/* dir2/   //将dir1下所有文件移动到dir2下
```

## 重定向符 >和>>
```bash
命令1 >file  //将左侧命令1的结果覆盖写入右侧文件中
命令1 >>file //将左侧命令1的结果追加写入右侧文件中
```
## 管道符 |
```bash
命令1 |  命令2   //将管道符左边命令1的结果 作为右边命令2的输入
```
## cat/more 查看文件内容
```bash
cat filename                    //终端显示文件内容
cat file1 file2                 //终端显示多个文件内容
cat file1 file2 > merged_file   //将多个文件内容写入到新文件中
cat -n filename                 //显示行号
cat -v filename                 //显示非打印字符 用^表示
cat filename | tail             //显示文件末尾 默认情况下显示最后10行
cat new_content >> existing_file//将内容追加到文件
```
## grep 从文件中通过关键字过滤文件行
```bash
grep -i "pattern" file.txt             //忽略大小写
grep -r "pattern" /path/to/directory   //递归搜索目录中的文件
grep -n "pattern" file.txt             //显示匹配行的行号
grep -v "pattern" file.txt             //反向匹配，显示不包含匹配模式的行
grep -c "pattern" file.txt             //只显示匹配行的计数
grep -A 2 "pattern" file.txt           //显示匹配行及后面两行 -A num或-B num或-C num
grep --color "pattern" file.txt        //高亮显示匹配的文本
grep -E "pattern" file.txt             //使用扩展正则表达式
grep -w "pattern" file.txt             //仅匹配整个单词 而不是匹配包含该模式的所有单词
```
## wc 数量统计
```bash
wc filename             //统计文件的:行数 字数 字符数
wc file1 file2 file3    //统计多个文件的:行数 字数 字符数
wc -l filename          //只统计文件的行数
wc -w filename          //只统计文件的字数
wc -c filename          //只统计文件的字符数
wc -m filename          //只统计文件的字符数 忽略多字节字符
wc -L filename          //显示文件中最长行的长度
```
## echo 输出指定内容
```bash
echo hello     //输出hello
echo "hello "  //输出hello 尽量带"" 否则空格隔开容易视为第二个命令
```
## 环境变量
```bash
export 变量名=变量值 //临时设置
export a=6
echo $a  //$符号被用于取“变量”的值 配合echo可以通过echo $变量输出值

配置~/.bashrc文件    //针对当前用户永久生效
配置/etc/profile文件//针对所有用户永久生效
通过 source 配置文件  进行立刻生效
```
## 反引号`
```bash
echo pwd    //输出pwd
echo `pwd`  //将被反引号`包围的内容视为命令去执行
```
## tail 查看文件尾部的内容 跟踪文件更新
```bash
tail filename        //显示文件末尾的内容 默认显示文件末尾的最后 10 行
tail file1 file2     //同时显示多个文件的末尾内容
tail -n 2 filename   //显示最后2行文件末尾内容 可省略n 直接 tail -2 filename
tail -c 2 filename   //显示文件末尾2字节的内容
tail -f filename     //实时监视文件的变化

```
## which/find 查找
```bash
which 命令1      //查找命令1的程序文件存放的位置
which -a 命令1   //查找所有匹配的命令 而不仅仅是第一个
find /path/to/search -name filename.txt //在指定路径下搜索文件名name为 filename.txt 的文件
find /path/to/search -type f            //在指定路径下搜索所有普通文件
find /path/to/search -type d            //在指定路径下搜索所有目录
find /path/to/search -size +1M          //在指定路径下搜索文件大小 大于 1MB 的文件
find /path/to/search -mtime -7          //在指定路径下搜索最近 7 天内修改过的文件
//组合查找 在指定路径下搜索文件名匹配 *.txt、类型为文件且大小大于 1MB 的文件
find /path/to/search -name "*.txt" -type f -size +1M
//在指定路径下搜索文件名匹配 *.log 的文件 并删除
//{} 是一个占位符 表示找到的每个文件名将替换这个占位符
//\; 是告诉 find 命令 在每个 -exec 命令的结尾使用分号来表示命令的结束
find /path/to/search -name "*.log" -exec rm {} \; 
```
## 快捷键
```bash
Ctrl + C 强制停止
Ctrl + D 退出账号的登录 退出某些特点程序的专属页面 不能用于退出vi/vim
ctrl + R = history !内容 输入内容去匹配历史命令 然后回车键可以自己执行 键盘左、右键可以得到此命令
Ctrl + A 跳到命令开头
Ctrl + E 跳到命令结尾
Ctrl + U 删除这行命令
Ctrl + 键盘左/右键 向左/右跳一个单词
Ctrl + L = clear 清空终端内容
```

# *vim/vi 编辑器
vim 兼容全部的vi功能

![image](https://github.com/Amaz1ngJR/Technology/assets/83129567/03489074-c40d-4d1e-990b-131f3e5e246b)

横分屏 ：sp 文件名(省略就是两个相同的文件)；竖分屏 ：vsp 文件名；Ctrl + ww切换分屏文件

|         模式       |     命令 (shift+i)表示大写I    |                       描述            |
| ------ | --------------- | ----------------------------------------------------------------- |
|       命令模式      |     i      |             在当前光标位置进入  输入模式                   |
|       输入模式      |     esc      |             任何情况下按esc都能回到命令模式                   |
|       命令模式      |     a      |             在当前光标位置之后 进入  输入模式                   |
|       命令模式      |     I       |             在当前行的开头进入  输入模式                   |
|       命令模式      |     A      |             在当前行的结尾进入  输入模式                   |
|       命令模式      |     o      |             在当前光标的下一行进入  输入模式                   |
|       命令模式      |     O      |             在当前光标的上一行进入  输入模式                   |
|       命令模式      |     K      |             进入光标处函数的man                   |
|       命令模式      |     向上键、k      |             向上移动光标                   |
|       命令模式      |     向下键、j      |             向下移动光标                   |
|       命令模式      |     向左键、h      |             向左移动光标                   |
|       命令模式      |     向右键、l      |             向右移动光标                   |
|       命令模式      |     0     |             移动光标到当前行的开头                   |
|       命令模式      |     $     |             移动光标到当前行的结尾                   |
|       命令模式      |     pageup     |             向上翻页                   |
|       命令模式      |     pagedown     |             向下翻译                   |
|       命令模式      |     /     |             进入搜索模式                   |
|       命令模式      |     n     |             向下继续搜索                  |
|       命令模式      |     N     |            向上继续搜索                   |
|       命令模式      |     dd     |            删除光标所在行的内容              |
|       命令模式      |     ndd     |            n是数字 表示删除当前光标向下n行         |
|       命令模式      |     yy     |            复制当前行                |
|       命令模式      |     nyy     |       n是数字 复制当前行和下面的n行       |
|       命令模式      |     p     |            粘贴复制的内容                |
|       命令模式      |     u     |            撤销修改                  |
|       命令模式      |     ctrl+r     |           反向撤销修改              |
|       命令模式      |     gg     |            跳到首行                |
|       命令模式      |     G     |            跳到行尾                   |
|       命令模式      |     dG     |            从当前行开始 向下全部删除                  |
|       命令模式      |     dgg     |           从当前行开始 向上全部删除                  |
|       命令模式      |     d$     |            从当前光标开始 删除到本行的结尾             |
|       命令模式      |     d0     |            从当前光标开始 删除到本行的开头              |
|       底线命令模式      |     :wq      |             保存并退出                   |
|       底线命令模式      |     :q      |              仅退出                   |
|       底线命令模式      |     :q!      |             强制退出                   |
|       底线命令模式      |     :w      |             仅保存                   |
|       底线命令模式      |     :set nu      |             显示行号                   |
|       底线命令模式      |     :set paste      |             设置粘贴模式                   |

光标处 按着r 再按别的键 可以将光标值改为所按下的键的值 按x删除 按s删除并进入输入模式
