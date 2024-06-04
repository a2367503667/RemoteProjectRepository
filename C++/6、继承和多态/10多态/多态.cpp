#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

/*
	什么是多态？
	同一个操作作用于不同的对象，可以有不同的解释，会产生不同的效果，即为多态(和动态联编一样)

	多态的作用：
	1、可以解决项目中的解耦合问题，提高程序的课扩展性
	2、应用程序不需要在调用函数当中，用代码枚举出子类的成员函数代码(如下面的courseOperate函数，我们
	   并没有提供子类的成员函数，我们只调用了父类MyCourse的成员函数即可输出不同的子类成员函数)，只需
	   对抽象父类进行处理即可


	多态的三个条件：
	1、有继承关系；2、子类重写父类的虚函数；3、有父类指针指向子类对象
	三者发生即可多态发生

		我们的应用程序进行更新，一般都是基于多态的形式进行更新的，因为之前的代码都是可运行的我们一
	般都是不会去修改原来的代码，所以我们都是会再写一个新的类，然后再去继承旧的类，利用多态的形式去
	添加新的功能，除非原来的代码有问题需要修改，要不然基本上都是以多态的形式增添新功能。
*/

// 我们以课程为例
class MyCourse
{
public:
	virtual void attendClass()
	{
		std::cout << "上专业课程" << std::endl;
	}
};

class CPlusPlus :public MyCourse
{
public:
	void attendClass()
	{
		std::cout << "上C++程序设计课" << std::endl;
	}

};

class Mathematics :public MyCourse
{
public:
	void attendClass()
	{
		std::cout << "上大学数学课" << std::endl;
	}

};

class English :public MyCourse
{
public:
	void attendClass()
	{
		std::cout << "上大学英语课" << std::endl;
	}
};

// 指针方式传递
void courseOperate(MyCourse* c)
{
	c->attendClass();
}
void test01()
{
	// 如何书写多态？
	// 1、先有父类指针对象
	MyCourse* myCour = nullptr;

	// 2、创建子类指针对象，并赋值给父类指针对象
	myCour = new Mathematics; // 其中Mathematics类是MyCourse的子类
	// 以上即为多态
	courseOperate(myCour); // 然后我们再测试一下
	delete myCour; // 测试完之后释放指针对象

	// -------------------------------------
	// 剩下的接着测试
	myCour = new CPlusPlus;
	courseOperate(myCour);
	delete myCour;

	myCour = new English;
	courseOperate(myCour);
	delete myCour;
	myCour = nullptr;


}

int main()
{
	test01();


	return 0;
}
