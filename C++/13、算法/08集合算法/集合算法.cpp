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

// 集合算法就是进行一些集合运算的，如：并集、交集和补集等等
/*
	set_intersection算法 求两个set集合的交集
	注意:两个集合必须是有序序列
	@param beg1 容器1开始迭代器
	@param end1 容器1结束迭代器
	@param beg2 容器2开始迭代器
	@param end2 容器2结束迭代器
	@param dest  目标容器开始迭代器
	@return 目标容器的最后一个元素的迭代器地址
*/
void test01()
{
	vector<int> v1, v2;
	int n1 = 10, n2 = 15;
	for (int i = 1; i <= n1; ++i)
	{
		v1.push_back(i);
	}
	for (int i = 5; i < n2; ++i)
	{
		v2.push_back(i);
	}

	vector<int> v3;
	auto printFunc = [](int val)->void {cout << val << " "; };
	// 因为取交集的话，最多只会是最小长度的容器
	v3.resize(min(v1.size(), v2.size())); // risize之后，元素默认值为0
	cout << "v3：";
	for_each(v3.begin(), v3.end(), printFunc);
	cout << endl;

	set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), v3.begin());
	cout << "v3：";
	for_each(v3.begin(), v3.end(), printFunc);
	cout << endl;
}

/*
	set_union算法 求两个set集合的并集
	注意:两个集合必须是有序序列
	@param beg1 容器1开始迭代器
	@param end1 容器1结束迭代器
	@param beg2 容器2开始迭代器
	@param end2 容器2结束迭代器
	@param dest  目标容器开始迭代器
	@return 目标容器的最后一个元素的迭代器地址
*/
void test02()
{
	vector<int> v1, v2;
	int n1 = 10, n2 = 15;
	for (int i = 1; i <= n1; ++i)
	{
		v1.push_back(i);
	}
	for (int i = 5; i < n2; ++i)
	{
		v2.push_back(i);
	}

	vector<int> v3;
	// 因为是取并集，所以长度最长是两个容器相加
	v3.resize(v1.size() + v2.size());

	// 并集处理是会去重的(把重复的元素去除，只保留一个)
	set_union(v1.begin(), v1.end(), v2.begin(), v2.end(), v3.begin());
	cout << "v3：";
	auto printFunc = [](int val)->void {cout << val << " "; };
	for_each(v3.begin(), v3.end(), printFunc);
	cout << endl;
}

/*
	set_difference算法 求两个set集合的差集
	注意:两个集合必须是有序序列
	@param beg1 容器1开始迭代器
	@param end1 容器1结束迭代器
	@param beg2 容器2开始迭代器
	@param end2 容器2结束迭代器
	@param dest  目标容器开始迭代器
	@return 目标容器的最后一个元素的迭代器地址

	假设有A集合{1,2,3,4,5} B集合{2,3,4,5,6} 那么A与B的差集为1
	B与A的差集为6
*/

void test03()
{
	vector<int> v1, v2;
	for (int i = 1; i <= 6; ++i)
	{
		v1.push_back(i);
	}	
	for (int i = 3; i <= 7; ++i)
	{
		v2.push_back(i);
	}

	vector<int> v3;
	// 因为差集有可能是一个集合减去一个空集，所以最大的长度是容器长度取最大
	v3.resize(max(v1.size(), v2.size()));
	set_difference(v1.begin(), v1.end(), v2.begin(), v2.end(), v3.begin());
	cout << "v3(v1 - v2)：";
	auto printFunc = [](int val)->void {cout << val << " "; };
	for_each(v3.begin(), v3.end(), printFunc);
	cout << endl;

	v3.clear();
	v3.resize(max(v1.size(), v2.size()));
	set_difference(v2.begin(), v2.end(), v1.begin(), v1.end(), v3.begin());
	cout << "v3(v2 - v1)：";
	for_each(v3.begin(), v3.end(), printFunc);
	cout << endl;
}


int main(int argc, char* argv[])
{
	srand((unsigned)time(nullptr));
	test03();

	return 0;
}
