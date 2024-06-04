#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>

template<class NameType, class AgeType>
class Maker
{
public:
	Maker(NameType name, AgeType age);
		//:name(name), age(age) {}

	// 1、类模板成员函数的类内实现(这个比较简单)
	void printMes();
	//{
	//	std::cout << "name = " << this->name << "，age = " << this->age << std::endl;
	//}

	void modifyName(NameType name);

	void func();

	void func02();
private:
	NameType name;
	AgeType age;
};

// 2、类模板的成员函数类外实现
/*
	注：类模板在类外实现时，需要指定类模板的数据类型，但是我们不好指定类型
		由于泛型理论上是可以支持任意类型的，如果我们在类外就确定好了类模板的值
		那该成员函数就失去了通用性从而失去泛型的意义，因此我们在类外实现类模板的成
		员函数也是写成泛型的形式，即成员函数模板，其中同样也需要指定类模板的数据类型
		如下面的写法：
*/

template<typename NameType, typename AgeType>
void Maker<NameType, AgeType>::modifyName(NameType name)
{
	this->name = name;
}

/*
	这里是在类外实现类模板Maker的成员函数，但是这种方式是极其不推荐的，因为
	这样就是上面所描述的，已经指定了类模板的数据类型，那这个成员函数就失去了原本
	所具有的通用性，也就失去了泛型编程的意义，因此下面的写法最好不要出现
*/
void Maker<std::string, int>::func()
{
	this->age = 30;
}

/*
	千万不要出现这种写法，Maker是一个类模板，必须指定类型，否则报错(这个点已经多次强调了)
	template<typename NameType, typename AgeType>
	void Maker::func02()
	{

	}

	下面这种才是正确写法：
*/
template<typename NameType,typename AgeType>
void Maker<NameType, AgeType>::func02()
{

}
template<typename NameType,typename AgeType>
void Maker<NameType, AgeType>::printMes()
{
	std::cout << "name = " << this->name << "，age = " << this->age << std::endl;
}

template<typename NameType,typename AgeType>
Maker<NameType, AgeType>::Maker(NameType name, AgeType age)
{
	this->name = name;
	this->age = age;
}

// 以上的实现都是类模板成员函数的类外实现
void test01()
{
	Maker<std::string, int> m("张三", 20);
	m.printMes();
}


int main()
{
	test01();

	return 0;
}
