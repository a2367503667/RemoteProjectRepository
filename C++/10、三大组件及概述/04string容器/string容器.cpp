#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <xstring>
using namespace std;

/*
	string容器

	1、数据结构：连续的储存空间(类似于数组)
	2、迭代器：std::string::iterator  属于随机访问迭代器
	3、常用的API：
	assign() at() append() find() rfind() replace() insert() erase() compare() substr() c_str() size() length()
	4、常用的API中的注意事项：
		(1)在访问越界时，[]不会抛出异常，而at会抛出异常
		(2)对于at和[]来说，他们都是返回string的引用的，但是如果我们接收了原来的引用，而string又改变了内存地址，此时
		如果我们继续用原来的引用的话，就属于非法操作，就好比如：刚开始stirng s1 = "hello"; 我获取了对应的引用
		char &a = s1.at(0);  char &b = s1.at(1); 然后我们接着改变s1 = "ppppppppppppppppppppppppppppppppppp";
		此时，s1很长，可能空间不足就会重新分配空间，也就是说，s1.at(0)与s1.at(1)的引用被改变了，这时候我们再去
		使用原来的引用a和b就属于超控野引用，就是属于非法操作(下面给出例子证明)

*/

/*
string();//创建一个空的字符串 例如: string str;
string(const string& str);//使用一个string对象初始化另一个string对象
string(const char* s);//使用字符串s初始化
string(int n, char c);//使用n个字符c初始化
*/
// 1、构造函数
void test01()
{
	// 容器内部会做处理，所以不需要指定类型
	std::string s1; // 无参构造
	
	std::string s2(s1);  // 拷贝构造

	std::string s3("Hello"); // 有参构造

	std::string s4(10, 'c'); // s4="cccccccccc"; 其中c有10个
}
void test001()
{
	string sStr = "hello C++";
	const char* cStr = "learn more knowledge";

	string s1(sStr);
	cout << s1 << endl;

	string s2(cStr);
	cout << s2 << endl;

	string s3(8, 'C');
	cout << s3 << endl;

}


/*
string& operator=(const char* s);//char*类型字符串 赋值给当前的字符串
string& operator=(const string& s);//把字符串s赋给当前的字符串
string& operator=(char c);//字符赋值给当前的字符串
string& assign(const char* s);//把字符串s赋给当前的字符串
string& assign(const char* s, int n);//把字符串s的前n个字符赋给当前的字符串
string& assign(const string& s);//把字符串s赋给当前字符串
string& assign(int n, char c);//用n个字符c赋给当前字符串
string& assign(const string& s, int start, int n);//将s从start开始n个字符赋值给字符串,如s=hello,那么n=3,start=1，那么是hello中从e开始复制3个字符(包括e)
*/
// 2、基本赋值操作
void test02()
{
	std::string s1;

	s1 = "hello world"; // 重载=运算符 把char*赋值给当前字符串
	std::cout << "s1 = " << s1 << std::endl;

	std::string s2;
	s2.assign(s1); // 把字符串s1赋值给当前字符串s2
	std::cout << "s2 = " << s2 << std::endl;

	s2.assign("world"); // 把常量字符串"world"赋值给s2，需要注意的是，assign只会显示最新的数据，即只会显示world
	std::cout << "s2 = " << s2 << std::endl;	
}
void test002()
{
	string sStr = "hello C++";
	const char* cStr = "learn more knowledge";
	char ch = 'C';

	string s1;
	s1.assign(sStr);
	cout << s1 << endl;

	string s2;
	s2.assign(cStr);
	cout << s2 << endl;

	string s3;
	s3.assign(6, 'C');
	cout << s3 << endl;

	string s4;
	s4.assign(cStr, 10);
	cout << s4 << endl;

	string s5;
	s5.assign(sStr, 6, 3);
	cout << s5 << endl;

	cout << "-----------------------" << endl;

	string s6;
	s6 = ch;
	cout << s6 << endl;

	string s7;
	s7 = sStr;
	cout << s7 << endl;

	string s8;
	s8 = cStr;
	cout << s8 << endl;

}


