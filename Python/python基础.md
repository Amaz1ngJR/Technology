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
### 增删改查
```python
# ------------------------------增--------------------
# 原始使用字符串格式化 (% 操作符)
print("Hello %s" % "World")  # 输出: Hello World
# 使用 + 或者 += 连接字符串
original = "Hello"
original += " World"
print("Hello" + ' World ' + original)  # 输出: Hello World Hello World

# 使用 str.join() 方法增加
parts = ["Hello", "World"]
result = " ".join(parts)
print(result)  # 输出: Hello World

# 或者连接多个字符串
result = "".join(["Hello", " ", "World"])
print(result)  # 输出: Hello World

# 使用 f-string (Python 3.6+)
name = "World"
greeting = f"Hello {name}"
print(greeting)  # 输出: Hello World

# 使用 format() 方法
# 使用空花括号 - 按顺序
text1 = "{} {}".format("Hello", "World")
print(text1)  # 输出: Hello World

# 使用数字位置 - 明确指定
text2 = "{1} {0}".format("World", "Hello")
print(text2)  # 输出: Hello World

# 使用关键字参数
text = "{greeting} {name}".format(greeting="Hello", name="World")
print(text)  # 输出: Hello World

# 混合位置和关键字参数
text = "{0} {name}".format("Hello", name="World")
print(text)  # 输出: Hello World

# 甚至可以重复使用同一个参数
text3 = "{0} {0} {1}".format("Hello", "World")
print(text3)  # 输出: Hello Hello World

# ------------------------------删--------------------
text = "  hello world  \n"
# 去除两端空白字符（空格、制表符、换行符等）
stripped = text.strip()   # "hello world"
# 只去除左边
left_stripped = text.lstrip()  # "hello world  \n"
# 只去除右边
right_stripped = text.rstrip() # "  hello world"
# 去除指定字符
custom_strip = "xxhelloxx".strip("x")  # "hello"

# ------------------------------改--------------------
# 替换
text = "I like apples and apples."
# 替换所有匹配项
new_text = text.replace("apples", "oranges")  # "I like oranges and oranges."
# 只替换前 n 个匹配项
partial_replace = text.replace("apples", "oranges", 1)  # "I like oranges and apples."

# 分割与连接
text = "apple,banana,orange"
# 按分隔符分割成列表
fruits = text.split(",")  # ['apple', 'banana', 'orange']
# 按空白字符（空格、制表符、换行符）分割
words = "a b c".split()  # ['a', 'b', 'c']
# 从右边分割
right_split = "a.b.c".rsplit(".", 1)  # ['a.b', 'c'] (只分割最后一次)
# 用分隔符连接列表
joined = "-".join(fruits)  # "apple-banana-orange"

# ------------------------------查--------------------
text = "Hello, World!"
# 查找子串位置（找不到返回 -1）
index = text.find("World")  # 首个字符下标7
# index() 方法，找不到会抛出 ValueError
# index = text.index("World")  # 7
# 检查是否以特定字符串开头/结尾
starts_with_hello = text.startswith("Hello")  # True
ends_with_exclamation = text.endswith("!")    # True
# 检查字符串内容类型
is_alpha = "abc".isalpha()      # True 纯字母
is_digit = "123".isdigit()      # True 纯数字
is_alnum = "abc123".isalnum()   # True 字母数字
is_lower = "hello".islower()    # True 纯小写
is_upper = "HELLO123!".isupper()    # True 纯大写 数字标点符号不影响判断
print("123!@#".isupper())     # False - 没有字母字符时返回False
text = "HELLO WORLD"
if text.isupper():
    text = text.lower()  # 转换为小写
    print(text)  # 输出: hello world
```
### 遍历
```python
s = "Hello"

# 直接遍历每个字符
for char in s:
    print(char, end=" ")
# 输出: H e l l o

# 使用索引正向遍历
for i in range(len(s)):
    print(f"索引 {i}: {s[i]}", end=" | ")
# 输出: 索引 0: H | 索引 1: e | 索引 2: l | 索引 3: l | 索引 4: o |

# 同时获取索引和字符
for index, char in enumerate(s):
    print(f"位置 {index}: '{char}'")

# 使用负索引反向遍历
for i in range(-1, -len(s)-1, -1):
    print(f"负索引 {i}: {s[i]}", end=" | ")
# 输出: 负索引 -1: o | 负索引 -2: l | 负索引 -3: l | 负索引 -4: e | 负索引 -5: H |

# 使用 reversed() 反向遍历字符
for char in reversed(s):
    print(char, end=" ")
# 输出: o l l e H

# 使用切片反向遍历
for char in s[::-1]:
    print(char, end=" ")
# 输出: o l l e H

# 使用递减的索引
for i in range(len(s)-1, -1, -1):
    print(f"索引 {i}: {s[i]}", end=" | ")
# 输出: 索引 4: o | 索引 3: l | 索引 2: l | 索引 1: e | 索引 0: H |

# ----------------------重要提示！---------------
# 字符串是不可变的，所以"修改"实际上是创建新的字符串 
# 在Python的for循环中，循环变量i是只读的，不能在循环体内修改它的值。而while循环可以自由控制循环变量

s = "hello"
for i in range(len(s)):
    if s[i] == 'l':
        i += 2  # 这不会影响实际的循环！
        print(f"跳过到索引 {i}")
    print(s[i])
i = 0
while i < len(s):
    if s[i] == 'l':
        print(f"跳过字符 '{s[i]}' 在位置 {i}")
        i += 1  # 直接跳过这个字符
        continue
    print(s[i])
    i += 1
```
## 列表 List
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

