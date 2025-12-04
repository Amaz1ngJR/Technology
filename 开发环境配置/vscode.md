## 在终端中打开vscode
在安装完vs code后

打开 VSCode，使用快捷键 Command + Shift + P 打开命令面板
输入“Shell Command”并选择 
```
Shell Command: Install 'code' command in PATH
```
将把code命令添加到你的系统路径中，使得可以在终端中使用它来启动VSCode
```bash
code .   
```
将启动vs code并显示当前目录的内容
## 快捷键
匹配多项
```
cmd + shift + L
```
## 调试方法

### DEBUG CONSOLE
看变量的内存中存储的值
```
-exec x/16 变量名称
```
例如
```
-exec x/16t rtcp --二进制看内存中的值
-exec x/16u rtcp --转成无符号的十进制的值
-exec x/16b rtcp --以字节16进制数显示
-exec x/16x rtcp --32 位（4 字节）的十六进制数

--其他看help
-exec help x
```

```bash
sudo unlink /usr/local/bin/code
```