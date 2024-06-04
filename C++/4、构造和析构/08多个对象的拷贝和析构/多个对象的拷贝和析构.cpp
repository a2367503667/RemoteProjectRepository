#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

class BMW
{
public:
	BMW()
	{
		std::cout << "BMW构造函数" << std::endl;
	}
	~BMW()
	{
		std::cout << "BMW析构函数" << std::endl;
	}
};

class Buick
{
public:
	Buick()
	{
		std::cout << "Buick构造函数" << std::endl;
	}
	~Buick()
	{
		std::cout << "Buick析构函数" << std::endl;
	}
};

class Maker
{
public:
	Maker()
	{
		std::cout << "Maker构造函数" << std::endl;
	}
	~Maker()
	{
		std::cout << "Maker析构函数" << std::endl;
	}


private:
	BMW bmw; // 成员对象
	Buick buick; // 成员对象
};

// 1、执行下面代码会去先去调用BMW的构造函数，接着调用Buick的构造函数，最后再去调用Maker的构造函数
// 在调用析构函数时，就会先调用Maker的析构函数，接着在去调用Buick的析构函数，最后再去调用BMW的析构函数
// 其实成员对象的构造函数和析构函数的调用顺序是和Maker中的成员对象的排列顺序有关，因为BMW排在前，Buick排在后
// 所以就先调用BMW的构造函数再调用Buick的构造函数，而析构函数就与构造函数的调用顺序相反
// 2、但是如果在Maker类中，有成员对象的构造函数或析构函数的权限不可以访问时，就会报错(只要有一个就会报错)
// 3、总的来说，如果类里面有成员对象，就会先去调用成员对象的构造函数，析构函数的调用顺序相反
void test01()
{
	Maker m;
}

class BMW1
{
public:
	BMW1(int a)
	{
		std::cout << "BMW1有参构造函数" << "   a = " << a << std::endl;
	}
	~BMW1()
	{
		std::cout << "BMW1析构函数" << std::endl;
	}
};

class Buick1
{
public:
	Buick1(int b, int c)
	{
		std::cout << "Buick1有参构造函数" << "   b = " << b << "   c = " << c << std::endl;
	}
	~Buick1()
	{
		std::cout << "Buick1析构函数" << std::endl;
	}
};

// 如果成员对象中，调用的是有参构造函数，你Maker1构造函数直接写是会报错的，因为在创建Maker1对象时
// 会先调用BMW1和Buick1的构造函数，但是这两个类的构造函数是有参的，你没有途径给它传入参数，因此就会报错
// 所以，要想解决这个问题，就需要提供初始化列表，如下：
// 注：初始化列表只能写在构造函数的函数头右边，其他函数都不能用
class Maker1
{
public:
	// 初始化列表格式 对象名(参数表(个数需看对象的类中的构造函数)) 
	// 有多个对象：  对象名(xxx),对象名(xxx)...    每个对象用逗号隔开，其中xxx是参数表
	// 但是如果你想构造函数可以任意输入数值，就需要把Maker1的构造函数改成有参构造函数
	// 并且每个有参构造函数都需要写上初始化列表，包括拷贝构造函数也需要写
	/*
	// 这个不能改变构造函数形参列表的值，下面进行改写：
	Maker1() :bmw(20), buick(10, 20)
	{

	}
	
	*/
	Maker1(int a, int b, int c) :bmw(a), buick(b, c)
	{
		std::cout << "Maker1有参构造函数" << std::endl;
	}

	// 同样的，拷贝构造函数也需要写上初始化列表
	Maker1(const Maker1& m, int a, int b, int c) :bmw(a), buick(b, c)
	{
		std::cout << "Maker1拷贝构造函数" << std::endl;
	}
	~Maker1()
	{
		std::cout << "Maker1析构函数" << std::endl;
	}
private:
	BMW1 bmw;
	Buick1 buick;
};

void test02()
{
	// 相应地，Maker1就不能用无参构造函数了，因为Maker1的成员对象都是调用有参构造函数的
	// 如果Maker1可以使用无参构造函数，那就没办法给他的成员对象的有参构造器赋值了(准确来说是自由赋值)
	// 如果是固定赋值的话，是可以直接写Maker1无参构造函数的，但是想自由地赋值，就只能通过有参构造函数进行初始化了
	// 下面那行会报错：
	// Maker1 m1;
	Maker1 m1(10, 20, 30); // 这样才不会报错

}


int main()
{
	// test01();
	test02();


	return 0;
}
