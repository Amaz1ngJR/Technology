# Golang基础
[在线编程](https://www.runoob.com/try/runcode.php?filename=helloworld&type=go)
mac下 直接 brew install go 运行： go run demo.go 或者使用go build demo.go生成二进制文件demo ./demo

网络代理
使用 GOPROXY： 你可以设置 GOPROXY 环境变量来使用国内的 Go 模块代理，比如 goproxy.cn，它提供了一个更稳定的模块下载服务。
```bash
export GOPROXY=https://goproxy.cn,direct
```
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
	print(res)
	println()
	fmt.Println("hello")
	print("---")
	fmt.Println(res)
}
```
## 变量
### 变量声明与初始化
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
### 全局变量与局部变量
全局变量可以在整个包甚至外部包（被导出后）使用
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
### const 常量
```golang
package main
import"fmt"
func main() {
	const LENGTH int = 10 //显式类型定义
   	const WIDTH = 5  //隐式类型定义
	const a, b, c = 1, false, "str" //多重赋值

   	var area int
   	area = LENGTH * WIDTH
   	fmt.Printf("面积为 : %d", area)
   	println()
   	println(a, b, c)  
}
```
常量还可以用作枚举：
```golang
package main

import "unsafe"
const (
    a = "abc"
    b = len(a)			// b = 3
    c = unsafe.Sizeof(a)	// c = 16 unsafe.Sizeof 测量的是变量在内存中占用的“大小”
				//Go 的字符串是一个 2个字段的结构体，unsafe.Sizeof 测的是这个结构体的大小，不是它指向的数据
)

func main(){
    println(a, b, c)
}
```
特殊常量iota
```golang
const (
    a = iota
    b = iota
    c = iota
)
//or
const (
    a = iota
    b 
    c
)
```
```golang
package main

import "fmt"

func main() {
	const (
	    a = iota   //0
	    b          //1
	    c          //2
	    d = "ha"   //独立值，iota += 1
	    e          //"ha"   iota += 1
	    f = 100    //iota +=1
	    g          //100  iota +=1
	    h = iota   //7,恢复计数
	    i          //8
	)
	fmt.Println(a,b,c,d,e,f,g,h,i)

	const (
	    j=1<<iota
	    k=3<<iota
	    o
	    p
	)
	println("j = ", j);
	println("k = ", k);
	println("o = ", o);
	println("p = ", p);
}
```
## 函数闭包（匿名函数）

## time
```golang
package main

import "fmt"
import "time"
func main() {
   	start := time.Now()
	startTimeStr := start.Format("2006-01-02 15:04:05.000")
	fmt.Println(“开始计时：” + startTimeStr)
	i := 1
	for i < 10000000 {
		i++
	}
	duration := time.Since(start) // 计算耗时
	durationMs := float64(duration.Milliseconds()) / 1000.0 // 转为 float，单位秒
	fmt.Println(durationMs)
	//模拟在日志中，反复计时
	start = time.Now()
	i = 1
	for i < 100000000 {
		i++
	}
	duration = time.Since(start) // 计算耗时
	durationMs = float64(duration.Milliseconds()) / 1000.0 // 转为 float，单位秒
	fmt.Println(durationMs)
}
```
