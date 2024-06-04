#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>

// 初识STL
template<class T>
class Maker
{
public:
	// 保护原生指针，给原生指针取别名
	typedef T* iterator;

	Maker()
	{
		this->mCapacity = 0;
		this->mSize = 0;
		this->myArr = new T[this->mCapacity];

		for (int i = 0; i < 100; ++i)
		{
			this->myArr[i] = 0;
		}
	}

	Maker(int capacity, int size, T val)
	{
		this->mCapacity = capacity;
		this->mSize = size;
		this->myArr = new T[this->mCapacity];

		for (int i = 0; i < this->mCapacity; ++i)
		{
			if (i < this->mSize)
			{
				// this->myArr[i] = val;
				this->myArr[i] = val + i;
			}
			else
			{
				this->myArr[i] = 0;
			}
		}
	}

	Maker(int capacity)
	{
		this->mCapacity = capacity;
		this->mSize = 0;
		this->myArr = new T[this->mCapacity];

		for (int i = 0; i < this->mCapacity; ++i)
		{
			this->myArr[i] = 0;
		}
	}

	Maker(const Maker& arr)
	{
		this->mCapacity = arr.mCapacity;
		this->mSize = arr.mSize;

		this->myArr = new T[this->mCapacity];
		for (int i = 0; i < this->mCapacity; ++i)
		{
			this->myArr[i] = arr.myArr[i];
		}
	}

	Maker& operator=(const Maker& arr)
	{
		if (this->myArr != nullptr)
		{
			delete[] this->myArr;
			this->myArr = nullptr;
		}
		this->mCapacity = arr.mCapacity;
		this->mSize = arr.mSize;

		this->myArr = new T[this->mCapacity];
		for (int i = 0; i < this->mCapacity; ++i)
		{
			this->myArr[i] = arr.myArr[i];
		}

		return *this;
	}

	void printArr()
	{
		for (int i = 0; i < this->mSize; ++i)
		{
			std::cout << "myArr[" << i << "] = " << this->myArr[i] << std::endl;
		}
	}

	// 提供开始迭代器
	T* begin()
	{
		return this->myArr;
	}

	// 提供结束迭代器
	T* end()
	{
		return this->myArr + this->mSize;
	}

	~Maker()
	{
		if (this->myArr != nullptr)
		{
			delete[] this->myArr;
			this->myArr = nullptr;
		}
	}

private:
	T* myArr;
	int mSize;
	int mCapacity;
};

// 在类外实现遍历算法，将数据结构和算法分开
template<typename T>
void printArr(T begin, T end)
{
	for (int i = 0; begin != end; ++i, ++begin)
	{
		std::cout << "myArr[" << i << "] = " << *begin << std::endl;
	}
}

void test01()
{
	Maker<int> arr(100, 10, 5);

	// arr.printArr();

	// 获取开始迭代器和结束迭代器
	Maker<int>::iterator begin = arr.begin();
	Maker<int>::iterator end = arr.end();

	// 使用迭代器和算法对容器进行遍历
	printArr<Maker<int>::iterator>(begin, end);

}



int main(int argc, char* argv[])
{
	test01();


	return 0;
}
