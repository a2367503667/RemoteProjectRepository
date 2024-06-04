#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>

/*
	vector容器
	向量是一个单口容器，也就是说，如果只使用push_back() 或pop_back()函数的话，就只会单方向操作(插入或删除)
	但是它的限制会比较少，还是可以进行中间插入或删除的操作(后面的stack限制会比较多)

	1、数据结构：线性连续的储存空间
	2、迭代器：随机访问迭代器(它会指向已分配的空间中目前已使用的范围)
	3、vector容器动态增长原理：
		(1)当储存空间不够时，会开辟另一个大的空间，然后把数据拷贝过去，最后再销毁原来的空间；
		(2)申请的空间会比用户需求申请的空间大一点，例如：用户申请了100容量，它就开辟一个105的容量，比原来的大一点；
		(3)因为重新分配空间，原来的空间会被释放掉，这时原来的迭代器就会失效，其实道理也是和string中使用at()的注意
		事项一样，需要程序员自己确保不对野指针或野引用进行操作
	4、常用的API：
	assign() at() push_back() resize() reverse() swap() insert() pop_back() clear() size() length() 
	front() back() erase()
	5、常用API的注意事项：
		(1)resize函数开辟空间并初始化，而reverse函数开辟空间不初始化，并且没有初始化的空间不可以访问
		(2)reverse的作用：如果容器需要储存大量空间，这时需要先用reverse开辟空间，再去使用，否则容器会按照
		空间的开辟规则重新划分空间，多次申请空间，这样就会很消耗性能和消耗时间
		(3)swap函数可以缩小容器的空间，但是需要配合匿名对象的使用
*/

// 打印容器的第三种方法
void printVectorData(const std::vector<int>& v)
{
	// 需要注意的是，如果容器被定义为常容器，那就需要使用常迭代器访问元素
	// 也就是说需要换成 std::vector<int>::const_iterator
	for (std::vector<int>::const_iterator i = v.begin(); i != v.end(); ++i)
	{
		std::cout << (*i) << " ";
	}
	std::cout << std::endl;
}


// 逆序打印容器
void printReverseVectorData(const std::vector<int>& v)
{
	for (std::vector<int>::const_reverse_iterator i = v.rbegin(); i != v.rend(); ++i)
	{
		std::cout << (*i) << " ";
	}
	std::cout << std::endl;
}


/*
vector<T> v; //采用模板实现类实现，默认构造函数
vector(v.begin(), v.end());//将v[begin(), end())区间中的元素拷贝给本身。
vector(n, elem);//构造函数将n个elem拷贝给本身。
vector(const vector& vec);//拷贝构造函数。

//例子 使用第二个构造函数 我们可以...
int arr[] = {2,3,4,1,9};
vector<int> v1(arr, arr + sizeof(arr) / sizeof(int));

*/
// 1、构造函数
void test01()
{
	int arr1[] = { 1,2,3,4,5,6 };
	// 将[arr1,arr1+6)的元素拷贝到v对象当中，需要注意，不包括arr1+6这个位置
	// 其实这个常用于其他容器的迭代器，也可以用于数组的指针(因为原生指针也是属于迭代器的一种)
	std::vector<int> v(arr1, arr1 + sizeof(arr1) / sizeof(arr1[0])); 

	// 第一种打印方式
	/*
	for (auto i = v.begin(); i != v.end(); ++i)
	{
		std::cout << (*i) << " ";
	}
	std::cout << std::endl;
	*/

	// 第二种打印方式
	/*
	for (int val : v)
	{
		std::cout << val << " ";
	}
	std::cout << std::endl;
	*/

	// 第三种打印方式
	printVectorData(v);

	// 逆序打印向量容器元素
	printReverseVectorData(v);

	std::vector<int> v2(10, 6); // 把10个6赋值到v2对象中
	printVectorData(v2);



}


/*
assign(beg, end);//将[beg, end)区间中的数据拷贝赋值给本身。
assign(n, elem);//将n个elem拷贝赋值给本身。
vector& operator=(const vector &vec);//重载等号操作符
*/
// 2、常用赋值操作
void test02()
{
	std::vector<int> v1;

	v1.assign(10, 8); // 赋值10个8
	std::vector<int> v2;

	v2.push_back(1);
	v2.push_back(2);
	v2.push_back(3);
	v2.push_back(4);
	v2.push_back(5);
	std::cout << "v1 = ";
	printVectorData(v1);
	std::cout << "v2 = ";
	printVectorData(v2);

	std::cout << "=============================" << std::endl;

	v1.swap(v2); // v1与v2进行交换(本质上是把两个内存空间的指针交换了)
	std::cout << "v1 = ";
	printVectorData(v1);
	std::cout << "v2 = ";
	printVectorData(v2);
}


