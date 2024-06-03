#pragma once
#include <stdio.h>

// void func();  声明就这样写是不行的
// 需要一下这样写，才可以解决编译名字不匹配问题
// 这个代码的意思是告诉C++编译器，找下面代码的函数，要以C语言的方式去寻找
// 并且告诉C++要用C语言的方式去编译和链接，而不是用C++的方式去编译和链接

/*
*我们分析一下下面选择性编译的意思：
* #ifdef __cplusplus  // 如果定义类这个宏(这个宏在C++中早已经定义了)
* (就执行这个区间的代码) #ifdef - #endif 之间的代码包括下面的{
* #endif
* 
* 同样道理
* #ifdef __cplusplus
* (执行这个区间的代码) }
* #endif
* 
* 目的：想这个函数声明在C语言和C++语言中都可以用
* 假如在C语言用这个头文件，没有__cplusplus这个宏，就会直接执行void func();这行代码
* 假如在C++用这个头文件，就有__cplusplus这个宏，那就会直接执行extern "C"{ void func(); }这个代码
* 所以这样写的好处就是让这个头文件在C/C++都兼容
*/

#ifdef __cplusplus
extern "C"
{
#endif
	void func(); // 这个是C语言的声明

#ifdef __cplusplus
}
#endif
