#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

class Maker
{
public:
	Maker()
	{
		std::cout << "无参构造函数" << std::endl;
		this->a = 20;
	}
	// 如果想用一个已有的对象去初始化另一个对象，就需要用到拷贝构造函数
	// 本质上就是传递一个Maker类型变量
	// 拷贝构造函数
	// 最好限制传进来的值不能被修改，因为这个属于源数据，不要修改
	Maker(const Maker &m) 
	{
		std::cout << "拷贝构造函数" << std::endl;
		this->a = m.a;
	}
	void printA()
	{
		std::cout << "a = " << a << std::endl;
	}

private:
	int a;
};


void test01()
{
	Maker m1;

	m1.printA();
	// 用一个已有的对象去初始化另一个对象
	Maker m2(m1);
	m2.printA();

}

// Maker2中没有写拷贝构造函数，但也可以使用构造函数
// 这也证明了编译器也给我们加了一个而外的函数
class Maker2
{
public:
	Maker2()
	{
		std::cout << "无参构造函数" << std::endl;
		this->a = 30;
	}
	// 编译器提供了默认的拷贝构造函数
	// 这个就相当于我们刚刚Maker1写的拷贝函数，只不过函数体里面只是一些基础的赋值
	// 如果有多个变量的情况下，就会一个个赋值
	// 例如：a = m.a;  b = m.b;  c = m.c ...
	/*
	编译器就是做了这个工作
	Maker2(const Maker2& m)
	{
		a = m.a;
	}
	*/


	void printA()
	{
		std::cout << "a = " << this->a << std::endl;
	}

private:
	int a;
};


// 拷贝构造函数中，形参必须要引用
void test02()
{
	// Maker2中没有写拷贝构造函数
	Maker2 m1;
	m1.printA();

	Maker2 m2(m1);
	m2.printA();
}

class Maker3
{
public:
	Maker3()
	{
		std::cout << "无参构造函数" << std::endl;
		this->a = 50;
	}
	Maker3(int a)
	{
		std::cout << "有参构造函数" << std::endl;
		this->a = a;
	}
	// 如果不加引用，会报错
	/*
	Maker3(const Maker3 m)
	{
		std::cout << "拷贝构造函数" << std::endl;
		this->a = m.a;
	}
	*/
	Maker3(const Maker3& m)
	{
		std::cout << "拷贝构造函数" << std::endl;
		this->a = m.a;
	}
	void printA()
	{
		std::cout << "a = " << a << std::endl;
	}

private:
	int a;
};

void test03()
{
	// 这个会调用有参构造函数
	Maker3 m1(10);
	m1.printA();


	Maker3 m2(m1);
	/*
	如果拷贝构造函数允许写常量，不写引用的话会出现一个问题
	就是当你传参给m2中拷贝构造函数时，就相当于const Maker3 m = m1;  那么编译器就会把它转化为const Maker3 m(m1);
	然后又会进行复制，即又变成了const Maker3 m = m1;  然后又会变成const Maker3 m(m1);  ......
	会无限循环下去，就会进入死循环
	编译器会进行 const Maker3 m = m1; -> const Maker3 m(m1);的转化是因为赋值的原理其实就是拷贝(把一个变量值赋给另一个变量)
	Maker3(const Maker3 m)
	{
		std::cout << "拷贝构造函数" << std::endl;
		this->a = m.a;
	}
	*/

	// 这个就是调用了拷贝构造函数，这也就反映了上面的那种情况
	// 如果拷贝构造函数中形参不是引用，那就会继续像下面那样赋值，也就说会调用拷贝构造函数
	// 从而出现死循环的情况
	Maker3 m3 = m1;


}

int main()
{
	// test01();
	// test02();
	test03();

	return 0;
}
