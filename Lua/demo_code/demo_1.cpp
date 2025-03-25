#include <iostream>
#include <string>
#include <lua.hpp>
#include "test.h"

// ------------------  一个需要注册到lua虚拟机中的cpp类 --------------
class MyTest
{
public:
    int m_a;
    float m_b;
    const int m_c;
    static int m_d;
    std::string m_s;
    MyTest() : m_c(100) { std::cout << "MyTest no args constructor" << std::endl; }
    MyTest(int a, float b, int c) : m_a(a), m_b(b), m_c(c)
    {
        std::cout << "MyTest constructor" << std::endl;
    }

    ~MyTest()
    {
        std::cout << "MyTest destructor" << std::endl;
    }

    std::string My_Print(std::string s)
    {
        std::cout << s << std::endl;
        return s;
    }

    int getA()
    {
        return m_a;
    }
};

// ------------------ 胶水代码 ------------------------
struct MyTestWrapper
{ // 用于包装 MyTest 对象的 userdata 结构体
    MyTest *ptr;
};

// Constructor
int MyTest_constructor(lua_State *L)
{
    int numArgs = lua_gettop(L); // 获取参数的数量以重载，但是对于参数类型顺序不同而发生的重载不能处理
    if (numArgs == 0)
    {
        MyTestWrapper *w = (MyTestWrapper *)lua_newuserdata(L, sizeof(MyTestWrapper)); // 创建了一个新的 Lua 用户数据对象并返回，同时将对象推入栈顶
        w->ptr = new MyTest();
        luaL_getmetatable(L, "MyTest"); // 从 Lua 状态机中获取名为 MyTest 的 metatable，成功会将它推入栈顶
        lua_setmetatable(L, -2);        // 将刚入栈顶栈顶元表设置为栈顶下第二个元素，即当前对象，的元表
    }
    else if (numArgs == 3)
    {
        int a = luaL_checkinteger(L, 1);
        float b = luaL_checknumber(L, 2);
        int c = luaL_checkinteger(L, 3);
        
        MyTestWrapper *w = (MyTestWrapper *)lua_newuserdata(L, sizeof(MyTestWrapper));
        w->ptr = new MyTest(a, b, c);
        luaL_getmetatable(L, "MyTest");
        lua_setmetatable(L, -2);
    }
    else
    {
        luaL_argerror(L, 1, "MyTest constructor expects 0 or 3 arguments");
    }
    return 1;
}

// Destructor
int MyTest_destructor(lua_State *L)
{
    MyTestWrapper *w = (MyTestWrapper *)luaL_checkudata(L, 1, "MyTest");
    delete w->ptr;
    return 0;
}

// My_Print method
int MyTest_My_Print(lua_State *L)
{
    MyTestWrapper *w = (MyTestWrapper *)luaL_checkudata(L, 1, "MyTest");
    const char *s = luaL_checkstring(L, 2);

    std::string result = w->ptr->My_Print(s);
    lua_pushstring(L, result.c_str());
    return 1;
}

// getA method
int MyTest_getA(lua_State *L)
{
    MyTestWrapper *w = (MyTestWrapper *)luaL_checkudata(L, 1, "MyTest"); // 获取名为MyTest的用户对象，成功会将它推入栈顶
    lua_pushinteger(L, w->ptr->getA());
    return 1;
}

// Index 函数，用于处理成员变量的访问
int MyTest_index(lua_State *L)
{
    // 从 Lua 栈中获取 MyTestWrapper 类型的 userdata
    MyTestWrapper *w = (MyTestWrapper *)luaL_checkudata(L, 1, "MyTest");
    const char *key = luaL_checkstring(L, 2); // 获取要访问的键
    // 根据键查找对应的成员变量或方法
    if (strcmp(key, "getA") == 0)
    {
        lua_pushcfunction(L, MyTest_getA);
    }
    else if (strcmp(key, "My_Print") == 0)
    {
        lua_pushcfunction(L, MyTest_My_Print);
    }
    else if (strcmp(key, "m_a") == 0)
    {
        lua_pushinteger(L, w->ptr->m_a);
    }
    else if (strcmp(key, "m_b") == 0)
    {
        lua_pushnumber(L, w->ptr->m_b);
    }
    else if (strcmp(key, "m_c") == 0)
    {
        lua_pushnumber(L, w->ptr->m_c);
    }
    else if (strcmp(key, "m_s") == 0)
    {
        lua_pushstring(L, w->ptr->m_s.c_str());
    }
    else
    {
        lua_pushnil(L);
    }

    return 1;
}

