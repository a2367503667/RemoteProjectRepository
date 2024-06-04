#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

/*
	其实我们通过查看结构可以看出num其实有两个，如下：

	09继承中同名成员的处理方法.cpp

	class Son       size(8):
			+---
	 0      | +--- (base class Father)
	 0      | | num
			| +---
	 4      | num
			+---

*/

class Father
{
public:
	Father()
	{
		num = 100;
	}

	void func()
	{
		std::cout << "Father func()" << std::endl;
	}

	void func(int a)
	{
		std::cout << "Father func(int a)" << std::endl;
	}

	void func(int a, int b)
	{
		std::cout << "Father func(int a, int b)" << std::endl;
	}

public:
	int num;
};

class Son :public Father
{
public:
	Son()
	{
		num = 100;
	}

	void func()
	{
		std::cout << "Son func()" << std::endl;
	}

public:
	int num;
};

// 1、测试成员变量
void test01()
{
	// 当子类和父类有同名成员时，子类的同名成员会隐藏父类的同名成员
	Son son;
	std::cout << "son.num = " << son.num << std::endl; // 100
	std::cout << "sizeof(Son) = " << sizeof Son << std::endl; // 8(说明有两个成员变量)

	// 假如我想访问父类的成员，那如何访问呢？答案是：通过作用域
	// 如下：

	// 注意书写形式：子类对象.父类名::父类成员变量(即xxx.yyy::k)
	// 其实可以按照语义来拆分，因为我们访问的是父类的num，所以是Father::num，而这个元素
	// 又是属于Son类的对象son的，所以就是son.Father::num，也就是给成员变量num加父类作用域即可
	son.Father::num = 200;
	std::cout << "son.Father::num = " << son.Father::num << std::endl;
	std::cout << "son.num = " << son.num << std::endl;

}

// 2、测试成员函数
void test02()
{
	Son son;

	// 很明显默认打印的是子类的
	son.func();

	// 需要注意，子类有和父类同名函数时，父类的所有函数重载都会被隐藏，所以下面这样调用会出错
	// son.func(10); //err
	// son.func(10, 20); //err

	// 那就只能通过作用域调用
	son.Father::func();
	son.Father::func(10);
	son.Father::func(10, 20);

}


int main()
{
	// test01();
	test02();

	return 0;
}
