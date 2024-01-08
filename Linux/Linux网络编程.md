# Socket编程
## 网络字节序
```
(计算机中)小端法：高位存高地址 低位存低地址
(网络中)大端法：高位存低地址 低位存高地址
```
OLD:调用以下库函数做网络字节序和主机字节序的转换(若主机已是大端字节序 下面库函数不做转换 原封不动返回)
```c++
#include <arpa/inet.h>
//h->host n->network l->32位长整数 s->16位短整数
uint32_t htonl(uint32_t hostlong);//本地->网络  (IP)
uint16_t htons(uint16_t hostshort);//本地->网络 (Port)
uint32_t ntohl(uint32_t netlong);//网络->本地  (IP)
uint16_t ntohs(uint16_t netshort);//网络->本地 (Port)
```
NEW:
```c++
#include <arpa/inet.h>

int inet_pton(int af, const char *src, void *dst);//点分十进制->网络字节序 成功返回1 传入非有效地址返回0 失败返回-1
//src:IP(点分十进制) dst:传出参数 转换后的 网络字节序的IP地址
const char *inet_ntop(int af, const void *src, char *dst, socklen_t size);//网络字节序->点分十进制 成功返回dst 失败返回NULL
//src:网络字节序IP dst:本地字节序 size:dst大小
相同参数：af:AF_INET(IPV4)、AF_INET6(IPV6) 
```
## 套接字socket及其数据结构
在TCP/IP协议中 IP地址+TCP/UDP端口号 唯一标识网络通讯中的一个进程 “IP地址+端口号”对应一个套接字socket 

两个socket组成的socket pair唯一标识一个连接(通讯过程中 socket一定是成对出现的)
![image](https://github.com/Amaz1ngJR/Technology/assets/83129567/35bb452b-c34b-4b96-af72-4a5fc6048b8b)

上图得 一个socket等于一个文件描述符+两个缓冲区即一个文件描述符指向一个套接字 该套接字内部由内核借助两个缓冲区实现

socket数据结构

![image](https://github.com/Amaz1ngJR/Technology/assets/83129567/6197b469-c5f9-4c97-9e71-23de5e0110ba)
man 7 ip 查看
```c++
struct sockaddr_in {
    sa_family_t    sin_family; /* address family: AF_INET */
    in_port_t      sin_port;   /* 网络字节序的端口号*/
    struct in_addr sin_addr;   /* internet address */
};
 /* Internet address. */
struct in_addr {
    uint32_t       s_addr;     /* 网络字节序的IP地址 */
};
```
bind中使用
```c++
struct sockaddr_in addr;
addr.sin_family = AF_INET; // AF_INET6;
addr.sin_port = htons(9527);
//int dst;
//addr.sin_addr.s_addr = inet_pton(AF_INET, "192.157,22,45", (void*)&dst);
addr.sin_addr.s_addr = htonl(INADDR_ANY);//取出系统中有效的任意IP地址(二进制类型)
size = sizeof(addr)
bind(fd, (struct  sockaddr*)&addr, size);//成功返回0 失败-1
```
socker模型创建流程图

![image](https://github.com/Amaz1ngJR/Technology/assets/83129567/78bb5008-527f-43bf-980e-ef4ab2fb93b5)
```
服务器段除了一个套接字用于和客户端通信外 还有一个套接字用于监听 故整个客户端/服务器有三个套接字
```
服务器端
```c++
socket();//产生一个套接字A 得到一个fd1句柄
bind();//绑定A的IP和端口号
listen();//设置监听的上限(同时与socket建立连接的数量)
accpet();//以套接字A作为参数阻塞监听客户端连接 当有客户端连接的时候返回一个与客户端连接的新套接字B用来与客户端通信 原来的套接字A用来监听
```
客户端
```c++
socket();//产生一个套接字C 得到一个fd2句柄
connect();//绑定C的IP和端口并与另一个套接字连接
```
## socket函数
```c++
#include <sys/types.h> //包含在#include <unistd.h>
#include <sys/socket.h>

int socket(int domain, int type, int protocol);//创建一个套接字 成功返回套接字的fd 失败返回-1
// domain:AF_INET、AF_INET6、AF_UNIX/AF_LOCAL(本地套接字)
// type: SOCK_STREAM(流式协议TCP)、SOCK_DGRAM(报式协议UDP)
//protocol:选用协议中的代表协议 默认传0 tcp/udp
int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);//给套接字绑定地址结构(IP和端口号)详见上述socket数据结构
int listen(int sockfd, int backlog);//设置同时与服务器连接的上限数backlog最大128(同时进行三次握手的客户端数量)成功返回0 失败-1
int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);//阻塞等待客户端建立连接 成功返回与客户端联立联系的新套接字的fd
//sockfd: 传入socket返回的fd但是并不是用该套接字与客户端连接而是使用该套接字的地址结构
//addr: 传出参数 成功与服务器建立连接的那个客户端的地址结构 不同于bind中的是传入参数 传的是自身的地址结构
//addrlen: 传入传出参数 入：addr大小 出：addr实际大小

int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);//使用现有的socket与服务器建立连接 成功返回0 失败-1
//addr:传入参数 服务器的地址结构 客户端可以使用bind绑定地址结构 不使用的话系统采用隐式绑定
```
# 高并发服务器
