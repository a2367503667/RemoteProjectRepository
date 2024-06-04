#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <functional>
#include <numeric>
using namespace std;

/*
	因为在C++11之后，bind1st和bind2nd被废弃，即已经不再使用了，然后C++官方给出新的函数
	模版bind替代bind1st和bind2nd，不过需要注意的是bind使用的参数中有std::placeholders，其中
	placeholders有很多成员，如：_1、_2、_3...

	placeholders是针对于实参来说的，也就是用来匹配实参用来占位的，就好比如对函数print(int a, int b)
	进行如下操作：
	
	auto myprint = band(print, 20, placeholders::_1);
	myprint(30);
	那么placeholders::_1就会去找实参中的第一个参数，实参的第一个参数就会占用_1这个位置
	其中，myprint只需要写一个参数是因为，我们固定了print(int a, int b)的第一个参数为20，只需要传一个
	参数即可，因此我们得到，a = 20, b = 30

	相应的_2、_3、_4...、_n，代表着函数实参的第n个参数，而且还需要注意的是，如果实参只有1个参数，而我们
	写_2或以上会报错，因为_2或以上会去尝试匹配实参的第2以上的实参位置，结果我们发现只有1个参数，此时就会
	出现参数匹配错误，因此我们需要按照实参的个数，按照规则进行匹配

*/

void myFunc1(int v1, int v2)
{
	cout << "v1 = " << v1 << endl;
	cout << "v2 = " << v2 << endl;
	cout << v1 + v2 << " ";
}

// 1、bind绑定普通函数(同样是实现在输出结果的基础上+100的案例)
void test1()
{
	vector<int> v1;

	int n = 10;
	for (int i = 0; i < n; ++i)
	{
		v1.push_back(rand() % 30 + 1);
	}
	cout << "原数据：";
	for_each(v1.begin(), v1.end(), [](int val)->void {cout << val << " "; });
	cout << endl;

	// _2是匹配函数实参的第二个参数的，_1是匹配函数参数的第一个参数的
	// 这里先写_2再写_1的话就代表函数greater<int>的第一个参数传入的是实参的第二个参数
	// 第二个参数传入的是实参的第一个参数，这也就实现了not2(greater<int>())
	sort(v1.begin(), v1.end(), bind(greater<int>(), placeholders::_2, placeholders::_1));

	cout << "现数据：";
	
	// 这里需要注意的是，200写的位置是绑定的位置，也就是说_1是我们传v1.begin()的位置
	// 因为v1.begin()会以实参的形式传入myFunc1函数，代表第一个实参
	for_each(v1.begin(), v1.end(), bind(myFunc1, 200, placeholders::_1));
	cout << endl;
}

struct MyFunc2
{
	void __thiscall operator()(int v1, int v2)
	{
		cout << "v1 = " << v1 << endl;
		cout << "v2 = " << v2 << endl;
		cout << v1 + v2 << endl;
	}
	
};

// 2、bind绑定自定义函数对象(实现在输出结果的基础上+250的案例)
void test2()
{
	vector<int> v2;

	// function类可以将传入的普通函数、成员函数、Lambda表达式、函数指针、函数对象等，进行处理，然后返回一个
	// 具有对应功能(指的是普通函数、成员函数、Lambda表达式、函数指针、函数对象等对应的功能)的函数对象给我们使用
	function<void(int)> myprint = [](int val)->void {cout << val << " "; };

	int n = 10;
	for (int i = 0; i < n; ++i)
	{
		v2.push_back(rand() % 50 + 1);
	}
	cout << "原数据：";

	// 因为这里的myprint已经是对象，所以我们不需要加()，之前加()是因为我们创建的是匿名对象
	// 我们没有像上面那样专门创建一个对象(如myprint)，所以这里直接传入对象myprint，for_each会
	// 通过对象myprint自动调用operator()函数
	for_each(v2.begin(), v2.end(), myprint);
	cout << endl;

	// 同样的将获取的值取反
	sort(v2.begin(), v2.end(), bind(greater<int>(), placeholders::_2, placeholders::_1));

	cout << "现数据：" << endl;
	// 同理，将第一个形数绑定为250，然后把对应的v2.begin()的值传递给第一个实参
	for_each(v2.begin(), v2.end(), bind(MyFunc2(), 250, placeholders::_1));
	cout << endl;
}

int main(int argc, char* argv[])
{
	srand((unsigned int)time(nullptr));
	test2();

	return 0;
}
