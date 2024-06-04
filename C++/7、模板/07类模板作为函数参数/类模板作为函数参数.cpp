#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>

template<class NameType, class AgeType = int>
class Maker1
{
public:
	Maker1(NameType name, AgeType age)
	{
		this->name = name;
		this->age = age;
	}

	void printMes()
	{
		std::cout << "name = " << this->name << "，age = " << this->age << std::endl;
	}

private:
	NameType name;
	AgeType age;
};

/*
	类模板作为函数参数
*/

// 1、指定传入的数据类型
void func01(Maker1<std::string>& m)
{
	m.printMes();
}
void test01()
{
	Maker1<std::string, int> m("张三", 20);
	func01(m);
}


// 2、参数模板化(即让该函数成为函数模板，在函数形参列表中传入该函数模板参数类型)
// 这种方式是最常用的
template<typename NameType,typename AgeType>
void func02(Maker1<NameType, AgeType>& m)
{
	m.printMes();
}
void test02()
{
	Maker1<std::string, int> m("李四", 21);
	func02(m);
	/*
		在运行到func02(m);
		会将m的数据对应类型代入到函数模板，进行二次编译，如下：
		void func02(Maker1<std::string, int>& m)
		{
			m.printMes();
		}
	*/
}


// 3、将整个函数成为函数模板，即将整个类型都初始为T(即将整个类模板化)
// 这种很少用，因为这个就是将整个函数模板化了，并且我们也不确定m是否有成员函数printMes()
// 这样很容易会报错
template<typename T>
void func03(T& m)
{
	m.printMes();
}
void test03()
{
	Maker1<std::string, int> m("王五", 22);
	func03(m);
}


int main()
{
	test01();
	std::cout << "------------------------" << std::endl;
	test02();
	std::cout << "------------------------" << std::endl;
	test03();

	return 0;
}