# 添加元素
numbers.append(6)
numbers.insert(1, 15)  # 在索引1处插入15

list1 = [1, 2]
list2 = [3, 4]
# 将另一个可迭代对象的所有元素添加到列表末尾
list1.extend(list2)  # list1 变为 [1, 2, 3, 4]
# 等价于 list1 += list2

# 删除元素
numbers.remove(15)     # 删除值为15的元素 （删除第一个匹配项）
popped = numbers.pop() # 删除并返回最后一个元素
popped_at_index = numbers.pop(0)  # 删除并返回索引0处的元素（可指定索引）
del numbers[0]         # 删除索引0的元素 不返回值

# 修改
numbers[0] = 10

# 查找与计数
numbers = [1, 2, 3, 2, 4, 2]
# 查找元素第一次出现的索引
first_index = numbers.index(2)  # 1
# 计算元素在列表中出现的次数
count_of_twos = numbers.count(2)  # 3
# 检查元素是否存在
has_three = 3 in numbers  # True
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
### 内置算法
```python
# 排序与反转
# list.sort(key=function, reverse=False)  # 原地排序

numbers = [3, 1, 4, 1, 5]
# 原地从小到大排序（修改原列表）
numbers.sort()
print(numbers)  # [1, 1, 3, 4, 5]
numbers.sort(reverse = 1) #从大到小排序
# 原地反转（修改原列表）
numbers.reverse()
print(numbers)  # [5, 4, 3, 1, 1]

# 二维数组排序
points = [[1, 2], [3, 4], [5, 6]]
points.sort(key=lambda p: (p[0], -p[1]))  # x 升序，y 降序
# 使用 sorted() 和 reversed() 返回新对象
sorted_numbers = sorted(numbers)  # 新列表 [1, 1, 3, 4, 5]
reversed_iter = reversed(numbers) # 返回迭代器，可用 list() 转换
```
## 元组 Tuple
不可变集合。
### 创建元组
```python
# 创建元组
point = (1, 2)
colors = ("red", "green", "blue")
# 单元素元组（注意逗号）
single = (42,)
# 空元组
empty_tuple = ()

# 元组查找与计数
point = (1, 2, 1, 3)
# 查找元素第一次出现的索引
first_index = point.index(1)  # 0
# 计算元素出现次数
count_of_ones = point.count(1)  # 2
```
### 对组pair
```python
# 使用元组表示对组
pair = (1, "hello")

# 访问
first = pair[0]  # 1
second = pair[1]  # "hello"

# 解包
key, value = pair

# 或者使用命名元组
from collections import namedtuple
Pair = namedtuple('Pair', ['first', 'second'])
p = Pair(1, "hello")
print(p.first, p.second)  # 1 "hello"

```
## 字典（哈希表） Dict
无序的键值对集合（对应c++中的std::unordered_map）
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
# 访问值/查找
print(person["name"])# 若键不存在，会抛出 KeyError
# 使用 get() 方法（推荐，若键不存在返回 None）
print(person.get("name"))
print(person.get("height", "Unknown"))  # 提供默认值，若键不存在则返回 "Unknown"

