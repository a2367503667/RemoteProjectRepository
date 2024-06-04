#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>

/*
	什么是仿函数？
	一个类如果重载了函数调用符号，那么这个类实例化的对象叫仿函数，如：Maker的对象为func
	那么func()就是仿函数，其实看起来也很像函数，实质func是Maker的对象，其实作用就是调用
	一个函数，和调用全局函数作用类似

	仿函数作用：
	1、为了保持很好的封装性，因为我们写全局函数的话，数量多起来就很难维护，尤其是在
	   一些大项目中，所以我们在某个类中重写()运算符的话，就可以通过对象做的调用函数
	   的效果，并且在一个类中维护起来也很方便；
	2、有很好的权限管理，因为写在全局的函数会被随意调用，没有权限之分，但是在类内重写()运
	   算符函数有权限，也就是可以很好地管理函数的权限问题；
	3、作为算法的策略(后面会详细讲)。
*/

class Maker1
{
public:
	Maker1(int id, std::string name) :id(id), name(name) {}

	// 1、重载()运算符函数
	void operator()()
	{
		std::cout << "欢迎使用Maker1仿函数" << std::endl;
	}

	// 2、含普通类型参数
	void operator()(int num1,int num2)
	{
		std::cout << "考研总成绩为：" << num1 + num2 << std::endl;
	}

	// 3、含类的参数
	void operator()(std::string str)
	{
		std::cout << this->name << str << std::endl;
	}

private:
	int id;
	std::string name;
};

void test01()
{
	Maker1 func(1, "张三");

	func();

	func(200, 250);

	func("好好学习，天天向上！");
}

int main()
{
	test01();

	return 0;
}
