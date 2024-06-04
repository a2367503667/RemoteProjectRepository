#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <numeric> // 算术生成算法头文件
#include <cstdlib>
#include <cstring>
#include <ctime>
using namespace std;

/*
	accumulate算法 计算容器元素累计总和
	@param beg 容器开始迭代器
	@param end 容器结束迭代器
	@param value累加值
*/
void test01()
{
	vector<int> v1;

	int n = 5;
	for (int i = 0; i < n; ++i)
	{
		v1.push_back((i + 1) * 10);
	}
	// 这个函数就是将所有元素的值都加起来，并且加上后面的1
	int ret = accumulate(v1.begin(), v1.end(), 1);
	cout << "ret = " << ret << endl;
}

class Maker
{
public:
	Maker() :age(0) {}
	Maker(int age) :age(age) {}
	int getAge()const { return this->age; }
	~Maker() = default;
private:
	int age;
};

struct MyFunc01
{
	int operator()(int val, const Maker& m)
	{
		return val + m.getAge();
	}

};

void test02()
{
	vector<Maker> v1;
	
	int n = 5;
	for (int i = 0; i < n; ++i)
	{
		v1.push_back(Maker((i + 1) * 10));
	}

	// 所需要传入的函数对象的样子为(val, 自定义类)，其中val值是每次加和的值，返回值为val的类型
	int ret = accumulate(v1.begin(), v1.end(), 2, MyFunc01());
	cout << "ret = " << ret << endl;
}

/*
	fill算法 向容器中添加元素
	@param beg 容器开始迭代器
	@param end 容器结束迭代器
	@param value t填充元素
*/
void test03()
{
	auto printFunc = [](int val)->void {cout << val << " "; };
	vector<int> v1;
	v1.resize(10);

	// 需要注意的是，如果没有预留空间的话，它是不会插入数据的(但不会报错)
	fill(v1.begin(), v1.end(), 88);
	cout << "v1的数据为：";
	for_each(v1.begin(), v1.end(), printFunc);
	cout << endl;
}

int main(int argc, char* argv[])
{
	srand((unsigned)time(nullptr));
	test03();

	return 0;
}
