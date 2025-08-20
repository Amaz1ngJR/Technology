# 虚拟环境
## 安装虚拟环境
### [安装Miniconda](https://www.anaconda.com/docs/getting-started/miniconda/install#macos-2)
```
mkdir -p ~/miniconda3
curl https://repo.anaconda.com/miniconda/Miniconda3-latest-MacOSX-arm64.sh -o ~/miniconda3/miniconda.sh
bash ~/miniconda3/miniconda.sh -b -u -p ~/miniconda3
rm ~/miniconda3/miniconda.sh
```
重启终端后执行以下命令 设置环境变量
```
source ~/miniconda3/bin/activate
```
### [安装miniforge可以免费商用](https://github.com/conda-forge/miniforge?tab=readme-ov-file)
选择合适的版本进行下载后
```
chmod +x Miniforge3*.sh
```
运行安装程序
```
./Miniforge3*.sh
```
设置环境变量
```
export PATH="/path/to/miniforge/bin:$PATH"
```

安装完上述conda后 第一次使用 需要conda init <shell> --将<shell>替换为你正在使用的shell，例如bash或zsh 然后关闭终端，再开一个新的
```
conda init --all
```
打开终端后会自动进入base
```
conda config --show auto_activate_base --看自动进入base的状态
conda config --set auto_activate_base false --关闭
conda config --set auto_activate_base true  --打开
```
## 虚拟环境相关
```
创建虚拟环境      conda create -n <环境名name> python=3.9
进/出虚拟环境     conda activate <环境名name> / conda deactivate
查看所有虚拟环境  conda env list 所有包 conda list 
删除虚拟环境      conda remove -n  <环境名name> --all
复制虚拟环境      conda create --name new_name --clone old_name

Mac下
创建虚拟环境          /usr/bin/python3 -m venv <环境名name> 
进/出虚拟环境         source <环境名name> /bin/activate / deactivate

CUDA版本：
使用nvcc --V查看的是cuda版本 使用nvidia-smi显示的CUDA是支持的最高版本，并不是当前的版本
```

## 依赖相关

记录依赖
```
pip freeze > requirements.txt
conda env export > environment.yml
```
快速搭建环境
```
pip install -r requirements.txt
conda env create -f environment.yml
```

## 镜像
```
pip install --upgrade pip
```
pip镜像
```
-i https://pypi.tuna.tsinghua.edu.cn/simple
-i https://pypi.mirrors.ustc.edu.cn/simple
-i https://mirrors.aliyun.com/pypi/simple/
```
# Python

## 字符串 String
### 表示方式
```python
# 单引号、双引号、三引号
single = 'Hello'
double = "World"
triple = """This is a
multiline string"""

# 打印字符串
print(single)
print(double)
# 打印多行字符串    
print(triple)

# f-string (推荐)
name = "Alice"
age = 30
print(f"Hello, {name}. You are {age}.")

# format方法
print("Hello, {}. You are {}.".format(name, age))

# % 格式化 (旧式)
print("Hello, %s. You are %d." % (name, age))
```
### 
## 列表 list
可变集合
### 创建列表
```python
# 创建列表
numbers = [1, 2, 3, 4, 5]
mixed = [1, "hello", 3.14, True]

# 空列表
empty_list = []

# 列表推导式
squares = [x**2 for x in range(5)]  # [0, 1, 4, 9, 16]
```
### 增删改查
```python
numbers = [1, 2, 3, 4, 5]

# 访问元素
print(numbers[0])      # 1
print(numbers[-1])     # 5 (最后一个)

# 切片
print(numbers[1:4])    # [2, 3, 4]
print(numbers[:3])     # [1, 2, 3]
print(numbers[2:])     # [3, 4, 5]

# 修改
numbers[0] = 10

# 添加元素
numbers.append(6)
numbers.insert(1, 15)  # 在索引1处插入15

# 删除元素
numbers.remove(15)     # 删除值为15的元素
popped = numbers.pop() # 删除并返回最后一个元素
del numbers[0]         # 删除索引0的元素
```
### 遍历
```python
numbers = [1, 2, 3, 4, 5]
for x in numbers:
    print(f"Value: {x}")

for i in range(len(numbers)):
    print(f"Index: {i}, Value: {numbers[i]}")

for i, x in enumerate(numbers):
    print(f"Index: {i}, Value: {x}")

    # 如果想让索引起始值不是0，可以指定 start 参数
for i, x in enumerate(numbers, start=1):
    print(f"Index: {i}, Value: {x}")  # 索引从1开始

    # 遍历前3个元素
for x in numbers[:3]:
    print(f"Value: {x}")

# 遍历从索引2开始的元素
for x in numbers[2:]:
    print(f"Value: {x}")

# 遍历每隔一个元素
for x in numbers[::2]:
    print(f"Value: {x}")

# 反向遍历方法1: 使用切片
for x in numbers[::-1]:
    print(f"Value: {x}")

# 反向遍历方法2: 使用 reversed()
for x in reversed(numbers):
    print(f"Value: {x}")

# 反向遍历方法3: 使用 range() 反向索引
for i in range(len(numbers) - 1, -1, -1):
    print(f"Index: {i}, Value: {numbers[i]}")
```

