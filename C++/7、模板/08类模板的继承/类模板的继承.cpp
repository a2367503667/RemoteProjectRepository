#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

/*
	其实继承类模板，我们本质上还是继承类本身而不是继承模板，因为我们继承类模板时，都需要确保类模板
	都带有其数据类型，不管是"普通类继承类模板"(如：class Maker2 :public Maker1<int>)，还是
	"类模板继承类模板"(如：class Maker3 :public Maker1<T2>)，都需要确保继承的那个类模板的数据
	类型是明确的(如：Maker1<int>或Maker1<T2>)，模板类后面都必须指定数据类型，并且在使用过程中
	只要涉及到Maker1都需要指定数据类型(如：	Maker3(T1 name, T2 m) :name(name), Maker1<T2>(m) {}这里
	的参数列表Maker1也需要指定类型)

	上面就一句话总结，那就是"必须告诉编译器父类的泛型类型是什么"
*/

// 类模板
template<class T>
class Maker1
{
public:
	Maker1(T m) :m(m) {}
	virtual void printMes() = 0;
public:
	T m;
};

// 1、普通类继承类模板
// 普通类
/*
	注："class Maker2:public Maker1"这样写是错误的，必须指定类模板Maker1的数据类型
		即需要告诉编译器父类的泛型数据类型具体是什么类型
*/
class Maker2 :public Maker1<int>
{
public:
	Maker2(int m) :Maker1(m) {}
	virtual void printMes() override
	{
		std::cout << "m = " << m << std::endl;
	}
};

void test01()
{
	Maker2 m(20);
	m.printMes();
}

// 2、类模板继承类模板
template<class T1, class T2>
class Maker3 :public Maker1<T2>
{
public:

	// 这里需要注意的是，使用参数列表初始化Maker1，必须要写上Maker1类模板的数据类型
	// 如果写成Maker1(m)就会报错，显示Maker1不是成员/类，必须要写成Maker1<T2>
	Maker3(T1 name, T2 m) :name(name), Maker1<T2>(m) {}
	virtual void printMes() override
	{
		// 这里需要注意的是，Maker3继承了Maker1<T2>的m成员
		std::cout << "name = " << this->name << "，age = " << this->m << std::endl;
	}

public:
	T1 name;
};

void test02()
{
	Maker3<std::string, int> m("张三", 21);
	m.printMes();
}



int main()
{
	test01();
	std::cout << "------------------------" << std::endl;
	test02();

	return 0;
}
