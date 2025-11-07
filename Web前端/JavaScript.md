# JavaScript

## JavaScript基本语法

### 变量

变量是用于存储数据的容器，使用`var`关键字声明变量。

```javascript
var name = "John";
var age = 30;
```

### 数据类型
JavaScript有8种数据类型：Undefined、Null、Boolean、Number、String、Symbol、BigInt、Object。

#### Undefined
表示变量声明了但未初始化。

```javascript
var x;
console.log(x); // 输出: undefined
```

#### Null
表示空值或空对象引用。

```javascript
var x = null;
console.log(x); // 输出: null
```

#### Boolean
表示真或假。

```javascript
var x = true;
var y = false;
```

#### Number
表示数字。

```javascript
var x = 10;
var y = 3.14;
```

#### String
表示文本。

```javascript
var x = "Hello";
var y = 'World';
```

#### Symbol
表示唯一且不可变的值。

```javascript
var x = Symbol("unique");
```

#### BigInt
表示任意精度的整数。

```javascript
var x = 1234567890123456789012345678901234567890n;
```

#### Object
表示对象，可以包含多个属性和方法。

```javascript
var person = {
  name: "John",
  age: 30,
  greet: function() {
    console.log("Hello, my name is " + this.name);
  }
};
```

### 运算符
运算符用于执行操作。

#### 算术运算符
```javascript
var x = 10;
var y = 5;

console.log(x + y); // 输出: 15
console.log(x - y); // 输出: 5
console.log(x * y); // 输出: 50
console.log(x / y); // 输出: 2
console.log(x % y); // 输出: 0
console.log(x ** y); // 输出: 100000
```

#### 比较运算符
```javascript
var x = 10;
var y = 5;

console.log(x == y); // 输出: false
console.log(x != y); // 输出: true
console.log(x > y); // 输出: true
console.log(x < y); // 输出: false
console.log(x >= y); // 输出: true
console.log(x <= y); // 输出: false
```

#### 逻辑运算符
```javascript
var x = true;
var y = false;

console.log(x && y); // 输出: false
console.log(x || y); // 输出: true
console.log(!x); // 输出: false
```

#### 位运算符
```javascript
var x = 5; // 二进制: 0101
var y = 3; // 二进制: 0011

console.log(x & y); // 输出: 1 (二进制: 0001)
console.log(x | y); // 输出: 7 (二进制: 0111)
console.log(x ^ y); // 输出: 6 (二进制: 0110)
console.log(~x); // 输出: -6 (二进制: 1100)
console.log(x << 1); // 输出: 10 (二进制: 1010)
console.log(x >> 1); // 输出: 2 (二进制: 0010)
```

### 字符串操作

#### 字符串连接
```javascript
var str1 = "Hello";
var str2 = "World";

console.log(str1 + " " + str2); // 输出: Hello World
```

#### 字符串长度
```javascript
var str = "Hello World";

console.log(str.length); // 输出: 11
```

#### 字符串索引
```javascript
var str = "Hello World";

console.log(str[0]); // 输出: H
console.log(str[1]); // 输出: e
```

#### 字符串方法
```javascript
var str = "Hello World";

console.log(str.toUpperCase()); // 输出: HELLO WORLD
console.log(str.toLowerCase()); // 输出: hello world
console.log(str.indexOf("o")); // 输出: 4
console.log(str.lastIndexOf("o")); // 输出: 7
console.log(str.slice(0, 5)); // 输出: Hello
console.log(str.replace("World", "JavaScript")); // 输出: Hello JavaScript
```

### 条件语句

#### if语句
```javascript
if (condition) {
  // 如果条件为真，则执行这里的代码
} else {
  // 如果条件为假，则执行这里的代码
}
```

#### if...else if...else语句

```javascript
if (condition1) {
  // 如果条件1为真，则执行这里的代码
} else if (condition2) {
  // 如果条件1为假且条件2为真，则执行这里的代码
} else {
  // 如果条件1和条件2都为假，则执行这里的代码
}
```

#### switch语句

```javascript
switch (expression) {
  case value1:
    // 如果表达式等于value1，则执行这里的代码
    break;
  case value2:
    // 如果表达式等于value2，则执行这里的代码
    break;
  default:
    // 如果表达式不等于任何case，则执行这里的代码
}
```

### 循环语句

#### for循环

```javascript
for (var i = 0; i < 10; i++) {
  // 循环体
}
```

#### while循环

```javascript
while (condition) {
  // 循环体
}
```

#### do...while循环

```javascript
do {
  // 循环体
} while (condition);
```

### 函数

函数是一段可重复使用的代码块，用于执行特定的任务。

```javascript
function greet(name) {
  console.log("Hello, " + name);
}

greet("John"); // 输出: Hello, John
```

### 对象

对象是JavaScript中的基本数据类型之一，用于存储键值对。

```javascript
var person = {
  name: "John",
  age: 30,
  greet: function() {
    console.log("Hello, my name is " + this.name);
  }
};

console.log(person.name); // 输出: John
person.greet(); // 输出: Hello, my name is John
```

### 数组

数组是用于存储多个值的有序集合。

```javascript
var fruits = ["apple", "banana", "orange"];

console.log(fruits[0]); // 输出: apple
console.log(fruits.length); // 输出: 3
```

### 事件处理

事件处理程序是当特定事件发生时执行的代码块。

```javascripthtml
<button onclick="myFunction()">点击我</button>

<script>
function myFunction() {
  alert("按钮被点击了！");
}
</script>
```

### DOM操作

DOM（文档对象模型）是用于访问和操作HTML文档的API。

```javascript
document.getElementById("myButton").addEventListener("click", function() {
  alert("按钮被点击了！");
});
```

### JSON

JSON（JavaScript Object Notation）是一种轻量级的数据交换格式。

```javascript
var person = {
  "name": "John",
  "age": 30,
  "city": "New York"
};

console.log(person.name); // 输出: John
```

### 异步编程

异步编程是处理异步操作（如网络请求）的方法。

```javascript
fetch("https://api.example.com/data")
  .then(response => response.json())
  .then(data => console.log(data))
  .catch(error => console.error(error));
```