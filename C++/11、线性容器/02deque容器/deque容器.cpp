#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <deque>


/*
	deque容器
	注意：它只是一些定量连续的空间连起来的一个大的空间，也就是说本质上并不是连续的

	为什么这么说？
	因为它的一些定量的连续空间，是通过中控器进行管理的，其中，中控器存储着
	每个小的连续空间的首地址，对deque容器的空间进行维护和管理，也就是说，迭代器并不是我们所想象的
	和vector容器一样简单，相对于vector容器来说是比较复杂的

	deque和vector的区别：两者最大的区别是deque它没有像vector那样有严格的空间连续机制，也就是说对于deque来说
	空间可以不是连续的，只需要让中控器动态地接一段新的地址，就可以继续输入数据，因此不需要通过reverse来进行
	空间的开辟与管理，并且deque还能常量时间对"头端"元素插入和删除元素，vector因为是单向的，因此想在"头端"插入
	元素的话需要O(n)时间

	1、数据结构：逻辑上是连续的，实际上是由多个定量的小连续空间组成的(通过中控器管理)，严格来说是不连续的
	2、迭代器：随机访问迭代器
	3、常用的API：
	assign() at() size() resize() push_back() push_front() pop_back() pop_front() insert() erase() front() back()


*/

// 输出deque的元素
void printDequeData(const std::deque<int>& d)
{
	for (std::deque<int>::const_iterator i = d.begin(); i != d.end(); ++i)
	{
		std::cout << (*i) << " ";
	}
	std::cout << std::endl;
}

// 1、验证是什么迭代器(结果是：随机访问迭代器)
void test()
{
	std::deque<int>::iterator begin;
	/*
		通过以下操作可以知道，迭代器是属于随机访问迭代器
		++begin;
		begin--;
		begin += 2;
	*/
}


/*
deque<T> deqT;//默认构造形式
deque(beg, end);//构造函数将[beg, end)区间中的元素拷贝给本身。
deque(n, elem);//构造函数将n个elem拷贝给本身。
deque(const deque& deq);//拷贝构造函数。
*/
// 2、构造函数
void test01()
{
	int arr[] = { 2,8,3,-7,15,6 };
	std::deque<int> d1(arr, arr + (sizeof arr / sizeof arr[0])); // 其实和vector一样
	printDequeData(d1);

	std::deque<int> d2(10, 8); // 赋值10个8
	printDequeData(d2);
}


/*
assign(beg, end);//将[beg, end)区间中的数据拷贝赋值给本身。
assign(n, elem);//将n个elem拷贝赋值给本身。
deque& operator=(const deque& deq); //重载等号操作符
swap(deq);// 将deq与本身的元素互换
*/
// 3、赋值操作
void test02()
{
	int arr[] = { 2,8,3,-7,15,6 };
	std::deque<int> d1(arr, arr + (sizeof arr / sizeof arr[0]));

	std::deque<int> d2;

	// 把d1的所有元素都拷贝过来
	d2.assign(d1.begin(), d1.end());
	printDequeData(d2);

	// 在末尾插入100
	d2.push_back(100);
	printDequeData(d2);

	std::cout << "==============================" << std::endl;

	// d1与d2进行交换
	d1.swap(d2);
	std::cout << "d1：";
	printDequeData(d1);
	std::cout << "d2：";
	printDequeData(d2);

}


/*
deque.size();//返回容器中元素的个数
deque.empty();//判断容器是否为空
deque.resize(num);//重新指定容器的长度为num,若容器变长，则以默认值填充新位置。如果容器变短，则末尾超出容器长度的元素被删除。
deque.resize(num, elem); //重新指定容器的长度为num,若容器变长，则以elem值填充新位置,如果容器变短，则末尾超出容器长度的元素被删除
*/
// 4、大小容量操作
void test03()
{
	std::deque<int> d1;

	std::cout << "d1.size = " << d1.size() << std::endl;

	if (d1.empty()) // 判断是否为空
	{
		std::cout << "d1 is empty!" << std::endl;
	}
	d1.resize(10, 7); // 赋值重置为10个7
	printDequeData(d1);
}


