#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;


// 1、引用的作用通常是作为函数参数来传递，这样更加节约空间
void func01(int& a, int& b)
{
	int sum = a + b;
	cout << "sum = " << sum << endl;

}

void test01()
{
	int a = 10;
	int b = 20;
	func01(a, b);
}

// 2、引用作为函数的返回值
// 这样是错误的写法，因为栈区的东西在使用后会被释放，返回的局部变量和引用都是已经被回收了
// 即使编译器通过了，但是也不能这么写，这个在以后的开发中会出现严重错误的
int& func02()
{
	int b = 10; // 不要返回局部变量的引用，其实本质上是返回它地址空间的东西(它的别名包括了空间的数据)
	int& p = b;
	return p;
}

// 静态局部变量是可以返回的
int& func03()
{
	// 这个调用多次不会改的原因是静态变量只会定义一次，有且只有一次
	// 在其他地方给他赋值，才会改变它的值，静态变量也可以作为返回值返回
	static int b = 10;
	return b;
}

// 接上面第二点的解释
void test02()
{
	int q = func02();
	cout << "q = " << q << endl;
	func02() = 200;
	cout << func02() << endl;
	// 上面代码都是错误的，只是编译器没有检查出来而已，不要返回局部变量的数据(包括指针、数值或者引用等)


	func03() = 100;
	cout << func03() << endl;
}

int main()
{
	// test01();
	test02();


	return 0;
}
