#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

// 1、值传递
void swap01(int a,int b)
{
	int tmp = a;
	a = b;
	b = tmp;
}

// 2、指针传递
void swap02(int* a, int* b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

// 3、引用传递
void swap03(int& a, int& b)
{
	int tmp = a;
	a = b;
	b = tmp;
}

// 打印输出
void myPrint(int a, int b)
{
	cout << "a = " << a << endl << "b = " << b << endl;
}


int main()
{
	int a = 10;
	int b = 20;
	swap01(a, b); // 传过去只有a和b的值，结果没有变化
	myPrint(a, b); // 10 20 
	cout << "------------------" << endl;

	swap02(&a, &b); // 指针传递，传过去的是地址，可以根据地址修改a与b的值
	myPrint(a, b); // 20 10

	cout << "------------------" << endl;
	swap03(a, b); // 10 20 因为上面换成了20 10 ，而且引用也会改变a和b的值
	myPrint(a, b);


	return 0;
}