## 元组 Tuple
不可变集合。
### 创建元组
```python
# 创建元组
point = (1, 2)
colors = ("red", "green", "blue")

# 空元组
empty_tuple = ()

# 单元素元组（注意逗号）
single = (42,)
```
## 字典 Dict
无序的键值对集合
### 创建字典
```python
# 创建字典
person = {"name": "Alice", "age": 30}
# 或使用 dict()
person = dict(name="Alice", age=30)

# 空字典
empty_dict = {}
```
### 增删改查
```python
# 访问值
print(person["name"])
# 使用 get() 方法（推荐，避免 KeyError）
print(person.get("name"))
print(person.get("height", "Unknown"))  # 提供默认值

# 添加/修改
person["city"] = "Beijing"
person["age"] = 31

# 删除
del person["city"]
# 或使用 pop()
city = person.pop("city", None)  # 提供默认值避免 KeyError
```
### 遍历
```python
# 遍历
for key, value in person.items():
    print(f"Key: {key}, Value: {value}")
# 只遍历键
for key in person:
    print(f"Key: {key}")
# 只遍历值
for value in person.values():
    print(f"Value: {value}")
```
## 集合 Set
无序的不重复元素
### 创建集合
```python
# 创建集合
fruits = {"apple", "banana", "orange"}
# 或使用 set()
numbers = set([1, 2, 3, 2, 1])  # {1, 2, 3}

# 空集合（不能用 {}，那是字典）
empty_set = set()
```
### 增删查
```python
# 添加单个元素
fruits.add("grape")

# 添加多个元素（从另一个可迭代对象）
fruits.update(["kiwi", "mango"])  # {'apple', 'banana', 'orange', 'grape', 'kiwi', 'mango'}
# 也可以传入字符串、元组、其他集合等
fruits.update("xyz")          # 添加 'x', 'y', 'z' 三个字符
more_fruits = {"pear", "peach"}
fruits.update(more_fruits)

# 删除元素
fruits.remove("banana")  # 如果元素不存在会报错
fruits.discard("banana") # 如果元素不存在不会报错

# 删除并返回一个任意元素（集合为空会抛出 KeyError）
popped_fruit = fruits.pop()

# 清空整个集合
fruits.clear()

# 删除集合本身（从命名空间中移除）
del fruits

# 检查元素是否存在（最常用）
if "apple" in fruits:
    print("Apple is in the set")

# 检查元素是否不存在
if "banana" not in fruits:
    print("Banana is not in the set")

# 获取集合大小
count = len(fruits)
print(f"集合中有 {count} 个元素")
```
### 集合运算
```python
a = {1, 2, 3, 4}
b = {3, 4, 5, 6}

# 并集：a 或 b 中的元素
union_set = a | b           # {1, 2, 3, 4, 5, 6}
union_set = a.union(b)      # 同上

# 交集：同时在 a 和 b 中的元素
intersection_set = a & b    # {3, 4}
intersection_set = a.intersection(b)  # 同上

# 差集：在 a 中但不在 b 中的元素
difference_set = a - b      # {1, 2}
difference_set = a.difference(b)  # 同上

# 对称差集：在 a 或 b 中，但不同时在两者中的元素
symmetric_diff_set = a ^ b  # {1, 2, 5, 6}
symmetric_diff_set = a.symmetric_difference(b)  # 同上

# 子集检查
c = {1, 2}
d = {1, 2, 3}
print(c.issubset(d))        # True, c 是 d 的子集
print(d.issuperset(c))      # True, d 是 c 的超集

# 不相交检查
e = {1, 2}
f = {3, 4}
print(e.isdisjoint(f))      # True, e 和 f 没有共同元素
```

