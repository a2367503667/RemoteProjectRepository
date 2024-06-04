#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

// 在C++中，是允许多继承的，多继承也就是子类继承两个及以上个类
// 多继承的问题就是当父类中有同名成员时，子类会出现二义性问题
/*
	下面是Son与Father1、Father2的结构图：

	11多继承.cpp

	class Son       size(12):
			+---
	 0      | +--- (base class Father1)
	 0      | | a
			| +---
	 4      | +--- (base class Father2)
	 4      | | a
			| +---
	 8      | c
			+---

*/

class Father1
{
public:
	Father1() :a(100) {}
public:
	int a;
};

class Father2
{
public:
	Father2() :a(200) {}

public:
	int a;
};

class Son :public Father1, public Father2
{
public:
	Son() :c(300) {}

public:
	int c;

};

void test01()
{
	// 但是我们会发现，多继承会出现问题，可能会出现二义性的问题，如下：
	Son son;

	// 因为两个父类都有a，此时就会出现二义性，只能通过作用域才可以使用
	// son.a; //err
	std::cout << "son.Father1::a = " << son.Father1::a << std::endl;
	std::cout << "son.Father2::a = " << son.Father2::a << std::endl;

}



int main()
{
	test01();

	return 0;
}
