#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

class Maker
{
public:
	Maker()
	{
		std::cout << "构造函数" << std::endl;

	}
	Maker(int a)
	{
		std::cout << "有参构造函数" << std::endl;
	}
	~Maker()
	{
		std::cout << "析构函数" << std::endl;
	}
};



/*
	而且在使用malloc时还需要做到这几个事情：1、程序员必须确定对象的长度(也就是sizeof(xxx))
											2、malloc返回的是一个void*，在C++中还得强转，要不然会报错
											3、malloc可以申请空间失败，也需要判断分配的指针是不是NULL才确定有没有
											申请成功(但是这个我们一般没有做什么操作)
											4、用户在使用对象初始化之前必须记住对它的初始化，不会调用构造函数进行
											初始化
*/
void test01()
{
	// 注意：用C语言方式申请空间，虽然在控制台没有发生什么异常，但是我们发现它并没有去调用我们的
	// 构造函数和析构函数，这样就会有麻烦了，如果我们在类里面有一些动态申请的空间，那我们就没办法
	// 通过析构函数进行释放，同时我们在用成员变量之前也没有通过构造函数对它进行初始化，因为我们知道
	// 如果使用未初始化的变量会报错，因此我们用C语言的方式去申请空间就会出现这些bug
	// 申请时也不会调用构造函数
	Maker *m = (Maker*)malloc(sizeof(Maker));
	if (m != NULL)
	{
		// 释放也不会调用析构函数
		free(m);
		m = NULL;
	}
}

void test02()
{
	// new的用法：
	// 用new就调用了类的构造函数
	Maker* m = new Maker; 

	// 用delete就会调用析构函数(释放堆区空间会调用类的析构函数)
	delete m;
	m = NULL;

	Maker* m2 = new Maker(10);

	delete m2;
	m2 = NULL;
}

int main()
{
	test02();

	return 0;
}
