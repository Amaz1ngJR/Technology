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
create table [if not exits] mytable(
    id int comment 'ID', # 字段1 字段1类型 [comment 字段1注释]
    name varchar(50) comment '姓名'
)comment '用户表';
```
查询数据表
```mysql
show tables; # 查询当前数据库所有的表
desc mytable; # 查询指定表名的表结构
show create table mytable; #查询指定表的建表语句
```
删除数据表
```mysql
drop table [if exists]  mytable; # 删除数据表
alter table  mytable drop id; # 删除表的字段
truncate table mytable; # 删除指定表并重新创建该表
```
修改数据表
```mysql
alter table mytable rename to my_table; # 修改表名
alter table mytable add ID int [comment 'id'][约束]; # 表中添加字段(如果表中有该字段 需要先删除)
alter table mytable modify ID bigint; # 修改表中数据类型为bigint
alter table mytable change id indx int [comment][约束]; #修改字段名和字段类型
```
## DML
表中插入数据
```mysql
insert into mytable (id,name) values (1,'Amaz1ng'); # 给指定字段添加数据
insert into mytable values (值1, 值2, ...); # 给全部字段添加数据
insert into  mytable (id, name2) values (3, 'Amaz1ng3'),(4, 'amaz1'),(5, 'aaa'); # 批量添加数据
insert into  mytable (值1，值2, ...),(值1，值2, ...),(值1，值2, ...);
```
表中删除数据
```mysql
delete from mytable [where 条件]; #删除表中所有数据内容 不能删除某一个字段的值(可以使用update将其设为null)
truncate [table] mytable; # 删除表再重新构建这个表
```
表中修改数据
```mysql
update mytable set name2 = 'amaz1ng4' [where id = 4]; #  没有where条件 则会修改整张表的所有数据
```
## DQL
![image](https://github.com/Amaz1ngJR/Technology/assets/83129567/2c88c85b-9866-406a-ac8f-93a9ac672000)

### 基础查询
查看表中多个字段数据
```mysql
select *from mytable; # 返回mytable表中的所有数据
select ID, name from mytable; # 返回mytable表中ID部分、name部分的数据
```
别名显示
```mysql
select name2 as '姓名',id '索引' from mytable; # as 可以省略 给表中字段设置别名
select * from mytable as t; # 给表设置别名
```
显示过滤某个字段重复的数据
```mysql
select distinct id from mytable; # 过滤id中重复记录
```
显示运算查询
```mysql
select name2,prince + 10 new_price from mytable; # 显示new_prince价格+10后的name2 
```
### where条件查询
|操作符|描述|	
|----|-----|
|=	|等号|
|<>, !=|不等于|
|>	|大于号|
|<	|小于号|
|>=	|大于等于号|
|<=	|小于等于号|
|and, &&| 并|
|or, \|\| | 或 |
|not, ! |非|
|is null | 为null|
|like 占位符|模糊匹配(_匹配单个字符,%匹配任意个字符)|
|in(...)|in列表中的值，多选1|
|between..and..|在闭区间之内|
```mysql
-- 查询有身份证号的员工
select * from mytable where id is not null;
-- 查询年龄等于18或20或40 的员工
select * from mytable where age = 18 or age = 20 or age = 40;
-- 查询名字为两个字的员工
select * from mytable where name like '__';
-- 查询身份证号最后一位是X的员工
select * from mytable where id like '%x';
```
### 聚合函数
将一列数据作为一个整体,进行**纵向**计算(null值不参与计算)

语法：select 聚合函数(字段列表) from 表名;
|函数|功能|
|----|----|
|count|统计数量|
|max|最大值|
|min|最小值|
|avg|平均值|
|sum|求和|
```mysql
-- 统计表中成员数量
select count(*) from mytable;
-- 统计杭州地区员工年龄之和
select sum(age) from mytable where workaddress = '杭州';
```
### 分组查询
```
语法： select 字段列表 from 表名 [where 条件] group by 分组字段名 [having 分组后过滤条件];
where是分组之前进行过滤的 不满足where条件的 不参与分组 having是分组之后对结果进行过滤
where不能对聚合函数进行判断 having可以
执行顺序：where->聚合函数->having 分组之后查询的字段一般为聚合函数和分组字段 查询其他字段无意义
```
```mysql
-- 根据性别分组 统计男女员工数量
select gender, count(*) from mytable group by gender;
-- 根据性别分组 统计男女员工平均年龄
select gender, avg(age) from mytable group by gender;
-- 根据工作地点分组 查询年龄小于45岁的员工 获取员工数量大于3的工作地址
select address,cout(*)from mytable where age < 45 group by address having count(*) > 3;
select address,cout(*) add_cnt from mytable where age < 45 group by address having add_cnt > 3;
```
### 排序查询
语法： select 字段列表 from 表名 order by 字段1 排序方式1(ASC默认的升序), 字段2 排序方式2(DESC降序),...; 多字段排序 先按第一个排序方式排序
```mysql
select * from mytable order by id desc;
```
### 分页查询
```
语法：select 字段列表 from 表名 limit 起始索引, 查询记录数量;
起始索引从0开始 0可以省略 起始索引 = (查询页码(1开始) - 1) * 每页显示记录个数
```
```mysql
-- 1 查询第1页数据 每页展示2条记录
select * from mytable limit 2;
-- 1 查询第2页数据 每页展示2条记录
select * from mytable limit 2,2;
```
## DCL
### 用户管理
```mysql
-- 查询用户
use mysql;
select  * from user;
-- 创建用户
create user 'temp'@'localhost' identified by '123456'; # 只能在当前主机localhost访问
create user 'temp'@'%' identified by '123456'; # 可以在任意主机访问
-- 修改用户密码
alter user 'temp'@'localhost' identified with mysql_native_password by '123';
-- 删除用户
drop user 'temp'@'localhost';
```
### 权限控制
|权限|描述|
|----|----|
|ALL,ALL PRIVILEGES|所有权限|
|SELECT|查询数据|
|INSERT|插入数据|
|UPDATE|修改数据|
|DELETE|删除数据|
|ALTER|修改表|
|DROP|删除数据库/表/视图|
|CREATE|创建数据库/表|
```mysql
-- 查询权限
show grants for 'root'@'localhost';
-- 授予权限
grant 权限列表(,隔开) on 数据库名.表名(可以用通配符*) to 'root'@'localhost';
-- 撤销权限
revoke 权限列表 on 数据库名.表名 from 'root'@'localhost';
```

# 函数
select 函数(参数)
## 字符串函数

|函数	|描述	|
|------|---------|
|ASCII(s)	|返回字符串 s 的第一个字符的 ASCII 码|
|CHAR_LENGTH(s)	/ CHARACTER_LENGTH(s)|返回字符串 s 的字符数|
|CONCAT(s1,s2...sn)|字符串 s1,s2 等多个字符串合并为一个字符串|
|CONCAT_WS(x, s1,s2...sn)|	同 CONCAT(s1,s2,...) 函数，但是每个字符串之间要加上 x，x 可以是分隔符|	
|FIELD(s,s1,s2...)|	返回第一个字符串 s 在字符串列表(s1,s2...)中的位置|
|FIND_IN_SET(s1,s2)|返回在字符串s2中与s1匹配的字符串的位置|	
|FORMAT(x,n)|函数可以将数字 x 进行格式化 "#,###.##", 将 x 保留到小数点后 n 位 最后一位四舍五入|
|INSERT(s1,x,len,s2)|字符串 s2 替换 s1 的 x 位置开始长度为 len 的字符串|	
|LOCATE(s1,s)|从字符串 s 中获取 s1 的开始位置	|
|LCASE(s) / LOWER(s)|	将字符串转换为小写|
|UCASE(s) / UPPER(s)|	将字符串转换为大写|	
|LEFT(s,n)	|返回字符串 s 的前 n 个字符|
|RIGHT(s,n)	|返回字符串 s 的后 n 个字符|
|LPAD(s1,len,s2)|	在字符串 s1 的开始处填充字符串 s2，使字符串长度达到 len	|
|RPAD(s1,len,s2)|	在字符串 s1 的结尾处添加字符串 s2，使字符串的长度达到 len	|
|LTRIM(s)	|去掉字符串 s 开始处的空格|
|RTRIM(s)	|去掉字符串 s 结尾处的空格|
|TRIM(s)	|去掉字符串 s 开始和结尾处的空格|
|SPACE(n)	|返回 n 个空格	|
|MID(s,n,len) / SUBSTRING(s,n,len) / SUBSTR(s, start, length)|从字符串 s 的 n 位置截取长度为 len 的子字符串|
|POSITION(s1 IN s)|从字符串 s 中获取 s1 的开始位置	|
|REPEAT(s,n)|将字符串 s 重复 n 次|
|REPLACE(s,s1,s2)|将字符串 s2 替代字符串 s 中的子串 s1|
|REVERSE(s)	|将字符串s的顺序反过来	|
|STRCMP(s1,s2)|	比较字符串 s1 和 s2，如果 s1 与 s2 相等返回 0 ，如果 s1>s2 返回 1，如果 s1<s2 返回 -1	|

## 数值函数
|函数|功能描述|
|----|-------|
|mod(x,y)|返回x mod y |
|rand()|返回0-1内随机数|
|round(x,y)|求参数x保留y位小数的四舍五入|
|greatest(a,b,...)|求列表中的最大值|
|least(a,b,...)|求列表中的最小值|
## 日期函数

## 流程函数

## 聚合函数

## 窗口/开窗函数
### 序号函数

### 分布函数

### 前后函数

### 头尾函数

### 开窗聚合函数

### 其他函数NTH_VALUE、NTILE

# 约束

# 多表查询

# 事务

