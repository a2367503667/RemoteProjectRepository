#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

// 自定义的数据类型(自定义类型时不分配空间)
struct Maker1
{
	char name[32];
	int age;
};

// 加强一：结构体定义变量时，不需要写struct了
void test01()
{
	// 此时才会分配空间
	// 在C++中，不需要写struct了，C语言要
	Maker1 a1;

}

// 加强二：结构体内部可以写函数

struct Maker2
{
	int a;
	void func()
	{
		cout << "func" << endl;
	}
};


void test02()
{
	Maker2 a2;
	// 访问也是用点的方法(.)
	a2.func();
}


int main()
{
	test02();

	return 0;
}
