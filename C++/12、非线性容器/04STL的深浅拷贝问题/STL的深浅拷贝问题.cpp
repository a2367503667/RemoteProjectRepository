#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <set>
using namespace std;

class MyArray
{
public:
	MyArray()
	{
		this->arr = new int[100];
		this->mSize = 0;
		this->mCapacity = 100;

		for (int i = 0; i < this->mCapacity; ++i)
		{
			*(this->arr + i) = 0;
		}
	}

	MyArray(int capacity, int size, int val)
	{
		this->mCapacity = capacity;
		this->mSize = size;
		this->arr = new int[this->mCapacity];

		for (int i = 0; i < this->mCapacity; ++i)
		{
			if (i < this->mSize)
			{
				*(this->arr + i) = val;
			}
			else
			{
				*(this->arr + i) = 0;
			}
		}
	}

	// 如果自定义类型中，有申请空间，就需要自定义拷贝函数和赋值函数
	// 拷贝构造函数
	MyArray(const MyArray& myarr)
	{
		this->mCapacity = myarr.mCapacity;
		this->mSize = myarr.mSize;
		this->arr = new int[this->mCapacity];

		for (int i = 0; i < this->mCapacity; ++i)
		{
			*(this->arr + i) = *(myarr.arr + i);
		}
	}

	// 赋值函数
	MyArray& operator=(const MyArray& myarr)
	{
		if (this->arr != nullptr)
		{
			delete this->arr;
			this->arr = nullptr;
		}

		this->mCapacity = myarr.mCapacity;
		this->mSize = myarr.mSize;
		this->arr = new int[this->mCapacity];

		for (int i = 0; i < this->mCapacity; ++i)
		{
			*(this->arr + i) = *(myarr.arr + i);
		}

		return *this;
	}

	void printArray()
	{
		for (int i = 0; i < this->mSize; ++i)
		{
			if (i == this->mSize - 1)
			{
				cout << *(this->arr + i) << endl;
			}
			else
			{
				cout << *(this->arr + i) << " ";
			}
		}
	}

	// 设置为const类型
	int getCapacity()const
	{
		return this->mCapacity;
	}

	~MyArray()
	{
		if (this->arr != nullptr)
		{
			delete this->arr;
			this->arr = nullptr;
		}
	}
private:
	int* arr;
	int mSize;
	int mCapacity;
};

struct MyCompare
{
	// 需要注意的是谓词需要将整体设置为const类型
	bool operator()(const MyArray& val1, const MyArray& val2) const
	{
		return val1.getCapacity() > val2.getCapacity();
	}
};

void test01()
{
	// 函数对象模板的类型中不需要加()
	set<MyArray, MyCompare> mys1;
	MyArray m1(50, 20, 8);

	// 这里本质上是将m1拷贝一份到mys1中去，所以会调用MyArray的拷贝构造函数
	// 如果自定义类中有动态分配空间，那就需要重载拷贝构造函数和赋值函数
	mys1.insert(m1);

	// 函数对象在模板的类型中不需要加()
	set<MyArray, MyCompare>::iterator it1 = mys1.find(m1);
	if (it1 == mys1.end())
	{
		cout << "查找失败" << endl;
	}
	else
	{
		cout << "查找成功，结果如下：" << endl;
		MyArray temp = *it1;
		temp.printArray();
	}
}


int main(int argc, char* argv[])
{
	test01();

	return 0;
}
