#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

/*
运算符重载：
	其实运算符重载只是为了我们自定义类方便使用，有时候我们的自定义Maker类中有
	成员num1和num2，如果我们想将对象m1和m2的对应num1和num2相加，需要取出数据再进行
	相加，这样会很麻烦，如果我们能像普通类型相加就会比较方便，如：m1+m2表示对应成员num1和
	num2相加，这样就会便于我们写代码，除了+之外，还有许多运算符都可以进行重载，但是也有些
	运算符是不能重载的，不能重载的运算符有这5个，分别是："sizeof"、".*"、"?:"、"->"、"::"

	注：
		1、在编程时，运算符重载不要改变其本身的含义，如：将+改成-的含义，这样就会失去我们使用
	运算符重载的意义，而且也不便于我们开发和代码阅读效果，即使可以也不能这样做；
		2、运算符重载就是对已有的运算符重新进行定义，赋予其另一层功能，以适应不同的数据类型；
		3、运算符重载的目的是让语法更加简洁；
		4、运算符重载的本质还是调用的函数(编译器自动取调用)；
		5、函数名叫做"operator"；
		6、运算符重载函数可以写成全局函数，也可以写成成员函数；
		7、运算符重载函数如果写成全局的，那么双目运算符的左边就是第一个参数，右边是第二个参数；
		8、运算符重载函数如果写成成员函数，那么双目运算符的左边是this，右边第一个参数；
		9、"="、"()"、"[]"、"->"和"->*"操作符只能是通过"成员函数"进行重载
		10、"<<"和">>"操作符最好通过"友元函数"重载；
		11、不要重载"&&"和"||"操作符，否则会失去短路规则。
*/

// 下面演示运算符重载
class Maker1
{
	// friend Maker1 operator+(Maker1& m1, Maker1& m2);
public:
	Maker1() :num1(0), num2(0) {}
	Maker1(int num1, int num2) :num1(num1), num2(num2) {}
	Maker1(const Maker1& m)
	{
		this->num1 = m.num1;
		this->num2 = m.num2;
	}

	// 这里其实调用的对象本身就是作为第一个参数，而函数中的第一个参数则为第二个参数
	// 如：m1+m2其实m1就是调用的对象的this，m2则为函数的第一个参数

	// 在类里面写的好处是，能够如意地使用私有成员变量，不需要添加友元
	Maker1 operator+(Maker1& m)
	{
		// 这里同样是匿名对象，效果也和全局写法一样
		return Maker1(this->num1 + m.num1, this->num2 + m.num2);
	}

	void printNum()
	{
		std::cout << "num1 = " << num1 << "，num2 = " << num2 << std::endl;
	}

	~Maker1() {}
private:
	int num1;
	int num2;
};
/*
	// 这个就是运算符重载，这样些之后，就能够使用m1+m2这种方式了
	// 由于num1和num2是私有成员，所以我们只能将此+号运算方式添加为Maker1的友元函数
	Maker1 operator+(Maker1& m1, Maker1& m2)
	{
		// 这个是匿名对象，如果编译器检查到主调函数有接这个返回值，是不会对匿名对象进行析构的
		// 因为编译器会节省内存，但是遇过检查到主调函数没有接这个返回值，就会直接对匿名对象进行析构
		return Maker1(m1.num1 + m2.num1, m1.num2 + m2.num2);
	}
*/

/*
	其实，这里的运算符重载函数带有返回值是有作用的
	1、返回值用于返回我们合并完的对象，然后便于我们获取运算后的值；
	2、便于我们使用链式编程。

	运算符建议：
	所有的一元运算符：成员
	"="、"()"、"[]"、"->"和"->*"：必须是成员
	"+="、"-="、"/="、"*="、"^="、"&="、"!="、"%="、">>="和"<<="：成员
	其他二元运算符：非成员
*/
void test01()
{
	Maker1 m1(10, 20);
	Maker1 m2(30, 40);

	Maker1 m = m1 + m2;
	m.printNum();
}


int main()
{
	test01();

	return 0;
}
