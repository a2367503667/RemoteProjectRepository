#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

/*
	在vs2013版本下，debug返回对象的话会是不同的两个对象，其中主调函数和被调函数结束都会去调用析构函数
	且被调函数对象返回给主调函数对象时，相当于拷贝了数据，也就是会调用拷贝构造函数；

	release返回对象的话，出于节省内存，被调函数结束后不会去调用析构函数释放对象，而是返回同一个对象
	给主调函数，此时主调函数并没有创建对象，并且被调函数的m与主调函数的m1是同一个对象，因此也就只会调取
	一个析构函数(也就是主调函数结束时会去调用析构函数)
*/


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

// 1、对象以值的方式给函数参数
void func(Maker m) // 之所以会调用拷贝构造函数，是因为这里做了一个操作Maker m = m1;(也会转化为Maker m(m1);)
{

}


void test01()
{
	// 调用无参构造函数
	Maker m1;
	// 调用拷贝构造函数
	func(m1);
}

// 2、用一个已有的对象去初始化另一个对象
void test02()
{
	Maker m1;
	Maker m2(m1);
}

// 3、函数的局部对象以值的方式从函数返回(也就是说返回一个对象)
// 在vs2022版本中，使用debug和release都是返回同一个对象
// 也就是说，func02发现你返回一个对象，为了节省空间就不会帮你释放掉这个m
// 直接把m返回到test03的m1，也就是说不会调用拷贝构造函数，也不会在func02函数中调用析构函数(因为m还没释放)
// 结果m1的地址和m的地址是一样的，即这两个是同一个对象，也就说明了，test03中的m1并没有创建对象
Maker func02()
{
	// 局部对象
	Maker m;
	std::cout << "局部对象m的地址：" << &m << std::endl;
	return m;
}

void test03()
{
	Maker m1 = func02();
	std::cout << "m1对象的地址：" << &m1 << std::endl;
}



int main()
{
	// test01();
	// test02();
	test03();


	return 0;
}
