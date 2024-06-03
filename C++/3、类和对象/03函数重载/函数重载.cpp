#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

// 函数重载是一种现象，允许函数名相同
// 在C语言中，会遇到某种困扰，就是函数没办法重载，但是如果我想写int加法又想写double加法怎么办？
// C++就提供了函数重载解决这个困扰，并且能够减少我们起什么函数名的烦恼如下：
int add(int a, int b)
{
	return a + b;
}

double add(double a, double b)
{
	return a + b;
}

// 函数重载的条件：1、同一个作用域；2、参数个数不同；3、参数的类型不同；4、参数的顺序不同 
// 下面会陆续举例：

// 1、参数的个数不同
void func() // 无参数
{
	cout << "func()" << endl;
}
void func(int a) // 1个参数
{
	cout << "func(int a)" << endl;
}

// 2、参数的类型不同
void func(char a)
{
	cout << "func(char a)" << endl;
}

// 3、参数的顺序不同
void func(int a, double e)
{
	cout << "func(int a, double e)" << endl;
}
void func(double e, int a)
{
	cout << "func(double e, int a)" << endl;
}

// 4、调用重载函数的注意：
// 1、严格的类型匹配，如果类型不匹配，那么尝试转换，转换成功就调用，失败就报错
void test01()
{
	int a = 10;
	double b = 3.14;
	// 啥都不传，就直接调用无参的函数
	func();

	// double转换不了int或char
	// func(b);  因为b是double类型，而没有参数是double类型的重载函数，那么编译器就会报错

	// 调用func(int,double)
	func(a, b);

	// 调用func(double,int)
	func(b, a);

	char c = 'c';
	// 把func(char a)注释掉都没有报错
	// 注释掉后调用了func(int a)函数
	// 也就是说char 转换成功int，调用了int类型的函数
	func(c);


}

// 函数重载和函数的默认参数一起使用，可能会出现二义性问题
void myFunc(int a, int b = 0)
{
	cout << "myFunc(int a, int b = 0)" << endl;
}

void myFunc(int a)
{
	cout << "myFunc(int a)" << endl;
}

void test02()
{
	// 这样编译器就会报错
	// 因为myFunc(int a, int b = 0)可以传一个参数，myFunc(int a)也可以传一个参数
	// 此时编译器无法选择哪个函数，因此就出现报错(二义性) 
	// myFunc(10);
}

// 函数返回值类型不作为重载的判断条件
// 因为函数我们使用时，我们只需要知道函数名和参数表即可，无需知道返回值类型
// 就好比如，func();编译器会根据函数名和形参表传进来的参数判断此函数是什么函数，不会去查看的返回值是什么
// 也因为我们调用函数时也不需要写返回值

int main02()
{
	test01();

	return 0;
}
