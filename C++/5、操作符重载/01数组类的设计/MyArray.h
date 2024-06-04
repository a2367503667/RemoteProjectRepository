#ifndef __MYARRAY_H__
#define __MYARRAY_H__
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include <ctime>

// 数组类结构
class MyArray
{
public:
	MyArray();
	MyArray(const MyArray& arr);
	MyArray(int capacity, int size, int val); // 数组容量 大小 初始值 

	// 头插数据
	void headInsert(int val);

	// 尾插数据
	void rearInsert(int val);

	// 某个位置插入数据
	void posInsert(int pos, int val);

	// 头部删除数据
	int delHead();

	// 尾部删除数据
	int delRear();

	// 删除某位置的数据
	int delPos(int pos);

	// 获取数组容量
	int getCapacity();

	// 获取数组大小
	int getSize();

	// 数组排序(默认升序)
	void sortArray();

	// 输出数据
	void printArray();

	~MyArray();

private:
	// 数组判空
	bool isEmpty();

	// 数组判满
	bool isFull();

	// 快排源码
	void quickSort(int l, int r);

private:
	int* pArray; // 数组
	int mSize; // 数组大小
	int mCapacity; // 数组容量
};




#endif
