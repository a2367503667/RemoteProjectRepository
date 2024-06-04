#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream> // 引入文件操作类库

/*

	格式：("方式"：作用)
	(1)"ios::in"：以输入方式打开文件

	(2)"ios::out"：以输出方式打开文件(这是默认方式)，如果已有此名字的文件，则将其原有内容全部清除

	(3)"ios::app"：以输出方式打开文件，写入的数据添加在文件末尾
	
	(4)"ios::ate"：打开一个已有的文件，文件指针指向文件末尾
	
	(5)"ios::trunc"：打开一个文件，如果文件已存在，则删除其中全部数据，如文件不存在，则建立新文件。
					 如已指定了ios::out方式，而未指定ios::app/ios::ate/ios::in，则同时默认此方式
	
	(6)"ios::binary"：以二进制方式打开一个文件，如不指定此方式则默认为ASCII方式
	
	(7)"ios::nocreate"：打开一个已有的文件，如文件不存在，则打开失败。nocrcate的意思是不建立新文件
	
	(8)"ios::noreplace"：如果文件不存在则建立新文件，如果文件已存在则操作失败，noreplace的意思是不更
						 新原有文件
	
	(9)"ios::in | ios::out"：以输入和输出方式打开文件，文件可读可写
	
	(10)"ios::out | ios::binary"：以二进制方式打开一个输出文件
	
	(11)"ios::in | ios::binary"：以二进制方式打开一个输入文件

	几点说明：
	1、 新版本的I/O类库中不提供ios::nocreate和ios::noreplace。

	2、每一个打开的文件都有一个文件指针，该指针的初始位置由I/O方式指定，每次读写都从文件指
	针的当前位置开始。每读入一个字节，指针就后移一个字节。当文件指针移到最后，就会遇到文件
	结束EOF（文件结束符也占一个字节，其值为-1)，此时流对象的成员函数eof的值为非0值(一般设
	为1)，表示文件结束了。

	3、可以用“位或”运算符“|”对输入输出方式进行组合，如上面的最后3行所示那样。还可以
	举出下面一些例子：
	
	(1)ios::in | ios::noreplace  // 打开一个输入文件，若文件不存在则返回打开失败的信息

	(2)ios::app | ios::nocreate  // 打开一个输出文件，在文件尾接着写数据，若文件不存在，则返回
									打开失败的信息
	
	(3)ios::out | ios::noreplace  //打开一个新文件作为输出文件，如果文件已存在则返回打开失败的信息
	
	(4)ios::in | ios::out | ios::binary  //打开一个二进制文件，可读可写，但不能组合互相排斥的
	方式，如 ios::nocreate | ios::noreplace。


	4、如果打开操作失败，open函数的返回值为0(假)，如果是用调用构造函数的方式打开文件的，则流对
	象的值为0。可以据此测试打开是否成功。
	如下：

	if(outfile.open("f1.bat", ios::app) ==0)
	{
		cout <<"open error";
	}
	或

	if( !outfile.open("f1.bat", ios::app) )
	{
		cout <<"open error";
	}

*/

// 写文件：把程序中的信息输出到缓冲区，然后写到文件中(ofstream)
void test01()
{
	// 1、定义文件输出流对象
	std::ofstream ofs;

	// 2、打开文件(指定打开文件方式)
	// 对照上面给出的表格
	ofs.open("test01.txt", std::ios::out | std::ios::trunc);

	// 3、判断文件是否打开
	if (!ofs.is_open())
	{
		perror("don't open:");
		return;
	}

	// 4、写入信息
	// 注意：std::endl会把换行输出到文件当中
	ofs << "姓名：张三" << std::endl;
	ofs << "年龄：21" << std::endl;
	ofs << "身高：172"; // 这里可以不加换行符，这样最后一行就不会换行

	// 5、完成操作后关闭文件
	ofs.close();
}

// 读文件：把磁盘信息输入到缓冲区，然后读到程序中去(ifstream)
void test02()
{
	// 1、创建文件输入对象
	std::ifstream ifs;

	// 2、打开文件
	ifs.open("test01.txt", std::ios::in);

	// 3、判断文件是否打开
	if (!ifs.is_open())
	{
		perror("don't open:");
		return;
	}

	// 4、读取文件内容
	// (1)第一种方式：使用右移运算符从文件中获取数据，赋值给buf
	
	char buf[1024]{ 0 };

	// 需要注意的是，这个不会读取'\n'
	while (ifs >> buf)
	{
		std::cout << buf << std::endl;
	}

	// (2)第二种方式：判断是否读到文件末尾
	/*
		char buf[1024]{0};

		while (!ifs.eof()) // 判断是否读到文件尾部
		{
			// 这里同样不会读取'\n'
			ifs.getline(buf, sizeof buf);
			std::cout << buf << std::endl;
		}
	*/

	// (3)第三种方式：使用一个一个字符的方式读取
	/*
		char ch;

		// 因为是一个一个字符读取，所以内容就取决于每次取出的字符
		// 所以会把文件中的'\n'读取出来
		while ((ch = ifs.get()) != EOF)
		{
			std::cout << ch;
		}
		std::cout << std::endl;
	*/

	// 5、完成操作后关闭文件
	ifs.close();
}




int main()
{
	test01();
	test02();

	return 0;
}
