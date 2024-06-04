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
	merge算法 容器元素合并，并存储到另一容器中
	注意：两个容器必须是有序的
	@param beg1 容器1开始迭代器
	@param end1 容器1结束迭代器
	@param beg2 容器2开始迭代器
	@param end2 容器2结束迭代器
	@param dest  目标容器开始迭代器
*/
void test01()
{
	auto printFunc = [](int val)->void {cout << val << " "; };
	vector<int> v1;
	vector<int> v2;

	int n = 5;
	for (int i = 0; i < n; ++i)
	{
		v1.push_back(rand() % 20);
		v2.push_back(rand() % 20);
	}

	// 需要注意的是，merge函数是需要元素有序的，否则会报错，因此我们需要先进性排序
	// 并且合并的两个数组都要是同升同降的，不能一升一降
	cout << "v1：";
	sort(v1.begin(), v1.end());
	for_each(v1.begin(), v1.end(), printFunc);
	cout << endl;
	cout << "v2：";
	sort(v2.begin(), v2.end());
	for_each(v2.begin(), v2.end(), printFunc);
	cout << endl;

	// 需要注意的是，v3需要开辟空间
	vector<int> v3;
	v3.resize(v1.size() + v2.size());
	// merge函数也没有对元素进行去重
	// 如果merge最后一个参数指定降序排序，那么就要求合并的数据全部都要降序
	// 即若最后一个参数为greater<int>()，那v1和v2都需要降序
	merge(v1.begin(), v1.end(), v2.begin(), v2.end(), v3.begin());
	cout << "v3：";
	for_each(v3.begin(), v3.end(), printFunc);
}

/*
	sort算法 容器元素排序
	@param beg 容器1开始迭代器
	@param end 容器1结束迭代器
	@param _callback 回调函数或者谓词(返回bool类型的函数对象)
*/
void test02()
{
	auto printFunc = [](int val)->void {cout << val << " "; };
	vector<int> v1;

	int n = 5;
	for (int i = 0; i < n; ++i)
	{
		v1.push_back(rand() % 20);
	}
	cout << "v1未排序前：";
	for_each(v1.begin(), v1.end(), printFunc);
	cout << endl;

	cout << "v1升序排序后：";
	sort(v1.begin(), v1.end());
	for_each(v1.begin(), v1.end(), printFunc);
	cout << endl;

	cout << "v1降序排序后：";
	sort(v1.begin(), v1.end(), greater<int>());
	for_each(v1.begin(), v1.end(), printFunc);
	cout << endl;
}

/*
	random_shuffle算法 对指定范围内的元素随机调整次序
	但是我们需要知道，它只是伪随机，并不是真正意义上的随机数，所以我们需要
	加随机数种子
	@param beg 容器开始迭代器
	@param end 容器结束迭代器
*/
void test03()
{
	auto printFunc = [](int val)->void {cout << val << " "; };
	vector<int> v1;

	int n = 10;
	for (int i = 0; i < n; ++i)
	{
		v1.push_back(i + 1);
	}
	cout << "v1未但乱顺序：";
	for_each(v1.begin(), v1.end(), printFunc);
	cout << endl;

	cout << "v1打乱顺序之后：";
	random_shuffle(v1.begin(), v1.end());
	for_each(v1.begin(), v1.end(), printFunc);
	cout << endl;
}

/*
	reverse算法 反转指定范围的元素
	@param beg 容器开始迭代器
	@param end 容器结束迭代器
*/
void test04()
{
	auto printFunc = [](int val)->void {cout << val << " "; };
	vector<int> v1;

	int n = 10;
	for (int i = 0; i < n; ++i)
	{
		v1.push_back(i + 1);
	}
	cout << "v1未翻转：";
	for_each(v1.begin(), v1.end(), printFunc);
	cout << endl;

	cout << "v1翻转后：";
	reverse(v1.begin(), v1.end());
	for_each(v1.begin(), v1.end(), printFunc);
	cout << endl;
}


int main(int argc, char* argv[])
{
	srand((unsigned)time(nullptr));
	test04();

	return 0;
}
