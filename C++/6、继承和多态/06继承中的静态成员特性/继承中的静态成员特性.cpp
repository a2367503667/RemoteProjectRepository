#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

/*
	需要注意的是，构造函数、析构函数以及赋值函数不能被继承
*/

class Father
{
public:

	static void func()
	{
		std::cout << "Father static func()" << std::endl;
	}

	static void func(int a)
	{
		std::cout << "Father static func(int a)" << std::endl;
	}

	static void func(int a, int b)
	{
		std::cout << "Father static func(int a, int b)" << std::endl;
	}

public:
	static int a;
};
int Father::a = 100;

class Son :public Father
{
public:

	//static void func()
	//{
	//	std::cout << "Son static func()" << std::endl;
	//}

	static int func()
	{
		std::cout << "Son static int func()" << std::endl;
		return 0;
	}

public:
	static int a;
	static int b;
};
int Son::a = 200;
int Son::b = 300;

// 1、查看静态成员变量
void test01()
{
	// 我们发现可以调用父类的静态成员，即静态成员也继承过来了
	Son son;

	// 当Son中没有静态成员a时，测试这个
	// std::cout << "son.a = " << son.a << std::endl; // 100

	// 如果没有同名是互不影响的
	std::cout << "son.b = " << son.b << std::endl; // 300

	// 当Son中的静态成员也是a时，观察会会出现什么情况
	// 我们发现是调用了Son的静态成员变量(即父类中的a被隐藏掉了)
	std::cout << "son.a = " << son.a << std::endl; // 200

	std::cout << "--------------------------" << std::endl;

	// 如果想访问的话，只能用作用域
	std::cout << "son.Father::a = " << son.Father::a << std::endl;

	// 或者使用父类类名触发访问(因为静态成员属于类)
	std::cout << "Father::a = " << Father::a << std::endl;

	std::cout << "--------------------------" << std::endl;

	// 从父类中继承过来的静态成员变量是父类的静态成员变量
	son.Father::a = 800;
	std::cout << "son.Father::a = " << son.Father::a << std::endl;

	// &(son.Father::a) = 00007FF7A011D000
	std::cout << "&(son.Father::a) = " << &(son.Father::a) << std::endl;

	// &(Father::a) = 00007FF7A011D000
	std::cout << "&(Father::a) = " << &(Father::a) << std::endl;

	// 由以上两个地址对比可知，是同一个变量

}

// 2、查看静态成员函数
void test02()
{
	Son son;

	// 同样的，只会调用子类的静态函数，父类的同名静态函数被隐藏了
	son.func();

	// 只能通过作用域的方式去访问
	son.Father::func();
	son.Father::func(10);
	son.Father::func(10, 20);

	std::cout << "---------------------------" << std::endl;

	// 也可以直接用父类类名触发访问(因为这个是静态成员，属于类)
	Father::func();
	Father::func(10);
	Father::func(10, 20);

	std::cout << "---------------------------" << std::endl;
	// 即使子类的静态函数和父类的静态函数的返回值不同和参数个数不同，也会隐藏父类的静态成员函数
	son.func(); // Son static int func()

	// 还有一点就是静态成员函数不能是虚函数(后面讲)

}


int main()
{
	test01();
	// test02();


	return 0;
}
