#pragma once
#include <glad/glad.h> // 包含glad来获取所有的必须OpenGL头文件

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
    Shader(const char* vertexPath, const char* fragmentPath);

    unsigned int ID;// 程序ID
    void use(); // 使用/激活程序
    // uniform工具函数
    void setBool(const std::string &name, bool value) const;  
    void setInt(const std::string &name, int value) const;   
    void setFloat(const std::string &name, float value) const;
private:
    //检查编译/链接错误
    void checkCompileErrors(unsigned int shader, const std::string& type);
};
