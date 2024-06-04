#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>


class Building
{
	friend class BestFriend; // 将BestFriend类添加成为友元类
	friend class MyFamily; // 将MyFamliy类添加到友元类
public:
	Building(std::string livingroom = "无人访问", std::string bedroom = "无人访问")
	{
		this->livingroom = livingroom;
		this->bedroom = bedroom;
	}

	void printVisit()
	{
		std::cout << "客厅：" << this->livingroom << std::endl;
		std::cout << "卧室：" << this->bedroom << std::endl;
		this->bedroom = "无人访问";
		this->livingroom = "无人访问";
	}

public:
	std::string livingroom;
private:
	std::string bedroom;
};

// 1、通过传参的形式访问私有成员
// 好朋友类
class BestFriend
{
public:

	// 作为Building的友元类后，就可以直接访问Building的私有成员了
	void func01(Building& b)
	{
		b.livingroom = "好朋友访问客厅";

		// 这本来是私有成员，现在可以被访问了
		b.bedroom = "好朋友访问卧室";
	}
};

// 客户类
class MyClient
{
public:
	void func01(Building& b)
	{
		b.livingroom = "客人访问客厅";
		// b.bedroom = "客人访问卧室"; // 不添加友元的话，没办法访问私有成员
	}

};

// 通过传参的形式访问私有成员
void test01()
{
	// 创建位置
	Building b;
	std::cout << "原始情况：" << std::endl;
	b.printVisit(); // 首先先查看一下访问情况

	std::cout << "-----------------------" << std::endl;

	// 创建好友
	BestFriend bf;
	std::cout << "好友访问：" << std::endl;
	bf.func01(b); // 先让好朋友访问
	b.printVisit(); // 然后再去查看访问情况
	
	std::cout << "-----------------------" << std::endl;

	// 创建客人
	MyClient mc;
	std::cout << "客人访问：" << std::endl;
	mc.func01(b); // 先让客人先访问
	b.printVisit(); // 然后再去查看访问情况
}
// --------------------------------

// 2、通过指针的形式访问私有成员(这次只提供一个类用于测试即可)
class MyFamily
{
public:
	MyFamily()
	{
		this->p = new Building;

		// 因为MyFamily类已经被添加成Building类的友元，所以可以给bedroom私有成员赋值
		// 刚开始直接赋值为"无人访问"
		this->p->bedroom = "无人访问";
		this->p->livingroom = "无人访问";
	}

	// 输出访问情况
	void printVisit()
	{
		std::cout << p->livingroom << std::endl;
		std::cout << p->bedroom << std::endl;
	}

	// 访问房间之后，就修改对应的值
	void visitedRoom()
	{
		this->p->bedroom = "家人访问卧室";
		this->p->livingroom = "家人访问客厅";
	}

	// 防止浅拷贝，重写一下拷贝构造
	MyFamily(const MyFamily& mf)
	{
		// 在动态申请空间之前，先判断传进来的对象的指针p是否为nullptr，不为nullptr就申请空间
		if (mf.p != nullptr)
		{
			this->p = new Building;
			p->livingroom = (mf.p)->livingroom;
			p->bedroom = (mf.p)->bedroom;
		}
		else
		{
			// 为nullptr就不需要申请空间
			this->p = nullptr;
		}
	}

	~MyFamily()
	{
		if (this->p != nullptr)
		{
			delete this->p;
			this->p = nullptr;
		}
	}
private:
	Building* p;
};

void test02()
{
	// 创建家人
	MyFamily mf;
	MyFamily m(mf);
	std::cout << "原始情况：" << std::endl;
	mf.printVisit(); // 首先先查看一下访问情况

	std::cout << "-----------------------" << std::endl;

	std::cout << "家人访问：" << std::endl;
	mf.visitedRoom(); // 先访问房间
	mf.printVisit(); // 然后再取查看一下访问情况

}



int main()
{
	// test01();
	test02();

	return 0;
}
