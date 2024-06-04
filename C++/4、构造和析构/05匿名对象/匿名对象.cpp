#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

class Maker
{
public:
	// 无参构造函数
	Maker()
	{
		std::cout << "无参构造函数" << std::endl;
		this->a = 20;
	}
	// 有参构造函数
	Maker(int a)
	{
		std::cout << "有参构造函数" << std::endl;
		this->a = 3;
	}
	// 拷贝构造函数
	Maker(const Maker& m)
	{
		std::cout << "拷贝构造函数" << std::endl;
		this->a = m.a;
	}
	// 析构函数
	~Maker()
	{
		std::cout << "析构函数" << std::endl;
	}

private:
	int a;
};

void test01()
{
	/*
	我们发现下面结果是：

	无参构造函数
	析构函数
	test01函数结束
	*/
	// 因为匿名对象的生命周期在当前行
	Maker();
	// 这个也是当前行
	Maker(10);
	std::cout << "test01函数结束" << std::endl;

	// 注意：如果匿名对象有名字来接，就不是匿名对象了，下面那个就不是了
	/*
		我们发现输出结果为：

		无参构造函数
		test01函数结束
		析构函数
	*/
	// 这样就说明了，下面那个语句中对象m1就不是匿名对象了，且生命周期也不是当前行，而是到test01函数结束
	Maker m1 = Maker();
	std::cout << "test01函数结束" << std::endl;
}


int main()
{
	test01();

	return 0;
}
