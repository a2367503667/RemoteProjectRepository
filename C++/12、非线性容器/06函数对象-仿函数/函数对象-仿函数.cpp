#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <functional> // 使用内建函数对象需要包含此头文件
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <typeinfo>
using namespace std;

template<typename T>
void printMsg(T& arr)
{
	typename T::iterator begin = arr.begin();
	typename T::iterator end = arr.end();

	while (begin != end)
	{
		cout << *begin << " ";
		++begin;
	}
	cout << endl;
}

/*
注意：
	(1)函数对象不是函数，是一个类实例化出来的对象；
	(2)重载operator()传一个参数称为“一元仿函数”，传两个参数称为“二元仿函数”

1、什么是函数对象？
	在类中重载()运算符，这个类实例化的对象称为函数对象(仿函数)

2、函数对象有什么作用？
	(1)作为函数参数进行传递，我们在类中编写一些操作，如打印输出，作为系统算法库或自定义算法库的参数；
	(2)可以根据自己的需要自定义一些算法的操作
	(3)可以保留调用信息，因为函数对象本质上是一个对象，而我们可以在类中定义一些信息，在函数对象被调
	用时，保留我们所需要的信息；
	(4)加快运行速度，因为类中的方法默认都是加上inline关键字，有可能被提升为inline函数，加快运行速度。

3、函数对象和普通函数的区别
	(1)函数对象有自己的状态(因为类的成员有权限)
	(2)函数对象有类型(类就是对象的类型)，而普通函数没有
	(3)函数对象(仿函数)在类中默认有inline修饰，运行速度相对于普通函数可能会更快

4、什么是谓词？
	(1)谓词是指普通函数或重载的operator()的返回值为bool类型的函数或者函数对象(仿函数)
	(2)谓词可以作为判断式(也就是说可以作为if、while、for等代码的条件，这个比较容易理解，因为函数返回
	的是true或false)
	(3)接收一个参数的谓词称为“一元谓词”，接收两个参数的谓词称为“二元谓词”

5、内建函数对象(所谓的内建函数对象就是系统库提供的一些仿函数)
	使用内建函数对象需要加上头文件#include <functional>

*/

struct MyFunc
{
	bool operator()(const int v1, const int v2)const
	{
		return v1 > v2;
	}
};

// 使用自定义函数对象
void test01()
{
	srand((unsigned int)time(nullptr));

	vector<int> v;
	int nums = 10;

	for (int i = 0; i < nums; ++i)
	{
		v.push_back(rand() % 100 + 1);
	}
	printMsg<vector<int>>(v);

	// 这里传递的是对象(匿名对象)，对于sort来说，允许传递函数对象、函数指针以及成员函数指针
	// 需要注意的是，成员函数指针是需要相应的对象进行调用的，也就是说前面的begin需要是对象
	// 这样才可以通过begin获取当前对象，并调用成员函数指针从而调用成员函数
	sort(v.begin(), v.end(), MyFunc());
	printMsg<vector<int>>(v);
}


/*
6个“算术类函数”对象,除了negate是一元运算，其他都是二元运算(下面六个常用作进行简单的算术运算)

template<class T>
T plus<T>//加法仿函数

template<class T>
T minus<T>//减法仿函数

template<class T>
T multiplies<T>//乘法仿函数

template<class T>
T divides<T>//除法仿函数

template<class T>
T modulus<T>//取模仿函数

template<class T>
T negate<T>//取反仿函数
*/
void test02()
{
	// 1、plus加法
	plus<int> p;
	cout << "plus(10, 20) = " << p(10, 20) << endl; // 调用重载的()函数

	// 2、minus减法
	minus<int> ms;
	cout << "minus(50, 80) = " << ms(50, 80) << endl; // 调用重载的()函数

	// 3、multiplies乘法
	multiplies<int> mp;
	cout << "multiplies(3, 40) = " << mp(3, 40) << endl;

	// 4、divides除法
	divides<int> ds;
	cout << "divides(75, 25) = " << ds(75, 25) << endl;

	// 5、modulus取模
	modulus<int> mod;
	cout << "modulus(913, 45) = " << mod(913, 45) << endl;

	// 6、negate取反(所谓的取反，就是求相反数，即886的相反数为-886)
	negate<int> ne;
	cout << "negate(886) = " << ne(886) << endl;
}




/*
6个“关系运算类”函数对象,每一种都是二元运算(下面六个通常用作谓词)

template<class T>
bool equal_to<T>//等于

template<class T>
bool not_equal_to<T>//不等于

template<class T>
bool greater<T>//大于

template<class T>
bool greater_equal<T>//大于等于

template<class T>
bool less<T>//小于

template<class T>
bool less_equal<T>//小于等于
*/

void test03()
{
	vector<int> v;

	v.push_back(8);
	v.push_back(-1);
	v.push_back(3);
	v.push_back(9);
	v.push_back(-11);
	v.push_back(13);

	// 使用内建的函数对象规则进行排序
	// (1)greater<int>()表示大于，即使用降序排序
	cout << "降序排序：";
	sort(v.begin(), v.end(), greater<int>());
	printMsg<vector<int>>(v);

	// (2)less<int>()表示小于，即使用升序排序
	cout << "升序排序：";
	sort(v.begin(), v.end(), less<int>());
	
	// 这里使用到了匿名函数[](int val)->void {cout << val << " "; }
	for_each(v.begin(), v.end(), [](int val)->void {cout << val << " "; });
	cout << endl;

}

/*
逻辑运算类运算函数,not为一元运算，其余为二元运算

template<class T>
bool logical_and<T>//逻辑与

template<class T>
bool logical_or<T>//逻辑或

template<class T>
bool logical_not<T>//逻辑非
*/
void test04()
{
	// logical_and逻辑与
	logical_and<int> la;
	cout << "logical_and(10, 0) = " << la(10, 0) << endl;

	// logical_or逻辑或
	logical_or<bool> lo;
	cout << "logical_or(false, true) = " << lo(false, true) << endl;

	// logical_not逻辑非
	logical_not<bool> ln;
	cout << "logical_not(true) = " << ln(true) << endl;
}


int main(int argc, char* argv[])
{
	test03();

	return 0;
}
