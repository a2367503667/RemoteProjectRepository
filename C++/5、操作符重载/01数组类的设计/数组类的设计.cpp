#include "MyArray.h"

void test01()
{
	// 生成随机数种子
	srand((unsigned)time(nullptr));
	MyArray arr(50, 0, 0);

	int size = 10;
	for (int i = 0; i < size; ++i)
	{
		// 生成0 - 100的随机数
		int num = rand() % 101;
		arr.rearInsert(num);
	}
	arr.printArray();
	std::cout << "-----------------------------------------" << std::endl;
	arr.sortArray();
	arr.printArray();

	/*
		尾删
		for (int i = 0; i < size; ++i)
		{
			arr.delRear();
			arr.printArray();
		}
	*/
	/*
		头删
		for (int i = 0; i < size; ++i)
		{
			arr.delHead();
			arr.printArray();
		}
	*/
	arr.delPos(5);
	arr.printArray();

	arr.posInsert(7, 58);
	arr.printArray();
	arr.sortArray();
	arr.printArray();
}

int main()
{
	test01();


	return 0;
}
