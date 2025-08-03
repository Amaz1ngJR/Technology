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
