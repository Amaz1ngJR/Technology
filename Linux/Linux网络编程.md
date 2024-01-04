# Socket编程
## 网络字节序
```
(计算机中)小端法：高位存高地址 低位存低地址
(网络中)大端法：高位存低地址 低位存高地址
```
调用以下库函数做网络字节序和主机字节序的转换(若主机已是大端字节序 下面库函数不做转换 原封不动返回)
```c++
#include <arpa/inet.h>
//h->host n->network l->32位长整数 s->16位短整数
uint32_t htonl(uint32_t hostlong);//本地->网络  (IP)
uint16_t htons(uint16_t hostshort);//本地->网络 (Port)
uint32_t ntohl(uint32_t netlong);//网络->本地  (IP)
uint16_t ntohs(uint16_t netshort);//网络->本地 (Port)
```
## 套接字socket
在TCP/IP协议中 IP地址+TCP/UDP端口号 唯一标识网络通讯中的一个进程 “IP地址+端口号”对应一个套接字socket 

两个socket组成的socket pair唯一标识一个连接(通讯过程中 socket一定是成对出现的)
![image](https://github.com/Amaz1ngJR/Technology/assets/83129567/35bb452b-c34b-4b96-af72-4a5fc6048b8b)
上图得 一个socket等于一个文件描述符+两个缓冲区即一个文件描述符指向一个套接字 该套接字内部由内核借助两个缓冲区实现

# 高并发服务器
