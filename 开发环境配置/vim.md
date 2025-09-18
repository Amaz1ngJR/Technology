## vim配置

Linux 没有盘符，只有一个根目录/，所有文件都在它下面

默认路径/etc/vim/vimrc,可以在~/路径下创建.vimrc进行配置 mac也有效

```
vim ~/.vimrc
```
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

## *vim/vi 编辑器
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
|       命令模式      |     d}     |            删除当前段落              |
|       底线命令模式      |     :wq      |             保存并退出                   |
|       底线命令模式      |     :q      |              仅退出                   |
|       底线命令模式      |     :q!      |             强制退出                   |
|       底线命令模式      |     :w      |             仅保存                   |
|       底线命令模式      |     :w filename   |             保存到新文件                   |
|       底线命令模式      |     :r filename   |             插入文件内容                   |
|       底线命令模式      |     :set nu      |             显示行号                   |
|       底线命令模式      |     :set paste      |             设置粘贴模式                   |
|       底线命令模式      |     :help      |            查看帮助文档                   |

光标处 按着r 再按别的键 可以将光标值改为所按下的键的值 按x删除 按s删除并进入输入模式

