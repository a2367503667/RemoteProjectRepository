#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

// 目标：实现单例模式
// 单例模式就是一个类只实例化一个对象

class Maker1
{
private:
	// 1、先把构造函数和拷贝构造函数私有化(不允许别人通过构造函数创建对象)
	Maker1() {}
	Maker1(const Maker1& m) {}
public:

	// 4、提供一个接口给外界接收对象，获取实例化出来的对象(还有就是静态函数
	// 可以直接用类名直接调用，非常方便，如果使用的是普通成员函数，我们没有对象就调用不了)
	static Maker1* getInstance()
	{
		return instance;
	}

	// 实例化的对象必须要私有化，要不然会被别人更改，我们只能获取，不能更改对象
private:
	// 2、定义一个类内的静态Maker1对象指针(如果因为我们已经将构造器私有化了，没办法创建对象，
	// 也没办法进行对普通成员初始化提供给外界使用，因为普通成员要使用需要实例化对象，但
	// 现在就是没有办法实例化对象，所以我们只能使用静态成员变量提供静态对象，并且静态对象
	// 获取比较方便，不需要通过构造函数方式获取，只需要类名即可获取)
	static Maker1 *instance;
};
// 3、在类外实例化对象，new一个对象指针(需要注意的是要加上作用域符，别少写*符号)
Maker1* Maker1::instance = new Maker1;

void test01()
{
	Maker1* m1 = Maker1::getInstance();
	Maker1* m2 = Maker1::getInstance();

	std::cout << "m1 = " << m1 << std::endl;
	std::cout << "m2 = " << m2 << std::endl;

	// 如果不把拷贝构造函数私有化的话，可以通过一下代码创建新的对象，因此一定要将其私有化
	// Maker1 m3 = m1;
}




int main()
{
	test01();

	return 0;
}
