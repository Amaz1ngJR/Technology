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

"使用 Ctrl+h/j/k/l 快速切换窗口
nnoremap <C-h> <C-w>h
nnoremap <C-j> <C-w>j
nnoremap <C-k> <C-w>k
nnoremap <C-l> <C-w>l
```

## *vim/vi 编辑器
vim 兼容全部的vi功能

![image](https://github.com/Amaz1ngJR/Technology/assets/83129567/03489074-c40d-4d1e-990b-131f3e5e246b)

横分屏 ：sp 文件名(省略就是两个相同的文件)；竖分屏 ：vsp 文件名；Ctrl + ww切换分屏文件

|         模式       |     命令     |                       描述            |
| :------------------: | :---------: | ----------------------------------------------------------------- |
|       命令模式      |     <kbd>I</kbd>      |    在当前光标位置进入  输入模式    |
|       输入模式      |     <kbd>Esc</kbd>      |   任何情况下按esc都能回到命令模式  |
|       命令模式      |     <kbd>A</kbd>       |       在当前光标位置之后 进入  输入模式   |
|       命令模式      |     <kbd>Shift</kbd> + <kbd>I</kbd>       |   在当前行的开头进入  输入模式   |
|       命令模式      |     <kbd>Shift</kbd> + <kbd>A</kbd>      |             在当前行的结尾进入  输入模式 |
|       命令模式      |      <kbd>O</kbd>      | 在当前光标的下一行进入  输入模式 |
|       命令模式      |     <kbd>Shift</kbd> + <kbd>O</kbd>      |  在当前光标的上一行进入  输入模式  |
|       命令模式      |     <kbd>Shift</kbd> + <kbd>K</kbd>      |  进入光标处函数的man|
|       命令模式      |     <kbd>⬆</kbd>、<kbd>K</kbd>      |  向上移动光标  |
|       命令模式      |     <kbd>⬇</kbd>、<kbd>J</kbd>      |  向下移动光标 |
|       命令模式      |     <kbd>⬅</kbd>、<kbd>H</kbd>      |  向左移动光标 |
|       命令模式      |     <kbd>➡️</kbd>、<kbd>L</kbd>       |  向右移动光标 |
|       命令模式      |     <kbd>Shift</kbd> + <kbd>.</kbd> + <kbd>.</kbd> （>）    |缩进当前行 |
|       命令模式      |     <kbd>Shift</kbd> + <kbd>,</kbd> + <kbd>,</kbd> （<）    |缩退当前行 |
|       命令模式      |     <kbd>0</kbd>     |移动光标到当前行的开头 |
|       命令模式      |     <kbd>Shift</kbd> + <kbd>4</kbd> （$）    |移动光标到当前行的结尾  |
|       命令模式      |     <kbd>PageUp</kbd>    |  向上翻页   |
|       命令模式      |     <kbd>PageDown</kbd>      |  向下翻译  |
|       命令模式      |     <kbd>/</kbd> + pattern + <kbd>Enter</kbd>  | 进入搜索模式 搜索 pattern|
|       命令模式      |     <kbd>N</kbd>     |             向下继续搜索  |
|       命令模式      |     <kbd>Shift</kbd> + <kbd>N</kbd>     |            向上继续搜索   |
|       命令模式      |     <kbd>Y</kbd> + <kbd>Y</kbd>     |            复制当前行  |
|       命令模式      |     <kbd>n</kbd> + <kbd>Y</kbd> + <kbd>Y</kbd>    |       n是数字 复制当前行和下面的n行  |
|       命令模式      |     <kbd>P</kbd>     |            粘贴复制的内容                |
|       命令模式      |     <kbd>G</kbd> + <kbd>;</kbd>    | 跳转到上一次修改的位置（可多次按，遍历修改历史） |
|       命令模式      |     <kbd>U</kbd>      |            撤销修改                  |
|       命令模式      |     <kbd>Ctrl</kbd> + <kbd>R</kbd>     |           反向撤销修改              |
|       命令模式      |     <kbd>G</kbd> + <kbd>G</kbd>     |            跳到首行                |
|       命令模式      |     <kbd>Shift</kbd> + <kbd>G</kbd>    |            跳到行尾                   |
|       命令模式      |     n + <kbd>Shift</kbd> + <kbd>5</kbd> (n%)  |  n是数字   跳转到文件的n%位置    |
|       命令模式      |     <kbd>Shift</kbd> + <kbd>5</kbd> (%)  |  光标放在括号 跳转到匹配的括号    |
|       命令模式      |     n + <kbd>J</kbd>    |      n是数字     向下跳n行                |
|       命令模式      |     n + <kbd>K</kbd>    |      n是数字     向上跳n行                |
|       命令模式      |     <kbd>n</kbd> + <kbd>Shift</kbd> + <kbd>G</kbd>   |（推荐用底线模式的） n是数字 跳到第n行开头 |
|       命令模式      |     <kbd>M</kbd> + <kbd>字母按键</kbd>   |      Mark标记光标位置为 字母按键[^1]   |
|       命令模式      |     <kbd>`</kbd> + <kbd>字母按键</kbd>   |      跳转到标记 字母按键[^1] 的精确位置（行列都跳）    |
|       命令模式      |     <kbd>D</kbd> + <kbd>D</kbd>    |            删除光标所在行的内容     |
|       命令模式      |     n + <kbd>D</kbd> + <kbd>D</kbd>     |            n是数字 删除当前光标向下n行     |
|       命令模式      |     <kbd>D</kbd> + <kbd>Shift</kbd> + <kbd>G</kbd>     |    从当前行开始 向下全部删除     |
|       命令模式      |     <kbd>D</kbd> + <kbd>G</kbd> + <kbd>G</kbd>     |    从当前行开始 向上全部删除      |
|       命令模式      |     <kbd>D</kbd> + <kbd>Shift</kbd> + <kbd>4</kbd>     |   从当前光标开始 删除到本行的结尾    |
|       命令模式      |     <kbd>D</kbd> + <kbd>0</kbd>     |            从当前光标开始 删除到本行的开头        |
|       命令模式      |     <kbd>D</kbd> + <kbd>}</kbd>     |      删除当前段落       |
|       命令模式      |     <kbd>Ctrl</kbd> + <kbd>Shift</kbd> + <kbd>6</kbd> (^)     | 快速在两个最近文件之间切换  |
|       底线命令模式      |     :wq      |    保存并退出   |
|       底线命令模式      |     :q      |   仅退出 |
|       底线命令模式      |     :q!      |  强制退出     |
|       底线命令模式      |     :w      |             仅保存                   |
|       底线命令模式      |     :w filename   |             保存到新文件     |
|       底线命令模式      |     :r filename   |             插入文件内容       |
|       底线命令模式      |     :e filename   |             打开其他文件       |
|       底线命令模式      |     :e #   |             快速在两个最近文件之间切换     |
|       底线命令模式      |     :sp/split filename | 水平分屏 打开其他文件 省略 filename，则新窗口打开当前文件的另一个副本| 
|       底线命令模式      |     :vsp/vsplit filename | 垂直分屏 打开其他文件 省略 filename，则新窗口打开当前文件的另一个副本|
|       底线命令模式      |     :set nu/number     |             显示行号    |
|       底线命令模式      |     :n   |             n是数字 跳到第n行开头     |
|       底线命令模式      |     :set paste   |             设置粘贴模式    |
|       底线命令模式      |     :help      |            查看帮助文档     |
|       底线命令模式      |     :marks     |            列出所有当前可用的标记及其位置     |
|       底线命令模式      |     :close   | 关闭当前窗口 Cannot close last window  |
|       底线命令模式      |     :only   |             关闭其他所有窗口，仅保留当前    |

