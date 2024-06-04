#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

// 复数计算要求：类型可以是int、double
template<class T>
class MyComplexCalculate
{
public:
	MyComplexCalculate()
	{
		this->a = 0;
		this->b = 0;
	}
	MyComplexCalculate(T a, T b)
	{
		this->a = a;
		this->b = b;
	}

	MyComplexCalculate operator+(const MyComplexCalculate& c)
	{
		return MyComplexCalculate(this->a + c.a, this->b + c.b);
	}

	MyComplexCalculate operator-(const MyComplexCalculate& c)
	{
		return MyComplexCalculate(this->a - c.a, this->b - c.b);
	}

	MyComplexCalculate operator*(const MyComplexCalculate& c)
	{
		return MyComplexCalculate(this->a * c.a - this->b * c.b, this->a * c.b + this->b * c.a);
	}

	void printComplex()
	{
		if (b >= 0)
		{
			if (this->a == 0 && this->b != 0)
			{
				std::cout << "复数值为：" << this->b << "i" << std::endl;
			}
			else if (this->a != 0 && this->b == 0)
			{
				std::cout << "复数值为：" << this->a << std::endl;
			}
			else if (this->a == 0 && this->b == 0)
			{
				std::cout << "复数值为：" << 0 << std::endl;
			}
			else
			{
				std::cout << "复数值为：" << this->a << " + " << this->b << "i" << std::endl;
			}
		}
		else
		{
			if (a == 0)
			{
				std::cout << "复数值为：" << this->a << this->b << "i" << std::endl;
			}
			else
			{
				std::cout << "复数值为：" << this->a << " - " << -(this->b) << "i" << std::endl;
			}
		}
	}

private:
	T a;
	T b;
};

void test01()
{
	// 1、复数整数运算
	MyComplexCalculate<int> m1(20, -5);
	MyComplexCalculate<int> m2(3, 9);

	// (1)复数加法
	MyComplexCalculate<int> m3 = m1 + m2;
	m3.printComplex();

	// (2)复数减法
	m3 = m1 - m2;
	m3.printComplex();

	// (3)复数乘法
	m3 = m1 * m2;
	m3.printComplex();

	std::cout << "-------------------------------" << std::endl;
	// ---------------------------------
	// 2、复数浮点数运算
	MyComplexCalculate<double> m11(3.14, -5.7);
	MyComplexCalculate<double> m22(4.64, 9.38);

	// (1)复数加法
	MyComplexCalculate<double> m33 = m11 + m22;
	m33.printComplex();

	// (2)复数减法
	m33 = m11 - m22;
	m33.printComplex();

	// (3)复数乘法
	m33 = m11 * m22;
	m33.printComplex();

}


int main()
{
	test01();


	return 0;
}
