#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <numeric>
#include <cstdlib>
#include <ctime>
using namespace std;

// 生成随机数
template<typename T>
void randMyArr(T& arr, int n)
{
	for (int i = 0; i < n; ++i)
	{
		arr.push_back(rand() % 50 + 21);
	}
}

// 打印输出容器
template<typename T>
void printMyArr(T& arr)
{
	for_each(arr.begin(), arr.end(), [](int val)->void {cout << val << " "; });
	cout << endl;
}


void test01()
{
	// 1、按数值查找(find)
	vector<int> v1;
	randMyArr(v1, 10);
	cout << "v1数据：";
	printMyArr(v1);

	// 需要注意的是，如果找不到数据，就会返回v1.end()，其中很显然，因为迭代器已经找到
	// 末尾了，所以it1如果是v1.end()的话，那就意味着不存在需要找的数据
	v1.push_back(40);
	vector<int>::iterator it1 = find(v1.begin(), v1.end(), 40);

	if (it1 == v1.end())
	{
		cout << "查找失败" << endl;
	}
	else
	{
		cout << "查找成功，结果为：" << *it1 << endl;
	}

	cout << "==================================" << endl;
	// 2、按条件查找(find_if)

	auto myjudge = [](int v1, int v2)->bool {
		return v1 > v2;
		};

	// 把v1的元素值当实参传给_1，绑定第二个形参为36
	// 同样道理，如果没有找到也是返回v1.end()
	vector<int>::iterator it2 = find_if(v1.begin(), v1.end(), bind(myjudge, placeholders::_1, 36));
	if (it2 == v1.end())
	{
		cout << "查找失败" << endl;
	}
	else
	{
		cout << "查找成功，满足条件(v > 36)的是：" << *it2 << endl;
	}
}

class Maker
{
public:
	Maker() :name(""), age(0) {}
	Maker(string name, int age) :name(name), age(age) {}
	string getName() const { return this->name; }
	int getAge() const { return this->age; }
	bool operator==(const Maker& m)
	{
		return this->age == m.age && this->name == m.name;
	}

	~Maker() = default;
private:
	string name;
	int age;
};

// 自定义函数对象
struct MyFunc01
{
	bool operator()(const Maker& m1, const Maker& m2)
	{
		return m1.getAge() > m2.getAge();
	}
};


void test02()
{
	vector<Maker> v1;
	v1.push_back(Maker("aaa", 18));
	v1.push_back(Maker("bbb", 19));
	v1.push_back(Maker("ccc", 20));
	v1.push_back(Maker("ddd", 21));
	v1.push_back(Maker("eee", 22));

	vector<Maker>::iterator it1 = find(v1.begin(), v1.end(), Maker("ccc", 20));
	if (it1 == v1.end())
	{
		cout << "查找失败" << endl;
	}
	else
	{
		cout << "查找成功，结果为：" << "姓名：" << it1->getName() << " 年龄：" << it1->getAge() << endl;
	}

	cout << "=========================================" << endl;

	vector<Maker>::iterator it2 = find_if(v1.begin(), v1.end(), bind(MyFunc01(), placeholders::_1, Maker("ddd", 21)));
	if (it2 == v1.end())
	{
		cout << "查找失败" << endl;
	}
	else
	{
		cout << "查询成功，结果为：" << "姓名：" << it2->getName() << " 年龄：" << it2->getAge() << endl;
	}

}

/*
	adjacent_find算法 查找相邻重复元素
	@param beg 容器开始迭代器
	@param end 容器结束迭代器
	@param  _callback 回调函数或者谓词(返回bool类型的函数对象)
	@return 返回相邻元素的第一个位置的迭代器
*/

bool myadjacent_func(const Maker& m1, const Maker& m2)
{
	return m1.getAge() == m2.getAge() && m1.getName() == m2.getName();
}

