[在线编程](https://www.runoob.com/try/runcode.php?filename=helloworld&type=go)
mac下 直接 brew install go 运行： go run demo.go 或者使用go build demo.go生成二进制文件demo ./demo

常用命令
```bash
go run: 运行Go程序
go build: 编译Go程序
go test: 运行测试
go get: 下载并安装包
go mod init: 初始化模块（Go 1.11+模块支持）
```

```golang
package main

import "fmt"

func main() {
	var number = 123
	var data = "2025-07-31"
	var url = "num=%d&data =%s"
	var res = fmt.Sprintf(url, number, data)
	fmt.Printf(res)
	fmt.Println("hello")
	fmt.Println(res)
}
```
## 变量
变量声明与初始化
```golang
package main
import "fmt"

func main() {

    // 声明一个变量并初始化
    var a = "Hello, World!"
	b := "Go is awesome!"
    fmt.Println(a + b)

    // 没有初始化就为零值
    var i int
    var f float64
    var bl bool
    var s string
    fmt.Printf("%v %v %v %q\n", i, f, bl, s)
}
```
全局变量与局部变量
```golang
package main
import "fmt"

var x, y int
var (  // 这种因式分解关键字的写法一般用于声明全局变量
    a int
    b bool
)

var c, d int = 1, 2
var e, f = 123, "hello"

//这种不带声明格式的只能在函数体中出现
//g, h := 123, "hello"

func main(){
    g, h := 123, "hello"
    fmt.Println(x, y, a, b, c, d, e, f, g, h)
}
```
声明了一个局部变量却没有在相同的代码块中使用它，会得到编译错误，例如下面这个例子当中的变量 a：
```golang
func main() {
   var a string = "abc"
   fmt.Println("hello, world")
}
```
多变量可以在同一行进行赋值
```golang
var a, b int
var c string
a, b, c = 5, 7, "abc"
//or
a, b, c := 5, 7, "abc"
```
交换两个类型相同的变量的值，则可以简单地使用
```golang
a, b = b, a
```
空白标识符 _ 也被用于抛弃值，如
```golang
_, b = 5, 7
```
