#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

class Maker1
{
public:
	Maker1(int id, int age)
	{
		this->id = id;
		this->age = age;
	}

	void printMaker()const
	{
		// id = 1; err
		// age = 20; err
		std::cout << "id = " << id << " age = " << age << std::endl;

		score = 100;
		std::cout << "score = " << score << std::endl;
	}

	void func01()
	{
		id = 2;
		age = 22;
	}

	static void func02()
	{
		int x = 100;
		std::cout << "x = " << x << std::endl;
	}


public:
	int id;
	int age;
	static int a;
	mutable int score; // 常对象也可以修改它的值
};
int Maker1::a = 100;

void test01()
{
	// 常对象(在对象类型前面加上const就是常对象)
	const Maker1 m1(1, 21);
	
	// 1、常对象就是不能修改对象里面的普通成员变量，也就是只要属于对象空间的成员变量都不能改变
	// 也就是说，上面除了静态成员变量，没有mutable修饰的都不能改变
	// m1.age = 100;

	// 2、有mutable修饰的变量可以改变
	m1.score = 200;
	std::cout << "m1.score = " << m1.score << std::endl;

	// 3、常对象也不能调用非常函数，因为非常函数有可能在函数体对普通成员变量进行修改
	// 而常对象是不能修改普通成员变量值的，因此不能调用
	// m1.func01();

	// 4、可以调用常函数
	m1.printMaker();

	// 5、可以调用静态函数以及使用静态成员
	m1.func02();
	std::cout << "a = " << m1.a << std::endl;
}


int main()
{
	test01();

	return 0;
}
