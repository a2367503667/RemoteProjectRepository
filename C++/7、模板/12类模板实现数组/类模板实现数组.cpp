#include "MyArray.hpp"

// 下面是测试案例：分别测试int、char和double
void test01()
{
	srand(unsigned(time(nullptr)));
	MyArray<int>* arr1 = new MyArray<int>(100);

	for (int i = 0; i < 10; ++i)
	{
		(*arr1)[i] = rand() % 101;
	}
	std::cout << "arr1数组的数据为：";
	arr1->printArr();
	
	std::cout << "-----------------------------" << std::endl;

	arr1->quickSort();
	std::cout << "排序后arr1数组的数据为：";
	arr1->printArr();

	std::cout << "-----------------------------" << std::endl;

	std::cout << "头插数据：58" << std::endl;
	arr1->headInsertData(58);
	std::cout << "头插数据后，arr1数组的数据为：";
	arr1->printArr();

	std::cout << "-----------------------------" << std::endl;

	std::cout << "尾插数据：21" << std::endl;
	arr1->rearInsertData(21);
	std::cout << "尾插数据后，arr1数组的数据为：";
	arr1->printArr();

	std::cout << "-----------------------------" << std::endl;

	std::cout << "在3位置插入数据：8" << std::endl;
	arr1->posAddData(8, 3);
	std::cout << "在3位置插入数据：8后，arr1数组的数据为：";
	arr1->printArr();

	std::cout << "-----------------------------" << std::endl;

	arr1->quickSort();
	std::cout << "排序后arr1数组的数据为：";
	arr1->printArr();

	std::cout << "-----------------------------" << std::endl;

	std::cout << "头删元素：" << (*arr1)[0] << std::endl;
	arr1->headDelData();
	std::cout << "头删后arr1数组的数据为：";
	arr1->printArr();

	std::cout << "-----------------------------" << std::endl;

	std::cout << "尾删元素：" << (*arr1)[arr1->getMySize() - 1] << std::endl;
	arr1->rearDelData();
	std::cout << "尾删后arr1数组的数据为：";
	arr1->printArr();

	std::cout << "-----------------------------" << std::endl;

	std::cout << "删除位置为6的元素" <<std::endl;
	arr1->posDelData(6);
	std::cout << "删除后arr1数组的数据为：";
	arr1->printArr();

	std::cout << "-----------------------------" << std::endl;

	MyArray<char>* arr2 = new MyArray<char>(100);

	for (int i = 0; i < 10; ++i)
	{
		(*arr2)[i] = (rand() % 26) + 'A';
	}
	std::cout << "arr2数组的数据为：";
	arr2->printArr();

	std::cout << "-----------------------------" << std::endl;

	arr2->quickSort();
	std::cout << "排序后arr2数组的数据为：";
	arr2->printArr();

	std::cout << "-----------------------------" << std::endl;

	std::cout << "头插数据：J" << std::endl;
	arr2->headInsertData('J');
	std::cout << "头插数据后，arr2数组的数据为：";
	arr2->printArr();

	std::cout << "-----------------------------" << std::endl;

	std::cout << "尾插数据：N" << std::endl;
	arr2->rearInsertData('N');
	std::cout << "尾插数据后，arr2数组的数据为：";
	arr2->printArr();

	std::cout << "-----------------------------" << std::endl;

	std::cout << "在6位置插入数据：f" << std::endl;
	arr2->posAddData('f', 6);
	std::cout << "在6位置插入数据：f后，arr2数组的数据为：";
	arr2->printArr();

	std::cout << "-----------------------------" << std::endl;

	arr2->quickSort();
	std::cout << "排序后arr2数组的数据为：";
	arr2->printArr();

	std::cout << "-----------------------------" << std::endl;

	std::cout << "头删元素：" << (*arr2)[0] << std::endl;
	arr2->headDelData();
	std::cout << "头删后arr2数组的数据为：";
	arr2->printArr();

	std::cout << "-----------------------------" << std::endl;

	std::cout << "尾删元素：" << (*arr2)[arr2->getMySize() - 1] << std::endl;
	arr2->rearDelData();
	std::cout << "尾删后arr2数组的数据为：";
	arr2->printArr();

	std::cout << "-----------------------------" << std::endl;

	std::cout << "删除位置为8的元素" << std::endl;
	arr2->posDelData(8);
	std::cout << "删除后arr2数组的数据为：";
	arr2->printArr();

	std::cout << "-----------------------------" << std::endl;

	MyArray<double>* arr3 = new MyArray<double>(100);

	for (int i = 0; i < 5; ++i)
	{
		(*arr3)[i] = (double)(rand() % 100 + 1) / (rand() % 50 + 1);
	}
	std::cout << "arr3数组的数据为：";
	arr3->printArr();

	std::cout << "-----------------------------" << std::endl;

	arr3->quickSort();
	std::cout << "排序后arr3数组的数据为：";
	arr3->printArr();

	std::cout << "-----------------------------" << std::endl;

	std::cout << "头插数据：2.795" << std::endl;
	arr3->headInsertData(2.795);
	std::cout << "头插数据后，arr3数组的数据为：";
	arr3->printArr();

	std::cout << "-----------------------------" << std::endl;

	std::cout << "尾插数据：3.956" << std::endl;
	arr3->rearInsertData(3.956);
	std::cout << "尾插数据后，arr3数组的数据为：";
	arr3->printArr();

	std::cout << "-----------------------------" << std::endl;

	std::cout << "在2位置插入数据：6.58" << std::endl;
	arr3->posAddData(6.58, 2);
	std::cout << "在2位置插入数据：6.58后，arr3数组的数据为：";
	arr3->printArr();

	std::cout << "-----------------------------" << std::endl;

	arr3->quickSort();
	std::cout << "排序后arr3数组的数据为：";
	arr3->printArr();

	std::cout << "-----------------------------" << std::endl;

	std::cout << "头删元素：" << (*arr3)[0] << std::endl;
	arr3->headDelData();
	std::cout << "头删后arr3数组的数据为：";
	arr3->printArr();

	std::cout << "-----------------------------" << std::endl;

	std::cout << "尾删元素：" << (*arr3)[arr3->getMySize() - 1] << std::endl;
	arr3->rearDelData();
	std::cout << "尾删后arr3数组的数据为：";
	arr3->printArr();

	std::cout << "-----------------------------" << std::endl;

	std::cout << "删除位置为3的元素" << std::endl;
	arr3->posDelData(3);
	std::cout << "删除后arr3数组的数据为：";
	arr3->printArr();

	std::cout << "-----------------------------" << std::endl;

	// -------------------------------------
	delete arr1;
	arr1 = nullptr;

	delete arr2;
	arr2 = nullptr;

	delete arr3;
	arr3 = nullptr;
}

int main()
{
	test01();

	return 0;
}
