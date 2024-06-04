#define _CRT_SECURE_NO_WARNINGS
#include <iostream>


int func01(int a, int b)
{
	// 2、同样地，我们也先给出异常的判断条件
	if (b == 0)
	{
		// 3、抛出异常(抛出一个int类型的异常)
		throw - 1; // 只要这里写int类型的数据就是抛出int类型的异常

		// 在抛出异常之后，就会在"throw -1;"这个位置跳出函数
		// 不会往下执行"std::cout << "往下执行" << std::endl;"这行代码
		std::cout << "往下执行" << std::endl;
	}
	return a / b;
}

void test01()
{
	int a = 10;
	int b = 20;
	
	// 1、把有可能出现异常的代码块写到try作用域当中
	try
	{
		func01(a, b);

		// 注：如果有异常的话，就会在"func01(a, b);"的位置跳转到catch的位置
		// 不会往下执行"std::cout << "throw后的代码" << std::endl;"这行代码
		// 但是如果没有异常的话，下面这行代码会被执行
		std::cout << "throw后的代码" << std::endl;
	}
	catch (int)	// 4、接收一个int类型的异常
	{
		// 5、在catch作用域内进行异常处理
		std::cout << "除数不能为0" << std::endl;
	}

}




int main()
{
	test01();

	return 0;
}
