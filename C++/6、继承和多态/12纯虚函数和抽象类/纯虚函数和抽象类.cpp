#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

/*
	1、依赖倒转：这个是一个业务问题，其实就我们一个项目一般都是有"业务层"和"实现层"的，业务层是用于
			     调用实现层写完的代码，但是有个问题，就是对于业务层的设计来说，需要实时观察实现层的
				 代码结构是怎么样的，因为有可能实现层的代码结构改变，就会导致业务层的调用代码结构也会
				 发生变化，这样就会有很大的开发困扰，但是我们在这两层之间加一个"抽象层"，这个抽象层只
				 提供需要实现的函数(包括参数、返回值等等)，业务层就可以根据抽象层的结构写地调用代码，
				 实现层就可以按照需求以"抽象层"的函数结构实现代码，这样业务层和实现层就不会相互影响，
				 就能够最大可能地降低开发的困扰，这就是依赖倒转(业务层依赖抽象层，实现层依赖抽象层)。
	
	2、开闭原则：对修改源代码关闭，对扩展新功能开放，其实就是不改动原来代码的基础上，只往原来的代码
				 添加新功能

	3、纯虚函数：因为在下面代码可以发现，抽象层的getNum函数其实带返回值是没有什么用处的，所以我们干
				 脆把函数体去掉，然后在函数签名后面加上=0即可，这个就是纯虚函数

	4、抽象类：含有纯虚函数的类被称为抽象类，是不能实例化对象的，子类没有实现父类的所有纯虚函数，子
			   类也会成为抽象类，实现父类的所有纯虚函数后即可实例化对象，虽然说抽象类不能实例化对
			   象，但是可以创建对象指针的，因为这个可以用于多态

*/

// 这个为抽象层
// 有纯虚函数的类被称为抽象类(MyRule即为抽象类)
class MyRule
{
public:
	//virtual int getNum(int a, int b)
	//{
	//	return 0;
	//}

	// 这个就是纯虚函数
	virtual int getNum(int a, int b) = 0;
};

// 实现层，用于实现抽象层的代码
class AddRule :public MyRule
{
public:
	virtual int getNum(int a, int b) // 重写父类虚函数(实现层依赖抽象层)
	{
		return a + b;
	}
};

// 这个也是实现层，模拟拓展拓展代码
class SubRule :public MyRule
{
public:
	virtual int getNum(int a, int b) // 重写父类虚函数(实现层依赖抽象层)
	{
		return a - b;
	}
};

// 业务层，用于调用抽象层的代码(即使实现层新天更多的功能，我们也不需要改动业务层的代码)
int invWork(MyRule* r)
{
	int a = 10;
	int b = 20;

	int val = r->getNum(a, b); // 业务层调用代码(业务侧依赖抽象层)
	return val;
}

void test01()
{
	MyRule* r = nullptr;

	// 加法业务
	r = new AddRule;
	int val = invWork(r);
	std::cout << "add val = " << val << std::endl;
	delete r;

	// 减法业务
	r = new SubRule;
	val = invWork(r);
	std::cout << "sub val = " << val << std::endl;
	delete r;
	r = nullptr;
}


// 验证抽象类的特点
class Maker1
{
public:
	virtual void func01() = 0;
	virtual void func02() = 0;
};

class Son :public Maker1
{
public:

};

class Son2 :public Maker1
{
public:
	virtual void func01()
	{
		std::cout << "void func01()" << std::endl;
	}

	virtual void func02()
	{
		std::cout << "void func02()" << std::endl;
	}
};

void test02()
{
	// 1、抽象类不能实例化对象
	// Maker1 m; //err

	// 2、子类没有实现父类的所有纯虚函数，子类也会成为抽象类
	// Son s; // err

	// 实现父类的所有纯虚函数后即可实例化对象
	Son2 s1;
	s1.func01();
	s1.func02();
}


int main()
{
	// test01();
	test02();

	return 0;
}
