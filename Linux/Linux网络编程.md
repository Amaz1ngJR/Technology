# Socket编程
## 套接字socket
在TCP/IP协议中 IP地址+TCP/UDP端口号 唯一标识网络通讯中的一个进程 “IP地址+端口号”对应一个套接字socket 

两个socket组成的socket pair唯一标识一个连接(通讯过程中 socket一定是成对出现的)
![image](https://github.com/Amaz1ngJR/Technology/assets/83129567/35bb452b-c34b-4b96-af72-4a5fc6048b8b)
上图得 一个socket等于一个文件描述符+两个缓冲区即一个文件描述符指向一个套接字 该套接字内部由内核借助两个缓冲区实现

# 高并发服务器
