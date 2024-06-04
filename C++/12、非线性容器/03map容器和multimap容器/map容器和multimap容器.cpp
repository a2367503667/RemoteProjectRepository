#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <map>
#include <string>
using namespace std;

template<typename T>
void printMsg(T& mym)
{
	typename T::iterator begin = mym.begin();
	typename T::iterator end = mym.end();

	while (begin != end)
	{
		cout << "key: " << begin->first << ", value: " << begin->second << endl;
		++begin;
	}
}

// 1、验证迭代器
void test01()
{
	map<int, string>::iterator it;
	it++;
	it--;
	// it + 2; // 双向迭代器

	multimap<int, string>::iterator it2;
	it2++;
	it2--;
	// it2 + 2; // 双向迭代器
}

/*
1、构造函数
map<T1, T2> mapTT;//map默认构造函数:
map(const map &mp);//拷贝构造函数

2、赋值操作
map&operator=(const map &mp);//重载等号操作符
swap(mp);//交换两个集合容器

3、大小操作
size();//返回容器中元素的数目
empty();//判断容器是否为空

4、插入操作
map.insert(...); //往容器插入元素，返回pair<iterator,bool>
map<int, string> mapStu;
// 第一种 通过pair的方式插入对象
mapStu.insert(pair<int, string>(3, "小张"));
// 第二种 通过pair的方式插入对象
mapStu.inset(make_pair(-1, "校长"));
// 第三种 通过value_type的方式插入对象
mapStu.insert(map<int, string>::value_type(1, "小李"));
// 第四种 通过数组的方式插入值
mapStu[3] = "小刘";
mapStu[5] = "小王";

5、删除操作
clear();//删除所有元素
erase(pos);//删除pos迭代器所指的元素，返回下一个元素的迭代器。
erase(beg,end);//删除区间[beg,end)的所有元素 ，返回下一个元素的迭代器。
erase(keyElem);//删除容器中key为keyElem的对组。

6、查找操作
find(key);//查找键key是否存在,若存在，返回该键的元素的迭代器；/若不存在，返回map.end();
count(keyElem);//返回容器中key为keyElem的对组个数。对map来说，要么是0，要么是1。对multimap来说，值可能大于1。
lower_bound(keyElem);//返回第一个key>=keyElem元素的迭代器。
upper_bound(keyElem);//返回第一个key>keyElem元素的迭代器。
equal_range(keyElem);//返回容器中key与keyElem相等的上下限的两个迭代器。

*/

// 2、插入数据
void test02()
{
	cout << "map: ------------------------" << endl;

	map<string, int> mym1;
	
	// 1、insert(pair)插入数据
	mym1.insert(pair<string, int>("aaa", 10));

	// 2、insert(make_pair)插入数据
	mym1.insert(make_pair("bbb", 20));

	// 3、使用insert的map::value_type插入数据
	mym1.insert(map<string, int>::value_type("ccc", 40));

	// 4、使用数组形式的key-value方法插入数据
	mym1["ddd"] = 30;

	printMsg<map<string, int>>(mym1);
	cout << mym1["ddd"] << endl; //30 输入键值，获取的是实值

	// 如果没有对应的实值，此时如果调用数组的key-value的话，会添加一个新的键值，如：
	cout << "mym1.size = " << mym1.size() << endl; // 4
	cout << mym1["eee"] << endl; // 调用mym1["eee"]就会添加一个键值对
	cout << "mym1.size = " << mym1.size() << endl; // 5

	pair<map<string, int>::iterator, bool> myp = mym1.insert(pair<string, int>("aaa", 30));

	// 如果插入相同键值的元素，则会插入失败
	if (myp.second == false)
	{
		cout << "插入失败" << endl;
	}
	else
	{
		cout << "插入成功，实值为：" << (myp.first)->second << endl;
	}

	cout << "multimap: -------------------------------" << endl;

	// multimap没有数组key-value(键值对)方式插入
	multimap<string, int> mym2;

	// 1、pair方式插入数据
	mym2.insert(pair<string, int>("aaaaaa", 100));

	// 2、make_pair方式插入数据
	mym2.insert(make_pair("bbbbbb", 200));

	// 3、multimap::value_type方式插入数据
	mym2.insert(multimap<string, int>::value_type("dddddd", 400));

	// multimap允许插入相同的元素
	mym2.insert(pair<string, int>("aaaaaa", 100));
	mym2.insert(make_pair("bbbbbb", 200));

	printMsg<multimap<string, int>>(mym2);

	multimap<string, int>::iterator it2 = mym2.insert(multimap<string, int>::value_type("kkkkkk", 800));

	if (it2 == mym2.end())
	{
		cout << "插入失败" << endl;
	}
	else
	{
		cout << "插入成功，实值为：" << it2->second << endl;
	}


}