/*
size();//返回容器中元素的个数
empty();//判断容器是否为空
resize(int num);//重新指定容器的长度为num，若容器变长，则以默认值填充新位置。如果容器变短，则末尾超出容器长度的元素被删除。
resize(int num, elem);//重新指定容器的长度为num，若容器变长，则以elem值填充新位置。如果容器变短，则末尾超出容器长>度的元素被删除。
capacity();//容器的真实容量
*/
// 3、大小与开辟空间操作
void test03()
{
	std::vector<int> v1;
	v1.push_back(1);
	v1.push_back(2);
	v1.push_back(3);
	v1.push_back(4);
	v1.push_back(5);

	std::cout << "v1.size() = " << v1.size() << std::endl;

	// 1、resize函数，开辟空间并且初始化
	v1.resize(10);
	std::cout << "v1.size() = " << v1.size() << std::endl; // 10
	// 输出元素查看一下值是多少？
	printVectorData(v1); // 1 2 3 4 5 0 0 0 0 0 我们发现，最后的五个元素是0，也就是说resize会帮我们对新开辟的空间进行初始化
	
	v1.resize(3);
	printVectorData(v1); // 1 2 3 结果是删除了多余出来的元素

	// 但是需要注意的是，resize虽然缩小范围了，但是本质上容器的容量是没有变的
	// 也就是说删减的只是我们可以操作的空间，真正开辟的空间还是10，以最大开辟出来的容量作为标准
	// std::cout << "v1.capacity = " << v1.capacity() << std::endl;

	// 2、reserve函数，开辟空间但不初始化
	v1.reserve(20); // 虽然申请了20个空间大小，但是并没有给我们新开辟的空间进行初始化，也就是说我们没办法访问未初始化的数据
	v1.push_back(88);
	printVectorData(v1); // 1 2 3 88 不能访问88之后那些未初始化的数据

	// 虽然说开辟了20个空间，这些空间都可以使用，但是没办法访问，因为还没初始化
	// 因此，size的值为4，而不是20
	std::cout << "v1.size() = " << v1.size() << std::endl; // 4
	std::cout << "v1.capacity() = " << v1.capacity() << std::endl;

	// 也就是说下面这行代码会报错，因为使用了未初始化的数据
	// std::cout << "v1[10] = " << v1[10] << std::endl; 

}


/*
reserve(int len);//容器预留len个元素长度，预留位置不初始化，元素不可访问。
*/
// 4、reverse的作用：用来预留开辟空间
void test04()
{
	std::vector<int> v;
	// 现在我们有一个需求，就是求我们输入数据后，vector重新分配空间的次数
	// 也就是说，如果我们输入数据的空间不足时，vector的空间配置器会给我们重新分配空间，我们就是需要求重新分配空间的次数

	// 我们记录一下当前空间的第一个元素的地址，然后再与新的空间的第一个元素地址比较
	// 如果地址相同则没有分配空间，如果不相同则分配了空间
	int* p = nullptr;
	int num = 0; // 这个是记录分配空间的次数

	/*
	for (int i = 0; i < 10000000; ++i)
	{
		v.push_back(i + 1);
		if (p != &v[0])
		{
			p = &v[0];
			++num;
		}
	}
	*/
	// 此时我们发现，我们开辟了41次空间，这就有时间消耗了
	// std::cout << "num = " << num << std::endl;

	// 我们换一种方式，就是先给他预留空间，减低开辟空间的次数呢？
	// 此时我们就需要使用到reverse函数，预先分配空间给容器，这样就不会重新开辟空间了，就会节省分配空间的时间
	v.reserve(10000000);

	for (int i = 0; i < 10000000; ++i)
	{
		v.push_back(i + 1);
		if (p != &v[0])
		{
			p = &v[0];
			++num;
		}
	}

	// 如果我们用了reverse后，发现我们只需要分配1次空间，这样就能够节省运行时间
	// 也就是说，当我们需要分配很大很大的空间时，我们就需要先想到用reverse函数先分配空间
	// 这样就不用在输入数据时，让空间配置器给我们重新划分空间，这样就会非常耗时间和耗性能
	std::cout << "num = " << num << std::endl;

}


