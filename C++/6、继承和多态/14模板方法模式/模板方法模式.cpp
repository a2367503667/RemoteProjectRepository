#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

/*
		模版方法模式其实就是给定一些模板(抽象类，其中里面有纯虚函数)，用来供给给别人，然后让不同的
	人实现代码，最后就会有不同的结果
*/

// 这个可以作为模板，因为冲茶和冲咖啡顺序都是这些步骤，但是实现的功能就不一样
class Drink
{
public:
	// 煮水
	virtual void boil() = 0;

	// 冲泡
	virtual void brew() = 0;

	// 倒入杯中
	virtual void pourInCup() = 0;

	// 加点辅料
	virtual void addSome() = 0;

	// 这个就是实现所有纯虚函数后的输出结果(属于调用模板，给子类进行多态调用的)
	// 需要注意的是，这个模板是写在抽象类里面，而不是写在子类里面，否则是没办法调用的
	void invWork()
	{
		boil();
		brew();
		pourInCup();
		addSome();
	}
};

class MyTea :public Drink
{
public:
	// 煮水
	virtual void boil()
	{
		std::cout << "1、煮山泉水" << std::endl;
	}

	// 冲泡
	virtual void brew()
	{
		std::cout << "2、泡铁观音茶叶" << std::endl;
	}

	// 倒入杯中
	virtual void pourInCup()
	{
		std::cout << "3、倒入茶杯当中" << std::endl;
	}

	// 加点辅料
	virtual void addSome()
	{
		std::cout << "4、加点蜂蜜" << std::endl;
	}
};

class MyCoffee :public Drink
{
public:
	// 煮水
	virtual void boil()
	{
		std::cout << "1、煮蒸馏水" << std::endl;
	}

	// 冲泡
	virtual void brew()
	{
		std::cout << "2、冲泡雀巢咖啡" << std::endl;
	}

	// 倒入杯中
	virtual void pourInCup()
	{
		std::cout << "3、倒入咖啡杯中" << std::endl;
	}

	// 加点辅料
	virtual void addSome()
	{
		std::cout << "4、加点方糖" << std::endl;
	}
};

void test01()
{
	Drink* d = nullptr;

	// ---------------------
	// 茶
	d = new MyTea;
	d->invWork(); 
	delete d;

	std::cout << "------------------------" << std::endl;

	// ---------------------
	// 咖啡
	d = new MyCoffee;
	d->invWork();
	delete d;
	d = nullptr;
}



int main()
{
	test01();

	return 0;
}
