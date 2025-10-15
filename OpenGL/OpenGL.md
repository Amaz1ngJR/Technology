# 入门
## 渲染管线阶段概述
渲染管线 描述了从三维场景数据到最终二维屏幕上像素这一系列复杂处理步骤的有序集合
现代的渲染管线可以大致分为几个关键阶段：
* **顶点着色器**：处理每个顶点，进行坐标变换
* 几何着色器：处理图元，生成新图元
* 形状（图元）装配：将顶点数据组装成图元（如三角形、线段等）
* **光栅化**：把图元映射为最终屏幕上相应的像素, 将图元转换成片段
> 在片段着色器运行之前会执行裁切(Clipping)。裁切会丢弃超出你的视图以外的所有像素，用来提升执行效率。OpenGL中的一个片段是OpenGL渲染一个像素所需的所有数据。
* **片段着色器**：计算每个片段的颜色，进行光照计算和纹理采样
* 深度测试和模板测试：确定片段是否可见
* 混合和输出：将片段的最终颜色写入帧缓冲区

![image](https://github.com/Amaz1ngJR/Technology/assets/83129567/61bab369-4f7c-44db-af60-b6130133f7a0)

## 着色器
着色器是运行在GPU上的小程序，这些小程序为图形渲染管线的特定部分执行计算。现代OpenGL需要我们至少设置一个顶点和一个片段着色器
* 顶点着色器（Vertex Shader）
顶点着色器是OpenGL中第一个执行的着色器，它把一个单独的顶点作为输入。顶点着色器的主要目的是把3D坐标转换为另一种3D坐标，同时顶点着色器允许我们对顶点属性进行一些基本处理。
* 片段着色器（Fragment Shader）
片段着色器是OpenGL中第二个执行的着色器，它把一个单独的片段作为输入。片段着色器的主要目的是计算一个像素的最终颜色，它接受顶点着色器输出的颜色进行计算。
### 着色器程序（Shader Program）
顶点着色器和片段着色器必须链接成一个着色器程序才能使用。
```c++
// 编译着色器（以顶点着色器为例，片段着色器同理）
unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);//创建顶点着色器 并用ID(vertexShader)来引用它
//将源码附加到着色器对象上 第一个参数为要编译的着色器对象。第二参数指定了传递的源码字符串数量。第三个参数是顶点着色器真正的源码。第四个参数是可选的，用于指定源码字符串的长度（但通常我们让OpenGL自动计算这个值）。
glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
glCompileShader(vertexShader);//编译着色器

// 创建程序并链接
unsigned int shaderProgram = glCreateProgram(); // 创建一个着色器程序对象 并返回新创建程序对象的ID引用
glAttachShader(shaderProgram, vertexShader);//将着色器附加到程序对象上
glLinkProgram(shaderProgram);//链接程序对象
glDeleteShader(vertexShader);// 释放已链接的着色器对象（因为它们已经集成到程序中，不再需要单独保留）
glUseProgram(shaderProgram);//激活着色器程序
```
## 链接顶点属性
### VAO/VBO/EBO
```
顶点数组对象：Vertex Array Object，VAO
顶点缓冲对象：Vertex Buffer Object，VBO
元素缓冲对象：Element Buffer Object，EBO 或 索引缓冲对象 Index Buffer Object，IBO
```
1. VBO (Vertex Buffer Object，顶点缓冲对象)
	- 作用：
	> VBO 是用于在 GPU显存 中存储顶点数据的缓冲区对象。这些数据可以包括顶点坐标、颜色、纹理坐标、法线等;
	> 如果不使用VBO，每次绘制时都需要从CPU内存向GPU传递顶点数据，效率很低。使用VBO后，顶点数据只需上传一次到GPU，之后可重复使用，大大提高渲染效率。
 	```c++
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);//GL_ARRAY_BUFFER：表示这是一个存储顶点属性数据的缓冲
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);//GL_STATIC_DRAW：提示OpenGL数据不会频繁更改
  	```
2. VAO (Vertex Array Object，顶点数组对象)
	- 作用：
	VAO 用于 记录顶点属性的配置状态，比如：
		- 哪些顶点属性是启用的（如位置、颜色等）；
		- 每个属性如何从VBO中解析（偏移、步长、类型等）；
		- 使用了哪个或哪些VBO。
	- 关键点：
	> VAO本身不存储顶点数据，它存储的是对VBO的引用和顶点属性指针的设置。
	> 它的作用是“记住”顶点数据的布局和配置，这样在渲染时只需绑定一个VAO，就能恢复所有顶点属性的设置。
 	
3. EBO / IBO (Element Buffer Object / Index Buffer Object，索引缓冲对象)
   - 作用：
     > EBO 用于存储 顶点索引，以便使用 glDrawElements 进行绘制，实现索引绘制（Indexed Drawing）
     > 使用EBO可以避免重复存储相同的顶点，节省内存并提高效率
    
```c++
// 初始化流程：
glGenVertexArrays(1, &VAO);
glGenBuffers(1, &VBO);
glGenBuffers(1, &EBO);

glBindVertexArray(VAO);// 绑定VAO

glBindBuffer(GL_ARRAY_BUFFER, VBO);// 绑定VBO
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);// 将顶点数据复制到缓冲中

glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);// 绑定EBO
glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);// 将索引数据复制到缓冲中

// 设置顶点属性
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
glEnableVertexAttribArray(0);// 启用顶点属性0

glBindVertexArray(0); // 解绑
```
OpenGL仅当3D坐标在3个轴（x、y和z）上-1.0到1.0的范围内时才处理它。所有在这个范围内的坐标叫做标准化设备坐标(Normalized Device Coordinates)，此范围内的坐标最终显示在屏幕上（在这个范围以外的坐标则不会显示）。
![image](https://github.com/Amaz1ngJR/Technology/assets/83129567/0e492a47-97aa-4a6e-b86a-c7d988d06643)

## 纹理
纹理坐标起始于(0, 0)，也就是纹理图片的左下角，终止于(1, 1)

<img alt="image" src="https://github.com/user-attachments/assets/ad19a8db-0ea6-4f0d-8aa2-1455c00c13d0" />
### 纹理的环绕方式
|环绕方式	|描述|
|:----------|-----|
|GL_REPEAT|对纹理的默认行为。重复纹理图像。|
|GL_MIRRORED_REPEAT|	和GL_REPEAT一样，但每次重复图片是镜像放置的。|
|GL_CLAMP_TO_EDGE	|纹理坐标会被约束在0到1之间，超出的部分会重复纹理坐标的边缘，产生一种边缘被拉伸的效果。|
|GL_CLAMP_TO_BORDER|	超出的坐标为用户指定的边缘颜色。|

<img alt="image" src="https://github.com/user-attachments/assets/82b2d03e-bb5c-4c0a-8127-b0806f87893f" />

```c++
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
/*第一个参数指定了纹理目标
第二个参数指定设置的选项与应用的纹理轴，指定S、T轴
最后一个参数需要我们传递一个环绕方式*/

//如果选择GL_CLAMP_TO_BORDER选项，需要使用glTexParameterfv函数,还需要指定一个边缘的颜色
float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
```
### 纹理过滤
OpenGL需要知道怎样将纹理像素(Texture Pixel)映射到纹理坐标，比较重要的为GL_NEAREST（也叫邻近过滤，Nearest Neighbor Filtering）是OpenGL默认的纹理过滤方式

<img alt="image" src="https://github.com/user-attachments/assets/a298676b-ff0c-490f-a1f5-21279ab4403b" />

以及GL_LINEAR（也叫线性过滤，(Bi)linear Filtering）它会基于纹理坐标附近的纹理像素，计算出一个插值，近似出这些纹理像素之间的颜色

<img alt="image" src="https://github.com/user-attachments/assets/2f0d3929-ce65-4c7c-b8cf-a2f17ec03998" />

```c++
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
```
多级渐远纹理(Mipmap):距观察者的距离超过一定的阈值，OpenGL会使用不同的多级渐远纹理，即最适合物体的距离的那个

<img alt="image" src="https://github.com/user-attachments/assets/46c95821-586d-421a-8d4b-a5b07db3beb7" />

|过滤方式	|描述|
|:----------|-----|
|GL_NEAREST_MIPMAP_NEAREST|	使用最邻近的多级渐远纹理来匹配像素大小，并使用邻近插值进行纹理采样|
|GL_LINEAR_MIPMAP_NEAREST|	使用最邻近的多级渐远纹理级别，并使用线性插值进行采样|
|GL_NEAREST_MIPMAP_LINEAR	|在两个最匹配像素大小的多级渐远纹理之间进行线性插值，使用邻近插值进行采样|
|GL_LINEAR_MIPMAP_LINEAR	|在两个邻近的多级渐远纹理之间使用线性插值，并使用线性插值进行采样|

## 变换
### 矩阵运算

### 缩放

### 位移

### 旋转
角度变换
```
#define PI = 3.14159265359
弧度转角度 ： 角度 = 弧度 * (180.0f / PI)
角度转弧度 ： 弧度 = 角度 * (PI / 180.0f)
```

### MVP矩阵
模型（Model）、观察（View）、投影（Projection）矩阵的乘积Mp * Mv * Mm

顶点坐标一开始是局部空间(Local Space)的，通过Model矩阵(缩放→旋转→平移 TRS)变成世界坐标(World Coordinate)；

将相机放到世界坐标的原点，得到的逆矩阵就是View矩阵(相机是不动的，是世界在动)，将坐标进一步变成观察坐标(View Coordinate)；

然后选择投影方式（正交或者透视）通过投影矩阵将坐标进一步变成裁剪坐标(Clip Coordinate)（p矩阵并不是真正的做投影，而是为投影做准备）
最后通过视口变换的步骤变成屏幕坐标(Screen Coordinate)

<img alt="image" src="https://github.com/user-attachments/assets/cc3418a5-c6c3-43fd-941e-80006a92b301" />


### 3D

### 摄像机
欧拉角(Euler Angle)是可以表示3D空间中任何旋转的3个值，
一共有3种欧拉角：俯仰角(Pitch)、偏航角(Yaw)和滚转角(Roll)

<img alt="image" src="https://github.com/user-attachments/assets/cfdfc42c-026c-46be-ac1f-6c5e4428a4fb" />

# 光照





