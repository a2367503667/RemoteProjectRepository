#include "MyClass.hpp"

// 我们先在这里进行类模板的实现(还没将下面代码注释)
//template<typename NameType, typename AgeType>
//Maker<NameType, AgeType>::Maker(NameType name, AgeType age)
//{
//	this->name = name;
//	this->age = age;
//}
//
//template<typename NameType, typename AgeType>
//void Maker<NameType, AgeType>::printMes()
//{
//	std::cout << "name = " << this->name << "，age = " << this->age << std::endl;
//}

// 我们发现我们在cpp文件里面进行类模板实现，hpp文件里面声明会报错
#include "MyClass.hpp"
//template<typename T>
//void func01(T a)
//{
//	std::cout << "func01(T a)" << std::endl;
//}

