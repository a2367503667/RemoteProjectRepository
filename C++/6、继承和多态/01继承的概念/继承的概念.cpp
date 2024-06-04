#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

// 继承的作用是提高代码的复用性，子类可以使用父类的成员，那就可以公用一份代码
class Father
{
public:
	Father() :num1(10000000) {}
	Father(int num1) :num1(num1) {}
	void func01()
	{
		std::cout << "去上班" << std::endl;
	}

	void func02()
	{
		std::cout << "去旅游" << std::endl;
	}

	void func03()
	{
		std::cout << "现有：" << this->num1 << "人民币" << std::endl;
	}

private:
	int num1;
};

// 子类继承父类
class Son :public Father
{
public:


};

void test01()
{
	// 我们发现，子类(派生类)可以使用父类(基类)的成员
	Son s;
	s.func01();
	s.func02();
	s.func03();

}

int main()
{
	test01();

	return 0;
}
