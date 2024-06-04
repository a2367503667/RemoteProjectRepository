#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>

/*
	类模板：
		1、类模板和函数模板的区别是，函数模板可以自动推导数据类型，而类模板是必须要
		   用户指定参数类型；
		
		2、类模板可以有默认类型，其实函数模板也一样，这个规则和我们普通函数的默认参数规则
		   是一样的，假设有一个参数类型是默认参数，那么其后面的参数类型也必须是默认参数
		   如：template<class T1, class T2>如果我们想T1成为默认参数，那T2也一定是默认参数
		   这种写法template<class T1 = int, class T2>是错误的
*/


// 类模板(将我们需要变化的数据类型设置成模板参数中的类型即可)
template<class NameType, class AgeType = int>
class Maker1
{
public:
	Maker1(NameType name, AgeType  age)
	{
		this->name = name;
		this->age = age;
	}

	void printMes()
	{
		std::cout << "name = " << this->name << "，age = " << this->age << std::endl;
	}

public:
	NameType name;
	AgeType age;
};


void test01()
{
	// 1、类模板不会自动推导数据类型，要显式告诉编译器是什么类型
	// err：使用类模板与函数模板不一样，类模板必须传递数据类型，否则报错
	// Maker1 m1("张三", 20); // err

	// 正确写法
	Maker1<std::string, int> m1("张三", 20);
	m1.printMes();

	// 2、注意传入的参数是否有误，是否符合要求(其实这一点就和函数模板那个"比较大小"一样
	// 有可能传进去会"出现报错"或者"得不到我们预期的结果"，所以这个也需要我们程序员进行控制)
	// 就好比如，虽然没有报错，但是我们乱传数据会导致程序出现错误，因此我们需要程序员自己把握
	Maker1<int, int> m2(100, 200);
	m2.printMes();

	// Maker1<> m3("李四", 21); // err：必须通过参数列表告诉编译器模板对应的类型
 
}

void test02()
{
	// 1、类模板的参数类型可以有默认参数
	// 如下可知，当有默认参数后，我们可以只传一个参数，并且程序可以正常运行
	Maker1<std::string> m1("王五", 22);
	m1.printMes();

	// 2、当然我们也可以给定其参数类型(以传入的类型为准)
	Maker1<std::string, double> m2("赵六", 23.14);
	m2.printMes();


}



int main()
{
	// test01();
	test02();


	return 0;
}
