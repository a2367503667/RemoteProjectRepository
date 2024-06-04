#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
// 这个是标准异常类头文件库，需要包含(好像高版本的VS可以不包含，但是最好写一下)
#include <stdexcept> 
#include <string>

/*
	
	下面是常见的异常类：

	1、标准异常类的具体描述：格式("异常名称"：描述)

	(1)"exception"：所有标准异常类的父类

	(2)"bad_alloc"：当operator new and operator new[]，请求分配内存失败时

	(3)"bad_exception"：这是个特殊的异常，如果函数的异常抛出列表里声明了bad_exception异常，
					    当函数内部抛出了异常抛出列表中没有的异常，这时调用的unexpected函数
					    中若抛出异常，不论什么类型，都会被替换为bad_exception类型

	(4)"bad_typeid"：使用typeid操作符，操作一个NULL指针，而该指针是带有虚函数的类，这时抛
				     出bad_typeid异常

	(5)"bad_cast"：使用dynamic_cast转换引用失败的时候

	(6)"ios_base::failure"：io操作过程出现错误

	(7)"logic_error"：逻辑错误，可以在运行前检测的错误

	(8)"runtime_error"：运行时错误，仅在运行时才可以检测的错误

	=====================================================================================

	2、logic_error的子类：格式("异常名称"：描述)

	(1)"length_error"：试图生成一个超出该类型最大长度的对象时，例如vector的resize操作

	(2)"domain_error"：参数的值域错误，主要用在数学函数中。例如使用一个负值调用只能操作非负数的函数

	(3)"out_of_range"：超出有效范围

	(4)"invalid_argument"：参数不合适。在标准库中，当利用string对象构造bitset时，而string中的字
						   符不是’0’或’1’的时候，抛出该异常
	
	=============================================================================================

	3、runtime_error的子类：格式("异常名称"：描述)

	(1)"range_error"：计算结果超出了有意义的值域范围

	(2)"overflow_error"：算术计算上溢

	(3)"underflow_error"：算术计算下溢

	(4)"invalid_argument"：参数不合适。在标准库中，当利用string对象构造bitset时，而string中的
						   字符不是’0’或’1’的时候，抛出该异常


	以上标准异常类的成员：
	
	① 在上述继承体系中，每个类都有提供了"构造函数"、"拷贝构造函数"和"赋值操作符重载"。

	② "logic_error类"及其子类、"runtime_error类"及其子类，它们的构造函数是接受一个"string类型"的
	形式参数，用于异常信息的描述

	③ 所有的异常类都有一个what()方法，返回const char* 类型（C风格字符串）的值，描述异常信息。
	其中书写形式为"virtual const char * what() const override{}"

*/

// 1、抛出out_of_range异常类
class MyRangeError
{
public:
	MyRangeError(int age)
	{
		if (age < 0 || age>150)
		{
			// 直接给out_of_range对象赋值"年龄超出合法范围"后，它的what()函数就会返回"年龄
			// 超出合法范围"
			throw std::out_of_range("年龄超出合法范围");
		}
		else
		{
			this->age = age;
		}
	}

private:
	int age;
};

void func01()
{
	try
	{
		MyRangeError m1(250);
	}
	catch (std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}
}

void test01()
{
	func01();
}

// ----------------------------------------



// 2、继承exception异常父类，自己书写异常类
class MyException : public std::exception
{
public:
	MyException(std::string exceptWarn)
	{
		this->exceptWarn = exceptWarn;
	}

	MyException(const char* exceptWarn)
	{
		this->exceptWarn = exceptWarn;
	}

	virtual const char* what()const override
	{
		return this->exceptWarn.c_str();
	}
private:
	std::string exceptWarn;
};

// 使用自定义的异常类MyException
class Maker2
{
public:
	Maker2(int mCapacity)
	{
		this->mSize = 0;
		if (mCapacity > 100 || mCapacity < 0)
		{
			throw MyException("数组容量超出范围");
		}
		else
		{
			this->mCapacity = mCapacity;
		}
	}

private:
	int mSize;
	int mCapacity;
	int arr[100];
};

void func02()
{
	try
	{
		Maker2 m2(200);
	}
	catch (std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}
}

void test02()
{
	func02();
}


int main()
{
	// test01();
	test02();


	return 0;
}
