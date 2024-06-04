#define _CRT_SECURE_NO_WARNINGS
#include <iostream>


/*
	减法也是类似的，不详细解释，举例即可
*/
class Maker1
{
	friend Maker1 operator-(Maker1& m1, int num);
public:
	Maker1() :num1(0), num2(0) {}
	Maker1(int num1, int num2) :num1(num1), num2(num2) {}

	void printNum()
	{
		std::cout << "num1 = " << num1 << "，num2 = " << num2 << std::endl;
	}

	Maker1 operator-(Maker1& m)
	{
		return Maker1(this->num1 - m.num1, this->num2 - m.num2);
	}


	~Maker1() {}
private:
	int num1;
	int num2;
};

// Maker对象-int类型
Maker1 operator-(Maker1& m1, int num)
{
	return Maker1(m1.num1-num, m1.num2 - num);
}
void test01()
{
	Maker1 m1(20, 60);
	Maker1 m2(28, 38);

	Maker1 m3 = m1 - m2;
	m3.printNum();

	Maker1 m4 = m1 - 8;
	m4.printNum();

}


int main()
{
	test01();

	return 0;
}
