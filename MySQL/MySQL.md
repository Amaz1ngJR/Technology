**MySQL**

数据库(DB):存储数据的仓库 数据是有组织进行存储

数据库管理系统(DBMS): 操纵和管理数据库的大型软件

SQL:操作关系型数据库的**编程语言** 定义了一套操作关系型数据库统一标准
# 配置介绍
Linux Ubuntu下安装MySQL8.0
```bash
sudo apt install -y mysql-server  //安装
/etc/init.d/mysql start           //启动
/etc/init.d/mysql stop            //停止
/etc/init.d/mysql status          //查看状态
```
登录
```bash
第一次登录直接:sudo mysql
创建用户：CREATE USER 'YJR'@'localhost' IDENTIFIED BY 'your_password_here';
设置密码：ALTER USER ‘root’@’localhost’ IDENTIFIED WITH mysql_native_password BY ‘your_password_here’;
退出：exit
登录MySQL: mysql -uYJR -p //mysql -h 主机名 -u 用户名 -p  (-h可省略 -p告诉服务器将用密码登录 如果用户名密码为空 可忽略)
```
MySQL图形化界面

使用DataGrip 激活码vrg123.com 密码8866

# SQL
SQL语法不区分大小写 关键字最好大写
```
DDL:数据定义语言 用来定义数据库对象(数据库、表、字段)
DML:数据操作语言 用来对数据表中的数据进行增删改
DQL:数据查询语言 用来查询数据库中表的记录
DCL:数据控制语言 用来创建数据库用户、控制数据库的访问权限
```
|类型	|大小(Bytes)	|范围（有符号）|	范围（无符号）	|用途|
|-----|-----|-------------|---------------|----|
|TINYINT	|1 	|(-128，127)	|(0，255)	|小整数值|
|SMALLINT|	2 |	(-32 768，32 767)|(0，65 535)	|大整数值|
|MEDIUMINT|	3 |	(-8 388 608，8 388 607)|	(0，16 777 215)	|大整数值|
|INT或INTEGER|4 |	(-2 147 483 648，2 147 483 647)|	(0，4 294 967 295)	|大整数值|
|BIGINT	|8 |	(-9,223,372,036,854,775,808，9 223 372 036 854 775 807)	|(0，18 446 744 073 709 551 615)	|极大整数值|
|FLOAT	|4 |(-3.402 823 466 E+38，-1.175 494 351 E-38)，0，(1.175 494 351 E-38，3.402 823 466 351 E+38)|0，(1.175 494 351 E-38，3.402 823 466 E+38)|	单精度浮点数值|
|DOUBLE	|8|(-1.797 693 134 862 315 7 E+308，-2.225 073 858 507 201 4 E-308)，0，(2.225 073 858 507 201 4 E-308，1.797 693 134 862 315 7 E+308) |0，(2.225 073 858 507 201 4 E-308，1.797 693 134 862 315 7 E+308)|双精度浮点数值|
|DECIMAL| |	依赖于M和D的值	|依赖于M和D的值|	小数值|

|类型	|大小(Bytes)|	范围	|格式|	用途|
|----|-----------|------|-----|-----|
|DATE	|3	|1000-01-01/9999-12-31|	YYYY-MM-DD|	日期值|
|TIME	|3	|'-838:59:59'/'838:59:59'	|HH:MM:SS|	时间值或持续时间|
|YEAR|	1	|1901-2155|	YYYY|	年份值|
|DATETIME|	8	|'1000-01-01 00:00:00' 到 '9999-12-31 23:59:59'|	YYYY-MM-DD hh:mm:ss	|混合日期和时间值|
|TIMESTAMP|	4	|'1970-01-01 00:00:01' UTC 到 '2038-01-19 03:14:07' UTC 结束时间是第 2147483647 秒，北京时间 2038-1-19 11:14:07，格林尼治时间 2038年1月19日 凌晨 03:14:07|YYYY-MM-DD hh:mm:ss	|混合日期和时间值，时间戳|

|类型	|大小(Bytes)|用途|
|-----|-----------|-----|
|CHAR|	0-255|定长字符串|
|VARCHAR|	0-65535 |	变长字符串|
|TINYBLOB	|0-255 |不超过 255 个字符的二进制字符串|
|TINYTEXT|	0-255 |	短文本字符串|
|BLOB	|0-65 535 |二进制形式的长文本数据|
|TEXT|	0-65 535 |	长文本数据|
|MEDIUMBLOB|	0-16 777 215 |	二进制形式的中等长度文本数据|
|MEDIUMTEXT|	0-16 777 215|中等长度文本数据|
|LONGBLOB	|0-4 294 967 295 |二进制形式的极大文本数据|
|LONGTEXT	|0-4 294 967 295 |极大文本数据|
## DDL
### 数据库操作
创建数据库
```mysql
create database [if not exists] mybase [default charset字符集] [collate 排序规则];
```
查询数据库
```mysql
show databases; # 查看所有数据库
select database(); # 查询当前数据库
```
删除数据库
```mysql
drop database [if exists] mybase;
```
使用数据库
```mysql
use mybase;
```
### 数据表操作
创建数据表
```mysql
create table mytable(
id int comment '编号' # 字段1 字段1类型 [comment 字段1注释]
#...
)[comment 表注释];
```
##

##
# 函数

# 约束

# 多表查询

# 事务

# 存储引擎 

# 索引
