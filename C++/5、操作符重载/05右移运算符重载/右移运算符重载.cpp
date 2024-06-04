#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

/*
	重载右移运算符其实就是便于给出一个Maker1对象m1，通过cin>>m1的方式初始化对象m1的数据
	目的本质上和重载左移运算符类似，因为cin对象和cout也是构造函数也是被私有化，所以不能创建
	对象，并且cin对象属于std::istream类，而cout对象属于std::ostream类
*/

class Maker1
{
	friend std::istream& operator>>(std::istream& in, Maker1& m);
public:
	Maker1() {}
	Maker1(int num1) :num1() {}

	void printNum1()
	{
		std::cout << "num1 = " << this->num1 << std::endl;
	}

	~Maker1() {}
private:
	int num1;
};

std::istream& operator>>(std::istream& in, Maker1& m)
{
	in >> m.num1;
	in.get();
	return in;
}


void test01()
{
	Maker1 m1;
	std::cin >> m1;
	m1.printNum1();
}



int main()
{
	test01();

	return 0;
}
