#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <set>
#include <typeinfo>
using namespace std;

// 1、set和multiset的迭代器
void test01()
{
	// (1) set容器迭代器
	set<int>::iterator it;
	it++;
	it--;
	// it + 2; // 双向迭代器

	// (2) multiset容器迭代器
	multiset<int>::iterator it2;
	it2++;
	it2--;
	// it2 + 3; // 双向迭代器
}

// 打印set和multiset的元素
template<typename T>
void printElement(T& mys)
{
	typename T::iterator begin = mys.begin();
	typename T::iterator end = mys.end();

	while (begin != end)
	{
		cout << *begin << " ";
		++begin;
	}
	cout << endl;
}


/*

1、构造函数
set<T> st;//set默认构造函数：
mulitset<T> mst; //multiset默认构造函数:
set(const set &st);//拷贝构造函数

2、赋值操作
set&operator=(const set &st);//重载等号操作符
swap(st);//交换两个集合容器

3、大小操作
size();//返回容器中元素的数目
empty();//判断容器是否为空

4、插入和删除
insert(elem);//在容器中插入元素。
clear();//清除所有元素
erase(pos);//删除pos迭代器所指的元素，返回下一个元素的迭代器。
erase(beg, end);//删除区间[beg,end)的所有元素 ，返回下一个元素的迭代器。
erase(elem);//删除容器中值为elem的元素。

5、查找
find(key);//查找键key是否存在,若存在，返回该键的元素的迭代器；若不存在，返回set.end();
count(key);//查找键key的元素个数
lower_bound(keyElem);//返回第一个key>=keyElem元素的迭代器。
upper_bound(keyElem);//返回第一个key>keyElem元素的迭代器。
equal_range(keyElem);//返回容器中key与keyElem相等的上下限的两个迭代器。

*/

// 2、set和multiset元素的输出顺序默认是从小到大有序的
void test02()
{
	set<int> mys1;

	mys1.insert(4);
	mys1.insert(8);
	mys1.insert(-3);
	mys1.insert(9);
	mys1.insert(6);
	printElement<set<int>>(mys1);

	cout << "------------------------" << endl;

	multiset<int> mys2;

	mys2.insert(40);
	mys2.insert(80);
	mys2.insert(-30);
	mys2.insert(90);
	mys2.insert(60);
	printElement<multiset<int>>(mys2);
}

// 谓词
struct MyCompare
{
	// 需要注意的是，属于类的成员函数作为谓词时，需要在后面加const，否则会报错
	bool operator()(int v1, int v2)const
	{
		return v1 > v2;
	}
};

void printElement(set<int, MyCompare>& mys)
{
	set<int, MyCompare>::iterator begin = mys.begin();
	set<int, MyCompare>::iterator end = mys.end();

	while (begin != end)
	{
		cout << *begin << " ";
		++begin;
	}
	cout << endl;
}

// 3、逆序输出set和multiset容器的元素
void test03()
{
	set<int, MyCompare> mys1;
	mys1.insert(4);
	mys1.insert(8);
	mys1.insert(-3);
	mys1.insert(9);
	mys1.insert(6);
	printElement<set<int, MyCompare>>(mys1);

	cout << "------------------------" << endl;

	multiset<int, MyCompare> mys2;
	
	mys2.insert(40);
	mys2.insert(80);
	mys2.insert(-30);
	mys2.insert(90);
	mys2.insert(60);
	printElement<multiset<int ,MyCompare>>(mys2);
}

// 4、set容器不能有相同元素，multiset可以有相同元素
void test04()
{
	cout << "set: ---------------------------" << endl;

	set<int> mys1;
	mys1.insert(4);
	mys1.insert(8);
	mys1.insert(-3);
	mys1.insert(9);
	mys1.insert(6);

	// insert的返回值是一个对组pair<iterator, bool>
	// 其中iterator是插入成功后返回的值(键值和真值相同)，bool是判断是否插入成功
	// 如果插入失败iterator返回end()
	pair<set<int>::iterator, bool> myp1 = mys1.insert(8);

	if (myp1.second == false)
	{
		cout << "插入失败" << endl;
	}
	else
	{
		cout << "插入成功，插入的值为：" << *(myp1.first) << endl;
	}

	// 删除元素
	cout << typeid(mys1.erase(11)).name() << endl; // 返回的是unsigned int
	cout << *(mys1.erase(mys1.begin())) << endl; // 删除当前迭代器的值就会返回下一个迭代器的值
 	printElement<set<int>>(mys1);

	cout << "multiset: ---------------------------" << endl;

	multiset<int> mys2;
	mys2.insert(40);
	mys2.insert(80);
	mys2.insert(80);
	mys2.insert(80);
	mys2.insert(60);
	mys2.insert(90);

	// 这里需要注意一下，如果是multiset，那就返回迭代器，如果是set就返回对组
	// 这里很容易想得到，因为multiset是可以重复插入数据的，所以不需要返回是否插入成功的信息
	multiset<int>::iterator it = mys2.insert(80);
	cout << "mys2.size = " << mys2.size() << endl;
	
	// 注：如果有多个元素是80，那么会把所有的80都删掉
	cout << mys2.erase(80) << endl; // 返回被删除元素的字节大小unsigned int
	cout << *(mys2.erase(mys2.begin())) << endl; // 返回下一个元素的迭代器
	printElement<multiset<int>>(mys2);
}

