#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
#include <crtdbg.h>
#include <stdio.h>


// 1、new创建基础类型的数组
void test01()
{
	// 直接赋值
	// int* pInt = new int[10] {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; // 不推荐
	// for循环赋值(和我们习惯用的一样)
	// 1、整型数组
	int* pInt = new int[10];
	int i;
	for (i = 0; i < 10; i++)
	{
		pInt[i] = i + 1;
	}
	for (i = 0; i < 10; i++)
	{
		std::cout << "pInt[" << i << "] = " << pInt[i] << std::endl;
	}

	// 2、字符数组
	char* pChar = new char[64];
	memset(pChar, 0, 64);
	strcpy(pChar, "小美");
	std::cout << "pChar = " << pChar << std::endl;

	// 释放时需要注意：如果是new有中括号[]，那么就需要在delete后面加一个中括号[]
	// 要不然只会释放第一个元素的空间，这个需要看编译器，有些编译器能够检测出来但是有的不行
	// 所以还是规范书写，new有[]，那么delete也要加[]
	delete[] pInt;
	delete[] pChar;

	// ----------------------------------
	// 下面为拓展部分

	// 3、数组指针数组
	// 其中new后面的第一个数是数组指针的个数(也就是动态申请的个数)，如：int *x = new int[10];
	// 中的10是一样的意义，而除第一个数后面的代表数组指针指向数组的类型
	// 以下面这个为例，数组指针x指向一个有3个元素的一维数组，即(int*)[3]类型
	// 而相对应的，设有二维数组a[10][3]，x指针指向a二维数组的第一个元素，即a[0]

	// 下面这行代码就是代表这个意思，myArray指针指向有3个元素的一维数组，且动态申请了10个这样
	// 的空间，换个意思就是申请了一个二维数组myArray[10][3]
	// 如果只想申请1个空间，那就把10改成1即可(但是需要注意的是，即使为1，在释放时也要加上[])
	int(*myArray)[3] = new int[10][3];

	// 其实释放比较好理解，因为我们申请了10个指向只有3个元素的一维数组，那就意味着其实
	// 就是申请了10个空间大小的数组，所以释放就按照释放数组的方式写即可，如下：
	delete[] myArray;
	myArray = nullptr;

	// 同理，我们可以拓展到多维
	// 同样的，除了new后面第一个数代表数组元素个数之外，其他都需要参考定义类型的大小
	// 下面表示myArray2指针指向一个行为2，列为3的二维数组，而且这样的指针有10个，和上面道理一样
	// 如果只想申请1个空间，那就把10改成1即可(但是需要注意的是，即使为1，在释放时也要加上[])
	int(*myArray2)[3][2] = new int[10][3][2];

	// 释放时也是同理，其实也是一个数组，我们直接以数组形式释放即可
	delete[] myArray2;
	myArray2 = nullptr;

	// 4、指针数组

	// 也就是说，这个申请的也是一个数组，这个数组里面存的都是int*类型的指针
	// 这其实也就是我们申请这个空间之后，继续进行for循环对每个指针继续分配空间
	// 而对于pArray数组中的每个元素都指向一个一维数组
	int** pArray = new int* [10];

	// 释放也是一样的道理，当成数组释放即可，但是需要注意的是，因为有可能pArray每个元素又
	// 有可能动态申请了空间，需要先把每个元素的空间释放完之后，再去释放pArray
	delete[] pArray;
	pArray = nullptr;

	// 拓展到多维也是一样的，也是一层一层地创建，最后也是一层一层地释放
	int*** pArray2 = new int** [10];

	delete[] pArray2;
	pArray2 = nullptr;
}

// 2、用new创建对象数组
class Maker
{
public:
	Maker()
	{
		std::cout << "无参构造函数" << std::endl;
	}
	Maker(int a)
	{
		std::cout << "有参构造函数" << std::endl;
	}
	Maker(const Maker& m)
	{
		std::cout << "拷贝构造函数" << std::endl;
	}
	~Maker()
	{
		std::cout << "析构函数" << std::endl;
	}

};

void test02()
{
	// 调用无参构造器，但是没办法只能调用无参
	Maker* ms = new Maker[10]; //调用无参构造函数
	// 这里不加[]的话，在运行后程序会崩溃
	delete[] ms;

	// 调用有参构造器，大部分编译器不支持这种写法(所以建议不要用)，这方式又叫聚合初始化
	Maker* ms2 = new Maker[3]{ Maker(10),Maker(20),Maker(30) };
	delete[] ms2;
}

// 3、delete void*可能出错，不会调用对象的析构函数
void test03()
{
	void* ms3 = new Maker;

	// 如果用new接void*对象，那么在delete时不会调用析构函数
	// 因为在编译阶段，new和delete去关联对应类的构造函数和析构函数，但是void* C++没办法去识别是
	// 什么类型，所以没办法取关联对应类的析构函数，所以在释放时没办法去调用析构函数，也就是说
	// void*没办法指明函数的地址，也就没办法在对应的阶段去调用相应的函数
	delete ms3;
	// 在编译阶段，编译器已经确定好了函数的调用地址了，C++编译器不认识void*，不知道void*
	// 指向哪个函数，所以不会调用析构函数
	// 这种编译方式叫，静态联编
}

// 4、new和delete与malloc和free不要混搭使用
void test04()
{
	Maker* ms = new Maker;

	// 这样用很容易会出现bug的，因为如果你在构造函数里面(即类中)申请了堆区空间
	// 然后有使用free释放空间，那么就不会去调用析构函数，也就是你申请的空间不能得到释放
	free(ms);
}


int main()
{
	// test01();
	// test02();
	test03();



	return 0;
}
