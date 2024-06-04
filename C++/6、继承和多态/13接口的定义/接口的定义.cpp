#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

/*
	接口其实就是我们在抽象类中提供的纯虚函数，然后让别的类继承，并重写这些纯虚函数
*/

class Father
{
public:
	// 下面这些就是接口
	virtual void func01() = 0;
	virtual void func02(int a) = 0;
	virtual void func03(int a, int b) = 0;
};

// 在子类中实现这些接口
class Son :public Father
{
public:
	virtual void func01()
	{
		std::cout << "void func01()" << std::endl;
	}
	virtual void func02(int a)
	{
		std::cout << "void func02(int a)" << std::endl;
	}
	virtual void func03(int a, int b)
	{
		std::cout << "void func03(int a, int b)" << std::endl;
	}
};

// 抽象类也可以作为参数，以多态形式调用
/*
	这里需要注意的是，我们抽象类虽然是不能创建对象，但是我们可以作为函数参数
	因为传进来的参数只能是继承抽象类的子类(即有多态：Father *r = s)
*/
void invWork(Father* f)
{
	f->func01();
	f->func02(5);
	f->func03(5, 10);
}

void test01()
{
	// 虽然说抽象类不能实例化对象，但是可以创建对象指针的，如下：
	Father* r = nullptr;

	r = new Son;
	invWork(r);
	delete r;
	r = nullptr;
}



int main()
{
	test01();

	return 0;
}
