# Linux

Linux 没有盘符，只有一个根目录/，所有文件都在它下面

## *配置

```
Win + R： mstsc 远程连接
```

### **vim配置

默认路径/etc/vim/vimrc,可以在~/路径下创建.vimrc进行配置 vim ~/.vimrc

```c++
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

### **Byobu使用

安装byobu

```
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

## *Linux基本指令

### 创建

mkdir 创建新的目录（文件夹）touch 创建文件



## *Linux系统编程