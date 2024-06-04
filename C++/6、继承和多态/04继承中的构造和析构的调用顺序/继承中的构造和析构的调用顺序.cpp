#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

class Father
{
public:
	Father()
	{
		std::cout << "Father无参构造函数" << std::endl;
	}

	~Father()
	{
		std::cout << "Father析构函数" << std::endl;
	}
};

class Maker1
{
public:
	Maker1();
	~Maker1();
};
class Maker2
{
public:
	Maker2();
	~Maker2();
};

class Son :public Father
{
public:
	Son()
	{
		std::cout << "Son无参构造函数" << std::endl;
	}

	~Son()
	{
		std::cout << "Son析构函数" << std::endl;
	}
private:
	Maker1 m1;
	Maker2 m2;
};

Maker1::Maker1()
{
	std::cout << "Maker1无参构造函数" << std::endl;
}

Maker1::~Maker1()
{
	std::cout << "Maker1析构函数" << std::endl;
}

Maker2::Maker2()
{
	std::cout << "Maker2无参构造函数" << std::endl;
}

Maker2::~Maker2()
{
	std::cout << "Maker2析构函数" << std::endl;
}

void test01()
{
	/*
		实例1：
		我们发现调用顺序为(还没加入m1和m2成员)：
		Father无参构造函数
		Son无参构造函数
		Son析构函数
		Father析构函数

			其实这种调用顺序也是有一定道理的，因为我们子类中有可能会用到父类资源，因此我们
		应该先初始化父类资源，才能够初始化自己本身的资源，而且父类一定要提供public权限的构
		造函数和析构函数，否则子类无法创建对象
	*/

	/*
		实例2：
		我们发现调用顺序为(已经加入m1和m2成员)：
		Father无参构造函数
		Maker1无参构造函数
		Maker2无参构造函数
		Son无参构造函数
		Son析构函数
		Maker2析构函数
		Maker1析构函数
		Father析构函数

			也就是说，任何情况下都是先初始化父类资源后，才会初始化其他资源，对应子类中的
		成员对象创建顺序也是优先于子类对象的创建的(这个和之前的一样)
	
	*/

	Son s;

}


int main()
{
	test01();

	return 0;
}
