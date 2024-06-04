#include "MyArray.h"

// 数组类结构实现

// 默认容量为100，大小为20
MyArray::MyArray()
{
	this->mCapacity = 100;
	this->mSize = 0;
	this->pArray = new int[this->mCapacity];

	// 默认数组初始化为0
	for (int i = 0; i < this->mCapacity; ++i)
	{
		this->pArray[i] = 0;
	}
}
MyArray::MyArray(const MyArray& arr)
{
	if (arr.pArray == nullptr)
	{
		return;
	}
	this->mCapacity = arr.mCapacity;
	this->mSize = arr.mSize;
	this->pArray = new int[this->mCapacity];
	for (int i = 0; i < this->mCapacity; ++i)
	{
		this->pArray[i] = 0;
	}
}

// 数组容量 大小 初始值 
MyArray::MyArray(int capacity, int size, int val)
{
	this->mCapacity = capacity;
	this->mSize = size;
	this->pArray = new int[this->mCapacity];
	for (int i = 0; i < this->mCapacity; ++i) 
	{
		this->pArray[i] = val;
	}
}

// 头插数据
void MyArray::headInsert(int val)
{
	if (isFull())
	{
		std::cout << "数组已满" << std::endl;
		return;
	}
	
	int size = getSize();
	for (int i = size - 1; i >= 0; --i)
	{
		this->pArray[i + 1] = this->pArray[i];
	}
	this->pArray[0] = val;
	++this->mSize;
}

// 尾插数据
void MyArray::rearInsert(int val)
{
	if (isFull())
	{
		std::cout << "数组已满" << std::endl;
		return;
	}

	int size = getSize();
	this->pArray[size] = val;
	++this->mSize;
}

// 某个位置插入数据
void MyArray::posInsert(int pos, int val)
{
	int size = getSize();
	if (isFull() || pos<0 || pos>size - 1)
	{
		std::cout << "数组已满或pos不合法" << std::endl;
		return;
	}

	for (int i = size - 1; i >= pos; --i)
	{
		this->pArray[i + 1] = this->pArray[i];
	}
	this->pArray[pos] = val;
	++this->mSize;
}

// 头部删除数据(返回第一个数据)
int MyArray::delHead()
{
	if (isEmpty())
	{
		std::cout << "数组为空" << std::endl;
		return -1; // 这里不处理异常，直接返回-1
	}

	int tVal = this->pArray[0];
	int size = getSize();
	for (int i = 0; i < size - 1; ++i)
	{
		this->pArray[i] = this->pArray[i + 1];
	}
	--this->mSize;
	return tVal;
}

// 尾部删除数据(返回最后的数据)
int MyArray::delRear()
{
	if (isEmpty())
	{
		std::cout << "数组为空" << std::endl;
		return -1; // 找不到不处理异常，返回-1
	}

	int size = this->mSize;
	int tVal = this->pArray[size - 1];
	--this->mSize;
	return tVal;
}

// 删除某位置的数据
int MyArray::delPos(int pos)
{
	int size = getSize();
	if (isEmpty() || pos<0 || pos>size - 1)
	{
		std::cout << "数组为空或者pos不合法" << std::endl;
		return -1; // 这里不处理异常，直接返回-1
	}

	int val = this->pArray[pos];
	for (int i = pos; i < size - 1; ++i)
	{
		this->pArray[i] = this->pArray[i + 1];
	}
	--this->mSize;
}

// 获取数组容量
int MyArray::getCapacity()
{
	return this->mCapacity;
}

// 获取数组大小
int MyArray::getSize()
{
	return this->mSize;
}

// 数组排序(默认升序)
void MyArray::sortArray()
{
	int size = getSize();
	quickSort(0, size - 1);
}

// 输出数组元素
void MyArray::printArray()
{
	if (isEmpty())
	{
		std::cout << "数组为空" << std::endl;
		return;
	}
	std::cout << "数组的序列为：";
	int size = getSize();
	for (int i = 0; i < size; ++i)
	{
		if (i == size - 1)
		{
			std::cout << this->pArray[i] << std::endl;
		}
		else
		{
			std::cout << this->pArray[i] << " ";
		}
	}
}

// 快排源码
void MyArray::quickSort(int l, int r)
{
	if (l < r)
	{
		int val = this->pArray[l];
		int i = l;
		int j = r;

		while (i < j)
		{
			while (i < j && this->pArray[j] >= val)
			{
				--j;
			}
			if (i < j)
			{
				this->pArray[i] = this->pArray[j];
				++i;
			}
			while (i < j && this->pArray[i] <= val)
			{
				++i;
			}
			if (i < j)
			{
				this->pArray[j] = this->pArray[i];
				--j;
			}
		}
		this->pArray[i] = val;
		quickSort(l, i - 1);
		quickSort(i + 1, r);
	}
}

// 数组判空
bool MyArray::isEmpty()
{
	return this->mSize == 0;
}

// 数组判满
bool MyArray::isFull()
{
	return this->mCapacity == this->mSize;
}

MyArray::~MyArray()
{
	if (this->pArray != nullptr)
	{
		delete[] this->pArray;
		this->pArray = nullptr;
	}
}