/*
char&operator[](int n);//通过[]方式取字符
char& at(int n);//通过at方法获取字符
*/
// 3、访问和存取字符操作
void test03()
{
	std::string s1 = "hello world";
	int n = s1.size();

	// 一个个字符打印出来
	for (int i = 0; i < n; ++i)
	{
		std::cout << s1.at(i); // s1.at(i)就是取索引为i的元素
		// 也可以这样写 
		// std::cout << s1[i];  这里就重载了[]运算符
	}
	std::cout << std::endl;

	// 不过[] 和at()存在一定区别
	// []在访问越界时，不会抛出异常，但是at()访问越界时会抛出异常
	
	// 我们发现执行下面这个代码，程序会崩掉，那就意味着[]不会抛出异常
	/*
	try 
	{
		std::cout << "s1[100] = " << s1[100] << std::endl;
	}
	catch (std::out_of_range &e)
	{
		std::cout << "error:" << e.what() << std::endl;
	}
	*/

	// 我们发现下面代码输出结果为：error:invalid string position
	// 那就意味着at()会抛出异常
	/*
	try
	{
		std::cout << "s1.at(100) = " << s1.at(100) << std::endl;
	}
	catch (std::out_of_range &e)
	{
		std::cout << "error:" << e.what() << std::endl;
	}
	*/

	// 也可以通过迭代器遍历每个元素
	std::string::iterator begin = s1.begin();
	std::string::iterator end = s1.end();

	std::cout << "迭代器：s1 = ";
	while (begin != end)
	{
		std::cout << (*begin);
		++begin;
	}
	std::cout << std::endl;
}
void test003()
{
	string sStr = "learn C++";
	sStr.at(6) = 'c';
	cout << sStr << endl;

	sStr[6] = 'C';
	cout << sStr << endl;

	try
	{
		sStr.at(100) = 'Z';
	}
	catch (exception& ex)
	{
		cout << ex.what() << endl;
	}
}


/*
string& operator+=(const string& str); //重载+=操作符
string& operator+=(const char* str); //重载+=操作符
string& operator+=(const char c); //重载+=操作符
string& append(const char* s); //把字符串s连接到当前字符串结尾
string& append(const char* s, int n); //把字符串s的前n个字符连接到当前字符串结尾
string& append(const string& s); //同operator+=()
string& append(const string& s, int pos, int n); //把字符串s中从pos开始的n个字符连接到当前字符串结尾
string& append(int n, char c); //在当前字符串结尾添加n个字符c
*/
// 4、拼接操作
void test04()
{
	std::string s1 = "aaa";

	// 重载了+=运算符
	s1 += "bbb";
	s1 += 'c';
	std::cout << "s1 = " << s1 << std::endl;

	s1.append(" apple orange", 6); // 拼接字符串的前6个字符
	std::cout << "s1 = " << s1 << std::endl;
}
void test004()
{
	string sStr = "hello";
	string tStr = " Java";
	const char* cStr = " developer";
	const char ch = 'C';

	string s1 = sStr;
	s1 += " C++";
	cout << s1 << endl;

	string s2 = sStr;
	s2 += cStr;
	cout << s2 << endl;

	string s3 = sStr;
	s3 += ' ';
	s3 += ch;
	cout << s3 << endl;

	cout << "--------------------" << endl;

	string s4 = sStr;
	s4.append(cStr);
	cout << s4 << endl;

	string s5 = sStr;
	s5.append(tStr);
	cout << s5 << endl;

	string s6 = sStr;
	s6.append(5, ch);
	cout << s6 << endl;

	string s7 = sStr;
	s7.append(cStr, 4);
	cout << s7 << endl;

	string s8 = sStr;
	s8.append(tStr, 0, 5);
	cout << s8 << endl;
}


