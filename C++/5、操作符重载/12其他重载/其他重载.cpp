#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

/*
	还有其他符号重载，如"&"、"|"、"^"、"~"以及"!"等等，还可以重载普通类型，好
	比如：int、bool、double等等，这些都可以按需求来重载
*/

class Maker1
{
public:
	Maker1(int num1, double dNum2) :num1(num1), dNum2(dNum2) {}

	void printNum()
	{
		std::cout << "num1 = " << this->num1 << "，dNum2 = " << this->dNum2 << std::endl;
	}

	// 1、重载"&"
	bool operator&(const Maker1& m)
	{
		// 只要本对象的成员都不为0并且m对象的成员也都不为0，即可返回true，否则返回false
		return(this->num1 != 0 && this->dNum2 != 0) && (m.dNum2 != 0 && m.num1 != 0);
	}

	// 2、重载"|"
	bool operator|(const Maker1& m)
	{
		// 两个对象只要有一个对象的成员都不为0，则返回true，否则返回false
		return this->num1 != 0 && this->dNum2 != 0 || m.num1 != 0 && m.dNum2 != 0;
	}

	// 3、重载"^"(两个对象的对应成员进行异或运算，其实和"+"一样返回的不是对象本身，因为
	// a^b这个只是一个运算结果，这个运算过后并没有改变a的值，所以需要用临时对象去运算，最后
	// 返回一个结果，而且还需要注意的是，"^"运算只支持整型运算，不支持浮点型运算)
	Maker1 operator^(const Maker1& m)
	{
		// 因为没有提供无参构造，所以就用拷贝构造了，如果有无参构造也可以使用无参构造
		Maker1 temp(*this);
		temp.num1 ^= m.num1;
		return temp;
	}

	// 4、重载"~"(对本对象的成员进行"~"操作，返回对象本身即可，同理"~"运算也是需要整型数据
	// 不能使用浮点数)
	Maker1& operator~()
	{
		(*this).num1 = ~(*this).num1;

		return *this;
	}

	// 5、重载"!"(表示当前对像如果有元素为0的时候，才为true，否则为false)
	bool operator!()
	{
		return !(this->num1 != 0 && this->dNum2 != 0);
	}

	// 6、重载"bool"类型(注：重载类型没有返回值，重载"bool"后，可以把对象作为判断条件，就
	// 好比如if(m)，其中m是对象，如果不重载的话，是不能够作为判断条件的)
	operator bool()
	{
		return (*this).num1 != 0 && (*this).dNum2 != 0;
	}

	// 7、重载"int"(重载int之后，(int)m就会表示100，但是最好不要重载int类型，一般也没有人去重
	// 载int类型)
	operator int()
	{
		return 100;
	}

	// 8、重载"double"(这个也是同理，(double)m就会表示3.1415，但是一般没有人重载double类型)
	operator double()
	{
		return 3.1415;
	}

private:
	int num1;
	double dNum2;
};

void test01()
{
	// 下面就举几个例子即可
	Maker1 m1(888, 3.14);

	// 重载"bool"
	if (m1)
	{
		std::cout << "m1为true" << std::endl;
	}
	else
	{
		std::cout << "m1为false" << std::endl;
	}

	// 重载"!"
	if (!m1)
	{
		std::cout << "(!m1)为true" << std::endl;
	}
	else
	{
		std::cout << "(!m1)为false" << std::endl;
	}

	// 重载"int"
	int a = (int)m1;
	std::cout << "a = " << a << std::endl;

	// 重载"double"
	double b = (double)m1;
	std::cout << "b = " << b << std::endl;
}



int main()
{
	test01();

	return 0;
}
