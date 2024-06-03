#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

/*
* 1、类是自定义的数据类型，是C语言的结构体进化而成的；
* 2、对象是类实例化出来的，相当于数据类型定义一个变量
* 
*/


class Maker // Maker是类
{
public:
	int a; // 成员变量(成员属性)
	void func() // 成员方法(成员函数或成员行为)
	{
		cout << "func()" << endl;
	}
};

int main()
{
	Maker m; // m是对象



	return 0;
}