/*
int find(const string& str, int pos = 0) const; //查找str第一次出现位置,从pos开始查找
int find(const char* s, int pos = 0) const;  //查找s第一次出现位置,从pos开始查找
int find(const char* s, int pos, int n) const;  //从pos位置查找s的前n个字符第一次位置
int find(const char c, int pos = 0) const;  //查找字符c第一次出现位置
int rfind(const string& str, int pos = npos) const;//查找str最后一次位置,从pos开始查找
int rfind(const char* s, int pos = npos) const;//查找s最后一次出现位置,从pos开始查找
int rfind(const char* s, int pos, int n) const;//从pos查找s的前n个字符最后一次位置
int rfind(const char c, int pos = npos) const; //查找字符c最后一次出现位置
string& replace(int pos, int n, const string& str); //替换从pos开始n个字符为字符串str
string& replace(int pos, int n, const char* s); //替换从pos开始的n个字符为字符串s
*/
// 5、查找和替换
void test05()
{
	std::string s1 = "abcdefgd";
	std::cout << s1.find('d') << std::endl; // 查找的是从前往后找的d字符的索引，即3

	std::cout << s1.rfind('d') << std::endl; // 查找的是从后往前找到d字符的索引，即7

	std::cout << s1.find("abc") << std::endl; // 查找子串位置，找到则返回子串第一个字符的位置索引

	std::cout << s1.find("kkds") << std::endl; // 返回一个很大的值

	// 从索引2(包含)开始往后的4个元素替换成AAAA，假设替换的不是"AAAA"，而是"AAA"
	// 这时，索引2(包含)往后的4个元素就换成"AAA"
	s1.replace(2, 4, "AAAA"); 
	std::cout << "s1 = " << s1 << std::endl;
}
void test005()
{
	string sStr = "sdbvdf1ba1vanbf1v30384gv616v13d6b16EVB1b1s3fgn3ar16abs3fnrtjnutkm1u6i6smsvfae";
	int len = strlen(sStr.c_str()); // 77
	cout << "len = " << len << endl;

	int pos;

	const char* cs1 = "van";
	pos = sStr.find(cs1, 0);
	cout << pos << endl;

	string ss1 = "vdf1";
	pos = sStr.find(ss1, 2);
	cout << pos << endl;

	const char* cs2 = "bf1ajcka";
	pos = sStr.find(cs2, 0, 3);
	cout << pos << endl;

	const char ch1 = 'f';
	pos = sStr.find(ch1, 0);
	cout << pos << endl;

	const char* cs3 = "ms";
	pos = sStr.rfind(cs3, len - 1);
	cout << pos << endl;

	string ss3 = "6s";
	pos = sStr.rfind(ss3, len - 1);
	cout << pos << endl;

	const char* cs4 = "u6i6";
	pos = sStr.rfind(cs4, len - 1, 2);
	cout << pos << endl;

	const char ch2 = 'v';
	pos = sStr.rfind(ch2);
	cout << pos << endl;

	cout << "------------------------" << endl;

	string ss4 = "C++ developer";
	string newStr = sStr.replace(0, len, ss4);
	cout << sStr << endl;
	// cout << newStr << endl; // C++ developer

	const char* cs5 = "Java developer";
	string newStr2 = sStr.replace(0, len, cs5);
	cout << sStr << endl;
	// cout << newStr2 << endl; // Java developer

}


/*

compare函数在 > 时返回1，< 时返回-1，== 时返回0。
比较区分大小写，比较时参考字典顺序，排越前面的越小。
大写的A比小写的a小。

int compare(const string& s) const;//与字符串s比较
int compare(const char* s) const;//与字符串s比较
*/
// 6、比较操作
void test06()
{
	std::string s1 = "hello";
	std::string s2 = "hello";

	const char* str = "world";

	if (s1.compare(s2) == 0)
	{
		std::cout << "s1 == s2" << std::endl;
	}
	else
	{
		std::cout << "s1 != s2" << std::endl;
	}

	if (s1.compare(str) == 0)
	{
		std::cout << "s1 == str" << std::endl;
	}
	else
	{
		std::cout << "s1 != str" << std::endl;
	}
}
void test006()
{
	string sStr = "hello C++";
	int res;

	string s1 = "hello C++";
	res = sStr.compare(s1);
	if (res == 0)
	{
		cout << "sStr == s1" << endl;
	}
	else if (res > 0)
	{
		cout << "sStr > s1" << endl;
	}
	else
	{
		cout << "sStr < s1" << endl;
	}

	cout << "--------------------------" << endl;

	const char* cs1 = "hello C";
	res = sStr.compare(cs1);
	if (res == 0)
	{
		cout << "sStr == cs1" << endl;
	}
	else if (res > 0)
	{
		cout << "sStr > cs1" << endl;
	}
	else
	{
		cout << "sStr < cs1" << endl;
	}

}