/*
push_back(elem);//在容器尾部添加一个数据
push_front(elem);//在容器头部插入一个数据
pop_back();//删除容器最后一个数据
pop_front();//删除容器第一个数据
*/
// 5、双端删除(pop_front() pop_back())和插入操作
void test04()
{
	std::deque<int> d1;

	// 头插：100 90 80 70 60
	d1.push_front(60);
	d1.push_front(70);
	d1.push_front(80);
	d1.push_front(90);
	d1.push_front(100);

	// 尾插：10 20 30 40 50
	d1.push_back(10);
	d1.push_back(20);
	d1.push_back(30);
	d1.push_back(40);
	d1.push_back(50);
	printDequeData(d1); // 100 90 80 70 60 10 20 30 40 50

	// 前删
	d1.pop_front();

	// 后删
	d1.pop_back();
	printDequeData(d1); // 90 80 70 60 10 20 30 40

	std::cout << "d1.front = " << d1.front() << std::endl;
	d1.front() = 1000;
	std::cout << "d1.front = " << d1.front() << std::endl;

	std::cout << "d1.back() = " << d1.back() << std::endl;
	d1.back() = 500;
	std::cout << "d1.back() = " << d1.back() << std::endl;
	printDequeData(d1);
}


/*
insert(pos,elem);//在pos位置插入一个elem元素的拷贝，返回新数据的位置。
insert(pos,n,elem);//在pos位置插入n个elem数据，无返回值。
insert(pos,beg,end);//在pos位置插入[beg,end)区间的数据，无返回值。
*/
// 6、插入操作
void test05()
{
	std::deque<int> d1;

	d1.push_back(10);
	d1.push_back(20);
	d1.push_back(30);
	d1.push_back(40);
	d1.push_back(50);

	d1.insert(d1.begin() + 1, 100); // 在迭代器第二个位置前插入100
	d1.insert(d1.begin() + 2, 2, 0); // 在迭代器第三个位置前插入2个0
	printDequeData(d1); // 10 100 0 0 20 30 40 50

	std::cout << "==========================" << std::endl;

	std::deque<int> d2;
	d2.push_back(1000);
	d2.push_back(2000);
	d2.push_back(3000);

	// 把d1的[d1.begin(),d1.end())数据复制到d2迭代器第二个位置的前面
	d2.insert(d2.begin() + 1, d1.begin(), d1.end());
	printDequeData(d2); // 1000 10 100 0 0 20 30 40 50 2000 3000
}


/*
clear();//移除容器的所有数据
erase(beg,end);//删除[beg,end)区间的数据，返回下一个数据的位置。
erase(pos);//删除pos位置的数据，返回下一个数据的位置。
*/
// 7、删除操作(erase())
void test06()
{
	std::deque<int> d1;
	d1.push_back(10);
	d1.push_back(20);
	d1.push_back(30);
	d1.push_back(40);
	d1.push_back(50);

	// 下面那个返回的是一个迭代器(这个区间[d1.begin()+1,d1.end()-2)的下一个元素，即d1.end()-2)
	std::deque<int>::iterator i = d1.erase(d1.begin() + 1, d1.end() - 2);
	printDequeData(d1); // 10 40 50  删除了20 30
	std::cout << "*i = " << *i << std::endl; // 返回40
}

// 拓展：关于嵌套模板使用的注意事项
template<typename T>
void printDeque(const std::deque<T>& dq)
{
	// 这里前面之所以加typename是因为编译器不知道const_iterator是一个变量还是类型
	/*
		如：
		class deque
		{
			using const_iterator = int;
		}; // 这个是一个类型
		
		class deque
		{
			int const_iterator = 100;
		}; // 这个是一个类型

		这样就出现二义性了，编译器没办法识别，因此需要在类型前面加上typename表示这个是一个类型
	*/
	typename std::deque<T>::const_iterator begin = dq.cbegin();
	typename std::deque<T>::const_iterator end = dq.cend();

	while (begin != end)
	{
		std::cout << (*begin) << " ";
		++begin;
	}
	std::cout << std::endl;
}

/*
at(idx);//返回索引idx所指的数据，如果idx越界，抛出out_of_range。
operator[];//返回索引idx所指的数据，如果idx越界，不抛出异常，直接出错。
front();//返回第一个数据。
back();//返回最后一个数据
*/

int main()
{
	// test01();
	// test02();
	// test03();
	// test04();
	// test05();
	test06();



	return 0;
}
