#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

/*
	其实异常的多态就是我们将catch中的匹配类型改成父类，而我们在被调函数throw的子类就可以直接
	被catch匹配到，这样我们就可以一个匹配类型Father，就可以接受很多个Son的信息，提高代码的复用
	和代码的解耦合，也可以使得程序可以处理更多类型的异常情况
*/

class Father
{
public:
	virtual void printMes() = 0;
public:
	int a = 10;
	int b = 20;
};

class Son1 :public Father
{
public:
	virtual void printMes()override
	{
		std::cout << "Son1处理异常" << std::endl;
		std::cout << "Son1：" << "a = " << this->a << "，b = " << this->b << std::endl;
	}
};

class Son2 :public Father
{
public:
	virtual void printMes()override
	{
		std::cout << "Son2处理异常" << std::endl;
		std::cout << "Son2：" << "a = " << this->a << "，b = " << this->b << std::endl;
	}
};

class Son3 :public Father
{
public:
	virtual void printMes()override
	{
		std::cout << "Son3处理异常" << std::endl;
		std::cout << "Son3：" << "a = " << this->a << "，b = " << this->b << std::endl;
	}
};


void func01()
{
	throw Son1();
}

void func02()
{
	throw Son2();
}

void func03()
{
	throw Son3();
}

void test01()
{
	try
	{
		func01();
	}
	catch (Father& fa)
	{
		fa.printMes();
	}
}

void test02()
{
	try
	{
		func02();
	}
	catch (Father& fa)
	{
		fa.printMes();
	}
}

void test03()
{
	try
	{
		func03();
	}
	catch (Father& fa)
	{
		fa.printMes();
	}
}

int main()
{
	// 对于不同的测试，只是try里面调用的函数不同，而catch中的代码是相同的
	test01();
	std::cout << "------------------------" << std::endl;
	test02();
	std::cout << "------------------------" << std::endl;
	test03();


	return 0;
}
