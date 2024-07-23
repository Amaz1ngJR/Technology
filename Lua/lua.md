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
