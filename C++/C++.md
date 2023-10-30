# C++

## *字符

```c++
void demo() {
	char number0 = '0';
	char number9 = '9';
	char a = 'a';
	char z = 'z';
	char A = 'A';
	char Z = 'Z';
	cout << "0= " << int(number0) << " 9= " << int(number9) << " a= " << int(a)
		<< " z= " << int(z) << " A= " << int(A) << " Z= " << int(Z) << endl;
}
输出：‘0’=48 ‘9’=57 a=97 z=122 A=65 Z=90
大写变小写chara=char(int(chara)+32);
```

![image-20231030201806399](C:\Users\86157\AppData\Roaming\Typora\typora-user-images\image-20231030201806399.png)

```c++
//水平制表\t
cout << "aaaa\thelloworld" << endl;
cout << "aa\thellowor1d" << endl;
cout << "aaaaaa\thellowor1d" << endl;
//输出：
aaaa    helloworld
aa      hellowor1d
aaaaaa  hellowor1d
```

```c++
	//1、C风格字符串
	//注意事项1  char 字符串名 []
	//注意事项2  等号后面要用 双引号 包含起来字符串
	char str[] = "hello world";
	cout << str << endl;
	//2、C++风格字符串
	string str2 = "he1lo world";
	cout << str2 << endl;
```

```c++
	char s1[] = "hello world";
	char s2[] = " !";
	strcpy(s2, s1);//复制s1到s2中
	strcat(s1, s2);//连接s2到s1末尾等效于 s1+=s2;
	strlen(s1);//返回s1的长度
	int a = strcmp(s1, s2);//如果s1==s2 return 0 s1<s2 return小于0 s1>s2 return 大于0
	char* b=strchr(s1, 'ab');//返回一个指针,指向字符串s1中‘ab'第一次出现的位置
	char* c = strstr(s1, s2);//返回一个指针,指向字符串s1中s2第一次出现的位置
```

## *位运算