/*
string substr(int pos = 0, int n = npos) const;//返回由pos开始的n个字符组成的字符串
*/
// 7、子串
void test07()
{
	std::string s1 = "liweiyuan10@gmail.com";

	// 现在有一个需求，就是找到用户名字liweiyuan，该如何操作？
	// 1、先找到索引为1的下标
	int pos = s1.find('1');
	std::string userName = s1.substr(0, pos); // 获取字符范围[0,pos)
	std::cout << "用户名：" << userName << std::endl; // 注意：返回的字符串不包括pos位置的字符，即不包括1

	// 要想获取用户名后缀又如何操作？
	int pos2 = s1.find('@');
	std::string sRear = s1.substr(pos2 + 1); // [pos2+1,...) 从pos2+1(包括)到末尾
	std::cout << "邮箱后缀：" << sRear << std::endl;

}
void test007()
{
	string sStr = "hello Java developer";
	int pos = sStr.find(' ', 0);

	string s1 = "C++ and ";
	string newStr = sStr.insert(pos + 1, s1);
	cout << sStr << endl;
	cout << newStr << endl;

	cout << "-------------------------" << endl;
	sStr = "hello Java developer";

	const char* cs1 = "C and ";
	string newStr2 = sStr.insert(pos + 1, cs1);
	cout << sStr << endl;
	cout << newStr2 << endl;

	cout << "-------------------------" << endl;
	sStr = "hello  developer";
	const char ch1 = 'C';
	string newStr3 = sStr.insert(pos + 1, 1, ch1);
	cout << sStr << endl;
	cout << newStr3 << endl;

	cout << "-------------------------" << endl;
	sStr = "hello Java developer";
	pos = sStr.find('J', 0);

	string newStr4 = sStr.erase(pos, 5);
	cout << sStr << endl;
	cout << newStr4 << endl;

}


/*
string& insert(int pos, const char* s); //在pos位置的前面插入字符串s
string& insert(int pos, const string& str); //在pos位置前面插入插入字符串str
string& insert(int pos, int n, char c);//在指定位置插入n个字符c
string& erase(int pos, int n = npos);//删除从Pos开始的n个字符
*/
// 8、插入和删除操作
void test08()
{
	std::string s1 = "AAA";

	s1.insert(1, "bbb"); // 在索引为1的后面插入"bbb" 
	std::cout << "s1 = " << s1 << std::endl;

	s1.insert(3, 5, 'C'); // 在索引为3的位置后面插入5个'C'
	std::cout << "s1 = " << s1 << std::endl;

	s1.erase(2, 4); // 从索引为2的位置(包含)开始删除4个字符
	std::cout << "s1 = " << s1 << std::endl;
}
void test008()
{
	string email = "liweiyuan@gmail.com";
	int pos;
	int len = strlen(email.c_str());

	pos = email.find('@', 0);

	// 不包括pos位置[0, pos)
	string name = email.substr(0, pos);
	cout << name << endl;

	// string domain = email.substr(pos+1, len);
	string domain = email.substr(pos + 1);
	cout << domain << endl;
}


/*
//string 转 char*
string str = "itcast";
const char* cstr = str.c_str();
//char* 转 string
char* s = "itcast";
string sstr(s);
*/
// 9、string与char*进行转换
void test09()
{
	const char* str = "hello world";
	std::string s1 = std::string(str); // char*转换为string
	// 或者这样写也行
	// std::string s1 = str;
	std::cout << "s1 = " << s1 << std::endl;

	const char* str1 = s1.c_str(); // string转换成char*
	std::cout << "str1 = " << str1 << std::endl;

}
void test009()
{
	string sStr = "good good study, day day up";
	cout << "string: " << sStr << endl;

	const char* cStr = sStr.c_str();
	cout << "const char*: " << cStr << endl;

}