/*
swap(vec);// 将vec与本身的元素互换。
*/
// 5、swap的使用：可以用来缩小真实容量
void test05()
{
	std::vector<int> v;

	for (int i = 0; i < 10000000; ++i)
	{
		v.push_back(i);
	}

	// 我们发现，真实容量和size是不一样的，容器会另外开辟多点空间给我们使用
	std::cout << "v.capacity = " << v.capacity() << std::endl; // v.capacity = 11958657
	std::cout << "v.size = " << v.size() << std::endl; // v.size = 10000000

	std::cout << "===========================" << std::endl;

	std::cout << "缩小空间：" << std::endl;
	v.resize(10); // 我们把空间缩小为10
	// v.reserve(5); // 注意，使用reverse函数不会改变size的大小，只有resize才会改变size的大小

	// 再查看一下是不是真的缩小空间了
	// 最后我们发现，真实容量并没有缩小，只是size改变了
	std::cout << "v.capacity = " << v.capacity() << std::endl; //v.capacity = 11958657
	std::cout << "v.size = " << v.size() << std::endl; // v.size = 10

	// 这样就出现问题了，那我们申请了一个那么大的空间，但是我们又不用，这样就会导致别人也没办法使用
	// 就会导致大量空间的浪费，这时我们怎么解决这个问题？
	
	// 那我们思考一个问题：就是我们可不可以把现在缩小的空间的元素，复制到新的容器里面，这样新的容器的
	// 大小就是我们所需要的大小了
	
	// 我们发现结果确实如此
	std::vector<int> v2(v);
	std::cout << "v2.capacity = " << v2.capacity() << std::endl; // v2.capacity = 10
	std::cout << "v2.size = " << v2.size() << std::endl; // v2.size = 10

	// 但是也有一个问题，那就是我们没办法把原来那个很大空间的容器对象给释放掉，这样它还是占那一片很大的空间
	// 这时又该怎么办？
	// 我们可以使用匿名对象，先调用拷贝构造函数，给匿名对象赋值，此时的效果和上面的v2(v)一样
	// 此时匿名对象的容量就降下来了，这时，我们再让匿名对象与当前的容器对象v进行交换，此时v的真实
	// 容量大小就等于了匿名对象的真实容量大小，而匿名对象的容量大小就是v对象那个很大的容量
	// 又因为匿名对象的生命周期只在当前行，所以当前行结束后，匿名就会调用析构函数把那个很大的空间给释放掉
	// 这样就不会占用很大的空间，浪费空间了
	std::vector<int>(v).swap(v);

	std::cout << "v.capacity = " << v.capacity() << std::endl;
	std::cout << "v.size = " << v.size() << std::endl;

}


/*
at(int idx); //返回索引idx所指的数据，如果idx越界，抛出out_of_range异常。
operator[];//返回索引idx所指的数据，越界时，运行直接报错
front();//返回容器中第一个数据元素
back();//返回容器中最后一个数据元素
*/
// 6、数据存取操作
void test06()
{
	std::vector<int> v;
	
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);

	std::cout << "获取第一个元素：" << v.front() << std::endl; // 获取第一个元素：1
	std::cout << "获取最后一个元素：" << v.back() << std::endl; // 获取最后一个元素：5

	// 同时，front和back的值也可以改变，也就是说返回的是引用
	v.front() = 100;
	v.back() = 500;

	std::cout << "获取第一个元素：" << v.front() << std::endl; 
	std::cout << "获取最后一个元素：" << v.back() << std::endl;
	// 打印输出元素
	printVectorData(v);
}


/*
insert(const_iterator pos, int count, <T> ele);// 迭代器指向位置pos前面插入count个ele元素
insert(const_iterator pos, <T> elem); // 在pos位置前面插入elem元素
push_back(ele); //尾部插入元素ele
pop_back();//删除最后一个元素
erase(const_iterator start, const_iterator end);//删除迭代器从start到end之间的元素，其中不包括end，即[start, end)
erase(const_iterator pos);//删除迭代器指向的元素
clear();//删除容器中所有元素
*/
// 7、插入和删除(同样道理的，删除元素或者清空元素时，容器真实容量大小是没有变化的)
void test07()
{
	std::vector<int> v;

	for (int i = 0; i < 5; ++i)
	{
		v.push_back(i+1);
	}
	printVectorData(v); // 1 2 3 4 5

	// 在第三个元素前的位置插入元素100(使用迭代器，需要注意的是，迭代器是从0位置数起的，也就是说当前位置为1，+2后为3)
	v.insert(v.begin() + 2, 100);
	printVectorData(v); // 1 2 100 3 4 5

	// 在第三个元素前的位置插入两个元素100
	v.insert(v.begin() + 2, 2, 100);
	printVectorData(v); // 1 2 100 100 100 3 4 5

	// 删除最后一个元素
	v.pop_back();
	std::cout << "v.capacity = " << v.capacity() << std::endl;
	printVectorData(v); // 1 2 100 100 100 3 4

	// 删除迭代器位置的元素
	v.erase(v.begin() + 2);
	std::cout << "v.capacity = " << v.capacity() << std::endl;
	printVectorData(v); // 1 2 100 100 3 4

	// 删除迭代器区间内的元素(需要注意区间，是[v.begin()+2,v.begin()+4)并不包括v.begin()+4)
	v.erase(v.begin() + 2, v.end() - 2);
	std::cout << "v.capacity = " << v.capacity() << std::endl;
	printVectorData(v); // 1 2 3 4

	// 清空容器中的元素
	v.clear();
	std::cout << "v.capacity = " << v.capacity() << std::endl;
	printVectorData(v);
}


int main()
{
	// test01();
	// test02();
	// test03();
	// test04();
	// test05();
	// test06();
	test07();

	return 0;
}
