#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

/*
	前置++和后置++一般用于整型的+1操作(前置--和后置--对应-1操作)，前置++是先完成加法操作得出数据
	而对于后置++是先得出数据再进行操作(有滞后+1特性)，但是这些只适用于整型变量，我们如果想用于类
	的话，我们就需要重载
*/

class Maker1
{
	friend std::ostream& operator<<(std::ostream& out, const Maker1& m);
public:
	Maker1(int num1, int num2) :num1(num1), num2(num2) {}

	// 1、前置++
	// void operator++() 其实使用void 也是可以完成操作的，但是这样就不能用于链式编程了
	// 因为在普通变量当中，可以这样操作++(++a)，也就是说可以一直套用前置++，也就是说返回出来的
	// 值，我们是可以当做左值也可以当右值的，因此这里需要用Maker1&类型
	Maker1& operator++()
	{
		++this->num1;
		++this->num2;

		// 返回本身对象即可，因为我们是通过本对象调用的，并且我们嵌套使用前置++都是调用同一个对象
		return *this; 
	}

	// 2、后置++(因为都是++，如果直接写()就会和前置++冲突，因此这里需要用到占参数int)
	// void operator++(int)首先这样写是不行的，因为我们需要得到对象，因此需要返回值，但是我们
	// 不能够返回一个引用，首先"假象"m是局部变量，不能返回局部变量的引用，其次就是我们后置++是不可以
	// 进行链式编程的，即不存在(a++)++这种情况，也就是说我们既想得到值，又不能返回局部变量引用那
	// 么只能返回一个局部对象m，但是返回去之后也会调用拷贝构造函数，因为m会作为值拷贝出去，拷贝完
	// 之后就会被析构函数释放掉
	Maker1 operator++(int)
	{
		// 我们先考虑一个问题，如果++之后值还不变呢？
		// 其实我们可以先拷贝一个相同的对象m，然后对本对象进行++，最后返回一个"假象"m即可
		Maker1 m(*this);
		++(*this).num1;
		++(*this).num2;

		return m;
	}

	// -------------------------------
	// 前置--和后置--同理

	// 3、前置--
	Maker1& operator--()
	{
		--this->num1;
		--this->num2;
		return *this;
	}

	// 4、后置--
	Maker1 operator--(int)
	{
		Maker1 m(*this);
		--this->num1;
		--this->num2;

		return m;
	}


	void printNum()
	{
		std::cout << "num1 = " << this->num1 << "，num2 = " << this->num2 << std::endl;
	}

private:
	int num1;
	int num2;
};

std::ostream& operator<<(std::ostream& out, const Maker1& m)
{
	out << "num1 = " << m.num1 << "，num2 = " << m.num2;
	return out;
}


void test01()
{
	Maker1 m(10, 20);

	// 1、验证前置++
	std::cout << ++m << std::endl;
	
	// 2、验证后置++
	std::cout << m++ << std::endl; // 输出后再输出一次m
	std::cout << m << std::endl;

	// 3、验证前置--
	std::cout << --m << std::endl;

	// 4、验证后置--
	std::cout << m-- << std::endl; // 输出后再输出一次m
	std::cout << m << std::endl;
}


int main()
{
	test01();

	return 0;
}
