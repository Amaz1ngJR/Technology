# 入门
## 渲染管线
渲染管线 描述了从三维场景数据到最终二维屏幕上像素这一系列复杂处理步骤的有序集合
现代的渲染管线可以大致分为几个关键阶段：
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
 	- 使用流程：
	```c++
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	
	glBindVertexArray(0); // 解绑，保存配置
 	```
3. EBO / IBO (Element Buffer Object / Index Buffer Object，索引缓冲对象)
   - 作用：
     > EBO 用于存储 顶点索引，以便使用 glDrawElements 进行绘制，实现索引绘制（Indexed Drawing）
     > 使用EBO可以避免重复存储相同的顶点，节省内存并提高效率
     
![image](https://github.com/Amaz1ngJR/Technology/assets/83129567/61bab369-4f7c-44db-af60-b6130133f7a0)

![image](https://github.com/Amaz1ngJR/Technology/assets/83129567/0e492a47-97aa-4a6e-b86a-c7d988d06643)

## 着色器

## 纹理

### 纹理单元

## 变换
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

<img width="1642" height="820" alt="image" src="https://github.com/user-attachments/assets/cc3418a5-c6c3-43fd-941e-80006a92b301" />


### 3D

### 摄像机
欧拉角(Euler Angle)是可以表示3D空间中任何旋转的3个值，
一共有3种欧拉角：俯仰角(Pitch)、偏航角(Yaw)和滚转角(Roll)

<img width="1670" height="588" alt="image" src="https://github.com/user-attachments/assets/cfdfc42c-026c-46be-ac1f-6c5e4428a4fb" />

# 光照




