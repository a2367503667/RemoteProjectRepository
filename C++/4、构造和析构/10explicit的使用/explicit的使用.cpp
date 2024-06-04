#define _CRT_SECURE_NO_WARNINGS
#include <iostream>


/*
	explicit的作用：在C++Basis03的第4个小项目中，有一个赋值是Maker m6 = 10;的操作
					但是我们知道Maker不是一个整型，是一个Maker类，这样赋值很容易给别人
					带来误解，提高了代码的阅读难度，所以我们使用explicit关键字来解决这个问题
*/


// explicit这个关键字只能放在构造函数前面
class Maker
{
public:
	explicit Maker(int m)// 防止编译器优化Maker m = 10;这种格式
	{

	}
};

void test01()
{
	// 如果还没在Maker构造函数前面加explicit的话，是没有问题的，但是加了之后，运行就会报错
	// Maker m = 10;
}

int main()
{
	test01();


	return 0;
}
