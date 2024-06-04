#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

class Father
{
public:
	virtual void printMes()
	{
		std::cout << "Father：printMes()" << std::endl;
	}
};

class Son :public Father
{
public:
	virtual void printMes()override
	{
		std::cout << "Son：printMes()" << std::endl;
	}
};

class Maker
{
public:

};


/*
	静态类型转换(static_cast<>())：
	1、用于类层次结构中的父类和子类之间的"指针"或"引用"之间的转换；
	   (1)向上转型，即子类向父类转换，是安全的；
	   (2)向下转型，即父类向子类转换，由于没有动态类型检查，是不安全的；

	2、用于基本数据类型之间的转换，如把int转换成char，把char转换成int，但是这种转换的安全性
	   需要程序员自己把握，因为有可能小范围变成大范围会出现非法访问的情况，或者double类型转换成
	   其他类型(如：int、char等)，也会出现相应的问题

*/
// static_cast
void test01()
{
	// 1、"基础类型"转换
	char c1 = 'c';

	// char --> double

	// 参数列表"<>"中，填入的是要转换成的类型(如：想把c1转换成double，那就在"<>"中写double)
	double d1 = static_cast<double>(c1); // 也能这么写 double d1 = (double)c1;

	/*
		int a = 10;
		int* pa = &a;

		double d = 3.14;
		double* pd = &d;

		// 这样转是错误的，编译器会提示转换无效，因为静态转换不适合普通类型的"指针"或"引用"转换
		double* x = static_cast<double*>(pa);
	*/

	// 2、有层次关系类的"指针"转换
	Father* f1 = nullptr;
	Son* s1 = nullptr;

	// 这个是向下转型(不安全)
	Son* s2 = static_cast<Son*>(f1);

	// 这个是向上转型(安全)
	Father* f2 = static_cast<Father*>(s1);

	/*
		// 没有层级(继承)关系的类转换会报错
		Maker* m = nullptr;
		Father* f3 = static_cast<Father*>(m); // err
	*/

	// 3、有层次关系类的"引用"转换
	Father fa;
	Son so;

	Father& refFa = fa;
	Son& refSn = so;

	// 子类的引用转换成父类引用(安全)
	Father& refF = static_cast<Father&>(refSn);

	// 父类的引用转换成子类引用(不安全)
	Son& refS = static_cast<Son&>(refFa);

}



/*
	动态类型转换(dynamic_cast<>())：
	1、dynamic_cast主要用于"类层次"间的"向上转换"和"向下转换"；

	2、在类层次间进行向上转换时，dynamic_cast和static_cast转换效果是一样的

	3、但是在在类层次间进行向下转换时，dynamic_cast具有类型检查功能，比static_cast更安全

*/
// 2、dynamic_cast
void test02()
{
	/*
		// 1、基础类型不能进行转换
		char c1 = 'a';
		double d1 = dynamic_cast<double>(c1);

		// 2、不允许普通类型的指针或引用转换(和static_cast一样)
		char* ch = nullptr;
		double* d = dynamic_cast<double*>(ch);
	*/ 

	// 3、层级之间的向下转换
	Father* f1 = nullptr;
	Son* s1 = nullptr;

	// 向上转型(安全)
	Father* fp1 = dynamic_cast<Father*>(s1);

	// 注：只有在多态的情况下，才允许父类往子类转型(即向下转型)，否则会报错
	// Son* sp1 = dynamic_cast<Son*>(f1); // err：在没有多态的情况下，向下转型会报错

	// 有多态关系之后，dynamic_cast转换允许向下转型
	Son* sp2 = dynamic_cast<Son*>(f1);

}



/*
	常量转换(const_cast)：
	1、该运算符用来修饰类型的const属性

	2、常量指针被转化成非常量指针，并且仍然指向原来的对象；

	3、常量引用被转换成非常量引用，并且仍然指向原来的对象；

	4、不能直接对非指针和非引用的变量使用const_cast操作符去直接移除它的const，也就是说
	   不能对普通类型(int、char或double)和类(如：自定义类Maker或库类stirng等)，只要不是指针
	   或引用都不能使用

	5、这个是用于同一大类型的常量进行转换，也就是不能跨越不同的大类型进行转换，如："const int*"和 
	   "const double*"之间的转换，类就更加不行了
*/
// 3、const_cast
void test03()
{
	// 注：常量指针有两种写法："const int*" 和 "int const*" 
	// 1、常量指针转换非常量指针
	const int* ip1 = nullptr;
	// const --> 不带const
	int* p1 = const_cast<int*>(ip1);

	// 2、非常量指针转换成常量指针
	int* p2 = nullptr;
	const int* ip2 = const_cast<const int*>(p2);

	// 3、指针常量转换成非指针常量
	 int* const ip3 = nullptr;
	 int* p3 = const_cast<int*>(ip3);

	 // 4、非指针常量转换成指针常量
	 int* p4 = nullptr;
	 int* const ip4 = const_cast<int* const>(p4);

	 /*
		注：只能更改限定类型，不能更改转换基本类型
		const int* p5 = nullptr;
		// double* d1 = const_cast<double*>(p5); // err
	 */

}


/*
	重新解释类型(reinterpret_cast)：这个最不安全的一种转换机制，最有可能出问题

	主要是用于将一种数据类型从一种类型转换成为另一种类型，它可以将一个指针转换
	成一个整数，也可以将一个整数转换成为一个指针

	由下面例子可知，这个转换极其不安全

*/
// 4、reinterpret_cast
void test04()
{
	// 1、普通整型转换成指针
	int a = 100;
	int* pa = reinterpret_cast<int*>(a);

	// 2、不同类型数据都可以转换成指针
	int b = 200;
	double* d = reinterpret_cast<double*>(b);

	// 3、没有关系的类也都可以随意进行指针转换
	Maker* m = nullptr;
	Father* f = reinterpret_cast<Father*>(m);

}


int main()
{
	test01();
	//test02();
	//test03();
	//test04();

	return 0;
}
