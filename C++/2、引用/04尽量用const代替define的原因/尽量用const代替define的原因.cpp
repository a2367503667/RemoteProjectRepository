#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
#define MY_NUM 128
const short my_num = 128;

// 注：下面两个函数属于函数重载
void func(short my_short)
{
	cout << "func(short my_short)" << endl;
}

void func(int my_int)
{
	cout << "func(int my_int)" << endl;
}

#define c 30
void test01()
{
	// define不管是在函数里面还是外面，都能够给文件中任何地方使用，也就是说没有作用域的限制
	#define b 20
	const int a = 80; // 这个只能在本函数中使用
	cout << "a = " << a << endl;
}

int main()
{
	// 1、const作为常量可以指定类型，而define不能指定类型，下面可以验证：
	// 调用的是参数为int类型的函数，也就意味着调不了short参数的函数
	func(MY_NUM); 
	// 而const定义的变量就可以指定类型(上面已经定义了const short类型变量)，如：
	// 这个就可以调用short参数类型的函数，如果想调用int的也可以定义一个const int my_num = 128;
	// 因此const作常量就可以指定类型，而define不能指定类型
	func(my_num);

	// 2、const修饰的变量作为常量有作用域限制，而define作为常量没有作用域限制(不重视作用域)
	cout << "b = " << b << endl;
	cout << "c = " << c << endl;
	test01();


	return 0;
}
