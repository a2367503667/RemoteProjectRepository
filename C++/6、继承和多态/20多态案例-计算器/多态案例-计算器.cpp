#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

class CalRule
{
public:
	virtual double getNum(double a, double b) = 0;
};

class AddRule :public CalRule
{
public:
	virtual double getNum(double a, double b)
	{
		return a + b;
	}
};

class SubRule :public CalRule
{
public:
	virtual double getNum(double a, double b)
	{
		return a - b;
	}
};

class MulRule :public CalRule
{
public:
	virtual double getNum(double a, double b)
	{
		return a * b;
	}
};

class DivRule :public CalRule
{
public:
	virtual double getNum(double a, double b)
	{
		if (b == 0)
		{
			std::cout << "除数不能为0" << std::endl;
			return -1;
		}
		return a / b;
	}
};

void test01()
{
	CalRule* r = nullptr;

	// 加
	r = new AddRule;
	std::cout << "add = " << r->getNum(10, 20) << std::endl;
	delete r;
	
	// 减
	r = new SubRule;
	std::cout << "sub = " << r->getNum(10, 20) << std::endl;
	delete r;

	// 乘
	r = new MulRule;
	std::cout << "mul = " << r->getNum(10, 20) << std::endl;
	delete r;

	// 除
	r = new DivRule;
	std::cout << "div = " << r->getNum(10, 20) << std::endl;
	delete r;

	r = new DivRule;
	std::cout << "div = " << r->getNum(10, 0) << std::endl;
	delete r;
	r = nullptr;
}


int main()
{
	test01();

	return 0;
}
