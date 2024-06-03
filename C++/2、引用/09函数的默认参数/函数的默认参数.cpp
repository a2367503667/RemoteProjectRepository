#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
// #include "test.h"  直接复制函数头到test.h文件里面，如果函数体有默认参数，那么会出现报错


// int b = 0就是函数的默认参数
// 当然，b可以为其他值，不一定是0
int myFunc(int a, int b = 0)
{
	return a + b;
}

void test01()
{
	// 函数默认参数的作用
	// 当函数内常要用到形参的某个值，但偶尔要使用其他值
	cout << "myFunc(10,20) = " << myFunc(10, 20) << endl;
	// 当传入一个参数时，就会采取默认值，这样就会增加函数的灵活性
	cout << "myFunc(10) = " << myFunc(10) << endl;

}

// 函数参数的注意事项：
// 1、函数的默认参数后面的参数必须都是默认参数，例如下面这一行就会报错，因为b后面的参数没有给默认值
// 也就是说如果函数有默认参数，那函数的最右边的形参必须有默认参数
/*
改为：
int myFunc02(int a, int b = 0, int c = 2)(对)
int myFunc02(int a, int b = 0, int c)(错)
{

}
*/

// 2、函数的声明和实现不能同时有函数的默认参数
// 一般出现的问题在哪呢？
// 就是一般我们会把声明写在头文件里面，然后会顺手把函数头直接复制到头文件里面，然后没有注意函数体有
// 默认参数，此时就会出现编译报错的情况
// void myFunc03(int a, int b = 0);  有默认参数就会编译报错
void myFunc03(int a, int b); // 应改为这样
void myFunc03(int a, int b = 0)
{

}

// 函数的占位参数，没有形参的名字，当然，没有名字的话在函数体里面没办法用到这个值，因为没有名字
// 占位参数在后面的运算符重载时，区分前加加或后加加才有用(后面讲)
void func(int a, int)
{

}
// 占位形参也可以有默认值，即可以传一个也可以传两个参数
void func01(int a, int = 10)
{

}


void test02()
{
	// 会报错，因为要传两个参数
	// func(100);
	func(100, 20); // 这个才是正确用法
	func01(20); // 传一个参数
	func01(20, 80); // 传两个参数
}

// 默认参数和占位参数混搭
// 注：默认参数还是要在最右边，要不然就会报错
// void func02(int a = 20, int);  这个就会报错
void func02(int, int a = 20)
{


}

void test03()
{
	// 不传值不行，因为占位参数没有给默认值，至少给一个值
	// func02();  会报错

	func02(10); // 可以传一个值
	func02(20, 30); // 可以传两个值
}


int main()
{
	test01();

	return 0;
}
