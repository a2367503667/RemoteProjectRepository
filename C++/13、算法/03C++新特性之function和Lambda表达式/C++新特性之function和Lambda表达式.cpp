#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <algorithm>
#include <numeric>
#include <typeinfo>
using namespace std;

/*
	1、std::function是用作将一个普通函数、成员函数、函数指针、成员函数指针、Lambda表达式等转换成对应的
	函数对象，并用于给算法模版进行调用，或者便于我们参数的传递和使用的，属于C++11新特性，所以需要重点
	取掌握

	2、Lambda表达式也可以写匿名函数，而匿名函数是我们开发中的一大便利，因为有时候我们只需要一些很简短
	的代码，完成一个功能，但是如果我们为了很简短的代码就写一个函数的话，处理起来会非常麻烦，因此我们就
	会写匿名函数，在一些代码中完成一个小的操作，辅助我们其他模块的执行，就好比如，我们在for_each中想查看
	每个元素的结果，我们就需要传递一个普通函数或函数对象，但是仅仅因为查看一下元素这个简单的功能就需要
	写一个函数，就会使得代码结构很复杂，所以我们就会写一个Lambda表达式(匿名函数)，便于我们直接运用在我们
	的for_each函数当中

	Lambda表达式的形式
	[捕捉列表](形参列表)->返回值类型{ 函数体 }
	(1)所谓的捕捉列表就是用来获取当前程序中的变量或对象等信息的
	(2)形参列表和普通函数的形参列表意义一样
	(3)返回值类型则是和普通函数的返回值类型意义一样
	(4)函数体是进行函数实现的

	通常Lambda表达式的实现不会过长，只会实现一些较为简单的代码和功能


	这里补充一个知识点，函数指针的写法是：返回值类型 (*函数指针名)(参数列表)，如：void(*func)(int)
	其中，*在函数指针名前面，和int* p一样，*在p的前面
*/

void func01()
{
	cout << "func01普通函数 --> void()function函数对象" << endl;
}
// 1、将普通函数转换成function函数对象
void test01()
{
	function<void()> myfunc01 = func01;
	myfunc01();
}

struct func02
{
	void operator()()
	{
		cout << "func02函数对象 --> void()function函数对象" << endl;
	}
};
// 2、将函数对象转换成function函数对象
void test02()
{
	// 需要注意的是，如果要转换函数对象，那对应的值就是对象，即func02()
	function<void()> myfunc02 = func02();
	myfunc02();
}


void func03()
{
	cout << "void(*)()函数指针 --> function函数对象" << endl;
}
// 3、将函数指针转换成function函数对象
void test03()
{
	/*
		其实func03和&func03含义是一样的，都代表函数指针
		auto f = func03;
		auto ff = &func03;
		cout << "f = " << typeid(f).name() << endl;
		cout << "ff = " << typeid(ff).name() << endl;
	*/

	// &func03函数名其实也可以代表函数指针，所以效果和func03是一样的
	function<void()> myfunc03 = &func03;
	myfunc03();

	// 下面的结果是：class std::function<void (__cdecl*)(void)> __cdecl(void)
	// 需要注意的是function<void(*)()>类似这种函数指针类型，是无法使用的，我们只能定义函数类型，如：void()
	// 只是会有这种类型，但是在function中不能使用
	cout << "function<void(*)()>的类型为：" << typeid(function<void(*)()>()).name() << endl;

}

class MyClass
{
public:
	void func04(int val)
	{
		cout << "val = " << val << endl;
		cout << "成员函数func04 --> function函数对象" << endl;
	}

};
// 4、将成员函数转换成function函数对象
void test04()
{
	// 这里需要注意一下，因为成员函数不能脱离对象的调用，成员函数是属于对象的，也就是说它需要对象才能
	// 触发调用，因此我们在进行转换的时候，需要将MyClass*(或MyClass)作为function的参数类型进行传递，如
	// 下void(MyClass*, int)，如果成员函数形参列表中含有对应的参数，那就需要加上参数，在上面可以看到
	// 有int类型，那我们就需要将int类型传入，而对应的MyClass*(或MyClass)就是用来给function内部提供一个
	// 对象指针(或对象)，便于操作成员函数MyClass::func04的，相对应的，我们可以得到一个void(MyClass*, int)
	// 的函数对象，我需要将对象指针(或对象)传递进去才可以正确调用
	function<void(MyClass*, int)> myfunc04 = &MyClass::func04;

	MyClass myobj;
	// 因为成员函数属于对象，所以我们只能通过对象或对象指针进行触发调用
	myfunc04(&myobj, 20);

	// 下面的结果是：void (__thiscall MyClass::*)(int)
	cout << "&MyClass::func04的类型是：" << typeid(&MyClass::func04).name() << endl;

}

