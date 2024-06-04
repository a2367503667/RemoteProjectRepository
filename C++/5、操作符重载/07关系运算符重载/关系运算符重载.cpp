#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>

/*
	关系运算符主要是重载">"、"<"、"=="、"!="、"<="、">="其实也是比较简单的

	应用场景就是比对两个对象m1和m2的关系，我们不能直接进行m1>m2这些比较，所以我们只能通过
	重载运算符达到能够比较的目的
*/

class Maker1
{
public:
	Maker1(std::string name, int id) :name(name), id(id) {}

	// 重载">"
	bool operator>(const Maker1& m)
	{
		return this->id > m.id;
	}

	// 重载"<"
	bool operator<(const Maker1& m)
	{
		return this->id < m.id;
	}

	// 重载">="
	bool operator>=(const Maker1& m)
	{
		return this->id >= m.id;
	}

	// 重载"<="
	bool operator<=(const Maker1& m)
	{
		return this->id <= m.id;
	}

	// 重载"=="
	bool operator==(const Maker1& m)
	{
		return this->name == m.name && this->id == m.id;
	}

	// 重载"!="
	bool operator!=(const Maker1& m)
	{
		return this->name != m.name || this->id != m.id;
	}

private:
	std::string name;
	int id;
};

void test01()
{
	Maker1 m1("张三", 18);
	Maker1 m2("李四", 19);
	Maker1 m3("王五", 20);
	Maker1 m4("赵六", 21);
	Maker1 m5("陈七", 22);
	Maker1 m6("老八", 23);

	// 验证">"
	if (m1 > m2)
	{
		std::cout << "m1 > m2" << std::endl;
	}
	else
	{
		std::cout << "m1 <= m2" << std::endl;
	}
	 
	// 验证"<"
	if (m4 < m5)
	{
		std::cout << "m4 < m5" << std::endl;
	}
	else
	{
		std::cout << "m4 >= m5" << std::endl;
	}

	// 验证">="
	if (m3 >= m2)
	{
		std::cout << "m3 >= m2" << std::endl;
	}
	else
	{
		std::cout << "m3 < m2" << std::endl;
	}

	// 验证"<="
	if (m4 <= m3)
	{
		std::cout << "m4 <= m3" << std::endl;
	}
	else
	{
		std::cout << "m4 > m3" << std::endl;
	}

	// 验证"=="
	if (m5 == m6)
	{
		std::cout << "m5 == m6" << std::endl;
	}
	else
	{
		std::cout << "m5 != m6" << std::endl;
	}

	// 验证"!="
	if (m1 != m6)
	{
		std::cout << "m1 != m6" << std::endl;
	}
	else
	{
		std::cout << "m1 == m6" << std::endl;
	}



}



int main()
{
	test01();


	return 0;
}
