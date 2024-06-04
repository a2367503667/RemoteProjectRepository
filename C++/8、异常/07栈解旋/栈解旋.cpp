#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

/*
	栈解旋：所谓栈解旋就是我们在函数中有异常需要抛出，因为在抛出异常后，当前函数需要开辟的空间就要
			被释放掉，那之前我们创建的对象和栈中的数据都不再有用，这时就会调用相应的析构函数对其
			进行释放，结束当前函数，把异常数据抛出到上一层函数

			如：下面func01中有a和m两个局部变量，其中m是对象，当我们需要抛出异常时，throw前面的变量
			就不具有意义，都会被释放掉，此时就会调用m对象相应的析构函数提前释放(这个就是栈解旋)，当
			throw到上层函数后，func01函数和里面的变量就会被释放掉

*/


class Maker
{
public:
	Maker()
	{
		std::cout << "Maker构造函数" << std::endl;
	}

	Maker(const Maker& m)
	{
		std::cout << "Maker拷贝构造函数" << std::endl;
	}

	~Maker()
	{
		std::cout << "Maker析构函数" << std::endl;
	}
};

void func01()
{
	int a = 10;
	Maker m; // 调用一次构造函数(1)

	// 需要注意的是，这里调用了拷贝构造函数

	// 在throw时 (1)中的m被调用析构函数
	throw m; // 调用一次拷贝构造函数(2) 在throw后(2)中的m调用了一次析构函数

	// 需要注意一点就是，这里的throw下面的变量都不具有空间，因为在throw对象m后这个函数就结束了
	// 因此还没分配好空间
	int b = 20;
	double d = 30;
}

void test01()
{
	try
	{
		func01();
	}
	catch (Maker m) // 这个调用了拷贝构造函数  在处理异常结束后就调用析构函数
	{
		std::cout << "接收一个Maker类型的异常" << std::endl;
	}
	catch (...)
	{
		std::cout << "接收一个其他类型的异常" << std::endl;
	}
}


int main()
{
	test01();


	return 0;
}
