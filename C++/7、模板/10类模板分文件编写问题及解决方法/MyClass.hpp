#ifndef __MYCLASS_HPP__
#define __MYCLASS_HPP__
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

template<class NameType, class AgeType>
class Maker
{
public:
	Maker(NameType name, AgeType age);
	void printMes();
private:
	NameType name;
	AgeType age;
};

// 类模板成员函数的实现必须写在头文件里面
template<typename NameType, typename AgeType>
Maker<NameType, AgeType>::Maker(NameType name, AgeType age)
{
	this->name = name;
	this->age = age;
}

template<typename NameType, typename AgeType>
void Maker<NameType, AgeType>::printMes()
{
	std::cout << "name = " << this->name << "，age = " << this->age << std::endl;
}

// 同样道理，函数模板要想多文件使用，就需要在头文件中实现函数
template<typename T>
// 需要注意的是，需要在函数签名前加上inline(具体原因见main文件)
// 并且在系统头文件中的对应"函数模板"和"函数模板具体化函数"也加了inline关键字
// 其实目的也是按照main文件里面写的一样(具体原因见main文件)
inline void func01(T a)
{
	std::cout << "func01(T a)" << std::endl;
}

inline void func02()
{
	for (int i = 0; i < 10; ++i)
	{
		std::cout << "func02" << std::endl;
	}
}

#endif