void test03()
{
	vector<int> v1;

	v1.push_back(10);
	v1.push_back(20);
	v1.push_back(30);
	v1.push_back(40);
	v1.push_back(40);
	v1.push_back(60);

	// 1、adjacent_find(begin(), end())是便于我们使用基本数据类型的
	vector<int>::iterator it1 = adjacent_find(v1.begin(), v1.end());
	if (it1 == v1.end())
	{
		cout << "查找相邻元素失败" << endl;
	}
	else
	{
		cout << "查找成功，相邻元素的第一个元素为：" << *it1 << endl;
	}

	cout << "=======================================" << endl;

	// 2、adjacent_find(begin(), end(), func)是便于我们处理自定义类和自定义查询规则的

	vector<Maker> v2;

	v2.push_back(Maker("aaa", 18));
	v2.push_back(Maker("bbb", 19));
	v2.push_back(Maker("ccc", 20));
	v2.push_back(Maker("ccc", 20));
	v2.push_back(Maker("ddd", 22));
	v2.push_back(Maker("eee", 23));

	vector<Maker>::iterator it2 = adjacent_find(v2.begin(), v2.end(), myadjacent_func);
	if (it2 == v2.end())
	{
		cout << "查询相邻元素失败" << endl;
	}
	else
	{
		cout << "查找成功，相邻元素的第一个元素为：" << "姓名：" << it2->getName() << " 年龄：" << it2->getAge() << endl;
	}
}

/*
	binary_search算法 二分查找法
	注意: 在无序序列中不可用
	@param beg 容器开始迭代器
	@param end 容器结束迭代器
	@param value 查找的元素
	@return bool 查找返回true 否则false
*/

class Student
{
public:
	Student() :name(""), age(0) {}
	Student(string name, int age) :name(name), age(age) {}
	string getName() const { return this->name; }
	int getAge() const { return this->age; }
	
	bool operator==(const Student& stu1)const
	{
		return this->age == stu1.age && this->name == stu1.name;
	}

	bool operator>(const Student& stu1)const
	{
		return this->age > stu1.age;
	}

	bool operator<(const Student& stu1)const
	{
		return this->age < stu1.age;
	}

private:
	string name;
	int age;
};

void test04()
{
	vector<int> v1;
	v1.push_back(10);
	v1.push_back(20);
	v1.push_back(30);
	v1.push_back(40);
	v1.push_back(50);
	v1.push_back(60);

	bool flag = binary_search(v1.begin(), v1.end(), 30);
	if (flag)
	{
		cout << "找到元素为30" << endl;
	}
	else
	{
		cout << "未找到元素" << endl;
	}

	cout << "===============================" << endl;
	// 使用自定义对象查找
	vector<Student> v2;
	v2.push_back(Student("a1", 1));
	v2.push_back(Student("a2", 2));
	v2.push_back(Student("a3", 3));
	v2.push_back(Student("a4", 4));
	v2.push_back(Student("a5", 5));
	v2.push_back(Student("a6", 6));
	v2.push_back(Student("a7", 7));

	// 需要注意的是，如果是元素是升序的，那么就必须使用less<>()函数对象，不过这个是默认的，可以不写
	// 但如果是元素是降序的，那就必须使用greater<>()函数对象，这个是需要指定第四个参数的
	// 并且自定义对象需要重载>或<等运算符，自己指定比较规则，否则会报错
	bool flag2 = binary_search(v2.begin(), v2.end(), Student("a6", 6), less<Student>());
	if (flag2)
	{
		cout << "查找元素Student(\"a6\", 6)成功" << endl;
	}
	else
	{
		cout << "查找元素失败" << endl;
	}
}

/*
	count算法 统计元素出现次数
	@param beg 容器开始迭代器
	@param end 容器结束迭代器
	@param  value回调函数或者谓词(返回bool类型的函数对象)
	@return int返回元素个数
*/
void test05()
{
	vector<int> v1 = { 1,1,2,1,3,4 ,5,6 };

	// 这代码的意思是统计元素为1的个数
	int n =  count(v1.begin(), v1.end(), 1);
	cout << "n(count) = " << n << endl;

	// 这行的意思是，统计大于2的个数
	n = count_if(v1.begin(), v1.end(), [](int val)->bool {return val > 2; });
	cout << "n(count_if) = " << n << endl;

}

int main(int argc, char* argv[])
{
	srand((unsigned int)time(nullptr));
	test05();

	return 0;
}