// 10、string重新分配空间的一些注意问题
void test10()
{
	std::string s1 = "hello";

	char& a = s1.at(0);
	char& b = s1.at(1);

	a = '1';
	b = '2';

	std::cout << "空间重新分配前：" << std::endl;
	std::cout << "a = " << a << std::endl;
	std::cout << "&a = " << (void*)&a << std::endl;
	std::cout << "b = " << b << std::endl;
	std::cout << "&b = " << (void*)&b << std::endl;
	std::cout << "s1 = " << s1 << std::endl;

	s1 = "ppppppppppppppppppppppppppppppppppppppppppppppppp";

	std::cout << "空间重新分配后：" << std::endl;
	// 我们发现没有结果，其实此时已经属于非法操作了，因为空间已经被回收
	std::cout << "a = " << a << std::endl; // 此时输出的结果为a =
	std::cout << "&a = " << (void*)&s1.at(0) << std::endl;
	std::cout << "b = " << b << std::endl; // 此时输出的结果为b =
	std::cout << "&b = " << (void*)&s1.at(1) << std::endl;
	std::cout << "s1 = " << s1 << std::endl;

	// 通过对比可以发现，s1变化前后，地址发生了改变，也就是说，我们仍然去操作原来的引用a和b这时就是非法操作野引用
	// 此时我们在执行下面两行代码，会发现程序崩掉了
	// a = '3';
	// b = '4';

}
void test010()
{
	string email = "2367503667@qq.com";
	int pos;
	char& a = email[0];
	char& b = email[1];
	a = '3';
	b = '2';
	cout << email << endl;
	cout << "addr: " << (void*)&email[0] << endl; // 原来的地址

	pos = email.find('@', 0);
	string newEmail = email.replace(0, pos, "2049798862");
	cout << "addr: " << (void*)&email[0] << endl; // 地址改变了

	// 原来的空间被释放掉了，这时还访问原来的空间那就是非法访问，属于错误操作
	// a = '2'; // err
	// b = '3'; // err
	cout << email << endl;
	cout << "addr: " << (void*)&email[0] << endl;

}


// 11、用迭代器遍历string对象的元素
void test11()
{
	std::string s1 = "abcliweiyuan@icloud.com";

	// 第一种遍历方式
	std::cout << "s1 = ";
	/*
	for (auto i = s1.begin(); i != s1.end(); ++i)
	{
		std::cout << (*i);
	}
	std::cout << std::endl;
	*/

	// 第二种遍历方式
	/*
	std::string::iterator begin = s1.begin();
	std::string::iterator end = s1.end();

	while (begin != end)
	{
		std::cout << (*begin);
		++begin;
	}
	std::cout << std::endl;
	*/

	// 反向遍历

	// 反向输出结果 s1 = moc.duolci@nauyiewilcba
	std::string::reverse_iterator rBegin = s1.rbegin();
	std::string::reverse_iterator rEnd = s1.rend();

	while (rBegin != rEnd)
	{
		std::cout << (*rBegin);
		++rBegin;
	}
	std::cout << std::endl;



}
void test011()
{
	string email = "abcliweiyuan@icloud.com";

	string::iterator begin = email.begin();
	string::iterator end = email.end();

	while (begin != end)
	{
		cout << (*begin);
		++begin;
	}
	cout << endl;

	cout << "--------------------------" << endl;

	string::reverse_iterator rbegin = email.rbegin();
	string::reverse_iterator rend = email.rend();

	while (rbegin != rend)
	{
		cout << (*rbegin);
		++rbegin;
	}
	cout << endl;

}

// 12、使用swap函数降低容器的容量
void test12()
{
	string s1 = "learn C++";

	// 如果开发时提前知道需要开辟一个很大的数组时，就用reserve函数进行开辟
	// 否则如果你一次一次加进去的话，空间配置器会多次分配空间，对不足的空间进行调整
	s1.reserve(100000000);

	cout << "size = " << s1.size() << endl;
	cout << "capacity = " << s1.capacity() << endl;

	s1.resize(10);

	cout << "size = " << s1.size() << endl;
	cout << "capacity = " << s1.capacity() << endl;

	s1.resize(5);
	cout << "size = " << s1.size() << endl;
	cout << "capacity = " << s1.capacity() << endl;

	s1.clear(); // 这个只是清空size
	cout << "size = " << s1.size() << endl;
	cout << "capacity = " << s1.capacity() << endl;

	// 这行代码的意思是，先调用拷贝构造函数，将size变小的字符串s1拷贝到匿名对象当中
	// 然后接着与当前的s1对象进行交换(本质上就是容器中的const char*的指针交换)，交换完
	// 之后，s1整体容量就变小了，而且匿名对象过了当前行也就会被释放掉，因此这样的操作就
	// 能够把s1的容量降下来了
	string().swap(s1);

	cout << "size = " << s1.size() << endl; // 0
	cout << "capacity = " << s1.capacity() << endl; // 0
}

int main()
{
	// test01();
	// test02();
	// test03();
	// test04();
	// test05();
	// test06();
	// test07();
	// test08();
	// test09();
	// test10();
	// test11();
	test12();

	return 0;
}
