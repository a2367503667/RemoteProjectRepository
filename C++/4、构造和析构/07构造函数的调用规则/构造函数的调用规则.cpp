#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

class Maker
{
public:
	Maker()
	{
		std::cout << "无参构造函数" << std::endl;
	}
	Maker(int a)
	{
		std::cout << "有参构造函数" << std::endl;
	}
	Maker(const Maker& m)
	{
		std::cout << "拷贝构造函数" << std::endl;
	}
	~Maker()
	{
		std::cout << "析构函数" << std::endl;
	}
};

// 1、如果自己提供了有参构造函数，编译器就不会提供无参构造函数
void test01()
{
	// 如果有提供有参构造函数，自己又没有写无参构造函数，下面这句话就会报错
	// Maker m;

	Maker m(10);
	// 编译器会提供了默认的拷贝构造
	Maker m1(m);


}

// 2、如果自己提供了拷贝构造函数，编译器就不会提供默认构造函数
void test02()
{
	// 如果自己写了拷贝构造函数，下面这行代码就会报错
	// Maker m;



}

int main()
{
	test01();

	return 0;
}
