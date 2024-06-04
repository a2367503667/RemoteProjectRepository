#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

// 注：在VS中是没有正在的检验的
// 在VS这样写是会报warning的，但是程序还是能够正常运行，但是在QT里面就会报错
// 在函数签名后面写上"throw(int, char)"就是异常接口声明，表示只能抛出这些异常(但是在VS中无效
// 在QT中有效)
int func01(int a, int b)throw(int, char)
{
	if (b == 0)
	{
		throw - 1;
		//throw 'a';
		//throw 3.14;
	}
	return a / b;
}

void test01()
{
	int a = 10;
	int b = 0;

	try
	{
		func01(a, b);
	}
	catch (double)
	{
		std::cout << "接收一个double类型的异常" << std::endl;
	}
	catch (int)
	{
		std::cout << "接收一个int类型的异常" << std::endl;
	}
	catch (char)
	{
		std::cout << "接收一个char类型的异常" << std::endl;
	}
	catch (...)
	{
		std::cout << "接收一个其他类型的异常" << std::endl;
	}

}



int main()
{


	return 0;
}
