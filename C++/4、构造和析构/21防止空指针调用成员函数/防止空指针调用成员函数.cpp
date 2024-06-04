#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

class Maker1
{
public:
	Maker1()
	{
		if (this == nullptr)
		{
			std::cout << "this == nullptr" << std::endl;
			return;
		}
		this->a = 10;
		this->b = 20;
	}

	void printVal()
	{
		// 这一层就是防止this为nullptr指针，去访问成员变量
		if (this == nullptr)
		{
			std::cout << "this == nullptr" << std::endl;
			return;
		}
		std::cout << "a = " << this->a << " b = " << this->b << std::endl;
	}

private:
	int a;
	int b;
};

void test01()
{
	Maker1* m1 = nullptr;

	// 这里会报错，因为m1这个指针本质上就是一个指向对象的指针，也就是相当于成员函数
	// 中的this，那我们开始就把指针m1赋值为nullptr，那就意味着这个对象里面的this指针为nullptr
	// 我们成员函数里面默认就是使用this去访问成员变量数据的，那就变成了用nullptr指针去访问
	// 成员变量数据了，因此就会报错

	// 为了防止指针对象this为nullptr，去访问类的成员数据，我们应该在成员函数的开头做
	// 一层校验判断if(this==nullptr)，所有函数都加了之后，就不会报错了
	// 但是我们还是尽量不要使用空指针去访问数据，这样很容易会出现问题
	m1->printVal();


}


int main()
{
	test01();

	return 0;
}
