#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>

/* 
		二进制文件读写就是将我们的数据以二进制的方式存到文件中，或者从文件以二进制的形式
	将数据取出到缓冲区中，最后输入到程序当中
*/

class Maker1
{
public:
	Maker1()
	{
		this->age = 0;
		for (int i = 0; i < 64; ++i)
		{
			this->myStr[i] = 0;
		}
	}
	Maker1(const char* str, int age)
	{
		this->age = age;
		strcpy(this->myStr, str);
	}

	Maker1(const Maker1& str)
	{
		this->age = str.age;
		strcpy(this->myStr, str.myStr);
	}

	void printMes()
	{
		std::cout << "姓名：" << this->myStr << std::endl;
		std::cout << "年龄：" << this->age << std::endl;
	}

private:
	char myStr[64];
	int age;
};


// 写文件
void test01()
{
	Maker1 m1("张三", 21);
	Maker1 m2("李四", 22);
	Maker1 m3("王五", 20);

	// 1、创建文件输出流对象
	std::ofstream ofs;

	// 2、打开文件
	ofs.open("test02.txt", std::ios::out | std::ios::trunc | std::ios::binary);

	// 3、判断文件是否打开
	if (!ofs.is_open())
	{
		perror("don't open:");
		return;
	}

	// 4、将内容写入文件
	ofs.write(reinterpret_cast<const char*>(&m1), sizeof m1);
	ofs.write(reinterpret_cast<const char*>(&m2), sizeof m2);
	ofs.write(reinterpret_cast<const char*>(&m3), sizeof m3);

	// 5、操作完成后关闭文件
	ofs.close();
}

// 读文件
void test02()
{
	Maker1 m1;
	Maker1 m2;
	Maker1 m3;

	// 1、创建文件输入流对象
	std::ifstream ifs;

	// 2、打开文件
	ifs.open("test02.txt", std::ios::in | std::ios::binary);

	// 3、判断文件是否打开
	if (!ifs.is_open())
	{
		perror("don't open:");
		return;
	}

	// 4、向文件读取数据
	ifs.read(reinterpret_cast<char*>(&m1), sizeof m1);
	ifs.read(reinterpret_cast<char*>(&m2), sizeof m2);
	ifs.read(reinterpret_cast<char*>(&m3), sizeof m3);

	m1.printMes();
	std::cout << "-----------------------------" << std::endl;
	m2.printMes();
	std::cout << "-----------------------------" << std::endl;
	m3.printMes();

	// 5、操作完成后关闭文件
	ifs.close();
}



int main()
{
	test01();
	test02();

	return 0;
}