// Newindex 函数，用于处理成员变量的修改
int MyTest_newindex(lua_State *L)
{
    MyTestWrapper *w = (MyTestWrapper *)luaL_checkudata(L, 1, "MyTest");
    const char *key = luaL_checkstring(L, 2);

    if (strcmp(key, "m_a") == 0)
    {
        w->ptr->m_a = luaL_checkinteger(L, 3);
    }
    else if (strcmp(key, "m_b") == 0)
    {
        w->ptr->m_b = luaL_checknumber(L, 3);
    }
    else if (strcmp(key, "m_s") == 0)
    {
        w->ptr->m_s = luaL_checkstring(L, 3);
    }
    else
    { // 如果键不是可修改的成员变量，则抛出错误
        luaL_error(L, "Attempt to assign to readonly property '%s'", key);
    }

    return 0;
}

int luaopen_MyTest(lua_State *L)
{ // 注册 MyTest 类

    luaL_newmetatable(L, "MyTest"); // 创建 MyTest 类的 metatable

    // 设置析构函数
    lua_pushcfunction(L, MyTest_destructor);
    lua_setfield(L, -2, "__gc");
    // 设置 __index 函数
    lua_pushcfunction(L, MyTest_index);
    lua_setfield(L, -2, "__index");
    // 设置 __newindex 函数
    lua_pushcfunction(L, MyTest_newindex);
    lua_setfield(L, -2, "__newindex");

    // 创建一个全局表，绑定 MyTest 构造函数
    lua_newtable(L);                          // 创建一个空表
    lua_pushcfunction(L, MyTest_constructor); // 推送构造函数
    lua_setfield(L, -2, "new");               // 绑定构造函数到 'new' 字段
    lua_setglobal(L, "MyTest");               // 设置全局表 'MyTest'

    return 1;
}

int main()
{
    lua_State *L = luaL_newstate(); // 创建 Lua 状态机
    luaL_openlibs(L);               // 加载标准库

    luaopen_MyTest(L); // 注册 MyTest 类

    // luaL_dofile(L, "lua.lua");
    //--------- lua虚拟机中调用cpp--------
    if (luaL_dostring(L, R"lua(
        local obj = MyTest.new(10, 3.14, 5)
        local obj2 = MyTest.new()
        print(obj:getA())
        print(obj.m_b)
        print(obj.m_c)
        print(obj2.m_c)
        print(obj.m_c)
        obj.m_a = 100
        print(obj.m_a)
        obj.m_s = "Hello World"
        print(obj.m_s)
        print(obj:My_Print("Hello Lua"))
        obj.m_c = 404 -- const 不能修改，抛出错误   
        )lua"))
    {
        std::cerr << "Error executing Lua code: " << lua_tostring(L, -1) << std::endl;
        lua_pop(L, 1); // Pop error message from stack
    }

    lua_close(L); // 关闭 Lua 状态机
    return 0;
}

//---------------使用sol2将c++代码注册到lua中
int main() {
     // 创建 sol 状态
    sol::state sol_state;
    // 打开 Lua 基础库
    sol_state.open_libraries(sol::lib::base);
    // 胶水代码
    sol::usertype<MyTest> usertype_mytest = sol_state.new_usertype<MyTest>(
        "MyTest",
        // 注册构造函数！！！
        sol::constructors<MyTest(), MyTest(int, float, int)>(),
        // 注册成员变量
        "m_a", &MyTest::m_a,
        "m_b", &MyTest::m_b,
        "m_c", &MyTest::m_c,
        "m_s", &MyTest::m_s,
        // 注册静态成员变量
        "m_d", &MyTest::m_d,
        // 注册成员函数
        "My_Print", &MyTest::My_Print,
        "getA", &MyTest::getA
    );
    // 定义 Lua 脚本
    const char* lua_script = R"lua(
        local obj = MyTest.new(10, 3.14, 5) -- 调用带参数的构造函数
        local obj2 = MyTest.new()           -- 调用无参构造函数
        print("obj:getA():", obj:getA())    -- 调用成员函数
        print("obj.m_b:", obj.m_b)          -- 访问成员变量
        print("obj.m_c:", obj.m_c)          -- 访问常量成员变量
        print("obj2.m_c:", obj2.m_c)        -- 访问另一个对象的常量成员变量
        obj.m_a = 100                       -- 修改成员变量
        print("obj.m_a after modification:", obj.m_a)
        obj.m_s = "Hello World"             -- 修改字符串成员变量
        print("obj.m_s:", obj.m_s)
        print("obj:My_Print('Hello Lua'):", obj:My_Print("Hello Lua")) -- 调用成员函数并打印返回值
    
        obj.m_c = 404 -- 尝试修改常量成员变量，会抛出错误
    )lua";
    // 加载并执行 Lua 脚本文件
    //sol_state.script_file("../a.lua");
    sol_state.script(lua_script);

    return 0;
}