# 判断键是否存在
if "key1" in hash_map:
    print("存在")

# 添加/修改
person["city"] = "Beijing"
person["age"] = 31

# 删除
del person["city"]
# 或使用 pop()
value = hash_map.pop("key2", None)  # 安全删除  提供默认值避免 KeyError
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
### 内置算法
```python
# 更新与合并
dict1 = {"a": 1, "b": 2}
dict2 = {"c": 3, "d": 4}
# 将另一个字典的键值对更新到当前字典（会覆盖同名键）
dict1.update(dict2)  # dict1 变为 {"a": 1, "b": 2, "c": 3, "d": 4}
# Python 3.9+ 支持合并操作符
merged = dict1 | dict2  # 创建新字典
dict1 |= dict2  # 原地更新 dict1

#排序
# Python 3.7+ 中普通dict保持插入顺序 哈希表 (带顺序记录)
ordered_dict = {}
ordered_dict["c"] = 3
ordered_dict["a"] = 1
ordered_dict["b"] = 2

# 按键排序遍历
for key in sorted(ordered_dict.keys()):
    print(f"{key}: {ordered_dict[key]}")  # a:1, b:2, c:3

# 视图
person = {"name": "Alice", "age": 30}
# 获取所有键的视图（动态的）
keys_view = person.keys()  # dict_keys(['name', 'age'])
# 获取所有值的视图（动态的）
values_view = person.values()  # dict_values(['Alice', 30])
# 获取所有键值对的视图（动态的）
items_view = person.items()  # dict_items([('name', 'Alice'), ('age', 30)])
# 👉 视图是动态的，字典改变，视图也随之改变。
```
### 多重哈希表
对应c++中的std::unordered_multimap
```python
from collections import defaultdict
# 使用defaultdict实现多重映射
multi_map = defaultdict(list)

# 插入多个相同键的值
multi_map["key1"].append("value1")
multi_map["key1"].append("value2")
multi_map["key2"].append("value3")

# 获取某个键的所有值
values = multi_map["key1"]  # ["value1", "value2"]

# 遍历
for key, values_list in multi_map.items():
    for value in values_list:
        print(f"{key}: {value}")

# 查找特定键值对
if "key1" in multi_map:
    if "value1" in multi_map["key1"]:
        print("找到key1-value1")
```
### 多重映射
对应c++中的std::multimap
```python
from collections import defaultdict

# 方法1: 使用defaultdict + list
multi_map = defaultdict(list)
multi_map[2].append("b")
multi_map[1].append("a")
multi_map[2].append("c")

# 按键排序遍历
for key in sorted(multi_map.keys()):
    for value in multi_map[key]:
        print(f"{key}: {value}")  # 1:a, 2:b, 2:c

from sortedcontainers import SortedList  # 需要安装: pip install sortedcontainers
# 方法2: 使用sortedcontainers（更高效）
try:
    from sortedcontainers import SortedDict
    sorted_multi_map = SortedDict()
    sorted_multi_map.setdefault(2, []).append("b")
    sorted_multi_map.setdefault(1, []).append("a")
    sorted_multi_map.setdefault(2, []).append("c")
except ImportError:
    pass
```
## 集合 Set
无序的不重复元素（对应c++中的std::unordered_set）
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

# 遍历
for item in hash_set:
    print(item)
```
### 内置算法
```python
a = {1, 2, 3, 4}
b = {3, 4, 5, 6}

# 并集：a 或 b 中的元素
union_set = a | b           # {1, 2, 3, 4, 5, 6}
union_set = a.union(b)      # 同上
a.update(b) # 原地并集（修改 a） 等价于 a |= b

# 交集：同时在 a 和 b 中的元素
intersection_set = a & b    # {3, 4}
intersection_set = a.intersection(b)  # 同上
a.intersection_update(b) # 原地交集（修改 a）等价于 a &= b