// 5、查找set和multiset容器的元素
void test05()
{
	cout << "set: --------------------------" << endl;
	set<int> mys1;

	mys1.insert(4);
	mys1.insert(8);
	mys1.insert(-3);
	mys1.insert(9);
	mys1.insert(6);

	set<int>::iterator it1 = mys1.find(9);
	if (it1 == mys1.end())
	{
		cout << "元素不存在" << endl;
	}
	else
	{
		cout << "查找成功，元素为：" << *it1 << endl;
	}

	set<int>::iterator it2 = mys1.lower_bound(3);
	if (it2 == mys1.end())
	{
		// 当set容器中不存在3,且没有元素大于3时，就会返回end()
		cout << "查找失败" << endl;
	}
	else
	{
		cout << "查找成功，元素为：" << *it2 << endl;
	}

	set<int>::iterator it3 = mys1.upper_bound(9);
	if (it3 == mys1.end())
	{
		// 当set容器中没有元素大于9时，就返回end()
		cout << "查找失败" << endl;
	}
	else
	{
		cout << "查找成功，元素为：" << *it3 << endl;
	}

	// equal_range返回值的第一个元组参数是lower_bound，第二个元祖参数是upper_bound
	// pair对应的两个值的情况和lower_bound与upper_bound的单独情况相对应
	pair<set<int>::iterator, set<int>::iterator> myp1 = mys1.equal_range(8);
	cout << "myp1.first = " << *(myp1.first) << endl;
	cout << "myp1.second = " << *(myp1.second) << endl;

	cout << "multiset: -----------------------------" << endl;

	multiset<int> mys2;

	mys2.insert(40);
	mys2.insert(10);
	mys2.insert(80);
	mys2.insert(80);
	mys2.insert(150);
	mys2.insert(110);

	cout << "mys2.count(80) = " << mys2.count(80) << endl;
	cout << "mys2.size = " << mys2.size() << endl;

	multiset<int>::iterator it4 = mys2.lower_bound(200);
	if (it4 == mys2.end())
	{
		// 如果不存在200，则返回end()
		cout << "查找失败" << endl;
	}
	else
	{
		cout << "查找成功，元素为：" << *it4 << endl;
	}

	multiset<int>::iterator it5 = mys2.upper_bound(100);
	if (it5 == mys2.end())
	{
		cout << "查找失败" << endl;
	}
	else
	{
		cout << "查找成功，元素为：" << *it5 << endl;
	}
	
	pair<multiset<int>::iterator, multiset<int>::iterator> myp2 = mys2.equal_range(80);
	cout << "lower_it = " << *(myp2.first) << endl;
	cout << "lower_it = " << *(myp2.second) << endl;
}

class Maker
{
public:
	Maker()
	{
		this->name = "";
		this->age = 0;
	}
	
	Maker(string name, int age)
	{
		this->name = name;
		this->age = age;
	}

	string getName()const
	{
		return this->name;
	}

	int getAge()const
	{
		return this->age;
	}

private:
	string name;
	int age;
};

struct MyCompareMaker
{
	bool operator()(const Maker& m1,const Maker& m2)const
	{
		return m1.getAge() < m2.getAge();
	}
};

// 6、元素为自定义类型
void test06()
{
	cout << "set: --------------------------" << endl;
	set<Maker, MyCompareMaker> mys1;

	mys1.insert(Maker("aaa", 18));
	mys1.insert(Maker("bbb", 19));
	mys1.insert(Maker("bbb", 19));
	mys1.insert(Maker("ddd", 21));
	mys1.insert(Maker("eee", 22));
	mys1.insert(Maker("fff", 23));

	for (auto begin = mys1.begin(); begin != mys1.end(); ++begin)
	{
		cout << "name: " << begin->getName() << " age: " << begin->getAge() << endl;
	}
	cout << "mys1.size = " << mys1.size() << endl;

	cout << "multiset: --------------------------" << endl;

	multiset<Maker, MyCompareMaker> mys2;

	mys2.insert(Maker("aaaaa", 28));
	mys2.insert(Maker("bbbbb", 29));
	mys2.insert(Maker("bbbbb", 29));
	mys2.insert(Maker("bbbbb", 29));
	mys2.insert(Maker("ccccc", 30));
	mys2.insert(Maker("ddddd", 31));

	for (auto begin = mys2.begin(); begin != mys2.end(); ++begin)
	{
		cout << "name: " << begin->getName() << " age: " << begin->getAge() << endl;
	}
	cout << "mys2.size = " << mys2.size() << endl;
}



int main(int argc, char* argv[])
{
	test06();

	return 0;
}
