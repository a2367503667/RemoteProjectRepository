#define _CRT_SECURE_NO_WARNINGS
#include <iostream>


class Maker
{
public:
	// 按照参数类型分：有参和无参函数
	Maker() // 无参
	{
		std::cout << "无参构造函数" << std::endl;
	}
	Maker(int a) // 有参
	{
		std::cout << "有参构造函数" << std::endl;
		this->a = a;
	}

	// 按类型分：普通构造函数和拷贝构造函数
	Maker(const Maker& m)
	{
		std::cout << "拷贝构造函数" << std::endl;
	}
	Maker(double b)
	{
		std::cout << "普通构造函数" << std::endl;
		this->b = b;
	}
	/*
	
	Maker()
	{
		std::cout << "普通构造函数" << std::endl;
	}

	*/

	// 还有一个默认的赋值函数，后面可以学

private:
	int a;
	double b;
};

void test01()
{
	// 1、无参构造函数
	Maker m1;

	// 2、有参构造函数
	Maker m2(10);

	// 3、拷贝构造函数
	Maker m3(m1);


	// 4和5这两种方式很少用
	// 4、拷贝构造函数
	Maker m4 = m2;

	// 5、有参构造函数，这个调用方式其实就是相当于m5(10)
	Maker m5 = Maker(10);

	// 6、有参构造函数，相当于Maker m6 = Maker(10);那就是和5一样了
	Maker m6 = 10;

	// 7、这个是调用无参构造函数，因为在初始化的使用就调用构造函数
	Maker m7;
	// 而m7 = m6; 是属于赋值操作，也就是说，前面m7就已经存在了，所以下面的赋值操作是不会去调用构造函数的
	// 和Maker m7 = m6; 这种情况不同，因为此时还没有m7对象，需要用构造函数构造出来，因此才会调用拷贝构造函数
	m7 = m6;
}



int main()
{
	test01();

	return 0;
}