## 函数
### 可变参数
```python
def sum_all(*args):
    return sum(args)

print(sum_all(1, 2, 3, 4))  # 10

def greet_all(**kwargs):
    for key, value in kwargs.items():
        print(f"{key}: {value}")

greet_all(name="Alice", age=30)
```
### 匿名函数 lambda
```python
square = lambda x: x ** 2
print(square(5))  # 25
```
### 高阶函数
```python
numbers = [1, 2, 3, 4, 5]
squared = list(map(lambda x: x**2, numbers))
print(squared) # [1, 4, 9, 16, 25]

# map: 对序列每个元素应用函数
doubled = list(map(lambda x: x*2, numbers))
print(doubled) # [2, 4, 6, 8, 10]

# filter: 过滤序列中满足条件的元素
evens = list(filter(lambda x: x % 2 == 0, numbers))
print(evens) # [2, 4]

# reduce: 对序列进行累积计算
from functools import reduce
total = reduce(lambda x, y: x + y, numbers)
print(total) # 15
```
## 面向对象编程 (OOP)
```python
# 属性装饰器
class Circle:
    def __init__(self, radius):
        self._radius = radius  # 私有变量约定
    
    @property # 保护属性
    def radius(self):
        return self._radius
    
    @radius.setter # 设置属性
    def radius(self, value):
        if value < 0:
            raise ValueError("半径不能为负数")
        self._radius = value
    
    @property
    def area(self):
        return 3.14159 * self._radius ** 2

c = Circle(5)
print(c.radius)  # 5
print(c.area)    # 计算属性
c.radius = 10    # 使用setter
# c.radius = -1  # 会抛出异常


class Animal:
    """动物基类"""
    
    # 类变量
    species_count = 0
    
    def __init__(self, name, age):
        """构造函数"""
        self.name = name  # 实例变量
        self.age = age
        Animal.species_count += 1
    
    def info(self):
        return f"Name: {self.name}, Age: {self.age}"
    
    def make_sound(self):   #虚函数
        raise NotImplementedError("子类必须实现此方法")

        # 创建实例
dog = Animal("Buddy", 3)
print(dog.info())

# 继承
class Dog(Animal):
    def __init__(self, name, age, breed):
        super().__init__(name, age)  # 调用父类构造函数
        self.breed = breed
    
    def make_sound(self): # 实现虚函数
        return "Woof! Woof!"
    
    def info(self):
        # 重写父类方法
        base_info = super().info()
        return f"{base_info}, Breed: {self.breed}"

class Cat(Animal): # 另一个子类
    def make_sound(self): # 实现虚函数
        return "Meow~"

# 多态
def animal_sound(animal):
    print(animal.make_sound())

dog = Dog("Buddy", 3, "Golden Retriever")
cat = Cat("Luna", 2)

animal_sound(dog)  # Woof! Woof!
animal_sound(cat)  # Meow~
```

## 文件操作
### 读取文件
```python
# 读取整个文件
with open('file.txt', 'r', encoding='utf-8') as f:
    content = f.read()
    print(content)

# 逐行读取
with open('file.txt', 'r', encoding='utf-8') as f:
    for line in f:
        print(line.strip())  # strip() 去除换行符

# 读取所有行到列表
with open('file.txt', 'r', encoding='utf-8') as f:
    lines = f.readlines()
```
### 写入文件
```python
# 写入文件（覆盖）
with open('output.txt', 'w', encoding='utf-8') as f:
    f.write("Hello, World!\n")
    f.write("第二行\n")

# 追加到文件
with open('output.txt', 'a', encoding='utf-8') as f:
    f.write("追加的内容\n")
```
### JSON处理
```python
import json

# Python对象转JSON字符串
data = {"name": "Alice", "age": 30}
json_str = json.dumps(data, ensure_ascii=False, indent=2)
print(json_str)

# JSON字符串转Python对象
json_str = '{"name": "Alice", "age": 30}'
data = json.loads(json_str)
print(data["name"])

# 读取JSON文件
with open('data.json', 'r', encoding='utf-8') as f:
    data = json.load(f)

# 写入JSON文件
with open('data.json', 'w', encoding='utf-8') as f:
    json.dump(data, f, ensure_ascii=False, indent=2)
```

## 并发编程

### 多线程
```python
import threading
import time

def worker(name):
    print(f"Worker {name} started")
    time.sleep(2)
    print(f"Worker {name} finished")

# 创建并启动线程
threads = []
for i in range(3):
    t = threading.Thread(target=worker, args=(i,))
    threads.append(t)
    t.start()
print("All workers started")
# 等待所有线程完成
for t in threads:
    t.join()

print("All workers done")
```
### 多进程
```python
import multiprocessing
import time

def worker(name):
    print(f"Worker {name} started")
    time.sleep(2)
    print(f"Worker {name} finished")

if __name__ == '__main__':
    processes = []
    for i in range(3):
        p = multiprocessing.Process(target=worker, args=(i,))
        processes.append(p)
        p.start()
    print("All workers started")
    for p in processes:
        p.join()
    
    print("All workers done")
```

### 异步编程 (asyncio)
```python
import asyncio

async def say_hello(name, delay):
    print(f"Hello {name}!")
    await asyncio.sleep(delay)
    print(f"Bye {name}!")

async def main():
    # 并发执行
    await asyncio.gather(
        say_hello("Alice", 1),
        say_hello("Bob", 2)
    )

# 运行异步程序
asyncio.run(main())

# ---------上下文管理器-----------
# 使用 with 语句
with open('file.txt', 'r') as f:
    content = f.read()

# 自定义上下文管理器
class MyContextManager:
    def __enter__(self):
        print("进入上下文")
        return self
    
    def __exit__(self, exc_type, exc_val, exc_tb):
        print("退出上下文")
        # 返回True会抑制异常
        return False

with MyContextManager() as cm:
    print("在上下文中")

# 使用 contextlib
from contextlib import contextmanager

@contextmanager
def my_context():
    print("进入")
    try:
        yield "资源"
    finally:
        print("清理")

with my_context() as resource:
    print(f"使用 {resource}")
```