# 差集：在 a 中但不在 b 中的元素
difference_set = a - b      # {1, 2}
difference_set = a.difference(b)  # 同上
a.difference_update(b) # 原地差集（修改 a） 等价于 a -= b

# 对称差集：在 a 或 b 中，但不同时在两者中的元素
symmetric_diff_set = a ^ b  # {1, 2, 5, 6}
symmetric_diff_set = a.symmetric_difference(b)  # 同上
a.symmetric_difference_update(b) # 原地对称差集（修改 a）等价于 a ^= b

# 子集检查
c = {1, 2}
d = {1, 2, 3}
print(c.issubset(d))        # True, c 是 d 的子集
print(d.issuperset(c))      # True, d 是 c 的超集

# 不相交检查
e = {1, 2}
f = {3, 4}
print(e.isdisjoint(f))      # True, e 和 f 没有共同元素

# 排序
for item in sorted(ordered_set):
    print(item)  # 1, 2, 3
```
### 多重哈希集合
对应c++中的std::unordered_multiset
```python
from collections import Counter

# 使用Counter实现多重集合
multi_set = Counter()

# 插入元素（可重复）
multi_set.update([1, 2, 2, 3, 3, 3])
multi_set[4] += 2  # 直接增加计数 加2个4到集合中

# 获取元素出现次数
count = multi_set[2]  # 2

# 遍历所有元素（包括重复）
for element, count in multi_set.items():
    for _ in range(count):
        print(element)  # 模拟多重集合的遍历

# 删除元素
multi_set[2] -= 1  # 减少计数
if multi_set[2] <= 0:
    del multi_set[2]

# 转换为集合（去重）
unique_set = set(multi_set.keys())
```
### 多重集合
对应c++中std::multiset
```python
from collections import Counter
# 方法1: 使用Counter + 排序
multi_set = Counter([3, 1, 2, 2, 3, 3])
for element in sorted(multi_set.elements()):
    print(element)  # 1, 2, 2, 3, 3, 3

from sortedcontainers import SortedList
# 方法2: 使用sortedcontainers
try:
    sorted_multi_set = SortedList([3, 1, 2, 2, 3, 3])
    for element in sorted_multi_set:
        print(element)  # 1, 2, 2, 3, 3, 3
except ImportError:
    pass
```
## 堆 Heapq
对应c++中的std::priority_queue
### 小根堆
```python
import heapq
min_heap = []
heapq.heappush(min_heap, (2, "task2"))
heapq.heappush(min_heap, (1, "task1"))  # 优先级1最高
heapq.heappush(min_heap, (3, "task3"))

# 弹出最小元素
priority, value = heapq.heappop(min_heap)
print(value)  # "task1"
```

### 大根堆（通过取负）
```python
import heapq
max_heap = []
heapq.heappush(max_heap, (-2, "task2"))
heapq.heappush(max_heap, (-1, "task1"))  # -1最大，所以task1优先级最高
priority, value = heapq.heappop(max_heap)
print(value)  # "task1"，priority为-1
```
### PriorityQueue（线程安全）
```python
from queue import PriorityQueue
# 创建一个优先队列实例
pq = PriorityQueue()

# 使用 put() 方法插入元素
# 元素必须是可比较的，通常使用 (priority, data) 的元组形式
pq.put((2, "task2"))
pq.put((1, "task1"))
pq.put((3, "task3"))

# 使用 get() 方法取出优先级最高的元素（最小优先级值）
# get() 是阻塞操作，默认会等待直到有元素可用
priority, value = pq.get()
print(value)  # 输出: "task1" (优先级为1，最高)

priority, value = pq.get()
print(value)  # 输出: "task2"
```
## 队列 Queue
### Queue（线程安全）
```python
from queue import Queue

# 创建队列实例
q = Queue(maxsize=0)  # maxsize=0 表示无限大小（默认）

# --- 入队操作：put() ---
q.put(1)  # 添加元素 1
q.put(2)  # 添加元素 2
q.put(3)
print(f"队列大小: {q.qsize()}")  # 输出: 队列大小: 3

