#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;



// 引用本质上是一个常指针，例如：
// type &ref = val; ->  type* const ref = &val;
// 下面给出相应代码：
// int a = 10;
// int &aRef = a; 自动转换为 int* const aRef = &a; 也就是说aRef这个值本身没有办法改，并且也必须要初始化(常量必须初始化)
// aRef = 20;  本质上就是 *aRef = 20;  这样操作就使得a的值变为20了
// 

// 这个函数辨别指针常量和常量指针
void test01()
{
	int x;
	int const* y = &x; // 指向常量的指针(常量指针)
	const int* k = &x; // 指向常量的指针(常量指针)
	int* const z = &x; // 指针类型的常量(指针常量)

	// 为什么？
	// 其实区分很简单，我们以*为分割线，看const离谁近就是修饰谁
	// 第一个和第二个const离int近，则是修饰int，那就是int不能改，也就是指向常量的指针
	// 也就没办法改变指针指向那个常量的值，也就是常量指针(即*y = a会报错)
	// 第三个const离z比较近，也就是修饰指针的，因为z本质上就是一个指针，那就是指针类型的常量
	// 也就是指针常量(即z = &a会报错)

	// 或者也能够将const int *y与int const *k中的(*y)和(*k)看成一个整体，也就是说*y和*k是常量
	// 而对于z来说没有旁边没有*，那就是z这个指针本身是常量
	int a;
	y = &a; // *y = a; err
	k = &a; // *k = a; err
	*z = a; // z = &a; err
}


int main()
{

	// 注意：const int 与 int不是同一个数据类型，因此下面指针赋值会直接报错
	// const int a = 20;
	// int* p = &a; // 硬是要赋值就需要强转为 int *p = (int *)&a;
	int arr[] = { 1,2,3,4,5 };

	// 如何建立数组的引用？
	// 第一种方法：
	// 1、先定义数组类型
	typedef int(MY_ARR)[5]; // 定义数组类型
	// 2、后建立引用
	MY_ARR& arrRef = arr; // 建立引用，相当于 int &b = a;

	// 第二种方法
	// 直接定义引用
	// 注意：[]里面的数值要与原数组匹配，要不然会报错
	int(&arrRef1)[5] = arr;  // 也相当于 int &b = a;

	// 第三种方法
	typedef int(&MY_ARR1)[5]; // 建立引用数组类型
	MY_ARR1 arrRef2 = arr;

	for (int i = 0; i < 5; i++)
	{
		cout << arrRef[i] << endl;
	}
	cout << "--------------------" << endl;

	for (int i = 0; i < 5; i++)
	{
		arrRef1[i] = 100 + i;
		cout << arrRef1[i] << endl;
	}
	cout << "--------------------" << endl;

	for (int i = 0; i < 5; i++)
	{
		arrRef2[i] = 200 + i;
		cout << arrRef2[i] << endl;
	}



	return 0;
}