// 3、查找数据
void test03()
{
	cout << "map: --------------------------" << endl;
	map<string, int> mym1;

	mym1["aaa"] = 10;
	mym1["bbb"] = 20;
	mym1["ccc"] = 30;
	mym1["ddd"] = 40;
	mym1["eee"] = 50;
	mym1["fff"] = 60;

	map<string, int>::iterator it1 = mym1.find("ddd");
	if (it1 == mym1.end())
	{
		cout << "find查找失败" << endl;
	}
	else
	{
		cout << "find查找成功，实值为：" << it1->second << endl;
	}

	map<string, int>::iterator it2 = mym1.lower_bound("kkk");
	if (it2 == mym1.end())
	{
		cout << "lower_bound查找失败" << endl;
	}
	else
	{
		cout << "lower_bound查找成功，实值为：" << it2->second << endl;
	}

	map<string, int>::iterator it3 = mym1.upper_bound("ccc");

	if (it3 == mym1.end())
	{
		cout << "upper_bound查找失败" << endl;
	}
	else
	{
		cout << "upper_bound查找成功，实值为：" << it3->second << endl;
	}

	pair<map<string, int>::iterator, map<string, int>::iterator> myp1 = mym1.equal_range("eee");
	if (myp1.first == mym1.end())
	{
		cout << "myp1.fisrt查找失败" << endl;
	}
	else
	{
		cout << "myp1.first查找成功，实值为：" << (myp1.first)->second << endl;
	}

	if (myp1.second == mym1.end())
	{
		cout << "myp1.second查找失败" << endl;
	}
	else
	{
		cout << "my1.second查找成功，实值为：" << (myp1.second)->second << endl;
	}

	cout << "multimap: --------------------------------" << endl;

	multimap<string, int> mym2;

	mym2.insert(pair<string, int>("aaaaaa", 100));
	mym2.insert(pair<string, int>("aaaaaa", 300));
	mym2.insert(pair<string, int>("bbbbbb", 250));
	mym2.insert(pair<string, int>("bbbbbb", 300));
	mym2.insert(pair<string, int>("cccccc", 700));
	mym2.insert(pair<string, int>("dddddd", 580));
	cout << "mym2.count(\"aaaaaa\") = " << mym2.count("aaaaaa") << endl;
	
	multimap<string, int>::iterator it4 = mym2.find("cccccc");
	if (it4 == mym2.end())
	{
		cout << "find查找失败" << endl;
	}
	else
	{
		cout << "find查找成功，实值为：" << it4->second << endl;
	}

	multimap<string, int>::iterator it5 = mym2.lower_bound("dddddd");
	if (it5 == mym2.end())
	{
		cout << "lower_bound查找失败" << endl;
	}
	else
	{
		cout << "lower_bound查找成功，实值为：" << it5->second << endl;
	}

	multimap<string, int>::iterator it6 = mym2.upper_bound("kkkkkk");
	if (it6 == mym2.end())
	{
		cout << "upper_bound查找失败" << endl;
	}
	else
	{
		cout << "upper_bound查找成功，实值为：" << it6->second << endl;
	}

	pair<multimap<string, int>::iterator, multimap<string, int>::iterator> myp2 = mym2.equal_range("dddddd");
	if (myp2.first == mym2.end())
	{
		cout << "equal_range(first)查找失败" << endl;
	}
	else
	{
		cout << "equal_range(first)查找成功，实值为：" << (myp2.first)->second << endl;
	}
	
	if (myp2.second == mym2.end())
	{
		cout << "equal_range(second)查找失败" << endl;
	}
	else
	{
		cout << "equal_range(second)查找成功，实值为：" << (myp2.second)->second << endl;
	}
}


int main(int argc, char* argv[])
{
	test03();

	return 0;
}
