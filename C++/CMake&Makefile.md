# CMake&Makefile

插入图片

## CMake

```cmake
#CMakeLists.txt:
cmake_minimum_required(VERSION 2.9)#设置cmake最低版本(PowerShell cmake --version)
project(MyProject) #设置项目名称
set(CMAKE_CXX_STANDARD 14) #设置C++14标准
add_definitions(/utf-8) #设置utf-8格式
add_executable(main main.cpp func.cpp .cpp …) #使用指定的源文件来生成目标可执行文件
include_directories("include" "D:/include1" "D:/MyCode/include2") #指定头文件的搜索路径
add_definitions(/D_USE_MATH_DEFINES -D_CRT_SECURE_NO_DEPRECATE) #添加宏定义
cmake . #生成Makefile文件

#自动添加
file(GLOB_RECURSE SOURCES "src/*.cpp" "src2/func.*") #自动将src目录下.cpp以及src2目录下名为func的文件加入到项目中 记为SOURCES(可改名)
add_executable(main ${SOURCES})
FILE(GLOB HEAD_FILES "./*.h")#查找设置当前文件夹中所有的头文件

#添加编译选项
add_compile_options(-g -Wunused) #给后续的目标加上编译选项(调试、警告)
target_compile_options(main PUBLIC -Wall) #给指定目标加上编译选项

#多目标编译 生成多个可执行文件
{add_executable(main ${SOURCES} main.cpp)
add_executable(main1 ${SOURCES} main.cpp1)
add_executable(main2 ${SOURCES} main.cpp2)}(没有{})

#编译器
# linux平台的GCC编译器
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    message(STATUS "is gcc")
# Windows平台的MSVC编译器
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
message(STATUS "编译器是msvc")
# MacOS平台的Clang编译器
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang")
message(STATUS "编译器是AppleClang")
endif()

#Qt
set(CMAKE_AUTOMOC ON)#打开全局moc,设置自动生成moc文件
set(CMAKE_AUTOUIC ON) #打开全局uic
set(CMAKE_AUTORCC ON) #打开全局rcc
#查找需要的Qt库文件{
find_package(Qt5Widgets REQUIRED) 
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)}
FILE(GLOB UI_FILES "./*.ui")#查找设置当前文件夹中所有的ui文件
qt5_wrap_ui(WRAP_FILES ${UI_FILES}) #通过Ui文件生成对应的头文件
set(RCC_FILES rcc.qrc) #添加资源文件
add_executable(${PROJECT_NAME} ${SRC_FILES} ${HEAD_FILES} ${RCC_FILES} ${WRAP_FILES})#创建工程文件
target_link_libraries(${PROJECT_NAME} Qt5::Widgets Qt5::Core Qt5::Gui) #添加Qt5依赖项

#第三方库
set(QT_CMAKE_PATH "D:/iQT/5.14.2/msvc2017_64/lib/cmake")
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${QT_CMAKE_PATH})
set(CMAKE_PREFIX_PATH "path/to/your/opencv")#在指定的路径中查找库
find_package(OpenCV REQUIRED)
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})#链接

#编译
set(MUL_SOURCES ./mul/mul.cpp) #引用
add_library(mul STATIC ${MUL_SOURCES})#指定从某些源文件创建静态库
add_library(mul SHARED ${MUL_SOURCES})#指定从某些源文件创建动态库

#链接main.cpp中#include "mul.h"
link_directories(D:/lib) #链接库目录到所有目标
link_libraries(mul) #链接库名称到所有目标
target_link_directories(main PUBLIC ./) #链接库目录到指定目标
target_link_libraries(main mul) #链接库名称到指定目标

```

## Makefile

M/makefile：

一个规则 两个函数 三个自动变量 模式规则 静态模式规则 伪目标

### *一个规则

目标：依赖条件

(一个tab缩进)命令

