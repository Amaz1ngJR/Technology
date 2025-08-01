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
struct sockaddr_un {
    sa_family_t    sun_family; 
    char sun_path[UNIX_PATH_MAX];
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
socket模型创建流程图

TCP网络编程

![image](https://github.com/Amaz1ngJR/Technology/assets/83129567/78bb5008-527f-43bf-980e-ef4ab2fb93b5)

UDP网络编程 

![image](https://github.com/Amaz1ngJR/Technology/assets/83129567/9e56df27-d6f8-47ec-9399-650a386a5757)
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
## 网络socket

![image](https://github.com/user-attachments/assets/75211e78-74d3-45af-bcf4-ebd456b5796a)

函数原型
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
**设置端口复用**
```c++
#include <sys/types.h>    
#include <sys/socket.h>

int setsockopt(int sockfd, int level, int optname,
                      const void *optval, socklen_t optlen);//成功0失败-1
//设置端口复用 在bind之前设置
int opt = 1;
setsockopt(lfd, SOL_SOCKET, SO_REUSEADDR/SO_REUSEPORT, (void *)&opt, sizeof(opt));
```
**网络套接字具体实现服务器与客户端(1对1)【客户端输入小写字母 服务器将其转换成大写字母】**

服务器端
```c++
#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>
#include <arpa/inet.h>
#include <sys/socket.h>

void sys_err(const char* str) {
	perror(str);
	exit(1);
}

const uint32_t SERV_PORT = 9527;
int main() {
	struct sockaddr_in serv_addr, clit_addr;
	socklen_t clit_addr_len;
	char buf[BUFSIZ], client_IP[1024];//BUFSIZ = 4096
	//设置服务端socket数据结构 网络地址
	serv_addr.sin_family = AF_INET;//IPV4
	serv_addr.sin_port = htons(SERV_PORT);//绑定端口号
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);//绑定系统中有效的任意IP地址

	int lfd = socket(AF_INET, SOCK_STREAM, 0);//产生监听的套接字A
	if (lfd == -1)sys_err("socket error");

	int res = bind(lfd, (struct  sockaddr*)&serv_addr, sizeof(serv_addr));//绑定A的网络地址
	if (res == -1)sys_err("bind error");

	res = listen(lfd, 128);//设置监听的上限(同时与A建立连接的数量)
	if (res == -1)sys_err("listen error");

	clit_addr_len = sizeof(clit_addr);
	int cfd = accept(lfd, (struct sockaddr*)&clit_addr, &clit_addr_len);//阻塞等待客户端 返回与客户端连接的新套接字B cfd
	if (cfd == -1)sys_err("accept error");
	//输出客户端的网络地址
	std::cout << "client_IP = " <<
		inet_ntop(AF_INET, &clit_addr.sin_addr.s_addr, client_IP, 1024)
		<< " client_Port = " << ntohs(clit_addr.sin_port) << std::endl;

	while (1) {//运行该代码后 新建终端 输入 nc 127.1 9527(端口号)无需设置客户端 测试连接
		int ret = read(cfd, buf, sizeof(buf));//从客户端套接字读取数据到缓冲区
		write(STDOUT_FILENO, buf, ret);//将buf内容写入到终端
		for (int i = 0; i < ret; i++) {
			buf[i] = toupper(buf[i]);//将缓冲区中的字符转换为大写
		}
		write(cfd, buf, ret);//将转换后的数据写回客户端
	}
	//close(cfd);
	//close(lfd);
	return 0;
}
```
客户端
```c++
const uint32_t SERV_PORT = 9527;
int main() {
	struct sockaddr_in serv_addr;// 定义服务器地址结构体
	char buf[BUFSIZ];//BUFSIZ = 4096

    	// 设置服务器地址结构体的成员
	serv_addr.sin_family = AF_INET;// 使用IPv4地址
	serv_addr.sin_port = htons(SERV_PORT);// 设置服务器端口号，将主机字节序转换为网络字节序
	inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr.s_addr);//点分十进制->网络字节序

	int cfd = socket(AF_INET, SOCK_STREAM, 0);//创建客户端套接字C
	if (cfd == -1)sys_err("socket error");

	int res = connect(cfd, (struct  sockaddr*)&serv_addr, sizeof(serv_addr));//与服务器连接
	if (res == -1)sys_err("connect error");
	
	int cnt = 5;// 发送消息的次数
	while (cnt--) {
		write(cfd, "hello", 5);//向服务端发送一次 hello
		res = read(cfd, buf, sizeof(buf));//从服务器端接收数据到缓冲区
		write(STDOUT_FILENO, buf, res);//将从服务器接收的数据写入到标准输出
		sleep(1);
	}
	close(cfd);// 关闭套接字
	return 0;
}
```
## 本地套接字
```
int socket(int domain, int type, int protocol);domain: AF_INET --> AF_UNIX/AF_LOCAL
socket地址结构 sockaddr_in serv_addr --> sockaddr_un serv_addr
serv_addr.sin_family = AF_INET; --> serv_addr.sun_family = AF_UNIX;
serv_addr.sin_port = htons(SERV_PORT); serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
--> strcpy(srv_addr.sun_path, "srv.socket");

bind(lfd, (struct  sockaddr*)&serv_addr, sizeof(serv_addr));
--> int len = 2 + strlen("srv.socket");bind(lfd, (struct  sockaddr*)&serv_addr, len);
```

# 高并发服务器

## 多进程并发服务器
```c++
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <ctype.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <signal.h>

void catch_child(int signum) {//处理子进程退出的信号处理函数
	while (waitpid(0, nullptr, WNOHANG) > 0);
	return;// 回收已经退出的子进程
}

const uint32_t SERV_PORT = 9527;

int main() {
	struct sockaddr_in srv_addr, clt_addr;
	memset(&srv_addr, 0, sizeof(srv_addr));//memset逐字节赋值
	srv_addr.sin_family = AF_INET;
	srv_addr.sin_port = htons(SERV_PORT);
	srv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	// 创建监听套接字
	int lfd = socket(AF_INET, SOCK_STREAM, 0);
	bind(lfd, (struct sockaddr*)&srv_addr, sizeof(srv_addr));
	listen(lfd, 128);

	int pid, cfd, ret; char buf[BUFSIZ];
	while (1) {//父进程负责接受客户端的连接请求，而子进程则负责处理已经建立连接的客户端
		socklen_t clt_addr_len = sizeof(clt_addr);
		cfd = accept(lfd, (struct sockaddr*)&clt_addr, &clt_addr_len);//接受客户端连接 返回新套接字B
		pid = fork();
		if (pid < 0)sys_err("fork error");
		if (!pid) {// 子进程
			close(lfd);// 子进程作为客户端关闭监听的套接字
			break;
		}
		else { // 父进程设置 SIGCHLD 信号处理函数，避免僵尸进程
			struct sigaction act;
			act.sa_handler = catch_child;
			sigemptyset(&act.sa_mask);
			act.sa_flags = 0;
			ret = sigaction(SIGCHLD, &act, nullptr);
			if (ret)sys_err("sigaction error");
			close(cfd);//父进程作为服务器仅需要lfd用来建立连接
		}
	}

	if (!pid) {//子进程处理已经建立连接的客户端
		while (1) {
			ret = read(cfd, buf, sizeof(buf));// 读取客户端发送的数据
			if (!ret) {// 如果客户端关闭连接
				close(cfd);// 关闭客户端套接字
				exit(1);// 退出子进程
			}
			for (int i = 0; i < ret; i++)
				buf[i] = toupper(buf[i]);// 将接收到的数据转换为大写
			write(cfd, buf, ret);// 将转换后的数据写回客户端
			write(STDOUT_FILENO, buf, ret);// 将转换后的数据写入标准输出
		}
	}
	return 0;
}
```
## 多线程并发服务器
```c++
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

const uint32_t SERV_PORT = 9527;
const uint32_t MAXLINE = 8192;

struct s_info{//将网络地址与cfd绑定的结构体
	struct sockaddr_in cliaddr;
	int connfd;
};

void *do_work(void *arg){
	struct s_info *ts = (struct s_info*)arg;
	char buf[MAXLINE];
	char str[INET_ADDRSTRLEN];

	while (1) {
		int n = read(ts->connfd, buf, MAXLINE); //读客户端
		if (!n) {
			std::cout << "客户端fd" << ts->connfd << "关闭" << std::endl;
			break;
		}
		//输出客户端的网络地址
		std::cout << "client_IP = " <<
			inet_ntop(AF_INET, &(*ts).cliaddr.sin_addr, str, sizeof(str))
			<< " client_Port = " << ntohs((*ts).cliaddr.sin_port) << std::endl;
		for (int i = 0; i < n; ++i)
			buf[i] = toupper(buf[i]);//小写转换成大写
		write(STDOUT_FILENO, buf, n);//写出到屏幕
		write(ts->connfd, buf, n);//写回给客户端
	}
	close(ts->connfd);// 关闭客户端套接字
	return (void *)0; //pthread_exit(0);
}

int main() {
	struct sockaddr_in serv_addr, clt_addr;
	struct s_info ts[256];//创建结构体数组
	memset(&serv_addr, 0, sizeof(serv_addr));//memset逐字节赋值
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(SERV_PORT);
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	// 创建监听套接字A并绑定网络地址
	int lfd = socket(AF_INET, SOCK_STREAM, 0);
	bind(lfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
	listen(lfd, 128);

	int i = 0;
	pthread_t tid;
	while (1) {//主线程负责接受客户端的连接请求，而子线程则负责处理已经建立连接的客户端
		socklen_t clt_addr_len = sizeof(clt_addr);
		int connfd = accept(lfd, (struct sockaddr*)&clt_addr, &clt_addr_len);//接受客户端连接 返回新套接字B
		ts[i].cliaddr = clt_addr;
		ts[i].connfd = connfd;
		
		pthread_create(&tid, nullptr, do_work, (void*)&ts[i]);//这里ts是只读的 可以直接传地址
		pthread_detach(tid); //子线程分离 防止僵尸线程产生
		++i;
	}

	return 0;
}
```
## 多路I/O转接服务器
### select
```c++
#include <sys/select.h>

int select(int nfds, fd_set *readfds, fd_set *writefds,
	  fd_set *exceptfds, struct timeval *timeout);
//参数: nfds:所监听的所有文件描述符的最大值再+1(背后是一个for循环该值是循环的上限所以再加1)
//fd_set *三个参数(读、写、异常事件)都是传入传出参数 传入的时候是需要监听的文件描述符位图 传出的是实际发生事件的文件描述符位图 可以传空
void FD_CLR(int fd, fd_set *set);//将某个fd从fd位图中清出去(位图中删除)
int  FD_ISSET(int fd, fd_set *set);//判断fd是否在位图中 
void FD_SET(int fd, fd_set *set);//位图中添加fd
void FD_ZERO(fd_set *set);//把该位图的每个二进制位都置为0(清空位图)
// timeout是等待时长 1：NULL 永远等下去 2： 设置timeval 等待的时间 3：timeval 里时间全为0 检查描述字后立即返回 轮询
struct timeval {
	long tv_sec; //秒
	long tv_usec;//微妙
}
// 函数返回满足三个fd_set事件的总数
```
**select实现多路I/O转接服务器**
```
使用 cat /proc/sys/fs/file-max 查看当前计算机所能打开的最大文件个数(收硬件影响)
使用 ulimit -a 查看当前用户下的进程 打开文件描述符个数 默认为1024 sudo vi /etc/security/limits.conf修改上限值soft hard
优点：跨平台使用 同时监视多个文件描述符 当有文件描述符准备好时 select函数就会返回 可以避免使用多个线程或进程来处理多个连接 节省了系统资源
缺点：监听上限受文件描述符限制 最大1024 、 当需要监视的文件描述符数量增加时 select() 的性能可能会下降
```
```c++
#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>
#include <arpa/inet.h>
#include <sys/types.h>   
#include <sys/socket.h>
#include <sys/select.h>
#include <string.h>


const uint32_t SERV_PORT = 9527;

void sys_err(const char* str) {
	perror(str);
	exit(1);
}

int main() {
	char buf[BUFSIZ];
	struct sockaddr_in serv_addr, clit_addr;
	memset(&serv_addr, 0, sizeof(serv_addr));//memset逐字节赋值
	socklen_t clit_addr_len;
	//设置服务端socket数据结构 网络地址
	serv_addr.sin_family = AF_INET;//IPV4
	serv_addr.sin_port = htons(SERV_PORT);//绑定端口号
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);//绑定系统中有效的任意IP地址

	int lfd = socket(AF_INET, SOCK_STREAM, 0);//产生监听的套接字A
	if (lfd == -1)sys_err("socket error");
	//设置端口复用 
	int opt = 1, maxfd = lfd;	
	setsockopt(lfd, SOL_SOCKET, SO_REUSEADDR, (void *)&opt, sizeof(opt));

	int res = bind(lfd, (struct  sockaddr*)&serv_addr, sizeof(serv_addr));//绑定A的网络地址
	if (res == -1)sys_err("bind error");
	res = listen(lfd, 128);//设置监听的上限(同时与A建立连接的数量)
	if (res == -1)sys_err("listen error");

	fd_set rset, allset;
	FD_ZERO(&allset);//位图全置零
	FD_SET(lfd, &allset);//将lfd加入到监控位图中

	while (1) {
		rset = allset;//传入之前
		int nready = select(maxfd + 1,&rset, nullptr, nullptr, nullptr);
		if (nready < 0) sys_err("nready error");
		if (FD_ISSET(lfd, &rset)){//rest传出之后 有新的客户端连接请求
			clit_addr_len = sizeof(clit_addr);
			int connfd = accept(lfd, (struct sockaddr*)&clit_addr, &clit_addr_len);//不会阻塞
			FD_SET(connfd, &allset);//向监控位图里添加新的文件描述符

			if (maxfd < connfd) maxfd = connfd;
			if (nready == 1) continue; //只有lfd有事件 而该if就是处理lfd的
		}
		for (int i = lfd + 1; i <= maxfd; ++i){
			if (FD_ISSET(i, &rset)){
				int n = read(i, buf, sizeof(buf));
				if (!n) {//客户端关闭连接
					close(i);//服务器也关闭连接
					FD_CLR(i, &allset); //解除对此文件的监控
				}
				else if (n > 0){
					for (int j = 0; j < n; ++j)
						buf[j] = toupper(buf[j]);
					write(i, buf , n);
				}
			}
		}
	}
	close(lfd);
	return 0;
}
```
### poll
```c++
#include <poll.h>

int poll(struct pollfd *fds, nfds_t nfds, int timeout);
//参数：fds:监听的文件描述符【数组】
struct pollfd {
	int   fd;         /* 文件描述符 */
	short events;     /* 监听事件(读POLLIN、写POLLOUT、异常POLLOERR等) */
	short revents;    /* 返回事件 */
};
//nfds:监听数组中实际有效监听个数(数组大小为n但是里面可能存的内容小于n) timeout：>0超时时长 单位毫秒 -1阻塞等待 0不阻塞
//返回值：满足对应监听事件的文件描述符总个数 同select
```

**poll实现多路I/O转接服务器**
```c++
#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>
#include <arpa/inet.h>
#include <sys/types.h>   
#include <sys/socket.h>
#include <poll.h>
#include <string.h>


constexpr uint32_t SERV_PORT = 9527;
constexpr uint32_t MAXLINE = 80;
constexpr int OPEN_MAX = 1024;

void sys_err(const char* str) {
	perror(str);
	exit(1);
}

int main() {
	char buf[MAXLINE], str[INET_ADDRSTRLEN];
	struct sockaddr_in serv_addr, clit_addr;
	struct pollfd client[OPEN_MAX];
	memset(&serv_addr, 0, sizeof(serv_addr));//memset逐字节赋值
	socklen_t clit_addr_len;
	//设置服务端socket数据结构 网络地址
	serv_addr.sin_family = AF_INET;//IPV4
	serv_addr.sin_port = htons(SERV_PORT);//绑定端口号
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);//绑定系统中有效的任意IP地址

	int lfd = socket(AF_INET, SOCK_STREAM, 0);//产生监听的套接字A
	if (lfd == -1)sys_err("socket error");
	//设置端口复用 
	int opt = 1, maxfd = 0;	
	setsockopt(lfd, SOL_SOCKET, SO_REUSEADDR, (void *)&opt, sizeof(opt));

	int res = bind(lfd, (struct  sockaddr*)&serv_addr, sizeof(serv_addr));//绑定A的网络地址
	if (res == -1)sys_err("bind error");
	res = listen(lfd, 128);//设置监听的上限(同时与A建立连接的数量)
	if (res == -1)sys_err("listen error");

	client[0].fd = lfd;
	client[0].events = POLLIN; 

	for(int i = 1; i < OPEN_MAX; ++i)
		client[i].fd = -1; //初始化
	
	while (1) {
		int nready = poll(client, maxfd + 1, -1); //阻塞(-1)监听是否有客户端连接请求
		if (nready < 0) sys_err("nready error");
		if (client[0].revents & POLLIN) {  //listenfd有读事件就绪
			clit_addr_len = sizeof(clit_addr);
			int connfd = accept(lfd, (struct sockaddr *)&clit_addr, &clit_addr_len);
			//输出客户端的网络地址
			std::cout << "client_IP = " <<
				inet_ntop(AF_INET, &clit_addr.sin_addr.s_addr, str, 1024)
				<< " client_Port = " << ntohs(clit_addr.sin_port) << std::endl;
			int i;
			for (i = 1; i < OPEN_MAX; ++i) 
				if (client[i].fd < 0) {
					client[i].fd = connfd;//找到空闲位置放置connfd
					break;
				}
			if (i == OPEN_MAX) perror("too many clients");

			client[i].events = POLLIN; //设置监听读事件
			if (i > maxfd) maxfd = i;  //更新client[]中最大下标
			if (nready == 1) continue; //仅是lfd
		}
		for (int i = 1; i <= maxfd; ++i) {
			int sockfd = client[i].fd;
			if (sockfd < 0) continue;
			if (client[i].revents & POLLIN) {
				int n = read(sockfd, buf, MAXLINE);
				if (n < 0) {
					if (errno == EINTR) {}//被异常中断 需要重启
					if (errno == EAGAIN) {} //以非阻塞方式读 但没数据 需要再次读
					if (errno == ECONNRESET) {//连接被重置 需要关闭 移除监听队列
						close(sockfd);
						client[i].fd = -1;
					}
					else perror("read error");
				}
				else if (!n) {//客户端关闭连接
					std::cout << "客户端" << i << "关闭连接" << std::endl;
					close(sockfd);
					client[i].fd = -1;
				}
				else {
					for (int j = 0; j < n; ++j)
						buf[j] = toupper(buf[j]);
					write(sockfd, buf, n);
				}
				if(nready <= 1) break;
			}
		}
	}
	close(lfd);
	return 0;
}
```
### epoll
```
epoll是select/poll的增强版本 它能够显著提高程序在大量并发连接中只有少量活跃的情况下系统CPU利用率
因为它会复用文件描述符集合来传递结果 而不用开发者每次等待事件之前都必须重新准备要被监视的文件描述符集合
另外在获取事件的时候 它无须遍历整个被监视的描述符集 只要遍历那些被内核IO事件异步唤醒而加入Ready队列的描述符集合就行了
缺点是不能跨平台
```
```c++
#include <sys/epoll.h>

int epoll_create(int size);//size为所创建的红黑树的监听结点数量(仅供内核参考 后面可以动态拓展) 
int epoll_create1(int flags);//flags只支持EPOLL_CLOEXEC 在创建的epoll上设置O_CLOEXEC标志表示在执行时关闭文件描述符
//返回指向新创建红黑树的根节点的文件描述符fd 失败返回-1

int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);
//参数: epfd:epoll_create函数的返回值   fd:待监听的fd
//op:对该监听红黑树所做的操作:(增加fd到红黑树)EPOLL_CTL_ADD (修改fd的监听事件)EPOLL_CTL_MOD  (删除监听)EPOLL_CTL_DEL
//event: 是一个结构体地址   传出参数   函数成功返回0 失败-1
struct epoll_event {
	uint32_t     events;      /* Epoll 事件 */ EPOLLIN读 EPOLLOUT写 EPOLLERR异常
	epoll_data_t data;        /* User data variable */
};
typedef union epoll_data {
	void        *ptr;
	int          fd;  //对应函数参数里的fd 传出参数
	uint32_t     u32; 
	uint64_t     u64;
} epoll_data_t;

int epoll_wait(int epfd, struct epoll_event *events, int maxevents, int timeout);
//参数: envents: 一个结构体数组 不同于epoll_ctl中的envent只是一个结构体 传出参数 传出满足监听条件的fd对应的结构体
//maxevents:告诉内核这个envents的大小 不能超过epoll_create时的size
//timeout: >0 超时时间单位毫秒 -1 阻塞 0 立即返回   函数成功返回有多少文件描述符就绪 可作为循环上限 时间到返回0 失败返回-1
int epoll_pwait(int epfd, struct epoll_event *events,
	      int maxevents, int timeout,
	      const sigset_t *sigmask);
```

**epoll实现多路I/O转接服务器**
```c++
#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>
#include <arpa/inet.h>
#include <sys/types.h>   
#include <sys/socket.h>
#include <sys/epoll.h>
#include <string.h>

constexpr uint32_t SERV_PORT = 9527;
constexpr uint32_t MAXLINE = 8192;
constexpr int OPEN_MAX = 5000;

void sys_err(const char* str) {
	perror(str);
	exit(1);
}

int main() {
	char buf[MAXLINE], str[INET_ADDRSTRLEN];
	struct sockaddr_in serv_addr, clit_addr;
	struct epoll_event tep, ep[OPEN_MAX]; //tep: epoll_ctl参数 ep: epoll_wait参数
	memset(&serv_addr, 0, sizeof(serv_addr));//memset逐字节赋值
	socklen_t clit_addr_len;
	//设置服务端socket数据结构 网络地址
	serv_addr.sin_family = AF_INET;//IPV4
	serv_addr.sin_port = htons(SERV_PORT);//绑定端口号
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);//绑定系统中有效的任意IP地址

	int lfd = socket(AF_INET, SOCK_STREAM, 0);//产生监听的套接字A
	if (lfd == -1)sys_err("socket error");
	//设置端口复用 
	int opt = 1;	
	setsockopt(lfd, SOL_SOCKET, SO_REUSEADDR, (void *)&opt, sizeof(opt));

	int res = bind(lfd, (struct  sockaddr*)&serv_addr, sizeof(serv_addr));//绑定A的网络地址
	if (res == -1)sys_err("bind error");
	res = listen(lfd, 128);//设置监听的上限(同时与A建立连接的数量)
	if (res == -1)sys_err("listen error");

	int efd = epoll_create(OPEN_MAX);//创建epoll模型 efd指向红黑树根节点
	if (efd == -1) sys_err("epoll_create error");
	tep.events = EPOLLIN;
	tep.data.fd = lfd;

	res = epoll_ctl(efd, EPOLL_CTL_ADD, lfd, &tep);//将lfd及结构体添加到红黑树上
	if (res == -1) sys_err("epoll_ctl error");
	
	while (1) {
		int nready = epoll_wait(efd, ep, OPEN_MAX, -1); //阻塞(-1)监听是否有客户端连接请求
		if (nready == -1) sys_err("nready error");

		for (int i = 0; i < nready; ++i){
			if (!(ep[i].events & EPOLLIN)) continue; //跳过非读事件
			if (ep[i].data.fd == lfd) {//lfd事件
				clit_addr_len = sizeof(clit_addr);
				int connfd = accept(lfd, (struct sockaddr *)&clit_addr, &clit_addr_len);
				//输出客户端的网络地址
				std::cout << "client_IP = " <<
					inet_ntop(AF_INET, &clit_addr.sin_addr.s_addr, str, sizeof(str))
					<< " client_Port = " << ntohs(clit_addr.sin_port) << std::endl;
				tep.events = EPOLLIN;
				tep.data.fd = connfd;

				res = epoll_ctl(efd, EPOLL_CTL_ADD, connfd, &tep);//加入到红黑树中
				if (res == -1) sys_err("epoll_ctl error");
			}
			else{//非lfd事件
				int sockfd = ep[i].data.fd;
				int n = read(sockfd, buf, MAXLINE);
				if (!n) {//客户端关闭连接
					res = epoll_ctl(efd, EPOLL_CTL_DEL, sockfd, nullptr);//红黑树删除该sockfd
					if (res == -1) sys_err("epoll_ctl error");
					close(sockfd);
					std::cout << "close connect" << sockfd << std::endl;
				}
				else if (n < 0) {//出错
					epoll_ctl(efd, EPOLL_CTL_DEL, sockfd, nullptr);//红黑树删除该sockfd
					close(sockfd);
				}
				else {
					for (int i = 0; i < n; ++i)
						buf[i] = toupper(buf[i]);
					write(sockfd, buf, n);
					write(STDOUT_FILENO, buf, n);//写出到屏幕
				}
			}
		}
	
	}
	close(lfd);
	return 0;
}
```
### select、poll、epoll的区别
select 实现多路复⽤的⽅式是：

将已连接的 Socket 都放到⼀个**⽂件描述符集合**fd_set，然后调⽤ select 函数将 fd_set 集合拷⻉到内核⾥，让内核来检查是否有⽹络事件产⽣，检查的⽅式很粗暴，就是通过遍历 fd_set 的⽅式，当检查到有事件产⽣后，将此 Socket 标记为可读或可写， 接着再把整个 fd_set 拷⻉回⽤户态⾥，然后⽤户态还需要再通过遍历的⽅法找到可读或可写的 Socket，再对其处理。

select 使⽤固定⻓度的 BitsMap，表示⽂件描述符集合，⽽且所⽀持的⽂件描述符的个数是有限制的，在 Linux 系统中，由内核中的 FD_SETSIZE 限制， 默认最⼤值为 1024 ，只能监听 0~1023 的⽂件描述符。

select 机制的缺点：
```
（1）每次调用 select，都需要把 fd_set 集合从用户态拷贝到内核态，如果 fd_set 集合很大时，那这个开销也很大，比如百万连接却只有少数活跃连接时这样做就太没有效率。
（2）每次调用 select 都需要在内核遍历传递进来的所有 fd_set，如果 fd_set 集合很大时，那这个开销也很大。
（3）为了减少数据拷贝带来的性能损坏，内核对被监控的 fd_set 集合大小做了限制，一般为 1024，如果想要修改会比较麻烦，可能还需要编译内核。
（4）每次调用 select 之前都需要遍历设置监听集合，重复工作。
```
poll 不再⽤ BitsMap 来存储所关注的⽂件描述符，取⽽代之⽤动态数组，以链表形式来组织，突破了 select 的⽂件描述符个数限制，当然还会受到系统⽂件描述符限制。

但是 poll 和 select 并没有太⼤的本质区别，都是使⽤线性结构存储进程关注的 Socket 集合，因此都需要遍历⽂件描述符集合来找到可读或可写的 Socke，时间复杂度为 O(n)，⽽且也需要在⽤户态与内核态之间拷⻉⽂件描述符集合，这种⽅式随着并发数上来，性能的损耗会呈指数级增⻓。

epoll 通过两个⽅⾯，很好解决了 select/poll 的问题。
```
epoll 在内核⾥使⽤红⿊树来跟踪进程所有待检测的⽂件描述字，把需要监控的 socket 通过 epoll_ctl() 函数加⼊内核中的红⿊树⾥，通过对这棵⿊红树进⾏操作，这样就不需要像 select/poll 每次操作时都传⼊整个 socket 集合，只需要传⼊⼀个待检测的 socket，减少了内核和⽤户空间⼤量的数据拷⻉和内存分配;
epoll 使⽤事件驱动的机制，内核⾥维护了⼀个链表来记录就绪事件，当某个 socket 有事件发⽣时，通过回调函数，内核会将其加⼊到这个就绪事件列表中，当⽤户调⽤ epoll_wait() 函数时，只会返回有事件发⽣的⽂件描述符的个数，不需要像 select/poll 那样轮询扫描整个 socket 集合，⼤⼤提⾼了检测的效率。
```
![image](https://github.com/user-attachments/assets/0dbfa502-63fe-448a-83d3-b76db6f35632)

## epoll反应堆(Reactor模型)
epoll反应堆： epoll ET模式 + 非阻塞、轮询 + void *ptr
```
Epoll事件有两种模型： 考虑情景：一个写满2KB的管道 调用epoll_wait会返回rfd表示可以读了，但是只读1KB数据再次调用epoll_wait
Edge Triggered(ET) 边缘触发：只有数据到来才触发 不管缓冲区中是否还有数据（情景中epoll_wait不返回fd） event.events = EPOLLIN | EPOLLET;
ET是高速工作方式 只支持非阻塞socket(配合忙轮询读) :int flag = fcntl(cfd, F_GETFL); flag |= O_NONBLOCK; fcntl(cfd, F_SETFL, flag);
Level Triggered(LT) 水平触发(默认)：只要有数据就会触发 （情景中epoll_wait返回fd）event.events = EPOLLIN;
```
```c++
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <ctype.h>
#include <arpa/inet.h>
#include <sys/types.h>   
#include <sys/socket.h>
#include <sys/epoll.h>
#include <string.h>

constexpr uint32_t SERV_PORT = 9527;
constexpr uint32_t MAXLINE = 8192;
constexpr uint32_t MAX_EVENTS = 1024;
constexpr int OPEN_MAX = 5000;

void sys_err(const char* str) {
	perror(str);
	exit(1);
}

struct Event {
	int fd;     //要监听的文件描述符
	int events; //对应的监听事件
	void* arg; //泛型参数
	void (*call_back)(int fd, int events, void* arg);//回调函数
	int status; //是否监听
	char buf[BUFSIZ];
	int len;
	long last_active;//记录加入红黑树的时间
};

int g_efd;//全局变量 保存epoll_create返回的文件描述符
struct Event g_events[MAX_EVENTS + 1];

void eventset(struct Event* ev, int fd, void(*call_back)(int, int, void*), void* arg) {
	ev->fd = fd;
	ev->events = 0;
	ev->arg = arg;
	ev->call_back = call_back;
	ev->status = 0;
	memset(ev->buf, 0, sizeof(ev->buf));
	ev->len = 0;
	ev->last_active = time(nullptr);
	return;
}
void eventadd(int efd, int events, struct Event* ev) {
	struct epoll_event epv = { 0, {0} };
	int op;
	epv.data.ptr = ev;
	epv.events = ev->events = events;//读事件EPOLLIN或者写事件EPOLLOUT

	if (ev->status == 0) {
		op = EPOLL_CTL_ADD; //将其加入红黑树中 并将status置为1
		ev->status = 1;
	}

	if (epoll_ctl(efd, op, ev->fd, &epv) < 0)
		std::cout << "event " << ev->fd << " add " << events << " failed " << std::endl;
	else
		std::cout << "event " << ev->fd << " add " << events << " success " << std::endl;
}
void eventdel(int efd, Event* ev) {
	struct epoll_event epv = { 0, {0} };
	if (ev->status == 0)
		return;//不在红黑树上
	epv.data.ptr = nullptr;
	ev->status = 0;
	epoll_ctl(efd, EPOLL_CTL_DEL, ev->fd, &epv);//从红黑树上删除
}
void senddata(int fd, int events, void* arg);
void recvdata(int fd, int events, void* arg)
{ // read
	Event* ev = (Event*)arg;
	int len = recv(fd, ev->buf, sizeof(ev->buf), 0);//读文件描述符 数据存入buf中
	eventdel(g_efd, ev);//读完以后从红黑树上删除读事件
	if (len > 0) {
		ev->len = len;
		ev->buf[len] = '\0';//手动添加字符串结束标记

		eventset(ev, fd, senddata, ev);//将该fd对应的回调函数设为 senddata/write
		eventadd(g_efd, EPOLLOUT, ev);//将fd加入到红黑树中监听写事件
	}
	else close(ev->fd);
}
void senddata(int fd, int events, void* arg) {
	Event* ev = (Event*)arg;
	int len = send(fd, ev->buf, ev->len, 0);//将数据写回给客户端
	eventdel(g_efd, ev);//写完以后从红黑树上删除写事件
	if (len > 0) {
		eventset(ev, fd, recvdata, ev);//将该fd对应的回调函数设为 recvdata/read
		eventadd(g_efd, EPOLLIN, ev);//将fd加入到红黑树中监听读事件
	}
	else close(ev->fd);
}
void acceptconn(int lfd, int events, void* arg) {
	struct sockaddr_in clit_addr;
	socklen_t clit_addr_len = sizeof(clit_addr);
	int cfd, i;
	if ((cfd = accept(lfd, (sockaddr*)&clit_addr, &clit_addr_len)) == -1)
		sys_err("accept error");
	do {
		for (i = 0; i < MAX_EVENTS; ++i)
			if (g_events[i].status == 0)
				break;//找到一个空闲的元素
		if (i == MAX_EVENTS)break;
		int flag = 0;
		if ((flag = fcntl(cfd, F_SETFL, O_NONBLOCK)) < 0)//将cfd也设置为非阻塞
			sys_err("fcntl nonblocking");

		//给cfd设置一个 Event结构体
		eventset(&g_events[i], cfd, recvdata, &g_events[i]);
		eventadd(g_efd, EPOLLIN, &g_events[i]);//将fd添加到红黑树g_efd中 监听读事件
	} while (0);
	return;
}
//初始化监听套接字
void init_listen_socket(int efd) {
	struct sockaddr_in serv_addr;
	int lfd = socket(AF_INET, SOCK_STREAM, 0);
	fcntl(lfd, F_SETFL, O_NONBLOCK); //将socket设为非阻塞
	memset(&serv_addr, 0, sizeof(serv_addr)); // memset逐字节赋值
	// 设置服务端socket数据结构 网络地址
	serv_addr.sin_family = AF_INET;//IPV4
	serv_addr.sin_port = htons(SERV_PORT);//绑定端口号
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);//绑定系统中有效的任意IP地址
	//设置端口复用 
	int opt = 1;
	setsockopt(lfd, SOL_SOCKET, SO_REUSEADDR, (void*)&opt, sizeof(opt));

	int res = bind(lfd, (struct  sockaddr*)&serv_addr, sizeof(serv_addr));//绑定A的网络地址
	if (res == -1)sys_err("bind error");
	res = listen(lfd, 128);//设置监听的上限(同时与A建立连接的数量)
	if (res == -1)sys_err("listen error");

	eventset(&g_events[MAX_EVENTS], lfd, acceptconn, &g_events[MAX_EVENTS]);
	eventadd(efd, EPOLLIN, &g_events[MAX_EVENTS]);
	return;
}

int main() {
	g_efd = epoll_create(MAX_EVENTS + 1);
	if (g_efd <= 0)
		sys_err("epoll_create error");

	init_listen_socket(g_efd);//初始化监听套接字

	struct epoll_event events[MAX_EVENTS + 1];//保存已经满足就绪事件的文件描述符
	int check_pos = 0, i;
	while (1) {
		//超时验证 每次测试100个链接 不测试listenfd 当客户端60秒内没有和服务器通信 则关闭此客户端
		long now = time(nullptr);//当期时间
		for (i = 0; i < 100; ++i, ++check_pos) {
			if (check_pos == MAX_EVENTS)
				check_pos = 0;
			if (g_events[check_pos].status != 1)
				continue; // 不在红黑树上
			long take_time = now - g_events[check_pos].last_active;
			if (take_time >= 60) {
				close(g_events[check_pos].fd);
				std::cout << g_events[check_pos].fd << " time out" << std::endl;
				eventdel(g_efd, &g_events[check_pos]);//将该客户端从红黑树移除
			}
		}
		//监听红黑树 将满足的事件的文件描述符加至events数组中 1秒没有事件满足 返回0
		int nfd = epoll_wait(g_efd, events, MAX_EVENTS + 1, 1000);
		if (nfd < 0)
			break;

		for (int i = 0; i < nfd; ++i) {
			Event* ev = (Event*)events[i].data.ptr;
			if ((events[i].events & EPOLLIN) && (ev->events & EPOLLIN))//读操作就绪
				ev->call_back(ev->fd, events[i].events, ev->arg);
			if ((events[i].events & EPOLLOUT) && (ev->events & EPOLLOUT))//写操作就绪
				ev->call_back(ev->fd, events[i].events, ev->arg);
		}
	}

	return 0;
}
```
## 线程池
线程池的核心参数
```
核心线程数（Core Pool Size）：线程池中能够同时存在的线程数量。即使线程处于空闲状态，核心线程也会被保留在线程池中
最大线程数（Maximum Pool Size）：线程池中最大允许存在的线程数量。当线程池中的线程数量达到这个值时，后续的任务将被阻塞或拒绝
线程存活时间（Keep Alive Time）：当线程池中的线程数量超过核心线程数时，多余的空闲线程在被回收之前等待新任务的最长时间
工作队列（Work Queue）：用于存放提交的任务的队列。当线程池中的线程数量达到核心线程数时，新的任务将被放入工作队列中等待执行
```
```c++
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <ctype.h>
#include <arpa/inet.h>
#include <sys/types.h>   
#include <sys/socket.h>
#include <sys/epoll.h>
#include <string.h>

//-----STL
#include <vector>

constexpr uint16_t SERV_PORT = 9527;
constexpr uint16_t MAXLINE = 8192;
constexpr uint16_t MAX_EVENTS = 1024;
constexpr uint16_t OPEN_MAX = 5000;
constexpr uint16_t MIN_WAIT_TASK_NUM = 30;
constexpr uint16_t DEFAULT_THREAD_VARY = 10;

void sys_err(const char* str) {
	perror(str);
	exit(1);
}

struct threadpool_task_t{
    void *(*function)(void *); //函数指针 回调函数
    void *arg;//上面函数的参数
};//各子线程任务结构体

void *threadpool_thread(void *threadpool);
void *adjust_thread(void *threadpool);
class ThreadPool
{ // 线程池
public:
    int min_thr_num, max_thr_num; // 线程池中最小、最大线程个数
    int live_thr_num;//当前存活线程个数
    int busy_thr_num;//忙状态线程个数
    int wait_exit_thr_num;//要销毁的线程个数

    int queue_front;
    int queue_rear;
    int queue_size;
    int queue_max_size;

    bool shutdown; //线程池的使用状态
    
    pthread_mutex_t lock;          // 用于锁住本结构体
    pthread_mutex_t thread_counter;//记录忙状态线程个数的锁 --busy_thr_num
    pthread_cond_t queue_not_full;//当队满时 添加任务的线程阻塞
    pthread_cond_t queue_not_empty;//队不空的时候 通知等待任务的线程
    pthread_t adjust_tid;//存管理线程tid

    std::vector<pthread_t> threads;          // 存放线程池中每个线程的tid
    std::vector<struct threadpool_task_t> task_queue; // 任务队列 (数组首地址)

    ThreadPool(int min_thr_num,int max_thr_num,int queue_max_size):
    min_thr_num(min_thr_num),max_thr_num(max_thr_num),queue_max_size(queue_max_size)
    ,queue_front(0),queue_size(0),queue_rear(0),shutdown(false),live_thr_num(min_thr_num),
    busy_thr_num(0),wait_exit_thr_num(0){
        threads.resize(max_thr_num);
        task_queue.resize(queue_max_size);

        pthread_mutex_init(&lock, nullptr);
        pthread_mutex_init(&thread_counter, nullptr);
        pthread_cond_init(&queue_not_full, nullptr);
        pthread_cond_init(&queue_not_empty, nullptr);

        for (int i = 0; i < min_thr_num;++i){//启动min_thr_num个线程
            pthread_create(&threads[i], nullptr, threadpool_thread, (void *)this);
        }
        pthread_create(&adjust_tid, nullptr, adjust_thread, (void *)this);//创建管理线程
    }
};

void *threadpool_thread(void *threadpool)
{ // 线程池中各个工作线程
    ThreadPool *pool = (ThreadPool *)threadpool;
    threadpool_task_t task;

    while (1)
    {
        pthread_mutex_lock(&pool->lock); // 给整个结构体加锁
        while (pool->queue_size == 0 && !pool->shutdown)
        {                                                           // 没有任务
            pthread_cond_wait(&pool->queue_not_empty, &pool->lock); // 阻塞条件变量上
            // 清除指定数目的空闲线程
            if (pool->wait_exit_thr_num > 0)
            {
                pool->wait_exit_thr_num--;
                if (pool->live_thr_num > pool->min_thr_num)
                { // 如果线程池中线程数大于最小值时可以结束
                    pool->live_thr_num--;
                    pthread_mutex_unlock(&pool->lock);
                    pthread_exit(nullptr);
                }
            }
        }
        // 如果指定了true 要关闭线程池中每个线程 自行退出处理 销毁线程池
        if (pool->shutdown)
        {
            pthread_mutex_unlock(&pool->lock);
            std::cout << "thread" << pthread_self() << "is exiting" << std::endl;
            pthread_detach(pthread_self());
            pthread_exit(nullptr);
        }
        task.function = pool->task_queue[pool->queue_front].function;
        task.arg = pool->task_queue[pool->queue_front].arg;
        pool->queue_front = (pool->queue_front + 1) % pool->queue_max_size;
        pool->queue_size--;
        // 通知可以有新的任务添加进来
        pthread_cond_broadcast(&pool->queue_not_full);
        // 任务取出后 立即将线程池锁 释放
        pthread_mutex_unlock(&pool->lock);
        // 执行任务
        pthread_mutex_lock(&pool->thread_counter); // 忙状态线程数 变量锁
        ++pool->busy_thr_num;
        pthread_mutex_unlock(&pool->thread_counter);
        (*(task.function))(task.arg); // 执行回调函数
        // 任务结束处理
        pthread_mutex_lock(&pool->thread_counter);
        --pool->busy_thr_num;
        pthread_mutex_unlock(&pool->thread_counter);
    }
    pthread_exit(nullptr);
}

void *adjust_thread(void *threadpool){
    ThreadPool *pool = (ThreadPool *)threadpool;
    while(!pool->shutdown){
        sleep(10);//定时 对线程池管理
        pthread_mutex_lock(&pool->lock);
        int queue_size = pool->queue_size;
        int live_thr_num = pool->live_thr_num;
        pthread_mutex_unlock(&pool->lock);

        pthread_mutex_lock(&pool->thread_counter);
        int busy_thr_num = pool->busy_thr_num;
        pthread_mutex_unlock(&pool->thread_counter);

        //任务数大于最小线程池个数 存活的线程数少于最大线程个数时 创建新线程
        if(queue_size>=MIN_WAIT_TASK_NUM&&live_thr_num<pool->max_thr_num){
            pthread_mutex_lock(&pool->lock);
            int add =0;
            for (int i = 0; i < pool->max_thr_num && add < DEFAULT_THREAD_VARY 
            && pool->live_thr_num < pool->max_thr_num;++i){
                ++add;
                ++pool->live_thr_num;
            }
            pthread_mutex_unlock(&pool->lock);
        }
        //当忙线程*2 小于存活的线程数 且存活的线程数 大于 最小线程数时 销毁多余的空闲线程
        if((busy_thr_num*2)<live_thr_num&&live_thr_num>pool->min_thr_num){
            pthread_mutex_lock(&pool->lock);
            pool->wait_exit_thr_num = DEFAULT_THREAD_VARY;
            pthread_mutex_unlock(&pool->lock);
            for (int i = 0; i < DEFAULT_THREAD_VARY;++i)
                pthread_cond_signal(&pool->queue_not_empty);
        }
    }
    return nullptr;
}

int threadpool_add(ThreadPool *pool,void*(*function)(void*arg),void*arg){
    pthread_mutex_lock(&pool->lock);
    while((pool->queue_size==pool->queue_max_size)&&!pool->shutdown)//队列已满 
        pthread_cond_wait(&pool->queue_not_full, &pool->lock);//调wait阻塞
    if(pool->shutdown){
        pthread_cond_broadcast(&pool->queue_not_empty);
        pthread_mutex_unlock(&pool->lock);
        return 0;
    }
    if(pool->task_queue[pool->queue_rear].arg!=nullptr)//清空 工作线程调用的回调函数的参数
        pool->task_queue[pool->queue_rear].arg = nullptr;

    //添加任务到任务队列中
    pool->task_queue[pool->queue_rear].function = function;
    pool->task_queue[pool->queue_rear].arg = arg;
    pool->queue_rear = (pool->queue_rear + 1) % pool->queue_max_size;//模拟环形
    pool->queue_size++;

    //添加完任务后 队列不为空 唤醒线程池中等待处理任务的线程
    pthread_cond_signal(&pool->queue_not_empty);
    pthread_mutex_unlock(&pool->lock);
    return 0;
}

int threadpool_free(ThreadPool *pool){
    if(!pool)return -1;
    if(!pool->task_queue.empty())
        pool->task_queue.clear();
    if (!pool->threads.empty())
    {
        pool->threads.clear();
        pthread_mutex_lock(&pool->lock);
        pthread_mutex_destroy(&pool->lock);
        pthread_mutex_lock(&pool->thread_counter);
        pthread_mutex_destroy(&pool->thread_counter);
        pthread_cond_destroy(&pool->queue_not_empty);
        pthread_cond_destroy(&pool->queue_not_full);
    }
    delete (pool);
    pool = nullptr;
    return 0;
}

int threadpool_destroy (ThreadPool * pool){
    if(!pool)return -1;
    pool->shutdown = true;
    //先销毁管理线程
    pthread_join(pool->adjust_tid, nullptr);
    for (int i = 0; i < pool->live_thr_num;++i)
        //通知所有空闲线程
        pthread_cond_broadcast(&pool->queue_not_empty);
    for (int i = 0; i < pool->live_thr_num;++i)
        pthread_join(pool->threads[i], nullptr);
    threadpool_free(pool);
    return 0;
}

void* process(void*arg){
    printf("thread process");
    sleep(2);
    return nullptr;
}
int main(){
    ThreadPool *thp = new ThreadPool(3, 100, 100);//创建线程池 线程数量为3-100 队列最大为100
    printf("pool inited");

    int num[20];
    for (int i = 0; i < 20;++i){
        num[i] = i;
        std::cout << "add task " << i << std::endl;
        threadpool_add(thp, process, (void *)&num[i]);//向线程池添加任务
    }
    sleep(10);//等待子线程完成任务
    threadpool_destroy(thp);
    return 0;
}
```

# 网络问题排查
## 网络测试

### speedtest

### iperf3
在服务器端启动 iperf3
```bash
iperf3 -s
```
默认情况下，iperf3 服务器会在 TCP 端口 5201 上监听连接.如果想指定不同的端口，可以使用 -p 参数
```bash
iperf3 -s -p 5202
```
客户端运行以下命令来开始带宽测试(TCP)：
```bash
iperf3 -c <server_ip> -p 5202
```
确保防火墙允许外部访问端口，Linux下：
```bash
sudo ufw allow 5202/tcp
```
默认的 10 秒测试时间,使用 -t 参数自定义测试时间
```bash
iperf3 -c <server_ip>  -p 5201 -t 30
```
UDP:
```bash
iperf3 -c <server_ip> -u 
```
默认情况下，UDP测试会发送18Mbps的数据流。如果你想要改变这个速率，可以使用 -b 参数指定带宽
```bash
iperf3 -c <server_ip>  -u -b 10M
```
双向测试：如果你想同时测试上传和下载速度，可以在客户端使用 -d 参数：
```bash
iperf3 -c <server_ip> -d
```
并行流测试：使用 -P 参数指定并发流的数量以模拟多线程应用的情况： 创建4个并行的TCP连接进行测试
```bash
iperf3 -c <server_ip> -P 4
```
