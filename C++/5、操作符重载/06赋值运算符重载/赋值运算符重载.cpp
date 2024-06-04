#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

/*
	赋值运算符函数也是空类中默认四大方法之一，其中我们学过：默认构造、拷贝构造、析构
	而赋值运算符函数也是其中之一，一般情况下，我们都会去自己重写赋值运算符函数，因为它和
	拷贝构造函数一样存在浅拷贝的问题，因为赋值运算符函数是属于直接复制，如：m1 = m2，其中会
	把m2的所有数据复制到m1当中，那如果m2中存在动态申请空间，此时我们在这两个对象m1和m2都会释
	放，那就会出现一个空间释放两次的情况，因此，我们也需要解决这个问题。
*/


class Maker1
{
public:
	Maker1()
	{
		this->pArray = nullptr;
		this->mSize = 0;

		this->pArray = new int[100];
		this->mSize = 100;

		for (int i = 0; i < this->mSize; ++i)
		{
			this->pArray[i] = 0;
		}
	}

	Maker1(int mSize)
	{
		this->mSize = mSize;
		this->pArray = new int[this->mSize];

		for (int i = 0; i < this->mSize; ++i)
		{
			this->pArray[i] = 0;
		}
	}

	// 存在动态申请空间，必须要重新自己写拷贝构造函数
	Maker1(const Maker1& m)
	{
		if (this->pArray == nullptr)
		{
			return;
		}
		this->pArray = new int[m.mSize];
		this->mSize = m.mSize;

		for (int i = 0; i < this->mSize; ++i)
		{
			this->pArray[i] = 0;
		}
	}

	// 除了要写重新写拷贝构造函数之外，还需要写赋值运算符函数
	// 其中返回值是引用，是因为我们会有这种等式m1 = m2 = m3，这个赋值顺序就是m3把值赋给m2,
	// 紧接着m2把值赋给m1，最后完成赋值操作，然后我们返回值写void的话就不能采用这种链式编程
	// 并且如果我们返回值不是Maker1的引用的话，我们它就会在赋值的时候调用拷贝构造，并且达不到
	//m3把值赋给m2,m2把值赋给m1这种效果，这也改变了赋值运算符本身的含义，因此返回值必须是Maker1&
	Maker1& operator=(const Maker1& m)
	{
		// 1、先检查本对象(this)所对应的动态申请空间指针是否为nullptr，如果不为空则先释放空间
		if (this->pArray != nullptr)
		{
			delete[] this->pArray;
			this->pArray = nullptr;
		}

		// 2、释放空间之后就重新动态申请一个和m对象大小相同的空间，并且把值赋值给本对象(this)即可
		this->mSize = m.mSize;
		this->pArray = new int[this->mSize];

		for (int i = 0; i < this->mSize; ++i)
		{
			this->pArray[i] = 0;
		}

		// 最后返回的是自己本身，为什么？
		// 设m1 = m2，即是m1本身去调用赋值运算符函数，最后把m2的值赋给m1，如果还有一个对象m
		// 有关系m = m1 = m2，m = m1这个部分应该是m1的值赋值给m，那就是说我们m1 = m2运算完的结果
		// 需要返回m1，也就是赋值运算符的调用者，即返回this本身(注意是引用，所以是*this)
		return *this;
	}

	~Maker1()
	{
		if (this->pArray != nullptr)
		{
			delete[] this->pArray;
			this->pArray = nullptr;
		}
	}
private:
	int* pArray; // 数组
	int mSize; // 数组元素个数
};

void test01()
{
	Maker1 m1;

	Maker1 m2(50);

	m1 = m2;
}


int main()
{
	test01();

	return 0;
}
