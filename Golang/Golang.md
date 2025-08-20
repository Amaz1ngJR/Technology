# Golang基础
[在线编程](https://www.runoob.com/try/runcode.php?filename=helloworld&type=go)
mac下 直接 brew install go 运行： go run demo.go 或者使用go build demo.go生成二进制文件demo ./demo

网络代理
使用 GOPROXY： 你可以设置 GOPROXY 环境变量来使用国内的 Go 模块代理，比如 goproxy.cn，它提供了一个更稳定的模块下载服务。

临时设置
```bash
export GOPROXY=https://goproxy.cn,direct
```
永久设置
```bash
# 1. 设置模块代理为阿里云 goproxy.cn
go env -w GOPROXY=https://goproxy.cn,direct

# 2. 设置校验数据库（goproxy.cn 会自动代理 sum.golang.org）
go env -w GOSUMDB=sum.golang.org

# 3. 获取依赖
go get github.com/gorilla/websocket
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
### 变量类型转换
#### 整型转化为浮点型
```golang
package main
import "fmt"

func main() {
   var sum int = 17
   var count int = 5
   var mean float32
   
   mean = float32(sum)/float32(count)
   fmt.Printf("mean 的值为: %f\n",mean) // 3.400000
}
```
#### 字符串转换成整型变量
```golang
package main
import (
    "fmt"
    "strconv"
)

func main() {
    str := "123"
    num, err := strconv.Atoi(str)
    if err != nil {
        fmt.Println("转换错误:", err)
    } else {
        fmt.Printf("字符串 '%s' 转换为整数为：%d\n", str, num)
    }
}
```
#### 整形转字符串
```golang
package main
import (
    "fmt"
    "strconv"
)

func main() {
    num := 123
    str := strconv.Itoa(num)
    fmt.Printf("整数 %d  转换为字符串为：'%s'\n", num, str)
}
```
#### 字符串转换为浮点数
```golang
package main
import (
    "fmt"
    "strconv"
)

func main() {
    str := "3.14"
    num, err := strconv.ParseFloat(str, 64)
    if err != nil {
        fmt.Println("转换错误:", err)
    } else {
        fmt.Printf("字符串 '%s' 转为64位浮点型为：%f\n", str, num)
    }
	// 转换为float32
	f32, err := strconv.ParseFloat(str, 32)
	if err != nil {
		fmt.Println("转换错误:", err)
	} else {
		fmt.Printf("字符串 '%s' 转换为32位浮点数为：%f\n", str, float32(f32))
	}
}
```
#### 浮点型转字符串
```golang
package main
import (
    "fmt"
    "strconv"
)

func main() {
    num := 3.14
    str := strconv.FormatFloat(num, 'f', 3, 64)		//保留3位的64位浮点数
    fmt.Printf("浮点数 %f 转为字符串为：'%s'\n", num, str)
}
```
## 函数闭包（匿名函数）
Golang函数可以返回多个值
```golang
package main

import "fmt"

func swap(x, y string) (string, string) {
   return y, x
}

func main() {
   a, b := swap("World", "Hello")
   fmt.Println(a, b)
}
```
Go 语言支持匿名函数，可作为闭包
```golang
package main
import "fmt"

func getSequence() func() int {
   i:=0
   return func() int {
      i+=1
     return i  
   }
}

func main(){
   /* nextNumber 为一个函数 */
   nextNumber := getSequence()  

   /* 调用 nextNumber 函数，i 变量自增 1 并返回 */
   fmt.Println(nextNumber())  	//------------1
   fmt.Println(nextNumber())	//------------2
   fmt.Println(nextNumber())	//------------3
   
   /* 创建新的函数 nextNumber1，并查看结果 */
   nextNumber1 := getSequence()  
   fmt.Println(nextNumber1())  	//------------1
   fmt.Println(nextNumber1())  	//------------2
}
```
```golang
package main
import "fmt"

func main() {
    // 定义一个匿名函数并将其赋值给变量add
    // 在函数内部使用匿名函数
    multiply := func(x, y int) int {
        return x * y
    }

    product := multiply(4, 6)
    fmt.Println("4 * 6 =", product)

    // 将匿名函数作为参数传递给其他函数
    calculate := func(operation func(int, int) int, x, y int) int {
        return operation(x, y)
    }

    res := calculate(multiply, 2, 8)
    fmt.Println("2 * 8 =", res)

    // 也可以直接在函数调用中定义匿名函数
    difference := calculate(func(a, b int) int {
        return a - b
    }, 10, 4)
    fmt.Println("10 - 4 =", difference)
}
```

## 数组
Go 数组的长度不可改变
### 初始化
Go 语言数组声明需要指定元素类型及元素个数,如
```golang
var arr [10]float32
var numbers = [5] int {1, 2, 3, 4, 5}	//使用初始化列表来初始化数组的元素
numbers := [5] int {1, 2, 3, 4, 5}	//另一种写法
```
如果数组长度不确定，可以使用 ... 代替数组的长度，编译器会根据元素个数自行推断数组的长度：
```golang
var nums = [...] float32 {1000.0, 2.0, 3.4, 7.0, 50.0}
nums := [...] float32 {1000.0, 2.0, 3.4, 7.0, 50.0} //另一种写法
```
如果设置了数组的长度，我们还可以通过指定下标来初始化元素：
```golang
//  将索引为 1 和 3 的元素初始化
nums := [5] float32 {1:2.0, 3:7.0}
for i, x := range nums {
	println("i =", i, "num =", x)
}
```
### 元素访问
```golang
package main
import "fmt"
func main() {
    nums := [5] int {5, 4 ,3 ,2, 1}
	//c风格 使用[]访问元素
	for i := 0; i < len(nums); i++ {
		fmt.Println("Index:", i, "Value:", nums[i])
	}
	//类似python in的用法
	for i := range nums {
		fmt.Println("Index:", i, "Value:", nums[i])
	}
	for _, v := range nums {
		fmt.Println("Value:", v)
	}
	for i, x := range nums {
		println("i =", i, "x =", x)
	}
}
```
## 切片
### 初始化
```golang
package main
import "fmt"

func printSlice(x []int){
  	fmt.Printf("len=%d cap=%d slice=%v\n",len(x),cap(x),x)
	if(x == nil){
		fmt.Println("切片是空的")
   }
}

func main() {
	//声明一个未指定大小的数组来定义切片
	var s1 []int
	printSlice(s1)
	//使用 make() 函数来创建切片var slice1 []type = make([]type, len)
	var slice1 [] int = make([]int, 10)
	printSlice(slice1)
	//使用 make() 函数来创建切片var slice2 []type = make([]T, length, capacity)
	var slice2 [] int = make([]int, 10, 20)
	printSlice(slice2)
	// 切片初始化 [] 表示是切片类型，{1,2,3} 初始化值依次是 1,2,3，其 cap=len=3。
	s :=[] int {1,2,3 } 
	printSlice(s)

	//切片的截取 使用数组或者切片来截取成新的切片
	//s := arr[startIndex:endIndex] 上下限默认值为arr.begin, arr.end
	//将 arr 中从下标 startIndex 到 endIndex-1 下的元素创建为一个新的切片。
	arr := [3] int {1, 2, 3}
	s = arr[0:2]
	printSlice(s)
}
```
### append() 和 copy()
如果想增加切片的容量，我们必须创建一个新的更大的切片并把原分片的内容都拷贝过来
```golang
package main
import "fmt"

func printSlice(x []int){
  	fmt.Printf("len=%d cap=%d slice=%v\n",len(x),cap(x),x)
	if(x == nil){
		fmt.Println("切片是空的")
   }
}

func main() {
	var numbers []int
	printSlice(numbers)  		//len=0 cap=0 slice=[]
	
	/* 允许追加空切片 */
	numbers = append(numbers, 0)
	printSlice(numbers)		//len=1 cap=1 slice=[0]
	
	/* 向切片添加一个元素 */
	numbers = append(numbers, 1)
	printSlice(numbers)		//len=2 cap=2 slice=[0 1]
	
	/* 同时添加多个元素 */
	numbers = append(numbers, 2,3,4)
	printSlice(numbers)
	
	/* 创建切片 numbers1 是之前切片的两倍容量*/
	numbers1 := make([]int, len(numbers), (cap(numbers))*2)
	
	/* 拷贝 numbers 的内容到 numbers1 */
	copy(numbers1,numbers)
	printSlice(numbers1)  
}
```
## Map
Map 是一种无序的键值对的集合,当 Map 中的键值对数量达到容量时，Map 会自动扩容
### 定义
```golang
/* 使用 make 函数 */
map_variable := make(map[KeyType]ValueType, initialCapacity)

// 创建一个空的 Map
m := make(map[string]int)

// 创建一个初始容量为 10 的 Map
m := make(map[string]int, 10)

// 使用字面量创建 Map
m := map[string]int{
    "apple": 1,
    "banana": 2,
    "orange": 3,
}
```
### 常用操作
```golang
// 获取键值对
v1 := m["apple"]
v2, ok := m["pear"]  // 如果键不存在，ok 的值为 false，v2 的值为该类型的零值

// 修改键值对
m["apple"] = 5

// 获取 Map 的长度
len := len(m)

// 遍历 Map1
for k, v := range m {
	fmt.Printf("key=%s, value=%d\n", k, v)
}
// 遍历 map1，只读取 key
for key := range map1 {
	fmt.Printf("key is: %d\n", key)
}

// 遍历 map1，只读取 value
for _, value := range map1 {
	fmt.Printf("value is: %f\n", value)
}

// 删除键值对
delete(m, "banana")
```
## 结构体
```golang
package main
import "fmt"

type Person struct {
	//属性
    Name string
	Age  int
	//在 Go 中，结构体（struct）只用于定义数据字段（属性），
	//不能在 struct 内部声明方法,方法是绑定到类型上的函数，不是结构体的成员
}

func main() {
	a := Person{}
	a.Name = "Amaz1ng"
	b := Person{"abc", 18}
	fmt.Println("a`s name = ", a.Name, "b`s name = ", b.sayName())
}

//方法必须独立定义，使用 (p Type) 作为接收者 
func (p Person) sayName() string {
  return p.Name
}
```
## 接口
特点
```
隐式实现：
Go 中没有关键字显式声明某个类型实现了某个接口。
只要一个类型实现了接口要求的所有方法，该类型就自动被认为实现了该接口

接口类型变量：
接口变量可以存储实现该接口的任意值。
接口变量实际上包含了两个部分：
动态类型：存储实际的值类型。
动态值：存储具体的值。
零值接口：

接口的零值是 nil。
一个未初始化的接口变量其值为 nil，且不包含任何动态类型或值。

空接口：
定义为 interface{}，可以表示任何类型。
```
### 接口定义与实现
接口定义使用关键字 interface，其中包含方法声明
```golang
package main
import (
        "fmt"
        "math"
)

// 定义接口
type Shape interface {
        Area() float64
        Perimeter() float64
}

// 定义一个结构体
type Circle struct {
        Radius float64
}

// Circle 实现 Shape 接口
func (c Circle) Area() float64 {
        return math.Pi * c.Radius * c.Radius
}

func (c Circle) Perimeter() float64 {
        return 2 * math.Pi * c.Radius
}

func main() {
        c := Circle{Radius: 5}
        var s Shape = c // 接口变量可以存储实现了接口的类型
        fmt.Println("Area:", s.Area())
        fmt.Println("Perimeter:", s.Perimeter())
}
```

### 接口类型转换
接口类型转换有两种情况：类型断言和类型转换
#### 类型断言

#### 类型转换
## 面向对象编程
```golang
package main

import "fmt"

// ==================== 1. 定义接口（多态） ====================
// Speaker 接口定义了“会说话”的行为
type Speaker interface {
    Speak() string
}

// Mover 接口定义了“会移动”的行为
type Mover interface {
    Move() string
}

// ==================== 2. 定义基础结构体（封装） ====================
// Animal 是基础结构体，包含公共属性
type Animal struct {
    Name string
    Age  int
}

// 构造函数：Go 没有构造函数，但可以用 NewXXX 函数模拟
func NewAnimal(name string, age int) Animal {
    return Animal{Name: name, Age: age}
}

// Animal 的通用方法
func (a Animal) Info() string {
    return fmt.Sprintf("Name: %s, Age: %d", a.Name, a.Age)
}

// ==================== 3. 定义具体类型（组合代替继承） ====================
// Dog 结构体，嵌入 Animal（组合）
type Dog struct {
    Animal  // 匿名字段，实现“继承”
    Breed   string
}

// Cat 结构体
type Cat struct {
    Animal
    Color string
}

// ==================== 4. 为类型实现方法（行为） ====================
// Dog 实现 Speak 方法
func (d Dog) Speak() string {
    return fmt.Sprintf("%s says: Woof! Woof!", d.Name)
}

// Dog 实现 Move 方法
func (d Dog) Move() string {
    return fmt.Sprintf("%s runs on four legs.", d.Name)
}

// Cat 实现 Speak 方法
func (c Cat) Speak() string {
    return fmt.Sprintf("%s says: Meow~", c.Name)
}

// Cat 实现 Move 方法
func (c Cat) Move() string {
    return fmt.Sprintf("%s sneaks silently.", c.Name)
}

// ==================== 5. 多态使用（接口） ====================
func MakeItSpeak(s Speaker) {
    fmt.Println(s.Speak())
}

func MakeItMove(m Mover) {
    fmt.Println(m.Move())
}

// ==================== 主函数 ====================
func main() {
    // 创建 Dog 实例
    dog := Dog{
        Animal: NewAnimal("Buddy", 3),
        Breed:  "Golden Retriever",
    }

    // 创建 Cat 实例
    cat := Cat{
        Animal: NewAnimal("Luna", 2),
        Color:  "Black",
    }

    // 打印基本信息
    fmt.Println("=== Animal Info ===")
    fmt.Println(dog.Info()) // 继承 Animal 的方法
    fmt.Println(cat.Info())

    // 多态调用
    fmt.Println("\n=== Speaking ===")
    MakeItSpeak(dog) // 输出: Buddy says: Woof! Woof!
    MakeItSpeak(cat) // 输出: Luna says: Meow~

    fmt.Println("\n=== Moving ===")
    MakeItMove(dog) // 输出: Buddy runs on four legs.
    MakeItMove(cat) // 输出: Luna sneaks silently.

    // 直接调用方法
    fmt.Println("\n=== Direct Calls ===")
    fmt.Println(dog.Speak())
    fmt.Println(cat.Move())
}
```
## Go并发
Go 语言支持并发，通过 goroutines 和 channels 提供了一种简洁且高效的方式来实现并发
### Goroutine
goroutine 是轻量级线程,Go 中的并发执行单位,非阻塞的
```golang
package main
import (
        "fmt"
        "time"
)

func sayHello() {
        for i := 0; i < 5; i++ {
                fmt.Println("Hello")
                time.Sleep(100 * time.Millisecond)
        }
}

func main() {
        go sayHello() // 启动 Goroutine
        for i := 0; i < 5; i++ {
                fmt.Println("Main")
                time.Sleep(100 * time.Millisecond)
        }
}
```
### Channel
通道可用于两个 goroutine 之间通过传递一个指定类型的值来同步运行和通讯。
使用 make 函数创建一个 channel，使用 <- 操作符发送和接收数据。如果未指定方向，则为双向通道
```golang
package main
import "fmt"

func sum(s []int, c chan int) {
    sum := 0
    for _, v := range s {
        sum += v
    }
    c <- sum // 把 sum 发送到通道 c
}

func main() {
    s := []int{7, 2, 8, -9, 4, 0}

    c := make(chan int)//默认情况下，通道是不带缓冲区的。发送端发送数据，同时必须有接收端相应的接收数据。
    go sum(s[:len(s)/2], c)
    go sum(s[len(s)/2:], c)
    x, y := <-c, <-c // 从通道 c 中接收

    fmt.Println(x, y, x+y)

    ch := make(chan int, 2)//定义一个缓冲区大小为2,可以存储整数类型的通道
	// 因为 ch 是带缓冲的通道，我们可以同时发送两个数据，而不用立刻需要去同步读取数据
    ch <- 1
    ch <- 2

    // 获取这两个数据
    fmt.Println(<-ch)
    fmt.Println(<-ch)
}
```
### Select & WaitGroup
select 语句使得一个 goroutine 可以等待多个通信操作。select 会阻塞，直到其中的某个 case 可以继续执行
```golang
package main

import (
	"fmt"
	"time"
)

func main() {
	ch1 := make(chan string)
	ch2 := make(chan string)
	quit := make(chan int)
	
	go func() {
		time.Sleep(1 * time.Second)
		ch1 <- "来自ch1的消息"
	}()

	go func() {
		time.Sleep(2 * time.Second)
		ch2 <- "来自ch2的消息"
	}()
	
	go func() {
		time.Sleep(2 * time.Second)
		quit <- 0
	}()
	
	// 使用select等待多个channel
	for i := 0; i < 3; i++ {
		select {
		case msg1 := <-ch1:
			fmt.Println("接收到:", msg1)
		case msg2 := <-ch2:
			fmt.Println("接收到:", msg2)
		case <-quit:
            fmt.Println("quit")
            return
		}
	}
}
```
当多个case都准备好时，select会随机选择一个执行
```golang
package main

import "fmt"

func main() {
	ch1 := make(chan int, 1)
	ch2 := make(chan int, 1)

	ch1 <- 1
	ch2 <- 2

	select {
	case <-ch1:
		fmt.Println("从ch1接收")
	case <-ch2:
		fmt.Println("从ch2接收")
	}
}
// 输出可能是"从ch1接收"或"从ch2接收"，随机选择
```
带超时的select
```golang
package main
import (
	"fmt"
	"time"
)

func main() {
	ch := make(chan string)

	go func() {
		time.Sleep(3 * time.Second)
		ch <- "处理结果"
	}()

	select {
	case res := <-ch:
		fmt.Println(res)
	case <-time.After(2 * time.Second):
		fmt.Println("操作超时")
	}
}
```
非阻塞的select（使用default）
```golang
package main
import "fmt"

func main() {
	ch := make(chan int, 0)//改为1/0

	select {
	case ch <- 42:
		fmt.Println("值已发送到channel")
	default:
		fmt.Println("channel已满，无法发送")
	}

	select {
	case val := <-ch:
		fmt.Println("接收到:", val)
	default:
		fmt.Println("没有数据可接收")
	}
}
```
永久等待多个channel
```golang
package main
import (
	"fmt"
	"time"
)

func main() {
	tick := time.Tick(100 * time.Millisecond)
	boom := time.After(500 * time.Millisecond)

	for {
		select {
		case <-tick:
			fmt.Println("滴答")
		case <-boom:
			fmt.Println("砰!")
			return
		default:
			fmt.Println("    .")
			time.Sleep(50 * time.Millisecond)
		}
	}
}
```
sync.WaitGroup 用于等待多个 Goroutine 完成
```golang
package main
import (
        "fmt"
        "sync"
)

func worker(id int, wg *sync.WaitGroup) {
        defer wg.Done() // Goroutine 完成时调用 Done()
        fmt.Printf("Worker %d started\n", id)
        fmt.Printf("Worker %d finished\n", id)
}

func main() {
        var wg sync.WaitGroup

        for i := 1; i <= 3; i++ {
                wg.Add(1) // 增加计数器
                go worker(i, &wg)
        }

        wg.Wait() // 等待所有 Goroutine 完成
        fmt.Println("All workers done")
}
```
### Context
Context是Go语言中用于控制goroutine生命周期的标准工具，它可以传递取消信号、截止时间和其他请求范围的值，其主要方法
```golang
/*控制goroutine的生命周期
传递取消信号
设置超时/截止时间
在请求范围内传递值
*/
type Context interface {
    Deadline() (deadline time.Time, ok bool)
    Done() <-chan struct{}
    Err() error
    Value(key interface{}) interface{}
}
```
#### context.WithCancel
创建可取消的Context
```golang
package main
import (
	"context"
	"fmt"
	"time"
)

func worker(ctx context.Context) {
	for {
		select {
		case <-ctx.Done():
			fmt.Println("收到取消信号，退出")
			return
		default:
			fmt.Println("工作中...")
			time.Sleep(1 * time.Second)
		}
	}
}

func main() {
	ctx, cancel := context.WithCancel(context.Background())
	
	go worker(ctx)
	
	time.Sleep(3 * time.Second)
	cancel() // 发送取消信号
	
	time.Sleep(1 * time.Second) // 给worker时间处理退出
}
```
#### context.WithTimeout
创建带超时的Context
```golang
package main
import (
	"context"
	"fmt"
	"time"
)

func main() {
	ctx, cancel := context.WithTimeout(context.Background(), 2*time.Second)//2秒超时
	defer cancel() // 好的实践是总是调用cancel
	
	select {
	case <-time.After(3 * time.Second):
		fmt.Println("操作完成")
	case <-ctx.Done():
		fmt.Println("操作超时:", ctx.Err()) // 输出: context.DeadlineExceeded
	}
}
```
#### context.WithDeadline
相较于context.WithTimeout是指定相对于context创建的时间，内部其实是调用 WithDeadline，计算当前时间加上duration作为截止时间
context.WithDeadline可以指定时间，context.WithTimeout相当于
```golang
// 指定一个具体的截止时间点
deadline := time.Now().Add(2 * time.Second)
ctx, cancel := context.WithDeadline(context.Background(), deadline)
```
#### context.WithValue
传递请求范围的值
```golang
package main
import (
	"context"
	"fmt"
)

// 定义上下文键类型(避免字符串键冲突)
type ctxKey string

func main() {
	// 定义键
	const userIDKey ctxKey = "userID"
	
	// 创建带有用户ID的上下文
	ctx := context.WithValue(context.Background(), userIDKey, 123)
	
	// 在函数中获取值
	printUserID(ctx, userIDKey)
}

func printUserID(ctx context.Context, key ctxKey) {
	// 从上下文中获取值
	if v := ctx.Value(key); v != nil {
		fmt.Printf("用户ID: %d\n", v.(int)) // 类型断言
	} else {
		fmt.Println("上下文中找不到用户ID")
	}
}
```
### Mutex
互斥锁
```golang
package main
import (
	"fmt"
	"sync"
)

var (
	counter int
	mu      sync.Mutex
)

func increment() {
	mu.Lock()
	defer mu.Unlock() // 确保锁会被释放
	counter++
}

func main() {
	var wg sync.WaitGroup
	
	for i := 0; i < 100; i++ {
		wg.Add(1)
		go func() {
			defer wg.Done()
			increment()
		}()
	}
	
	wg.Wait()
	fmt.Println("最终计数器值:", counter) // 保证是100
}
```
读写锁
```golang
package main

import (
	"fmt"
	"sync"
	"time"
)

var (
	data  map[string]string
	rwMu  sync.RWMutex
)

func readData(key string) string {
	rwMu.RLock()         // 读锁
	defer rwMu.RUnlock() // 释放读锁
	return data[key]
}

func writeData(key, value string) {
	rwMu.Lock()         // 写锁
	defer rwMu.Unlock() // 释放写锁
	data[key] = value
}

func main() {
	data = make(map[string]string)
	
	// 并发读写
	go func() {
		for i := 0; i < 10; i++ {
			writeData(fmt.Sprintf("key%d", i), fmt.Sprintf("value%d", i))
		}
	}()
	
	go func() {
		for i := 0; i < 10; i++ {
			fmt.Println(readData(fmt.Sprintf("key%d", i)))
		}
	}()
	
	time.Sleep(1 * time.Second)
}
```
## Go文件处理

## time
```golang
package main
import "fmt"
import "time"

func main() {
   	start := time.Now()
	startTimeStr := start.Format("2006-01-02 15:04:05.000")
	fmt.Println("开始计时：" + startTimeStr)
	
	time.Sleep(100 * time.Millisecond)
	time.Sleep(1 * time.Second)
	
	duration := time.Since(start) // 计算耗时
	durationMs := float64(duration.Milliseconds()) / 1000.0 // 转为 float，单位秒
	fmt.Println(durationMs)
	fmt.Println(time.Since(start).Seconds())
}
```
