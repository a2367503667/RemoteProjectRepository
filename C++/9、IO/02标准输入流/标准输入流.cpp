#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

/*
	流的介绍：
	C++输入输出包含以下三个方面的内容：
	
	1、对系统指定的"标准设备"的输入和输出。即从键盘输入数据，输出到显示器屏幕。这种输入输出
	称为标准的输入输出，简称"标准I/O"。
	
	2、以"外存磁盘"文件为对象进行输入和输出，即从磁盘文件输入数据，数据输出到磁盘文件。以外存文
	件为对象的输入输出称为文件的输入输出，简称"文件I/O"。
	
	3、对"内存"中指定的空间进行输入和输出。通常指定一个字符数组作为存储空间(实际上可以利用该空
	间存储任何信息)。这种输入和输出称为字符串输入输出，简称"串I/O"。


	格式(类名：作用 || 在哪个头文件中声明)

	ios：抽象基类 || iostream
	=================================================================
	(1)标准I/O：

	istream：通用输入流和其他输入流的基类 || iostream

	ostream：通用输出流和其他输出流的基类 || iostream

	iostream：通用输入输出流和其他输入输出流的基类 || iostream

	=================================================================
	(2)文件I/O：

	ifstream：输入文件流类 || fstream

	ofstream：输出文件流类 || fstream
	
	fstream：输入输出文件流类 || fstream
	
	=================================================================
	(3)串I/O：

	istrstream：输入字符串流类 || strstream

	ostrstream：输出字符串流类 || strstream

	strstream：输入输出字符串流类 || strstream

*/

/*
	下面由标准I/O开始学习
	标准输入流对象cin：

	cin.get() //一次只能读取一个字符
	cin.get(一个参数) //读一个字符
	cin.get(两个参数) //可以读字符串
	cin.getline()
	cin.ignore()
	cin.peek()
	cin.putback()
*/

// 1、std::cin.get()
void test01()
{
	/*
		结果为：
		ab
		a
		b
		[
		]
	*/
	// std::cin.get()无参数
	char c = std::cin.get(); // 输入ab(别忘了还有'\n') 第一次获取一个a
	std::cout << c << std::endl;

	c = std::cin.get(); // 第二次获取b(证明没有清空缓冲区)
	std::cout << c << std::endl;

	c = std::cin.get(); //读取掉'\n'
	std::cout << "[" << c << "]" << std::endl; // 为了看出'\n'加上[]
}

// 接着test01函数测试
void test01_01()
{
	/*
		结果为：
		x
		[x]
		abcd
		[abcd]
	*/
	// 1、std::cin.get()一个参数(char)
	char c = '0';
	std::cin.get(c); // 输入x
	std::cout << "[" << c << "]" << std::endl;
	std::cin.get(); // 读取缓冲区中的'\n'
	
	// 2、std::cin.get()可链式编程
	char ch1, ch2, ch3, ch4;
	std::cin.get(ch1).get(ch2).get(ch3).get(ch4); // abcd
	std::cout << "[" << ch1 << ch2 << ch3 << ch4 << "]" << std::endl; // abcd
	std::cin.get(); // 读取缓冲区中的'\n'
}

// 接着test01函数测试
void test01_02()
{
	/*
		结果为：

		hello world
		[hello world]
		[
		]
	*/

	// 1、std::cin.get()两个参数(字符数组(起始指针)，字符个数)
	char buf[1024]{ 0 };
	// 输入"hello world"，读取"hello world"但是没有读取缓冲区中的'\n'
	std::cin.get(buf, sizeof(buf));

	char ch = std::cin.get(); // 看一下上面是否存留'\n'
	std::cout << "[" << buf << "]" << std::endl; // [hello world]
	std::cout << "[" << ch << "]" << std::endl; // 录入buf后，仍然存在'\n'

}
// =======================================


// 2、std::cin.getline()
void test02()
{
	/*
		结果为：
		hello world
		1(我们发现有"阻塞"显现，此时输入1)
		[hello world]
		[1]
	
	*/
	// 1、std::cin.getline()两个参数(字符数组(起始指针)，字符个数)
	char buf[1024]{ 0 };
	std::cin.getline(buf, sizeof(buf)); // 输入"hello world"
	char ch = std::cin.get(); // 判断是否留有'\n，我们发现清空了，此时输入1

	std::cout << "[" << buf << "]" << std::endl; // 输出[hello world]，没有读入'\n'
	std::cout << "[" << ch << "]" << std::endl; // [1]

	// std::cin.getline()这个函数读取一行数据，可以清空缓冲区中的'\n'
	// =======================================
}
// =======================================


