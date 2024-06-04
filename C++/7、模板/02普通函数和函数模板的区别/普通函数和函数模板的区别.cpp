#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

// 普通函数
int myAdd01(int a, int b)
{
	return a + b;
}

template<typename T>
int myAdd02(T a, T b)
{
	return a + b;
}

void test01()
{
	int a = 10;
	int b = 20;
	char c = 'c';

	// 1、普通函数可以进行隐式类型转换
	std::cout << "myAdd01 -> " << myAdd01(a, c) << std::endl;

	// 但是函数模板不行
	// std::cout << "myAdd02 -> " << myAdd02(a, c) << std::endl;
	// myAdd02(a, c); // err 因为编译器无法判别T到底是用int还是char

	// 要想进行隐式转换，必须给定参数列表(如：<int>)，否则会出现二义性报错
	std::cout << "myAdd02 -> " << myAdd02<int>(a, c) << std::endl;

}

int main()
{
	test01();



	return 0;
}
