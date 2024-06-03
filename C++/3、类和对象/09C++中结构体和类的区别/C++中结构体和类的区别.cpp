#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

// 结构体
// 可以在结构体里面写函数，写变量，也可以设置成员权限，也可以继承结构体
struct Maker1
{
	int a;
	void func()
	{

	}
public:
	int b;
};

// 结构体继承结构体
struct SonMaker1 :public Maker1
{



};


// 类
// 可以在类里面写函数，写变量，也可以设置成员权限，也可以继承类
class Maker2
{
	int a;
	void func()
	{

	}
public:
	int b;
};

// 类继承类
class SonMaker2 :public Maker2
{


};

// 但是类和结构体的主要区别就是，类的成员默认权限是私有，结构体默认的权限是公有
// 下面做一个验证
void test01()
{
	Maker1 m1; // 结构体
	Maker2 m2; // 类
	m1.b;
	m2.b;
	m1.a;
	// m2.a; 报错，因为类的成员默认权限是private
	// m2.func();  这个同理，没有给权限默认权限为private

}

// 所以有人会这样写类(忘记设置权限)
// 注意不要忘记给权限
class Maker3
{
	// 忘记给权限，导致使用的时候，点(.)不出来
	int a;
	void func()
	{

	}
};

void test02()
{
	// 忘了给权限然后就去使用
	Maker3 m3;
	// m3.a;
	// m3.func();
}


int main()
{
	test01();

	return 0;
}