// 3、std::cin.ignore()
void test03()
{
	/*
		结果为：
		ab
		[b]
	*/
	// 1、std::cin.ignore()无参数：默认忽略第一个字符
	std::cin.ignore(); // 输入ab
	char ch = std::cin.get(); // 只读取了b，将第一个字符忽略了
	std::cout << "[" << ch << "]" << std::endl; // [b]
}

// 接着test03测试
void test03_01()
{
	/*
		结果为：
		abcd
		[d]
	*/
	// 2、std::cin.ignore()有参数：忽略前n个字符
	std::cin.ignore(3); // 输入abcde
	char ch = std::cin.get(); // 读取了d，忽略了前三个字符abc
	std::cout << "[" << ch << "]" << std::endl; // [d]
}
// =======================================


// 4、std::cin.peek()
void test04()
{
	/*
		结果为：
		x
		[x]
		[x]
	*/
	// std::cin.peek()无参数，默认偷窥第一个字符
	char ch = std::cin.peek(); // 只看一下，但是不拿走(输入字符x)
	std::cout << "[" << ch << "]" << std::endl; // 输出[x]

	char c = std::cin.get(); // 看一下缓冲区还有没有字符(还有刚刚的字符x)
	std::cout << "[" << c << "]" << std::endl; // 输出[x]

}
// =======================================


// 5、std::cin.putback()
void test05()
{
	/*
		结果为：
		z
		[z]
		[z]
	*/
	// std::cin.putback()无参数，把刚刚上面拿走的字符返回去
	char ch = std::cin.get(); // 输入字符y(读走了字符y)
	std::cout << "[" << ch << "]" << std::endl; // 读取字符z，输出[z]
	std::cin.putback(ch); // 将字符z放回缓冲区
	ch = std::cin.get(); // 再次读取缓冲区
	std::cout << "[" << ch << "]" << std::endl; // 输出[z]
}

void test05_01()
{
	/*
		结果为：
		[0]
	*/

	// 这里印证了，std::cin.putback()函数可以将随意一个字符放入缓冲区当中
	// 即使这个字符不是在缓冲区取出来的也可以
	char ch = '0';
	std::cin.putback(ch);
	ch = std::cin.get();
	std::cout << "[" << ch << "]" << std::endl;
}
// =======================================


// 案例1：判断用户输入的是字符串还是数字(判断第一位即可)
void test06()
{
	/*
		结果1(输入数字)：
		123
		这是数字：123
	
		结果2(输入字符串)：
		hello world
		这是字符串：hello world

	*/
	char ch = std::cin.peek();
	if (ch <= '9' && ch >= '0')
	{
		int num;
		std::cin >> num; // 123
		std::cout << "这是数字：" << num << std::endl;
	}
	else
	{
		char buf[1024]{ 0 };
		std::cin.getline(buf, sizeof buf); // hello world
		std::cout << "这是字符串：" << buf << std::endl;
	}
}

// 案例2：输入一个1到10的数字，知道输入正确为止跳出循环
void test07()
{
	int num;
	while (true)
	{
		std::cout << "请输入1-10数字：";
		// 这里需要注意的是，当我们随便乱输入字符没有输入数字的时候，会导致缓冲区异常
		// 所以我们需要"重置标志位"并且"清空缓冲区"
		std::cin >> num;
		if (num <= 10 && num >= 1)
		{
			std::cout << "输入正确" << std::endl;
			break;
		}
		std::cout << "输入错误，请重新输入！" << std::endl;

		// 1、重置标志位
		std::cin.clear();

		// 2、清空缓冲区
		// std::cin.sync(); // 这个清除缓冲区方式在VS失效
		// 只需要写这个循环即可清空缓冲区里面的内容
		// 这个循环的含义就是，读取缓冲区一个数据，判断是不是'\n'，如果是的话就直接退出循环
		// 因为我们输入元素后最后都会按Enter(即会留下'\n')，所以说当我们将'\n'都读走之后，缓冲区
		// 就没有其他元素了，即缓冲区被清空
		while (std::cin.get() != '\n');
	}

	/*
		记住两个步骤(非常重要)：
		1、重置标志位：std::cin.clear();

		2、用循环清空缓冲区数据：while(std::cin.get()!='\n');
		
	*/

}



int main()
{
	// test01();
	// test01_01();
	// test01_02();
	// test02();
	// test03();
	// test03_01();
	// test04();
	// test05();
	// test05_01();
	// test06();
	test07();

	return 0;
}
