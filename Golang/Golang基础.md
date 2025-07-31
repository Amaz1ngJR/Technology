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
