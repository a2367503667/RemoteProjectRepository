#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

// 1、用this指针访问类的成员
class Maker1
{
public:
	Maker1()
	{
		// 这里可以直接给a和b赋值，是因为这个构造函数传进来一个this指针，然后通过
		// this->a = 10; this->b = 20;的方式赋值，只是编译器优化了而已
		a = 10;
		b = 20;
	}

	// 打印this指针的值
	void printThis()
	{
		std::cout << "this指针的地址为：" << this << std::endl;
	}

	// 使用this指针访问类的成员
	void func01()
	{
		std::cout << "a = " << this->a << " " << "b = " << this->b << std::endl;
		this->printThis(); // 打印this指针的值
	}

private:
	int a;
	int b;
};

// 2、验证this指针是不是指向本对象
void test01()
{
	Maker1 m;
	m.func01();

	// 我们发现this指针的值和&m的值相同，也就是说this就是指向对象m
	std::cout << "&m = " << &m << std::endl;
}

// 3、当有多个对象时，怎么区分哪个调用本对象的成员函数
void tset02()
{
	// 当有多个对象时，是通过this指针进行区分调用的，m1函数用m1的this指针调用
	// m2函数用m2的this指针调用，但是即使如此，对于同一个类来说，都是使用同一个函数func01()
	// 即这个函数func01()只有一份空间，这个不要混淆
	Maker1 m1;
	m1.func01();

	Maker1 m2;
	m2.func01();
}

/*
	补充：this指针是隐含在对象成员函数中的一种指针(注意是隐含着成员函数当中)，当对象创建
	      后，每个成员函数都自动生成一个隐含的this指针，这个指针是指向本对象(保存本对象地址)
		  虽然我们没有写上this指针，但是编译器默认会给我们加上，但是this指针不是本对象的一部分
		  用sizeof是算不出来的
*/

// 4、this指针的应用
class Maker2
{
public:
	Maker2() {}

	// (1)用于区分同名的变量，有可能参数和成员变量名字相同，此时只能用this进行赋值
	Maker2(int a, int b)
	{
		this->a = a;
		this->b = b;
	}

	// (2)用于返回对象本身
	Maker2& getMaker2()
	{
		return *(this); // 运算符重载时会使用
	}

	// (3)静态成员中不能使用this
	static void func01()
	{
		// 因为this的指向对象成员，而对于静态成员来说是属于类的，不属于对象
		// 并且静态成员的空间也不属于类，因此静态成员不能使用this指针
		// this->c = 300;
	}


private:
	int a;
	int b;
	static int c;
};
int Maker2::c = 30;

/*
	拓展：
	1、this指针指向的空间有没有储存静态成员变量？
	没有，因为this指针是指向本对象的储存空间，而静态成员不属于类的空间，因此没有储存静态成员空间

	2、this指针的指向是否可以改变？
	不能，空间已经分配好了，对象的空间地址已经确定，此时this指针就会指向这个空间，如果this可以改变
	的话，我们在类中定义的普通成员变量和成员函数就没办法通过this指针找到，因此this指针是不能改变的
	也就是说，this是一个指针常量，即Maker2* const this;
*/


int main()
{
	test01();

	return 0;
}
