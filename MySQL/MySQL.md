**MySQL**
数据库(DB):存储数据的仓库 数据是有组织进行存储

数据库管理系统(DBMS): 操纵和管理数据库的大型软件

SQL:操作关系型数据库的**编程语言** 定义了一套操作关系型数据库统一标准
# 配置介绍
Linux Ubuntu下安装MySQL8.0
```bash
Linux Ubuntu下安装MySQL8.0
安装：sudo apt install -y mysql-server
启动：/etc/init.d/mysql start
停止：/etc/init.d/mysql stop
查看状态：/etc/init.d/mysql status
```
登录
```bash
第一次登录直接:sudo mysql
创建用户：CREATE USER 'YJR'@'localhost' IDENTIFIED BY 'your_password_here';
设置密码：ALTER USER ‘root’@’localhost’ IDENTIFIED WITH mysql_native_password BY ‘your_password_here’;
退出：exit
登录MySQL: mysql -uYJR -p //mysql -h 主机名 -u 用户名 -p  (-h可省略 -p告诉服务器将用密码登录 如果用户名密码为空 可忽略)
```
# SQL
SQL语法不区分大小写 关键字最好大写
# 函数

# 约束

# 多表查询

# 事务

# 存储引擎 

# 索引
