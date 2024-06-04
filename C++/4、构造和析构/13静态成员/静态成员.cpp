#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

class Maker
{
public:
	Maker()
	{
		// 会报错
		// 因为静态成员变量需要再类内声明，类外初始化
		// a = 20;
	}


public:
	// 1、生命周期是整个程序，作用域在本类中，用它也需要用对象的方式访问
	static int a; 
};

// 2、静态成员需要在类内声明，在类外初始化
int Maker::a = 100;

void test01()
{
	// 生命周期是整个程序，作用域是test01里面
	static int a = 0;
}

void test02()
{
	// 3、静态变量是属于类的，不是属于对象的，可以直接Maker::就可以使用
	std::cout << "Maker a = " << Maker::a << std::endl;
	Maker m;
	// 4、静态成员变量可以用类去访问，也可以用对象去访问
	std::cout << "static a = " << m.a << std::endl;
}


class Maker1
{
public:
	Maker1()
	{

	}

	Maker1(int a, int b)
	{

	}

	// 5、静态成员函数只能访问静态成员变量，不能访问普通成员变量(普通成员变量属于每一个对象)
	static void setA(int a)
	{
		a2 = a;
		std::cout << "a2 = " << a2 << std::endl;
		// a1 = a;  报错，因为静态函数只能访问静态成员，不能访问对象
	}

// 静态变量不管权限是private 还是public 都需要在类外初始化
public:
	int a1;
	static int a2;
};

// 初始化是一定要做的
int Maker1::a2 = 200;
void test03()
{
	Maker1::setA(300);
}

class Maker2 
{
public:
	static void func(int a)
	{
		a1 = a;
		std::cout << "a = " << a1 << std::endl;
	}

private:
	static int a1;

};

int Maker2::a1 = 250;

void test04()
{
	Maker2::func(500);
	// 下面这句会报错，因为a1是私有成员，它只能够在类外初始化一次，但是不能够被类外使用，因为权限是私有的
	// Maker2::a1 = 800;

}

// const修饰的静态成员变量最好在类内初始化
// 因为这个值都不打算改了，也就是说都算是一个常量了，所以定义出来倒不如直接初始化
// 免得到时候再去初始化
class Maker3
{
public:
	void func() 
	{
		std::cout << "a = " << a << std::endl;
		std::cout << "b = " << b << std::endl;
	}

//这里也是一样的道理，不管是private还是public，都可以在外面初始化(只要是静态变量就行)
private:
	// 可以在类内初始化(最好)
	const static int a = 800;
	const static int b;
};

// 也可以在类外也可以初始化
const int Maker3::b = 666;

void test05()
{
	Maker3 m1;
	m1.func();

}

int main()
{
	test05();

	return 0;
}
