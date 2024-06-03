#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;


// 下面补充编译器不能优化的情况：
void test01()
{
	// 1、const int b = a;编译器不会优化结果 cout << "b = " << 10 << endl;
	int a = 10;
	const int b = a;
	// 如果上面那行写const int b = 10; 那么编译器就会在编译的时候优化代码
	// 这样做的话编译器就不能优化了，因为a在栈区，即在编译阶段编译器不清楚a是什么
	// 也就是说对于b = a来说，编译器不能识别a是什么，所以编译器不会优化
	int* p = (int*)&b;
	*p = 100;
	// 结果是b = 100
	cout << "b = " << b << endl;
	cout << "*p = " << *p << endl;
}

// 2、自定义数据类型，编译器不能优化
struct Maker
{
	Maker()
	{
		a = 100;
	}
	int a;
};

void test02()
{
	// 类实例化对象
	const Maker myA;
	cout << "myA =  " << myA.a << endl;
	Maker* p = (Maker*)&myA;
	p->a = 200;
	// 发觉这一段输出结果为：200，也就说明编译器没有做优化
	cout << "改：myA = " << myA.a << endl;
	cout << "p->a = " << p->a << endl;
}

int main()
{
	test02();

	return 0;
}
