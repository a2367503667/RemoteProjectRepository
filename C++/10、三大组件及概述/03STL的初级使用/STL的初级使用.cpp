#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector> // 向量容器
#include <string> // 字符串容器
#include <algorithm> // 算法
#include <cstdlib>
#include <cstring>

class Maker;
// 自定义类
class Maker
{
	friend std::ostream& operator<<(std::ostream& out, const Maker& val);
public:
	Maker(int age, std::string name)
	{
		this->age = age;
		this->name = name;
	}

private:
	int age;
	std::string name;
};


// 在for_each算法函数当中，需要传一个处理函数，便于遍历到的数据进行相应的处理
// 处理函数模板
template<typename T>
void printMsg(T val)
{
	std::cout << val << " ";
}

// 1、使用容器的一般过程(容器元素为普通变量)
void test01()
{
	// (1)创建容器对象
	std::vector<int> v;

	// (2)输入数据
	v.push_back(10);
	v.push_back(20);
	v.push_back(30);
	v.push_back(40);
	v.push_back(50);

	// (3)获取容器迭代器
	std::vector<int>::iterator begin = v.begin();
	std::vector<int>::iterator end = v.end();

	// (4)使用算法进行输出
	std::for_each(begin, end, printMsg<int>);
	std::cout << std::endl;
}

std::ostream& operator<<(std::ostream& out, const Maker& val)
{
	std::cout << "age = " << val.age << std::endl;
	std::cout << "name = " << val.name << std::endl;

	return out;
}


// 2、容器元素为对象
void test02()
{
	std::vector<Maker> v;

	v.push_back(Maker(18, "张三"));
	v.push_back(Maker(19, "李四"));
	v.push_back(Maker(20, "王五"));
	v.push_back(Maker(21, "赵六"));
	v.push_back(Maker(22, "老八"));

	std::vector<Maker>::iterator begin = v.begin();
	std::vector<Maker>::iterator end = v.end();

	while (begin != end)
	{
		std::cout << (*begin) << std::endl;
		++begin;
	}

}

// 3、存储的对象是指针
void test03()
{
	std::vector<Maker*> v;

	Maker* m1 = new Maker(18, "张三");
	Maker* m2 = new Maker(19, "李四");
	Maker* m3 = new Maker(20, "王五");
	Maker* m4 = new Maker(21, "赵六");
	Maker* m5 = new Maker(22, "老八");

	v.push_back(m1);
	v.push_back(m2);
	v.push_back(m3);
	v.push_back(m4);
	v.push_back(m5);

	std::vector<Maker*>::iterator begin = v.begin();
	std::vector<Maker*>::iterator end = v.end();

	while (begin != end)
	{
		std::cout << (**begin) << std::endl;
		++begin;
	}

	delete m1;
	delete m2;
	delete m3;
	delete m4;
	delete m5;

	m1 = m2 = m3 = m4 = m5 = nullptr;
}

// 4、容器嵌套容器
void test04()
{
	std::vector<std::vector<int>> vArr;

	std::vector<int> v1;
	std::vector<int> v2;
	std::vector<int> v3;
	std::vector<int> v4;
	std::vector<int> v5;

	for (int i = 0; i < 10; ++i)
	{
		v1.push_back(101 + i);
		v2.push_back(101 + i);
		v3.push_back(101 + i);
		v4.push_back(101 + i);
		v5.push_back(101 + i);
	}

	vArr.push_back(v1);
	vArr.push_back(v2);
	vArr.push_back(v3);
	vArr.push_back(v4);
	vArr.push_back(v5);

	std::vector<std::vector<int>>::iterator begin = vArr.begin();
	std::vector<std::vector<int>>::iterator end = vArr.end();

	while (begin != end)
	{
		// (1)指的是当前二维数组的元素(一维数组)的开始位置
		std::vector<int>::iterator sBegin = (*begin).begin();
		
		// (2)指的是当前二维数据的元素(一维数组)的结束位置
		std::vector<int>::iterator sEnd = (*begin).end();
		while (sBegin != sEnd)
		{
			std::cout << (*sBegin) << " ";
			++sBegin;
		}
		std::cout << std::endl;
		++begin;
	}
}

int main(int argc, char* argv[])
{
	// test01();
	// test02();
	// test03();
	test04();

	return 0;
}
