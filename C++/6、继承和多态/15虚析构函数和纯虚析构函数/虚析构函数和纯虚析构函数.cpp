#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

/*
	1、虚析构函数是为了解决父类指针指向子类对象时(多态)，并使用父类指针进行释放子类对象的情况
	   如果我们不将父类的析构函数写成虚析构函数，那我们用父类指针释放子类对象时就不会调用子类的
	   析构函数，假设子类中有动态申请空间，此时就会发生内存泄漏，所以需要把父类的析构函数写成虚
	   析构函数；

	   那为什么会这样呢？
	   其实是因为，我们正常调用的时候，父类Animal的析构函数默认是静态联编的，也就是说看到有父类
	   指针释放时(delete an;)，早就绑定好了父类析构函数的入口地址，因此就只会执行父类的析构函数，
	   当我们把父类的析构函数改成虚析构函数时，那父类中就会有"虚函数表指针"，其中父类的析构函数
	   的入口地址也会加入到"虚函数表"当中，当子类继承父类之后，得到"虚函数表指针"和"虚函数表"，然
	   后观察到父类的析构函数是虚函数，这时，编译器就会将当前子类的析构函数的入口地址覆盖掉父类的
	   析构函数入口地址，所以就变成了动态联编，这样的话，当编译器执行到"delete an;"这一行时，察觉到
	   是动态联编，此时就会去调用子类的析构函数释放子类资源，又因为"delete an;"本质上也是删除父类
	   的资源，即最后也会调用父类的析构函数，这样就会解决没办法调用子类析构函数的问题了。

	2、纯虚析构函数其实是用于抽象类的，因为我们知道抽象类只提供接口，一般不实现代码，所以我们会把
	   所有的函数都定义为纯虚函数，包括析构函数也是，但是有个问题，当我们只给出纯虚析构函数在代码
	   运行后会报错，因为析构函数只有签名部分，没有函数体，这样是没办法运行的，所以我们只能给纯虚
	   析构函数写函数体，但是纯虚析构函数只能在抽象类中定义签名，抽象类外进行实现(即纯虚析构函数只
	   能在抽象类中定义，抽象类外初始化)

	虚析构函数和纯虚析构函数的区别：
	1、有纯虚析构函数的类是抽象类，不能实例化对象，并且虚析构函数实体需要在类外实现；
	2、虚析构函数则不需要再类外实现；
*/

class Animal
{
public:
	Animal()
	{
		std::cout << "Animal 构造函数" << std::endl;
	}

	//void speak()
	//{
	//	std::cout << "Animal Speak" << std::endl;
	//}

	//void run()
	//{
	//	std::cout << "Animal Run" << std::endl;
	//}

	//~Animal()
	//{
	//	std::cout << "Animal 析构函数" << std::endl;
	//}

	virtual ~Animal()
	{
		std::cout << "Animal 析构函数" << std::endl;
	}
};

class Dog :public Animal
{
public:
	Dog()
	{
		std::cout << "Dog 构造函数" << std::endl;
		this->arr = new int[100];
		for (int i = 0; i < 100; ++i)
		{
			arr[i] = 0;
		}
	}

	~Dog()
	{
		std::cout << "Dog 析构函数" << std::endl;
		if (this->arr != nullptr)
		{
			delete[] this->arr;
			this->arr = nullptr;
		}
	}

private:
	int* arr; // 数组
};

// 1、当父类的析构函数不是虚析构函数
void test01()
{
	/*
		我们发现没有调用Dog的析构函数，因为对于Animal的析构函数来说是静态联编的，也就是说
		在编译阶段已经绑定好an所调用的析构函数了，这时我们将父类的析构函数改成虚析构函数即可

		Animal 构造函数
		Dog 构造函数
		Animal 析构函数
	*/
	Animal* an = nullptr;
	an = new Dog;
	delete an;
	an = nullptr;
}

// 2、当父类的析构函数是虚析构函数
void test02()
{
	/*
		当父类的析构函数改成虚析构函数时，即可调用Dog的析构函数

		Animal 构造函数
		Dog 构造函数
		Dog 析构函数
		Animal 析构函数
	*/
	Animal* an = nullptr;
	an = new Dog;
	delete an;
	an = nullptr;
}


// 3、假设是抽象类的情况(一般对于抽象类来说，里面所有接口都是纯虚函数，即析构函数也是虚函数)
class People
{
public:
	People()
	{
		std::cout << "People 构造函数" << std::endl;
	}

	virtual ~People() = 0;
};

People::~People()
{
	std::cout << "People 纯虚析构函数" << std::endl;
}

class Son :public People
{
public:
	Son()
	{
		std::cout << "Son 构造函数" << std::endl;
		this->arr = new int[100];
		for (int i = 0; i < 100; ++i)
		{
			arr[i] = 0;
		}
	}

	~Son()
	{
		std::cout << "Son 析构函数" << std::endl;
		if (this->arr != nullptr)
		{
			delete[] this->arr;
			this->arr = nullptr;
		}
	}

private:
	int* arr; // 数组
};

// 3、纯虚析构函数问题
void test03()
{
	/*
		注意：因为我们继承了抽象类People，其中它的析构函数是纯虚析构函数，也就是说子类Son也成为了
			  抽象类，此时我们就需要在子类中重写父类的纯虚析构函数，但是析构函数是独有的，子类没办法
			  重写，这样的话，下面的代码运行会报错，因为子类是抽象类无法构建对象

			  此时应该怎么解决呢？
			  我们只能在全局区域给抽象类People的纯虚析构函数写函数体，这样就可以解决这个问题了

			  修改后就不会报错了，下面是输出结果：

			  People 构造函数
			  Son 构造函数
			  Son 析构函数
			  People 纯虚析构函数
	*/
	People* p = nullptr;
	p = new Son;
	delete p;
	p = nullptr;
}

int main()
{
	// test01();
	// test02();
	test03();


	return 0;
}
