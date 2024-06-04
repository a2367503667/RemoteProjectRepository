#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <numeric>
#include <cstdlib>
#include <cstring>
#include <ctime>
using namespace std;

/*
	copy算法 将容器内指定范围的元素拷贝到另一容器中
	需要注意的是，新的容器需要我们手动开辟空间
	@param beg 容器开始迭代器
	@param end 容器结束迭代器
	@param dest 目标容器结束迭代器
*/
void test01()
{
	auto printFunc = [](int val)->void {cout << val << " "; };
	vector<int> v1;

	int n = 5;
	for (int i = 0; i < n; ++i)
	{
		v1.push_back((i + 1) * 10);
	}

	vector<int> v2;
	v2.resize(v1.size());
	copy(v1.begin(), v1.end(), v2.begin());
	cout << "v2容器的数据为：";
	for_each(v2.begin(), v2.end(), printFunc);
	cout << endl;
}

/*
	replace算法 将容器内指定范围的旧元素修改为新元素
	@param beg 容器开始迭代器
	@param end 容器结束迭代器
	@param oldvalue 旧元素
	@param oldvalue 新元素

	replace_if算法 将容器内指定范围满足条件的元素替换为新元素
	@param beg 容器开始迭代器
	@param end 容器结束迭代器
	@param callback函数回调或者谓词(返回Bool类型的函数对象)
	@param oldvalue 新元素

*/
void test02()
{
	auto printFunc = [](int val)->void {cout << val << " "; };
	vector<int> v1;

	int n = 5;
	for (int i = 0; i < n; ++i)
	{
		v1.push_back((i + 1) * 10);
	}
	v1.push_back(30);
	// 也就是说，我们把容器里面的某个/些元素替换成新的元素
	// 下面这个例子就是，将容器中的30都替换成300(如果有多个30那就会全部替换掉)
	replace(v1.begin(), v1.end(), 30, 300);
	cout << "v1替换值之后(replace)：";
	for_each(v1.begin(), v1.end(), printFunc);
	cout << endl;

	cout << "==================================================" << endl;

	// 先把数都替换回来
	replace(v1.begin(), v1.end(), 300, 30);

	auto myFunc = [](int val)->bool {return val > 30; };
	// 这个函数就是将只要大于30的数都替换成888
	replace_if(v1.begin(), v1.end(), myFunc, 888);
	cout << "v1替换值之后(replace_if)：";
	for_each(v1.begin(), v1.end(), printFunc);
	cout << endl;
}

/*
	swap算法 互换两个容器的元素
	@param c1容器1
	@param c2容器2
*/
void test03()
{
	auto printFunc = [](int val)->void {cout << val << " "; };
	vector<int> v1, v2;

	int n = 10;
	for (int i = 0; i < n; ++i)
	{
		v1.push_back(i + 1);
		v2.push_back((i + 1) * 100);
	}
	cout << "v1：";
	for_each(v1.begin(), v1.end(), printFunc);
	cout << endl;
	cout << "v2：";
	for_each(v2.begin(), v2.end(), printFunc);
	cout << endl;

	cout << "========================================================" << endl;

	swap(v1, v2);
	cout << "v1(交换后)：";
	for_each(v1.begin(), v1.end(), printFunc);
	cout << endl;
	cout << "v2(交换后)：";
	for_each(v2.begin(), v2.end(), printFunc);
	cout << endl;
}


int main(int argc, char* argv[])
{
	srand((unsigned)time(nullptr));
	test03();

	return 0;
}
