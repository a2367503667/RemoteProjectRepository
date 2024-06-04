#define _CRT_SECURE_NO_WARNINGS
#include <iostream>


// 1、空类的大小是1，不是0
class Maker1
{

};

void test01()
{
	std::cout << "sizeof(Maker1) = " << sizeof Maker1 << std::endl; // 结果是1
	
	// 因为如果是0的话，我们动态申请空间无法分配空间
	Maker1* m = new Maker1[20];

	delete[] m;
	m = nullptr;
}
// ----------------------------

// 2、成员函数、静态成员(变量和函数)均不占用类的大小
class Maker2
{
public:
	// 普通成员函数
	void fun01()
	{

	}

	// 静态成员函数
	static void fun02()
	{

	}

private:

	// 静态成员变量
	static int a;
};
int Maker2::a = 100;

void test02()
{
	std::cout << "sizeof(Maker2) = " << sizeof Maker2 << std::endl; //结果是1
}
// -------------------------------

// 3、为什么在类里面，我们不传参数，也可以直接访问成员变量
class Maker3
{
public:

	// 这里我们明明没有传入参数，但是可以使用a和b，这是为什么？
	// 其实已经传入参数了，只是编译器进行了优化
	// 本质的代码如下：
	/*
		其中pThis指针是指向这个类的对象的成员变量的(也可以说指向本对象)
		void func01(Maker3* pThis)
		{
			pThis->a = 10;
			pThis->b = 20;
			std::cout << "a = " << a << " " << "b = " << b << std::endl;
		}

		如：我们在实例化对象后有Maker3 m;
		则pThis指着就是指向m(pThis == &m)，也就是说我们通过这个指针就可以访问对象的成员
		而pThis在我们的用法里是this，也就是之后我们写代码可以用this代指本对象
	*/
	void func01()
	{
		a = 10;
		b = 20;
		std::cout << "a = " << a << " " << "b = " << b << std::endl;
	}

private:
	int a;
	int b;
};


int main()
{
	// test01();
	test02();


	return 0;
}