# --- 查看队首元素 ---
# ❌ Queue 没有直接提供 "peek" 或查看队首但不移除的方法。
# 替代方案 get() 后再 put() 回去（非原子操作，多线程下危险）
# item = q.get()
# print("队首:", item)
# q.put(item)  # 放回去，但顺序可能被打乱


# --- 出队操作：get() ---
item = q.get()  # 移除并返回最先进入的元素
print(item)  # 输出: 1

item = q.get()
print(item)  # 输出: 2

print(f"剩余大小: {q.qsize()}")  # 输出: 剩余大小: 1

# 创建一个大小受限的队列用于演示 full()
q = Queue(maxsize=3)  # 最多只能存放3个元素

print(f"初始: empty={q.empty()}, full={q.full()}, size={q.qsize()}")

# --- 演示 empty() ---
print(f"队列为空? {q.empty()}")  # 输出: True

# --- 入队操作 ---
q.put(1)
q.put(2)
q.put(3)
# 队列已满
print(f"队列已满? {q.full()}")  # 输出: True

# 阻塞与超时
# --- 非阻塞操作 ---
try:
    item = q.get_nowait()      # 等价于 get(block=False)
    print("获取成功:", item)
except queue.Empty:
    print("队列为空，无法获取")

try:
    q.put_nowait(4)            # 等价于 put(item, block=False)
    print("入队成功")
except queue.Full:
    print("队列已满，无法入队")

# --- 带超时的阻塞操作 ---
try:
    item = q.get(timeout=2.0)  # 最多等待2秒
    print("获取成功:", item)
except queue.Empty:
    print("等待2秒后队列仍为空")

try:
    q.put(5, timeout=1.0)      # 最多等待1秒
    print("入队成功")
except queue.Full:
    print("等待1秒后队列仍满")
```
### 双向队列
```python
from collections import deque

dq = deque()
# 从右侧操作
dq.append("right1")
dq.append("right2")
right_value = dq.pop()  # "right2"

# 从左侧操作
dq.appendleft("left1")
dq.appendleft("left2")
left_value = dq.popleft()  # "left2"

# 指定最大长度（循环缓冲区）
dq = deque(maxlen=3)
dq.append(1)
dq.append(2)
dq.append(3)
dq.append(4)  # 自动丢弃最左边的1
print(dq)  # deque([2, 3, 4], maxlen=3)

# 随机访问
print(dq[1])  # 3

# 旋转
dq.rotate(1)   # 向右旋转1位: [4, 2, 3]
dq.rotate(-1)  # 向左旋转1位: [2, 3, 4]
```
### 栈
```python
# 使用list实现栈
stack = []
stack.append(1)  # push
stack.append(2)
stack.append(3)

top = stack[-1]  # top: 3
popped = stack.pop()  # pop: 3

# 检查是否为空
is_empty = len(stack) == 0

# 使用deque实现栈（更高效）
from collections import deque
stack = deque()
stack.append(1)
stack.append(2)
popped = stack.pop()  # 2
```
## 算法
### 排序sorted
```python
sorted(iterable, key=function, reverse=False)
# key：一个函数，它接收列表中的每个元素，返回用于比较的值
# reverse=False：默认升序；reverse=True：降序
```
1. 按字符串长度排序
```python
words = ['apple', 'hi', 'banana', 'a', 'python']
sorted_words = sorted(words, key=len)
# ['a', 'hi', 'apple', 'banana', 'python']
```
2. 按字典中的某个字段排序
```python
students = [
    {'name': 'Alice', 'age': 25},
    {'name': 'Bob', 'age': 20},
    {'name': 'Charlie', 'age': 30}
]

# 按年龄排序
sorted_students = sorted(students, key=lambda x: x['age'])
# 输出: [{'name': 'Bob', 'age': 20}, {'name': 'Alice', 'age': 25}, {'name': 'Charlie', 'age': 30}]
```
3. 按对象的属性排序（使用 operator.attrgetter）
```python
from operator import attrgetter

class Person:
    def __init__(self, name, age):
        self.name = name
        self.age = age

    def __repr__(self):
        return f"Person('{self.name}', {self.age})"

people = [Person('Alice', 25), Person('Bob', 20), Person('Charlie', 30)]

