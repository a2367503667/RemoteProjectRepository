#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "MyArray.h"

/*
	我们对于普通变量的一级指针或者数组，可以使用[]运算符获取对应值的元素，但是对于自定义类
	来说就不行，如果我们想要用，这时就需要重载[]运算符

	这里我们直接使用上次数组类的设计代码即可，但是需要进行一些改进
*/

void test01()
{
	MyArray arr;
	int size = 20;

	for (int i = 0; i < size; ++i)
	{
		arr[i] = i + 100;
	}

	arr[8] = 1008;

	int mSize = arr.getSize();
	std::cout << "mSize = " << mSize << std::endl;

	arr.printArray();
}



int main()
{
	test01();

	return 0;
}
