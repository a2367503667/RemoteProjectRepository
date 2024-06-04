#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip> // io + manipulator --> 输入/输出操控器


void test01()
{
	// 1、输出一个字符
	std::cout.put('c'); // c
	std::cout << std::endl;

	// 2、链式编程输出字符
	std::cout.put('h').put('e').put('l').put('l').put('o').put('\n'); // hello(换行)
}

void test02()
{
	char buf[] = "hello world";

	// 将buf数据写到屏幕文件中
	std::cout.write(buf, sizeof buf);
}

// 1、通过流的成员函数实现格式化输出
void test03()
{
	int num = 99;

	// 设置输出内容的宽度为20(也就是说一次输出不够20位，就补齐20位)
	std::cout.width(20);

	// 宽度补齐的填充内容为'*'(不足20位时，补齐的内容为'*')
	std::cout.fill('*');

	std::cout << num << std::endl; // 默认右对齐是：******************99

	// 设置对齐的位置为左对齐(注意是数据对齐是左对齐，也就是数据99会到坐左边，之前默认右对齐)
	std::cout.setf(std::ios::left); // 左对齐后是：99******************

	std::cout << num << std::endl;

	// 下面我们将数值切换为其他进制(但是在切换之前先卸载当前进制)
	// dec：十进制  hex：十六进制  oct：八进制
	std::cout.unsetf(std::ios::dec); //卸载十进制

	// 安装十六进制
	std::cout.setf(std::ios::hex);

	// 为了能够清除看出是什么进制，我们再设置一下基数(十六进制以0x开头，八进制以0开头)
	std::cout.setf(std::ios::showbase); // 也就是数字前面会显示基数

	std::cout << num << std::endl; // 99 --> 0x63

	// 卸载十六进制，换成八进制
	std::cout.unsetf(std::ios::hex);

	// 安装八进制
	std::cout.setf(std::ios::oct);

	std::cout << num << std::endl; // 99 --> 0143
}

// 2、通过控制符来实现格式化输出
void test04()
{
	// 以下操作方式和test03是对应的
	int num = 99;

	std::cout << std::setw(20); // 设置宽度为200
	std::cout << std::setfill('~'); // 填充'~'
	std::cout << num << std::endl; // ~~~~~~~~~~~~~~~~~~99

	std::cout << std::setiosflags(std::ios::left); // 设置数据左对齐
	std::cout << num << std::endl; // 99~~~~~~~~~~~~~~~~~~

	std::cout << std::setiosflags(std::ios::showbase); // 显示基数

	std::cout << std::hex; // 设置十六进制
	std::cout << num << std::endl; // 0x63

	std::cout << std::oct; // 设置八进制
	std::cout << num << std::endl; // 0143

	std::cout << std::dec; // 设置十进制
	std::cout << num << std::endl; // 99

}

// 3、浮点数相应的格式处理
void test05()
{
	double d = 20.314;
	std::cout << d << std::endl; // 20.314

	// 设置显示浮点数(表示所有的小数都以123.456这种方式显示，因为之前是以科学计数法形式
	// 输出的，如：1.23456e+03)
	std::cout << std::setiosflags(std::ios::fixed);

	// 设置小数点的位数
	std::cout << std::setprecision(10); // 表示显示小数点后10位
	std::cout << d << std::endl; // 20.3140000000

}



int main()
{
	// test01();
	// test02();
	// test03();
	// test04();
	test05();


	return 0;
}