# 按 age 属性排序
sorted_people = sorted(people, key=attrgetter('age'))
print(sorted_people)
# 输出: [Person('Bob', 20), Person('Alice', 25), Person('Charlie', 30)]
```
4. 多条件排序（先按年龄，再按名字）
```python
students = [
    {'name': 'Alice', 'age': 25},
    {'name': 'Bob', 'age': 20},
    {'name': 'Charlie', 'age': 25},
    {'name': 'David', 'age': 20}
]

# 先按 age 升序，再按 name 升序
sorted_students = sorted(students, key=lambda x: (x['age'], x['name']))
print(sorted_students)
# 输出: [{'name': 'Bob', 'age': 20}, {'name': 'David', 'age': 20}, {'name': 'Alice', 'age': 25}, {'name': 'Charlie', 'age': 25}]
```
5. 按数字字符串的数值排序（避免 '10' < '2'）
```python
nums = ['10', '2', '20', '1']
sorted_nums = sorted(nums, key=int)
print(sorted_nums)
# 输出: ['1', '2', '10', '20']
```
6. 按文件扩展名排序
```python
files = ['a.py', 'b.txt', 'c.py', 'd.md', 'e.py']

# 按扩展名排序，.py 在前
sorted_files = sorted(files, key=lambda x: (x.endswith('.py'), x))
# 或更明确地：
sorted_files = sorted(files, key=lambda x: (not x.endswith('.py'), x))
print(sorted_files)
# 输出: ['a.py', 'c.py', 'e.py', 'b.txt', 'd.md']
```
7. 自定义复杂逻辑（例如：奇数在前，偶数在后，各自升序）
```python
nums = [3, 1, 4, 1, 5, 9, 2, 6]

# 奇数在前，偶数在后；奇数和偶数内部都升序
sorted_nums = sorted(nums, key=lambda x: (x % 2 == 0, x))
print(sorted_nums)
# 输出: [1, 1, 3, 5, 9, 2, 4, 6]
```

## 函数
### 默认参数
```python
def greet(name, greeting="Hello"):  # greeting 有默认值
    return f"{greeting}, {name}!"
print(greet("Alice"))           # "Hello, Alice!"
print(greet("Bob", "Hi"))       # "Hi, Bob!"
```
### 解包参数
```python
def func(a, b, c):
    print(a, b, c)
args = [1, 2, 3]
func(*args)  # 等价于 func(1, 2, 3)，将列表解包为位置参数
kwargs = {"a": 1, "b": 2, "c": 3}
func(**kwargs)  # 等价于 func(a=1, b=2, c=3)，将字典解包为关键字参数
```
### 可变参数
```python
def sum_all(*args):
    return sum(args)

print(sum_all(1, 2, 3, 4))  # 10

def greet_all(**kwargs):
    for key, value in kwargs.items():
        print(f"{key}: {value}")

greet_all(name="Alice", age=30)

def example_function(required_param, *args, **kwargs):
    print(f"Required: {required_param}")
    print(f"Args (tuple): {args}")
    print(f"Kwargs (dict): {kwargs}")

example_function("hello", 1, 2, 3, name="Alice", age=30)
# 输出：
# Required: hello
# Args (tuple): (1, 2, 3)
# Kwargs (dict): {'name': 'Alice', 'age': 30}
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
    content1 = f.read(10)  # 读取前10个字符
    current_pos = f.tell() # 获取当前文件指针位置
    f.seek(0)              # 将文件指针移动到开头
    content2 = f.read()    # 重新读取整个文件
    print(content2)

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
### 使用 pathlib (现代推荐方式)
```python
from pathlib import Path
# 创建 Path 对象
file_path = Path("data.txt")
# 读取文本
content = file_path.read_text(encoding='utf-8')
# 写入文本（覆盖）
file_path.write_text("Hello", encoding='utf-8')
# 追加文本
with file_path.open('a', encoding='utf-8') as f:
    f.write("\nWorld")
```
### JSON处理
```python
import json

# Python对象转JSON字符串
data = {"name": "Alice", "age": 30}
# 👉 `ensure_ascii=False` 允许非ASCII字符（如中文）直接显示，而不是转义成 \uXXXX。
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