#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>

// 目标：让MyFriend类的成员函数func01成为Building类的友元函数

// 3、但是这个还不行，因为MyFrined的成员函数参数用到了Building类，但是这时Building类
//    还没被构建出来，所以我们应该写一个类的声明，告诉编译器下面会存在Building类
class Building;

// 2、写上友元关系还不行，因为编译器不知道MyFriend类的结构，那就没办法确定
//    这个类中是否有func01这个成员函数，因此我们应该写出类MyFriend的结构
class MyFriend
{
public:
	MyFriend();
	void func01(Building& b);

	// 下面这两个是用来做多点实例的，是没有用的，只是起到测试作用
	static void func02();
	int func03();
private:
	std::string livingroom;
	std::string bedroom;
};


class Building
{
	// 1、先把友元关系写上(需要注意的是，要写上这个成员函数的类的作用域，否则就会被视为全局函数)
	friend void MyFriend::func01(Building& b);
public:
	Building(std::string livingroom = "无人访问", std::string bedroom = "无人访问")
	{
		this->livingroom = livingroom;
		this->bedroom = bedroom;
	}

	void printVisit()
	{
		std::cout << "客厅" << this->livingroom << std::endl;
		std::cout << "卧室" << this->bedroom << std::endl;
	}

public:
	std::string livingroom;
private:
	std::string bedroom;
};


MyFriend::MyFriend()
{
	this->livingroom = "好朋友访问客厅";
	this->bedroom = "好朋友访问卧室";
}

// 我要将这个函数成为Building类的友元函数
void MyFriend::func01(Building& b)
{
	b.livingroom = this->livingroom;
	b.bedroom = this->bedroom;

	std::cout << b.livingroom << std::endl;
	std::cout << b.bedroom << std::endl;
}

// 需要注意的是，如果这个函数是静态函数，只需要在class的结构声明里面写static即可，
// 外面实现时不需要写static
void MyFriend::func02()
{
	std::cout << "你好，我的朋友" << std::endl;
}

int MyFriend::func03()
{
	int a = 10;
	int b = 20;
	return a > b ? a : b;
}


void test01()
{
	// 创建访问空间
	Building b;
	std::cout << "原始情况：" << std::endl;
	b.printVisit(); // 输出当前访问的情况

	std::cout << "----------------------------" << std::endl;

	MyFriend mf;
	std::cout << "好友访问：" << std::endl;
	mf.func01(b); // 访问后并输出访问情况

}
/*
友元的注意事项：
	1、友元关系不能被继承；
	2、友元关系是单向的，类A是类B的友元，但类B不一定是类A的友元；
	3、友元关系不具有传递性，类B是类A的友元，类C是类B的友元，但类C不一定是类A的友元
	4、friend关键字只出现在声明处(我们之前写了好多次都在类的前面)；
	5、其他类、类成员函数和全局函数都可以声明为友元函数
	6、友元函数不是类的成员，不带this指针；
	7、友元函数可以访问对象的任何成员属性，包括私有属性
*/


int main()
{
	test01();

	return 0;
}
