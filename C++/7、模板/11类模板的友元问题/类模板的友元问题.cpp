#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>

/*
	普通函数与类模板的友元：
	1、类内实现友元；
	2、类外实现友元。
*/

template<class NameType, class AgeType>
class Maker
{
	// 1、普通函数在类模板中实现友元关系
	friend void printMaker(Maker<NameType, AgeType>& m)
	{
		std::cout << "name：" << m.name << "，age：" << m.age << std::endl;
	}

public:
	Maker(NameType name, AgeType age)
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

void test01()
{
	Maker<std::string, int> m("张三", 20);

	// 注：printMaker不是Maker的成员函数，这是它的友元函数，并且它是函数，并不是函数模板
	printMaker(m);
}

// -----------------------------------------
// 下面是类外实现

// 第五点(注意：一定要写清楚类模板的数据类型(即模板签名)，即使声明时没有传入数据类型也需要写上)
template<class NameType, class AgeType>
class Maker2;

// 第四点
// 注：因为这个是函数模板，所以同样需要写上模板签名
template<typename NameType, typename AgeType>
void printMaker2(Maker2<NameType, AgeType>& m);


template<class NameType, class AgeType>
class Maker2
{
	/*
		注：
		1、只"friend void printMaker2(Maker<NameType, AgeType>& m);"这样写的话，它会去找
		   printMaker2这个普通函数，而不是找printMaker2函数模板，这样的话在链接时就找不到
		   printMaker2普通函数，就会报"1个无法解析的外部命令"的错误，那下面就解决这个问题；

		2、首先我们需要在函数签名后面加上空参数列表"<>"；

		3、即使写了"<>"但是还是会报错，这是因为编译器不知道下面是否存在printMaker2这个函数模板
		   即不清楚这个函数模板是否实现，也就是编译器需要知道函数模板结构；

		4、为了解决编译器无法察觉是否有函数模板的实现，我们应该先在前面给出函数模板声明(如上)

		5、但是函数模板给出声明也不行，因为模板中涉及到Maker2，但是声明时还没有类模板，所以
		   还需要对Maker2类模板进行声明(如上)

		通过以上处理后，即可完成友元关系建立
	*/ 
	friend void printMaker2<>(Maker2<NameType, AgeType>& m);
public:
	Maker2(NameType name, AgeType age)
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



// 2、类外实现类模板的友元
// 函数要在类模板外实现友元，只能写成函数模板
template<typename NameType, typename AgeType>
void printMaker2(Maker2<NameType, AgeType>& m)
{
	std::cout << "printMaker2：" << std::endl;
	std::cout << "name = " << m.name << "，age = " << m.age << std::endl;
}

void test02()
{
	Maker2<std::string, int> m("李四", 21);

	printMaker2(m);
}


int main()
{
	// test01();
	test02();

	return 0;
}
