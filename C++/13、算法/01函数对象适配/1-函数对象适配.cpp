#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <functional>
#include <numeric>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
using namespace std;

/*
	需要注意的是，我们使用的一些算法通常都会在algorithm这个头文件当中
	但也有少部分算法在functional和numeric头文件当中，所以在我们使用函数库
	的算法时，都把这三个头文件都包含上
*/

// 自定义谓词
struct MyFunc
{
	void operator()(int val)
	{
		cout << val << " ";
	}
};

void test01()
{
	vector<int> v1;
	constexpr const int n = 8;

	for (int i = 0; i < n; ++i)
	{
		v1.push_back(rand() % 30 + 1);
	}
	cout << "原数据：";
	for_each(v1.begin(), v1.end(), [](int val)->void {cout << val << " "; });
	cout << endl;

	// 升序排序
	sort(v1.begin(), v1.end(), less<int>());

	cout << "现数据：";
	for_each(v1.begin(), v1.end(), MyFunc());
	cout << endl;

}

// 需求：现在想给每个数据在打印时都多加100
/*
	我们有很多种处理方法，好比如：
	1、在输出的位置直接加上100，如：
		cout << val + 100 << " "; // 但是这种拓展性很差，只能固定是100，不能改变成其他值

	2、在函数签名位置添加一个参数
		// 这种方式虽然拓展性提高了，但是我们不能整天改变参数的个数，并且对于系统的一些库函数
		// 我们没办法对库函数的参数进行修改
		void operator()(int v1, int v2)
		{
			cout << v1 + v1 << " ";
		}

	3、使用适配器添加参数
		在自定义函数或函数对象中，虽然适配器的做法还是会多添加一个参数，但是对于系统的库函数
		我们就不需要改变库函数的参数，使用适配的方式进行参数个数的拓展，这样代码更具有推展性
		因此，下面我们就使用这种方式解决上面的需求

		两个常用适配器bind1st和bind2nd
		取反适配器not1和not2
*/

// 自定义函数对象，并对其进行适配
// (1)先继承binary_function模板
// 其中模板参数分别代表：第一个参数类型，第二个参数类型，函数返回值
struct MyFunc2 :public binary_function<int, int, void>
{
	// (2)需要将函数改成const类型(最好参数也改成const类型)
	void operator()(const int v1, const int v2)const
	{
		// 我们将两个参数进行处理即可(这里是+，但是并不是所有情况都是+)
		// 我们会在外面调用的地方进行适配这两个参数中的其中一个，这样就可以达到
		// 多传递一个参数的目的

		// 为了便于观察现象，这里分别输出v1和v2，看看我们哪个是绑定的，哪个没被绑定
		// 被绑定的那个在输出时是不会变化的
		cout << "v1 = " << v1 << endl;
		cout << "v2 = " << v2 << endl;

		cout << v1 + v2 << " ";
	}
};

void test02()
{
	vector<int> v2;

	constexpr const int n = 10;
	for (int i = 0; i < n; ++i)
	{
		v2.push_back(rand() % 50 + 1);
	}
	cout << "原数据：";
	for_each(v2.begin(), v2.end(), [](int val)->void {cout << val << " "; });
	cout << endl;

	cout << "bind2nd: ==============================" << endl;
	cout << "现数据：";

	// 注意：bind2nd是绑定operator()的第二个参数的意思，也就是v2固定是100
	// 还要注意的是，这里的位置不能改变，也就是函数对象在前面，需要适配的值在后面
	// 这里绑定的只是operator()里面的参数，并不是这里的参数
	for_each(v2.begin(), v2.end(), bind2nd(MyFunc2(), 100));

	cout << "bind1st: ==============================" << endl;
	for_each(v2.begin(), v2.end(), bind1st(MyFunc2(), 200));
}

// not1和not2是用来适配取反
// not1是用于一个参数的函数对象，not2是用于两个参数的函数对象

// 如果需要使用not1和not2，就需要继承unary_function<>模板
// 其中第一个参数是operator的参数，第二个参数是operator的返回值
struct MyFunc3 :public unary_function<int, bool>
{
	constexpr bool operator()(const int val)const noexcept
	{
		return val >= 10;
	}
};

void test03()
{
	/*
	这里解释一下取反
		有时候我们的判断式是v > 10，但是我们想改变判断条件，想用v <= 10进行判断
		此时，我们就需要给整个判断式进行取反，但这样就会有一个问题，如果是我们自定义
		的函数对象或者函数，直接在代码对应地方修改还是相对容易的，但是如果我们用到库函数
		中的判断式，那我们就没办法进行修改了，所以我们就需要使用not1或not2用适配的方式
		进行取反，从而达到我们改变判断式的目
	*/
	vector<int> v3;

	constexpr const int n = 6;
	for (int i = 0; i < n; ++i)
	{
		v3.push_back(rand() % 38);
	}
	cout << "原数据：";
	for_each(v3.begin(), v3.end(), [](int val)->void {cout << val << " "; });
	cout << endl;

	sort(v3.begin(), v3.end(), less<int>());

	cout << "现数据：";
	for_each(v3.begin(), v3.end(), [](int val)->void {cout << val << " "; });
	cout << endl;

	// find_if函数模板的作用就是，找到对应满足要求的元素，成功则返回对应的迭代器，失败返回end()
	// 其中“对应满足的条件”是第三个参数，所以我们应该传递一个谓词(下面这个是自定义函数对象)

	// 下面使用not1进行适配(在下面这个例子中，not1只能适配operator()的一个参数)
	vector<int>::iterator it = find_if(v3.begin(), v3.end(), not1(MyFunc3()));
	if (it == v3.end())
	{
		cout << "查找失败" << endl;
	}
	else
	{
		cout << "查找成功，元素为：" << *it << endl;
	}

}

