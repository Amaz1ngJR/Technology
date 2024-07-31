[在线编译](https://www.jyshare.com/compile/66/)

mac下直接 brew install lua 运行：lua demo.lua
# 数据类型
|数据类型|描述|
|----|-----|
|nil	|这个最简单，只有值nil属于该类，表示一个无效值（在条件表达式中相当于false,nil 作比较时应该加上双引号）|
|boolean	|包含两个值：false和true, false 和 nil 看作是 false，其他的都为 true，数字 0 也是 true|
|number|	表示双精度类型的实浮点数|
|string	|字符串由一对双引号或单引号来表示,可以用[ [ 字符串内容 ] ] |
|function|	由 C 或 Lua 编写的函数|
|userdata	|表示任意存储在变量中的C数据结构|
|thread	|表示执行的独立线路，用于执行协同程序|
|table	|Lua 中的表（table）其实是一个"关联数组"（associative arrays），数组的索引可以是数字、字符串或表类型。在 Lua 里，table 的创建是通过"构造表达式"来完成，最简单构造表达式是{}，用来创建一个空表。|

# 变量
Lua 变量有三种类型：全局变量、局部变量、表中的域。

Lua 中的变量全是全局变量，哪怕是语句块或是函数里，除非用 local 显式声明为局部变量。

局部变量的作用域为从声明位置开始到所在语句块结束
```lua
a = 1   --默认全局变量
local b = 2  -- 局部变量
c, d = 3, 4   --多重赋值
```

# string
```lua
s = [[hello
/world,aa
bbb]]
s1 = "111"
s2 = '222'
s3 = s1..s2   --字符串连接符号不是+而是..
print(s)
print(s3)
print(#s3)  --返回字符串的长度
```
```lua
s = string.char(0x30, 0x31, 0x32, 0x33)
print(s)
n = string.byte(s, 2)
m = 0x31
print(n, m)
```
## 类型转换
```lua
a = tostring(10)
b = tonumber("10")
n = tonumber('abc') --转换失败的返回nil
print(type(a))
print(type(b))
print(n)
```

# function
语法：
```lua
f = function(...)
        --body
end

function f(...)
        --body
end
```

```lua
function out(a, b, c)
        print(a, b, c)
end
out(1, 2)

function f(a, b, c)
        return a, b
end
print(f(1,2))
```
## 可变参数
```lua
function average(...)
    result = 0
    local arg = {...}
    for i,v in ipairs(arg) do
        result = result + v
    end
    print("总共传入 " .. #arg .. " 个数")
    print("总共传入 " .. select("#",...) .. " 个数") --通过 select("#",...) 来获取可变参数的数量
    return result/select("#",...)
end

print("平均值为",average(10,5,3,4,5,6))
```
select('#', …) 返回可变参数的长度;
select(n, …) 用于返回从起点 n 开始到结束位置的所有参数列表。
```lua
do  
    function foo(...)  
        for i = 1, select('#', ...) do  -->获取参数总数
            local arg = select(i, ...); -->读取参数，arg 对应的是右边变量列表的第一个参数
            print("arg", arg);  
        end  
    end  
 
    foo(1, 2, 3, 4);  
end
```
## 匿名函数
```lua
function testFun(tab,fun)
        for k ,v in pairs(tab) do
                print(fun(k,v));
        end
end

tab={key1="val1",key2="val2"};
testFun(tab,
function(key,val)--匿名函数
        return key.."="..val;
end
);
```
# table
## 数字下标的表类似数组
```lua
--下标从1开始，里面可以同时存数字、字符串、数组、函数
a = {1, "abc", {}, function() end}
a[6] = 123
print(a[2], a[6], a[5])
print(#a)
table.insert(a, "666") --在数组末尾插入元素
print(a[7],#a)
table.insert(a, 2, '888') --在下标为2的地方插入元素，其后元素后移一个下标
print(a[2], a[3], #a)
res = table.remove(a,2)  --下标为2的地方删除元素，并返回该元素，其后元素前移一个下标
print(res, a[2], #a)
```
## 字符串下标的表
```lua
a = {
        a = 1,
        b = "1234",
        c = function()
        end,
        d = 1233,
        [",;"] = 123 
}
print(a["a"], a.b, a[",;"])
a["abc"] = "abcd"
print(a["abc"], a.def)
```
## 全局表_G
lua中所有的全局变量都存放在全局表_G中 多文件调用可以使用
```lua
a = 1
b = 2
print(_G["a"], _G.b)
print(_G.table.insert)
```
# 条件与分支
不等于是 ~= ,与或非对应and,or,not,返回结果不一定是ture或false,可以返回条件中的值，
```lua
print(0 > 10 and "yes" or "no")

if 0 then
        print("0 is true")
end

if 1 > 10 then
        print("1 > 10")
elseif 1 < 10 then
        print("1 < 10")
else
        print("no")
end
```
for循环
```lua
for  i = 1, 10 do
        print(i) --i仅在for循环中有意义
end
for  i = 1, 10, 2 do  --添加步长
        if i == 5 then break end
        i = 1 --这里修改i实际上说又创建了一个局部变量i，并不会修改循环中的i（循环中的i不可修改）
        print(i) --i仅在for循环中有意义
end
```
while/repeat循环
```lua
local n = 10
while n > 1 do
        if n == 5 then break end
        print(n)
        n = n - 1
end
```
# require多文件调用
require运行指定文件，只运行一次，文件名不带拓展名，目录层用.分开,从package.path中查找
```lua
--test.lua文件下：
print("hello")
return "done"
--lua.lua主文件下:
local res = require("test") --调用test.lua文件 获取返回值到res中
print(res)
```
# 元表（面向对象）
```lua
t = {a = 1}
mt = {
    __add = function(t, v)
        return t.a + v
    end,
}
setmetatable(t, mt)
--写成一行 
t = setmetatable({a = 1}, {              
    __add = function(t, v)
        return t.a + v
    end,
}) -- 写成一行 
print(t + 1)
```
## 元方法

|元方法|描述
|----|----------|
|__add	|对应的运算符 '+'.|
|__sub	|对应的运算符 '-'.|
|__mul	|对应的运算符 '*'.|
|__div	|对应的运算符 '/'.|
|__mod	|对应的运算符 '%'.|
|__pow  |次方|
|__unm	|取反|
|__idiv |向下取整|
|__concat|连接 '..'.|
|__eq	|对应的运算符 '=='.|
|__lt	|对应的运算符 '<'.|
|__le	|对应的运算符 '<='.|
|__band|按位与 '&' |
|__bor|按位或 '\|' |
|__bxor|按位异或'~'|
|__bnot|按位非'!'|
|__shl|左移|
|__shr|右移|
|_len|取长度'#'|

**__index**

索引table [ key ] 当table不是表或表table中不存在key关键字时触发，去元表(里面是表)里面找，或者返回元表(里面是函数)里的值
```lua
t = setmetatable({}, { 
    __index = function(a)
        return 123
    end
})
t2 = setmetatable({}, { 
    __index = {
        abc = 123,
        def = 456,
    }
})
print(t[1])
print(t2[1])
print(t2['abc'])
print(t2['def'])
```
Lua 查找一个表元素时的规则，其实就是如下 3 个步骤:

1.在表中查找，如果找到，返回该元素，找不到则继续

2.判断该表是否有元表，如果没有元表，返回 nil，有元表则继续

3.判断元表有没有 __index 方法，如果 __index 方法为 nil，则返回 nil；如果 __index 方法是一个表，则重复 1、2、3；如果 __index 方法是一个函数，则返回该函数的返回值

**__newindex**

table[key] = value语句，赋值时当table不是表或表table中不存在key触发，先去检查table中有没有__newindex元方法，

如果有，执行元方法。如果没有__newindex就直接添加属性key为value了
```lua
t = setmetatable({}, { 
    __newindex = function(t, k, v)
        rawset(t, k, v)
    end
})

t['abc'] = 111
print(t['abc'])
```
__newindex为方法
```lua
t = {}
b = {} --元表
b['__newindex'] = function()
    print('调用了__newindex元方法')
end

setmetatable(t, b) --注释和解注释这行代码

t.age = 20

print(t.age)
```
__newindex为表
```lua
t = {}
b = {} --元表
c = {} --表
b['__newindex'] = c
setmetatable(t, b) 
t.age = 20

print(t.age)
print(c.age)
```
**__call**

将一个表作为函数调用时，Lua会查找该表是否定义了`__call`元方法。如果找到了`__call`元方法，Lua将调用该元方法，并将表自身作为第一个参数传递给元方法
```lua
local myTable = {}

-- 定义__call元方法
function myTable:__call(...)
  print("表被调用了！")
  print("传入的参数是:", ...)
end

-- 将表作为函数调用
myTable("参数1", "参数2")
```
## 面向对象

语法糖
```lua
t = {
    a = 0,
    add = function(tab, sum)
        tab.a = tab.a + sum
    end
}
t:add(10) -- t.add(t, 10)
print(t['a'])
```

### 继承和多态的实现
```lua
-- 父类 
base = {
    base_print = function(self, arg_str)
        print(self.name..arg_str)
    end
}

function base:say_name()
    --冒号 : 调用方法时，Lua 会自动将调用表达式左侧的对象作为第一个参数传递给方法
    -- 方法的第一个参数通常被称为 self，代表调用该方法的对象 self 当参数为空的时候是一个隐式参数
    print(self.name)
end

function base.say_age(object, arg_str)
    --使用点 . 调用方法时，方法被视为一个普通的 Lua 函数，需要显式地传递所有参数，包括对象本身
    print(arg_str..object.age)
end

-- 子类
son = {}

-- son.__index = base-- 设置元表索引 可以理解成son继承了base
-- son['__index'] = base

function son.new(Name,Age)
    local obj = {}
    -- setmetatable(obj,son)-- 设置元表son可以拿到son到继承base里的属性
    setmetatable(obj,{__index = base})
    obj.name = Name     --表中添加属性name
    obj.age = Age       --表中添加属性age
    return obj
end

local p = son.new('aaa',10)
local p2 = son.new('bbb',20)
p:say_name() --使用:调用方法默认self为p
p.say_age(p,'年龄是') --使用.调用方法
p:say_age('年龄是')  --使用：调用方法可以省略self
p:base_print('展示多态')
p2:base_print('展示多态')
```

