#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

class Maker
{
public:
	// 如果没有写构造函数和析构函数，编译器会默认提供构造函数和析构函数
	/*
	// 相当于提供这两个函数，函数体都是空的
	Maker()
	{

	}
	~Maker()
	{

	}
	*/

	void setA(int a)
	{
		this->a = a;
	}
	int getA()
	{
		return this->a;
	}

private:
	int a;
};

void test01()
{
	Maker m;
	m.setA(10);
	std::cout << "a = " << m.getA() << std::endl;
}

int main02()
{
	test01();

	return 0;
}
