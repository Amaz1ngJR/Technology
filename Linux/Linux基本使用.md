# *配置

```
Win + R： mstsc 远程连接
```
## *用户和权限

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
byobu sudo apt-get install byobu 
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
## touch/mkdir 创建文件/文件夹
```bash
touch/mkdir filename          //创建文件/文件夹
touch/mkdir file1 file2 file3 //创建多个文件/文件夹
touch/mkdir /path/to/filename //特定(相对、绝对、特殊)路径下创建文件/文件夹
mkdir -p Dir/dir3/dir2/dir1   //递归在Dir下创建dir3 dir3下创建dir2 ...
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
## 反引号`
```bash
echo pwd    //输出pwd
echo `pwd`  //将被反引号`包围的内容视为命令去执行
```
## tail 查看文件尾部的内容 跟踪文件更新
```bash
tail filename        //显示文件末尾的内容 默认显示文件末尾的最后 10 行
tail file1 file2     //同时显示多个文件的末尾内容
tail -n 2 filename   //显示第2行的文件末尾内容
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
##快捷键
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
## 虚拟环境相关
```bash
创建虚拟环境      conda create -n <环境名name> python=0.0
进/出虚拟环境     conda activate <环境名name>/conda deactivate
查看所有虚拟环境  conda env list 所有包 conda list 
删除虚拟环境      conda remove -n  <环境名name> --all
复制虚拟环境      conda create --name new_name --clone old_name
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

# 用户权限
## 切换用户
su [ 选项 ]  [ 用户名 ]
```bash
su  //用户名省略切换到root
su - // - 表示重新加载新用户的环境变量
su -c 'ls /root' // c 表示允许在切换用户时指定要执行的命令
```
普通用户切换其他用户需要输入密码 root用户切换到其他用户 无需密码
## 配置sudo认证
切换到root用户 执行
```bash
visudo  //会自动通过vi编辑器打开/etc/sudoers
```
在文件的最后添加 并wq保存
```
yjr ALL=(ALL:ALL)         NOPASSWD:ALL
```
## 用户和用户组
