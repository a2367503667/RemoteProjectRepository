#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
#include <numeric>
#include <cstdlib>
#include <ctime>
using namespace std;

// 容器内生成随机数
template<typename T>
void randMyArr(T& arr, int n)
{
	for (int i = 0; i < n; ++i)
	{
		arr.push_back(rand() % 50 + 21);
	}
}

class MyFunc01
{
public:
	MyFunc01() :name(""), age(0), count(0) {}
	MyFunc01(string name, int age) :name(name), age(age), count(0) {}

	//MyFunc01(const MyFunc01& mf)
	//{
	//	cout << "MyFunc01拷贝构造函数" << endl;
	//}

	MyFunc01(const MyFunc01& mf) = default;

	void operator()(const int val)const
	{
		++(this->count);
		cout << val << " ";
	}

	string getName()
	{
		return this->name;
	}

	int getAge()
	{
		return this->age;
	}

	int getCount()
	{
		return this->count;
	}

private:
	string name;
	int age;
	mutable int count;
};

// 1、for_each算法
void test01()
{
	vector<int> v1;

	int n = 10;
	for (int i = 0; i < n; ++i)
	{
		v1.push_back(rand() % 50 + 1);
	}
	cout << "原数据：";
	for_each(v1.begin(), v1.end(), [](int val)->void {cout << val << " "; });
	cout << endl;

	sort(v1.begin(), v1.end(), less<int>());

	// 先重新书写operator()函数，然后在函数内部记录每次调用的次数并+1
	// 然后观察输出的次数
	cout << "现数据：";

	// 需要注意的是for_each函数只是拷贝了mf这个对象，也就是说变化的只是内部拷贝出来的
	// 对象mf'，而mf是不会发生变化的，但是我们可以使用MyFunc01对象mf2进行接收for_each的
	// 返回值，因为for_each的返回值是MyFunc01类型
	MyFunc01 mf2 = for_each(v1.begin(), v1.end(), MyFunc01());
	cout << endl;
	cout << "count = " << mf2.getCount() << endl;
}

struct MyAdd
{
	int operator()(int v1, int v2)
	{
		return v1 + v2;
	}
};


// 2、transform算法
void test02()
{
	vector<int> v1;
	randMyArr(v1, 10);

	auto myprint = [](int val)->void {cout << val << " "; };

	cout << "v1原数据：";
	for_each(v1.begin(), v1.end(), myprint);
	cout << endl;
	
	vector<int> v2;

	// transform函数是用于将一个容器的内容赋值到到另一个容器中去的
	// 并且在转义之前，必须要要给目标容器开辟空间，要不然会报错，因为
	// transform函数不会给容器开辟空间
	v2.resize(v1.size()); // 给v2开辟空间且大小和v1相同

	// 而且不仅可以将v1赋值给v2容器，还可以对数值进行处理后再赋值给v2容器
	// 只不过最后一个处理方式(函数或函数对象)需要自己定义


	// 下面就以每个数+200为例
	// 将第二个形参绑定为200
	transform(v1.begin(), v1.end(), v2.begin(), bind(MyAdd(), placeholders::_1, 200));
	cout << "v2数据：";
	for_each(v2.begin(), v2.end(), myprint);
	cout << endl;

	cout << "v1数据：";
	for_each(v1.begin(), v1.end(), myprint);
	cout << endl;

	cout << "===================================" << endl;
	// 上面只处理一个容器，即v1的数据处理后赋值给v2，其实我们还可以使用两个容器处理后的数值
	// 赋值给新的容器，下面就使用transform的第二个函数
	vector<int> v3;
	
	randMyArr(v2, rand() % 10 + 1);
	int size1 = v1.size();
	int size2 = v2.size();

	// 这里需要注意的是，我们选取源容器最大的作为我们目标容器的大小，避免出现赋值错误的问题
	if (size1 > size2)
	{
		v3.resize(size1);
	}
	else
	{
		v3.resize(size2);
	}

	/*
		注：transform函数只会以最小的容器为基准，也就是说v1元素比v2多，那v3最多只会处理v1容器
		这么多的数据，多出来的数据不会进行处理
	*/
	//			v1开始	 v1结束		v2开始		v3开始			加法函数对象	实参第一个参数	实参第二个参数
	transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), bind(MyAdd(), placeholders::_1, placeholders::_2));
	cout << "v1数据：";
	for_each(v1.begin(), v1.end(), myprint);
	cout << endl;

	cout << "v2数据：";
	for_each(v2.begin(), v2.end(), myprint);
	cout << endl;

	cout << "v3数据：";
	for_each(v3.begin(), v3.end(), myprint);
	cout << endl;

}



int main(int argc, char* argv[])
{
	srand((unsigned int)time(nullptr));
	test02();

	return 0;
}
