#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

class Maker
{
public:
	Maker()
	{
		std::cout << "Maker：普通构造函数" << std::endl;
	}
	Maker(const Maker& m)
	{
		std::cout << "Maker：拷贝构造函数" << std::endl;
	}
	~Maker()
	{
		std::cout << "Maker：析构函数" << std::endl;
	}

	void modifyData()
	{
		this->a = 10;
		this->b = 20;
	}

private:
	int a;
	int b;
};

// 测试1：
void func01()
{
	Maker m;
	throw m;
}

/*
	结果如下：

	Maker：普通构造函数
	Maker：拷贝构造函数
	Maker：拷贝构造函数
	Maker：析构函数
	接收一个Maker类型的异常
	Maker：析构函数
	Maker：析构函数

	
	test01分析()：
	1、当以func01()函数这种写法时，会在"Maker m;"调用一次普通构造函数，紧接着会调用拷贝构造函数
	   拷贝出一份新的m对象用于throw，在throw之前就会将"Maker m;"这一行创建的m对象调用析构函数进行
	   空间释放；(一次"普通构造"、一次"拷贝构造"、一次"析构"，并且这个"析构"是"Maker m;"的m对象)

	2、当test01的"catch (Maker m1)"接收时，就会将刚刚func01()函数中"throw m;"的m对象拷贝一份，即
	   调用"拷贝构造"，等catch代码块执行结束后，就会相继将"throw m"和"Maker m1"进行析构；(一次
	   "拷贝构造"、两次"析构")。
*/
void test01()
{
	try
	{
		func01();
	}
	catch (Maker m1)
	{
		std::cout << "接收一个Maker类型的异常" << std::endl;
	}
}
// -----------------------------------------

// 测试2：
void func02()
{
	/*
		注：之前说过匿名对象的生命周期只是当前行，但是这里在抛出后并没有对匿名对象进行析构
			而是在抛回给主调函数后，在主调函数执行完catch代码块后才会被释放
	*/
	throw Maker();
}

/*
	结果如下：

	Maker：普通构造函数
	Maker：拷贝构造函数
	接收一个Maker类型对象
	Maker：析构函数
	Maker：析构函数

	test02()分析：
	1、首先在func02()函数中的"throw Maker();"调用普通构造函数创建了一个匿名对象；(一次"普通构造")

	2、然后在test02()函数中"catch (Maker m1)"调用了拷贝构造函数创建m1对象，接着在catch代码块结束
	   后相继将"throw Maker();"的匿名对象和"catch (Maker m1)"中的m1对象进行析构；(一次"拷贝构
	   造"、两次"析构")。

*/
void test02()
{
	try
	{
		func02();
	}
	catch (Maker m1)
	{
		std::cout << "接收一个Maker类型对象" << std::endl;
	}
}
// -----------------------------------------

// 测试3：
void func03()
{
	throw Maker();
}

/*
	结果如下：

	Maker：普通构造函数
	接收一个Maker引用对象
	Maker：析构函数

	test03()分析：
	1、在func03()函数中同样抛出匿名对象Maker()，此时调用普通析构函数创建匿名对象；(一次"普通构造")

	2、在test03()函数中的"catch (Maker& m1)"，是直接用引用接收了func03()的匿名对象，也就是说不需要
	   进行拷贝操作，m1就是刚刚的匿名对象，所以此时没有调用拷贝构造函数，当catch代码块运行结束时，
	   直接将m1对象进行析构；(一次"析构")。

	由上面三个测试可知，我们以后就throw匿名对象，用引用去接被调函数抛出的匿名对象，这样就可以省下
	很多空间，所以之后如果进行异常处理的话，使用第三种方法(匿名抛出，引用接收)
*/
void test03()
{
	try
	{
		func03();
	}
	catch (Maker& m1)
	{
		m1.modifyData();
		std::cout << "接收一个Maker引用对象" << std::endl;
	}
}
// -----------------------------------------

// 测试4：
void func04()
{
	Maker m;
	std::cout << (int)&m << std::endl;
	throw& m;
}

/*
	结果如下：

	Maker：普通构造函数
	1701232
	Maker：析构函数
	1701232

	test04()分析：
	1、首先在func04()中"Maker m;"调用了普通构造函数创建了一个对象m，然后我们直接把m的地址throw回
	   主调函数；(一次"普通构造")

	这里需要注意一点，其实这里有种返回局部变量地址的含义，我们知道这种是错误的，因为在函数throw
	后，之前创建的变量和对象的空间都会被释放掉(栈解旋)，这里我们直接throw回一个局部变量的地址，显然
	和我们使用普通函数时返回一个局部变量地址类似，但是编译器会帮我们进行优化，因为它检测到我们需要
	throw回m对象的地址，所以就不会将m对象释放掉，然后把这个对象的地址赋值给我们的catch匹配变量当中
	(也就是说是编译器给我们进行优化了，这个和我们之前的"普通函数返回匿名对象，主调函数接收对象是同
	一个对象的情况是一样的"，也是编译器进行了优化)

	2、在test04()中，"catch(Maker *m1)"中的m1指针接收了func04()函数中m对象的地址，当catch代码块结
	   束后，就会将m1进行析构(一次"析构")。

	这种方法虽然可以，但是看起来不太安全，毕竟和返回一个局部变量的情况类似，所以还是使用第三种方式
	会比较安全
*/
void test04()
{
	try 
	{
		func04();
	}
	catch (Maker* m1)
	{
		std::cout << (int)m1 << std::endl;
	}
}
// -----------------------------------------

// 测试5：
void func05()
{
	// 返回动态申请空间的对象
	throw new Maker();
}

/*
	结果如下：

	Maker：普通构造函数
	13313128
	Maker：析构函数

	test05()分析：
	1、这里比较好理解，就是直接throw回一个动态申请空间的对象，会调用普通构造函数；(一次"普通构造")

	2、同样在test05中，"catch(Maker *m1)"的m1会接受对象指针，然后就可以对m1对象进行使用，但是需要
	   注意的是，这要我们自己手动释放，否则会出现内存泄漏现象(释放后就调用一次"析构")
*/
void test05()
{
	try
	{
		func05();
	}
	catch (Maker* m1)
	{
		std::cout << (int)m1 << std::endl;

		// 既然是动态申请空间，就需要我们手动释放，否则就会内存泄漏
		delete m1;
		m1 = nullptr;
	}
}
// -----------------------------------------

// 测试6：
void func06()
{
	throw 10;
}

/*
	结果如下：

	a = 10
	a = 20

	test06分析：
	我们在func06()函数只抛回了10，但是我们在test06中可以用引用接收，并且可以修改，这其实也是编译器
	给我们做的优化

*/
void test06()
{
	try
	{
		func06();
	}
	catch (int& a)
	{
		std::cout << "a = " << a << std::endl;
		a = 20;
		std::cout << "a = " << a << std::endl;
	}
}



int main()
{
	// test01();
	// test02();
	// test03();
	// test04();
	// test05();
	test06();

	return 0;
}
