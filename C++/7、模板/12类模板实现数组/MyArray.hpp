#ifndef __MYARRAY_H__
#define __MYARRAY_H__

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

template<class ArrayType>
class MyArray;


template<class ArrayType>
class MyArray
{
	friend std::ostream& operator<<(std::ostream& out, const ArrayType& a)
	{
		out << a;
		return out;
	}
	friend std::istream& operator>>(std::istream& in, ArrayType& a)
	{
		in >> a;
		return in;
	}
public:
	MyArray()
	{
		if (this == nullptr)
		{
			return;
		}
		this->mSize = 0;
		this->mCapacity = 0;
		this->arr = new ArrayType[1];
	}

	MyArray(int mCapacity)
	{
		if (this == nullptr)
		{
			return;
		}
		this->mCapacity = mCapacity;
		this->mSize = 0;
		this->arr = new ArrayType[this->mCapacity];
	}

	MyArray(const MyArray& a)
	{
		if (this == nullptr)
		{
			return;
		}
		this->mCapacity = a.mCapacity;
		this->mSize = a.mSize;
		this->arr = new ArrayType[this->mCapacity];

		for (int i = 0; i < this->mCapacity; ++i)
		{
			this->arr[i] = 0;
		}

		for (int i = 0; i < this->mCapacity; ++i)
		{
			this->arr[i] = a.arr[i];
		}
	}

	MyArray& operator=(const MyArray& a)
	{
		if (this->arr != nullptr)
		{
			delete[] this->arr;
			this->arr = nullptr;
		}

		this->mCapacity = a.mCapacity;
		this->mSize = a.mSize;
		this->arr = new ArrayType[this->mCapacity];

		for (int i = 0; i < this->mCapacity; ++i)
		{
			this->arr[i] = 0;
		}

		for (int i = 0; i < this->mCapacity; ++i)
		{
			this->arr[i] = a.arr[i];
		}

		return *this;
	}

	ArrayType& operator[](int pos)
	{
		if (this->mSize <= pos)
		{
			++this->mSize;
		}
		return this->arr[pos];
	}

	// 判满
	int isFull()
	{
		return this->mCapacity == this->mSize;
	}

	// 判空
	int isEmpty()
	{
		return this->mSize == 0;
	}

	// 头插法
	void headInsertData(ArrayType data)
	{
		if (this == nullptr || isFull())
		{
			return;
		}

		for (int i = this->mSize; i >= 1; --i)
		{
			this->arr[i] = this->arr[i - 1];
		}

		this->arr[0] = data;
		++this->mSize;
	}

	// 尾插法
	void rearInsertData(ArrayType data)
	{
		if (this == nullptr || isFull())
		{
			return;
		}
		this->arr[this->mSize++] = data;
	}

	// 在某个位置插入元素
	void posAddData(ArrayType data, int pos)
	{
		if (this == nullptr || isFull() || pos<0 || pos>this->mSize)
		{
			return;
		}

		for (int i = this->mSize; i > pos; --i)
		{
			this->arr[i] = this->arr[i - 1];
		}
		this->arr[pos] = data;
		++this->mSize;
	}

	// 头删
	void headDelData()
	{
		if (this == nullptr || isEmpty())
		{
			return;
		}

		for (int i = 0; i < this->mSize - 1; ++i)
		{
			this->arr[i] = this->arr[i + 1];
		}
		--this->mSize;
	}

	// 尾删
	void rearDelData()
	{
		if (this == nullptr || isEmpty())
		{
			return;
		}
		--this->mSize;
	}

	// 删除某个位置的元素
	void posDelData(int pos)
	{
		if (this == nullptr || isEmpty() || pos<0 || pos>this->mSize)
		{
			return;
		}

		for (int i = pos; i < this->mSize - 1; ++i)
		{
			this->arr[i] = this->arr[i + 1];
		}
		--this->mSize;
	}

	// 快速排序
	void quickSort()
	{
		if (this == nullptr || isEmpty())
		{
			return;
		}
		quickSort(0, this->mSize - 1);
	}

	// 打印数组数据
	void printArr()
	{
		if (this == nullptr || isEmpty())
		{
			return;
		}
		std::cout << "[";

		for (int i = 0; i < this->mSize; ++i)
		{
			if (i == this->mSize - 1)
			{
				std::cout << this->arr[i];
			}
			else
			{
				std::cout << this->arr[i] << ", ";
			}
		}
		std::cout << "]" << std::endl;
	}
	
	// 获取数组长度
	int getMySize()
	{
		return this->mSize;
	}

	~MyArray()
	{
		if (this == nullptr)
		{
			return;
		}
		if (this->arr != nullptr)
		{
			delete[] this->arr;
			this->arr = nullptr;
		}
	}

private:
	// 快速排序
	void quickSort(int l, int r)
	{
		if (this == nullptr)
		{
			return;
		}
		if (l < r)
		{
			int i = l;
			int j = r;
			ArrayType e = this->arr[i];

			while (i < j)
			{
				while (i < j && e <= this->arr[j])
				{
					--j;
				}
				if (i < j)
				{
					this->arr[i] = this->arr[j];
					++i;
				}
				while (i < j && e >= this->arr[i])
				{
					++i;
				}
				if (i < j)
				{
					this->arr[j] = this->arr[i];
					--j;
				}
			}
			this->arr[i] = e;

			quickSort(l, i);
			quickSort(i + 1, r);
		}
	}

private:
	int mSize;
	int mCapacity;
	ArrayType* arr;
};




#endif