>光标处 按着r 再按别的键 可以将光标值改为所按下的键的值 按x删除 按s删除并进入输入模式

|分屏后命令（在命令模式下）| 作用 |
|-----------------|-----|
|<kbd>Ctrl</kbd> + <kbd>W</kbd> 然后 <kbd>W</kbd> 	|依次循环切换窗口|
|<kbd>Ctrl</kbd> + <kbd>W</kbd> 然后 <kbd>H</kbd>、<kbd>J</kbd>、<kbd>K</kbd>、<kbd>L</kbd>	|切换到左、下、上、右边窗口|
|<kbd>Ctrl</kbd> + <kbd>W</kbd>  然后 <kbd>P</kbd>	|切换到上一个访问的窗口|
|:only 或 <kbd>Ctrl</kbd> + <kbd>W</kbd>  然后 <kbd>O</kbd> |	关闭其他所有窗口，只保留当前窗口|
|:close 或 <kbd>Ctrl</kbd> + <kbd>W</kbd> 然后 <kbd>C</kbd>	|关闭当前窗口|
|<kbd>Ctrl</kbd> + <kbd>W</kbd> 然后 <kbd>=</kbd>	|所有窗口等宽等高|
|<kbd>Ctrl</kbd> + <kbd>W</kbd> 然后 <kbd>Shift</kbd> + <kbd>-</kbd>(_)	|当前窗口最大化高度|
|<kbd>Ctrl</kbd> + <kbd>W</kbd> 然后 <kbd>Shift</kbd> + <kbd>\\</kbd>(\|)	|当前窗口最大化宽度|
|<kbd>Ctrl</kbd> + <kbd>W</kbd> 然后 <kbd>Shift</kbd> + <kbd>=</kbd>(+)	|增加当前窗口高度|
|<kbd>Ctrl</kbd> + <kbd>W</kbd> 然后 <kbd>-</kbd>(-)	|减少当前窗口高度|
|<kbd>Ctrl</kbd> + <kbd>W</kbd> 然后 <kbd>Shift</kbd> + <kbd>.</kbd>(>)	|增加当前窗口宽度|
|<kbd>Ctrl</kbd> + <kbd>W</kbd> 然后 <kbd>Shift</kbd> + <kbd>,</kbd>(<)	|减少当前窗口宽度|
>可以在 .vimrc 中添加以下映射，让切换更方便
```bash
# 使用 Ctrl+h/j/k/l 快速切换窗口
nnoremap <C-h> <C-w>h
nnoremap <C-j> <C-w>j
nnoremap <C-k> <C-w>k
nnoremap <C-l> <C-w>l
```
[^1]: - 小写字母标记（a–z）
        - 作用范围：仅限当前文件
    - 大写字母标记（A–Z）
        - 作用范围：全局，跨文件有效。
        - 持久化：Vim 会将这些标记保存在 ~/.viminfo 文件中（需启用 viminfo 功能），下次打开 Vim 时仍可使用。
        - 用途：在不同文件间快速跳转 
        > 注意：跳转时 Vim 会自动切换回标记所在的文件
    - 数字标记（0–9）（由 Vim 自动设置） 记录你最近退出 Vim 时的文件位置
        - '0：上次退出 Vim 时你编辑的文件和位置。
        - '1：上上次退出的位置。
        - ...
        - '9：第九次之前退出的位置。