template<typename T>
void func(T f)
{
	cout << "f的类型是：" << typeid(f).name() << endl;
}

// 5、查看一下函数传递到模版时，会被解析成什么类型
void test05()
{
	// 会被解析为函数指针：f的类型是：void (__cdecl*)(void)
	func(func01);

	cout << typeid(void(int)).name() << endl;
}

// 6、将Lambda表达式转换成为function函数对象
void test06()
{
	auto myfunc6 = []()->void {cout << "myfunc06的Lambda表达式 --> function函数对象" << endl; };

	// 需要注意的是，Lambda表达式的类型和普通函数的写法一样，即function模版参数列表书写和普通函数一样
	function<void()> myfunc06 = myfunc6;

	myfunc06();
}


// =========================================
// Lambda表达式(匿名函数)


// 1、捕捉列表为[]
void test07()
{
	auto func = []()->void {cout << "捕捉列表为[]的Lambda表达式" << endl; };
	func();
}

// 2、捕捉列表为[=]
void test08()
{
	int a = 10;
	int b = 20;

	/*
		需要注意的是，[=]只是做捕捉操作，并不是真正意义上得到a和b，可以被认为是得到a和b的值
		因此不能修改a和b的值，其实不让你修改，是为了变量保持不变性，确保变量的内容不变
	*/
	auto func = [=]() {
		// ++a, ++b; // a和b在Lambda表达式中是不能改的
		// 本质上a和b在Lambda表达式中都是const变量，不能被修改
		// 并且捕捉到的变量只是Lambda表达式中的副本，并不是真正意义上的a和b
		// 和函数的值传递是一个道理
		cout << "a = " << a << endl;
		cout << "b = " << b << endl;
		};
	func();
	cout << "a = " << a << endl;
	cout << "b = " << b << endl;

	/*
		但是如果我们想修改a和b的值，此时可以在Lambda表达式的函数体前加上mutable，此时a和b
		就能够修改，不过需要注意的是，即使在Lambda表达式中修改了a和b的值，也不会改变外面a和b的值

		mutable书写的位置在函数签名的后面，返回值类型的前面
	*/
	auto func1 = [=]()mutable ->void {
		++a, ++b;
		cout << "mutable: a = " << a << endl;
		cout << "mutable: b = " << b << endl;
		};
	func1();

	// 发现即使在Lambda表达式修改了a和b，test08的a和b都不会被修改
	cout << "test08: a = " << a << endl; // test08: a = 10
	cout << "test08: b = " << b << endl; // test08: b = 20
}

// 3、捕捉列表为[&]
void test09()
{
	int a = 100;
	int b = 200;
	
	/*
		引用捕捉顾名思义是可以修改a和b的值的，并且在内部修改后，外部的a和b也会改变
	*/
	auto func = [&]()->void {
		a += 10;
		b += 20;
		cout << "func: a = " << a << endl;
		cout << "func: b = " << b << endl;
		};
	func();

	cout << "test09: a = " << a << endl;
	cout << "test09: b = " << b << endl;

	cout << "===========================" << endl;

	a = 100, b = 200;
	/*
		不管加不加mutable，都是会改变a和b的值，其实mutable是允许修改常量的意思，对于当前a和b来说
		并不是常量，而且Lambda表达式中的a和b就是test08的a和b，所以还是会将变量修改掉
	*/
	auto func1 = [&]()mutable ->void {
		a += 20;
		b += 40;
		cout << "func1: a = " << a << endl;
		cout << "func1: b = " << b << endl;
		};
	func1();
	cout << "test09: a = " << a << endl;
	cout << "test09: b = " << b << endl;
}

// 4、捕捉列表=、&混合型
void test10()
{
	int x = 500;
	int y = 1000;

	// 注：如果不加mutable的话，x是不能被修改的，当然，即使加了mutable也不会真正修改外部的x
	auto func = [=, &y]()mutable->void {
		x += 100;
		y += 200;
		cout << "func: x = " << x << endl; // 600
		cout << "func: y = " << y << endl; // 1200
		};
	func();

	cout << "test10: x = " << x << endl; // 500
	cout << "test10: y = " << y << endl; // 1200

	cout << "========================" << endl;

	x = 500;
	y = 1000;
	auto func1 = [&x, y]()mutable->void {
		x += 300;
		y += 800;

		cout << "func1: x = " << x << endl; // 800
		cout << "func1: y = " << y << endl; // 1800
		};
	func1();

	cout << "test10: x = " << x << endl; // 800
	cout << "test10: y = " << y << endl; // 1000
}


int main(int argc, char* argv[])
{
	test10();


	return 0;
}
