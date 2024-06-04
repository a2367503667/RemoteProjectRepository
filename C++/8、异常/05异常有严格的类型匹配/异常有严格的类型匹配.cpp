#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

int func01(int a, int b)
{
	if (b == 0)
	{
		// 需要注意的是，异常有严格的类型匹配，它是不能进行类型转换的
		// throw 'a';
		// throw 3.14;
		// throw 3;
		throw "abc";
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
	catch (int)
	{
		std::cout << "接收一int类型的异常" << std::endl;
	}
	catch(char)
	{
		std::cout << "接收一个char类型的异常" << std::endl;
	}
	catch (double)
	{
		std::cout << "接收一个double类型的异常" << std::endl;
	}
	// 但是异常的处理类型有很多种的，我们没办法把它们全部列出来，那这样怎么办？
	catch (...) // 可以使用"..."表示其他类型(只要上面都匹配不了都进这里来匹配)
	{
		std::cout << "接收一个其他类型的异常" << std::endl;
	}

}


int main()
{
	test01();

	return 0;
}
