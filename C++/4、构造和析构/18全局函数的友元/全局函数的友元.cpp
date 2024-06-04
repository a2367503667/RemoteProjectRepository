#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>

/*
	友元的概念：
		我们考虑到安全和维护性引入封装的思想，但是封装后加入私有权限在其他函数或类中
	无法访问，因此我们就引入友元的概念，如果应该成员函数f1、全局函数f2或类c1被添加另
	一个类c2的友元，那f1、f2或c1就可以访问c2的私有成员，具有修改c2私有成员的权限
*/

// 验证且添加友元函数(即一个全局函数是一个类的友元)
class Building
{
	// 需要注意的是，友元函数并不是类的成员函数，所以没有权限之分，前面不需要用权限符号修饰
	friend void bestFriends(Building& f);
public:
	Building(std::string bedroom, std::string livingroom)
	{
		this->bedroom = bedroom;
		this->livingroom = livingroom;
	}

	void printSituation()
	{
		std::cout << bedroom << std::endl;
		std::cout << livingroom << std::endl;
	}

private: // 卧室私有访问
	std::string bedroom; // 卧室
public: // 课堂公有访问
	std::string livingroom; // 客厅
};

// 我们让好朋友访问我们的卧室
void bestFriends(Building& f)
{
	f.bedroom = "好朋友访问卧室"; // 添加友元之后，就可以访问私有成员了
	f.livingroom = "好朋友访问客厅";
	f.printSituation();
}

// 让客人只能访问客厅
void myClient(Building& c)
{
	// c.bedroom = "客人访问卧室";
	c.livingroom = "客人访问客厅";
	c.printSituation();
}

void test01()
{
	Building b1("无人访问", "无人访问");
	bestFriends(b1);
	
	std::cout << "-------------------------" << std::endl;
	Building b2("无人访问", "无人访问");
	myClient(b2);

}


int main()
{
	test01();

	return 0;
}
