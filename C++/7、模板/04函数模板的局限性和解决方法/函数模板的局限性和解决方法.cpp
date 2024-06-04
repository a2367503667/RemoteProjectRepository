#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>

/*

函数模板的实现机制：
	1、编译器并不是把函数模板处理成能够处理任何类型的函数；

	2、函数模板通过具体类型产生不同的函数；

	3、编译器会对函数模板进行"两次编译"，在声明的地方对函数模板代码本身进行编译，在调用的
	   地方对参数替换后的代码又进行编译。

函数模板的局限性：
	1、如果我们传入函数模板的参数为数组类型，那我们就没办法进行比较，即使可以比较也是
	   这两个数组地址的比较，并不是我们所需要的结果，如：数组a和数组b，传进去之后进行
	   比较if(a > b)，无论如何结果都是一样的(因为本质上是地址之间的比较)，对应的类也是一样
	   传两个类进去比较也会出现一系列的问题，这些比较就算得到结果都是没有意义的；
	
	2、对于上面的可能性，函数模板是无法处理的，有时候我们确实有这个需求，但是C++语法会出问题
	   此时我们可以提供重载的函数模板，然后将这个重载后的模板具体化，这样即可保持原来模板的
	   通用化，也可以使用上面这些特殊的需求函数模板(其中这样就相当于规定好模板了，就失去模板本
	   身通用化的意义了)
*/

template<typename T>
void myCompare(T a, T b)
{
	if (a > b)
	{
		std::cout << "a > b" << std::endl;
	}
	else
	{
		std::cout << "a <= b" << std::endl;
	}
}

void test01()
{
	int a[8] = { 1,2 };
	int b[3] = { 1,2,3 };


	// 局限性(具体如上)
	myCompare(a, b);
}

class Maker1
{
public:
	Maker1(std::string name, int age)
	{
		this->name = name;
		this->age = age;
	}



public:
	std::string name;
	int age;
};

template<typename T>
void myCompare2(T& a, T& b)
{
	if (a > b)
	{
		std::cout << "a > b" << std::endl;
	}
	else
	{
		std::cout << "a <= b" << std::endl;
	}
}

// 函数模板具体化(注：函数模板必须先已经存在，才能够具体化)
/*

步骤：
	
	注：我们一般不要对函数模板进行具体化，因为函数模板具体化会失去通用性(上面已经提到了)
	我们一般都用其他技术实现我们的需求，避开函数模板的具体化

	1、(重点注意)必须先存在需要具体化的函数模板，如果没有函数模板，直接具体化就会报错，提示
	   "不存在函数模板xxx"或"不可识别的模板声明/定义"；
	2、在具体化函数模板前加template<>；
	3、要在函数模板名后面指定参数类型，如下面<Maker1>；
	4、把所有函数模板泛型类型的"T"替换成函数模板后面的类型，如下面
	   (T& m1, T& m2) --> (Maker1& m1, Maker1& m2)
	5、具体化的函数模板如下：
*/
template<> void myCompare2<Maker1>(Maker1& m1, Maker1& m2)
{
	std::cout << "函数模板myCompare2的具体化" << std::endl;
	if (m1.age > m2.age)
	{
		std::cout << "a > b" << std::endl;
	}
	else
	{
		std::cout << "a <= b" << std::endl;
	}
}



void test02()
{
	Maker1 m1("张三", 20);
	Maker1 m2("李四", 21);

	// m1和m2这两个对象不可以直接进行比较
	// myCompare2(m1, m2); // err：在还没重载">"运算符或"具体化"之前是不能够直接进行比较的

	// 要想可以比较，只有两种方法，一种是重载比较运算符，另一种是对函数模板进行实例化
	// 下面就是具体化之后的函数模板
	myCompare2(m1, m2);
}



int main()
{
	// test01();
	test02();


	return 0;
}
