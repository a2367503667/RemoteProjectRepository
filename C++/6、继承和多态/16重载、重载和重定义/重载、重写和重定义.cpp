#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

/*
	1、重载：
		(1)同一个作用域中；
		(2)"参数个数"、"参数类型"和"参数数量不同"；
		(3)和函数的返回值没有关系；
		(4)const也可以作为重载的条件，如：func(const int a); 与 func(int a)视为重载。

	2、重定义(即是之前说的子类隐藏父类函数的情况)：
		(1)有继承；
		(2)子类(派生类)重新定义父类(基类)的同名成员(非virtual函数)。

	3、重写(属于子类覆盖掉父类的情况)：
		(1)有继承；
		(2)子类(派生类)重写父类(基类)的virtual函数；
		(3)"函数返回值"、"函数名"以及"函数参数"必须和父类(基类)完全一致。

*/

class Father
{
public:
	virtual void work()
	{
		std::cout << "在公司上班" << std::endl;
	}

	// 1、func()和func(int a)视为重载
	void func()
	{
		std::cout << "Father func()" << std::endl;
	}

	void func(int a)
	{
		std::cout << "Father func(int a)" << std::endl;
	}

};

class Son :public Father
{
public:

	// 2、重写父类函数work()
	virtual void work()
	{
		std::cout << "在学校上学" << std::endl;
	}

	// 3、重定义父类的函数func()
	// 也就是说，子类会隐藏掉父类中所有名为func的函数
	void func()
	{
		std::cout << "Son func()" << std::endl;
	}

};

int main()
{


	return 0;
}
