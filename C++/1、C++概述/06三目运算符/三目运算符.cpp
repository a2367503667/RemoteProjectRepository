#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
using namespace std;

void test01()
{
	int a = 10;
	int b = 20;
	// 从这可以看出C++返回的是左值，是空间，可以修改
	(a > b ? a : b) = 100;
	cout << "a = " << a << endl;
	cout << "b = " << b << endl;
}

int main()
{
	test01();

	return 0;
}