void test04()
{
	vector<int> v4;

	constexpr const int n = 10;
	for (int i = 0; i < n; ++i)
	{
		v4.push_back(rand() % 50 + 1);
	}
	cout << "原数据：";
	for_each(v4.begin(), v4.end(), [](int val)->void {cout << val << " "; });
	cout << endl;

	// 在debug模式下，not2适配系统库的内建函数对象可能会报错，如果要使用的话，要在release模式下
	// 运行，内建函数对象如，less、greater...
	// 除了可以适配我们自定义的函数对象之外，还可以适配系统库中的函数对象
	sort(v4.begin(), v4.end(), not2(greater<int>()));
	// sort(v4.begin(), v4.end(), not2(less<int>()));

	cout << "现数据：";
	for_each(v4.begin(), v4.end(), [](int val)->void {cout << val << " "; });
	cout << endl;
}


// 如何给普通函数进行适配多个参数
// (1)首先要给自定义普通函数添加一个参数
void MyPrint(int v1, int v2)
{
	// (2)紧接着在函数内部完成你所需要的处理方式
	// 这里的处理方式是v1+v2
	cout << v1 + v2 << " ";
}

void test05()
{
	vector<int> v5;

	constexpr const int n = 10;
	for (int i = 0; i < n; ++i)
	{
		v5.push_back(rand() % 50 + 1);
	}
	cout << "原数据：";
	for_each(v5.begin(), v5.end(), [](int val)->void {cout << val << " "; });
	cout << endl;

	// 在debug模式下，not2适配系统库的内建函数对象可能会报错，如果要使用的话，要在release模式下
	// 运行，内建函数对象如，less、greater...
	sort(v5.begin(), v5.end(), not2(greater<int>()));

	cout << "现数据：";
	// 最后绑定函数对象，其中我们需要把普通函数转化成为函数对象，才能够进行绑定，否则会报错
	// ptr_fun()函数是将一个普通函数转化为一个函数对象

	// 在底层源码中，MyPrint被赋值到pointer_to_binary_function类的operator()中，准确来说
	// 是把MyPrint函数指针传递到operator()的参数当中，在operator()里面进行调用，这样就相当于
	// 把MyPrint转换成了函数对象了

	for_each(v5.begin(), v5.end(), bind2nd(ptr_fun(MyPrint), 100));

}

// 成员函数进行适配
class Maker
{
public:
	Maker() :name(""), age(0) {}
	Maker(string name, int age) :name(name), age(age) {}

	string getName()
	{
		return this->name;
	}

	int getAge()
	{
		return this->age;
	}

	void makerPrint()
	{
		cout << "name：" << this->name << "，age：" << this->age << endl;
	}

private:
	string name;
	int age;
};

// 当vector里面的元素是对象时，使用mem_fun_ref进行转换
void test06()
{
	vector<Maker> vm1;

	vm1.push_back(Maker("aaa", 18));
	vm1.push_back(Maker("bbb", 19));
	vm1.push_back(Maker("ccc", 20));
	vm1.push_back(Maker("ddd", 21));
	vm1.push_back(Maker("eee", 22));
	vm1.push_back(Maker("fff", 23));

	// 需要注意的是，获取成员函数的指针，需要在前面加上&符号，但是在通常情况下不加也是
	// 表示成员函数的指针，但是有些编译器无法检测出来，因此最好还是加上&符号

	// 使用mem_fun_ref函数，系统底层会自动调用mem_fun_ref_t类模板，把成员函数传递给类模板
	// 在系统的类模板中，会帮我们重写operator()函数，并传入一个参数，且参数类型是，Maker类型
	// 同样道理，在debug模式下程序会崩溃，所以需要换成release模式才能够使用
	for_each(vm1.begin(), vm1.end(), mem_fun_ref(&Maker::makerPrint));
}

// 当vector中的元素是指针类时，使用mem_fun进行转换
void test07()
{
	vector<Maker*> vmp1;
	
	// 开辟空间
	vmp1.push_back(new Maker("aaa", 18));
	vmp1.push_back(new Maker("bbb", 19));
	vmp1.push_back(new Maker("ccc", 20));
	vmp1.push_back(new Maker("ddd", 21));
	vmp1.push_back(new Maker("eee", 22));
	vmp1.push_back(new Maker("fff", 23));

	for_each(vmp1.begin(), vmp1.end(), mem_fun(&Maker::makerPrint));

	// 释放空间
	for (vector<Maker*>::iterator begin = vmp1.begin(); begin != vmp1.end(); ++begin)
	{
		Maker* mp = *begin;
		if (mp != nullptr)
		{
			delete mp;
			mp = nullptr;
		}
	}

	vector<Maker*>().swap(vmp1);
}

int main01(int argc, char* argv[])
{
	srand(unsigned int(time(nullptr)));
	test07();


	return 0;
}
