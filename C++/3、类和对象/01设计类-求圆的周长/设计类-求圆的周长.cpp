#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string> // 这个就是C++的字符串类型头文件，C语言中是没有的
using namespace std;

// 设计圆的类
// 这个是一个自定义类型，是没有空间的，只有实例化对象后才会有内存
struct Circle
{
public:
	// 计算圆的周长
	// 传一个参数进去，给mR成员变量初始化
	// 而得到初始化后，mR的值就确定了，其他成员方法都可以使用
	void setR(double r)
	{
		mR = r;
	}
	// 计算圆的周长
	double getL()
	{
		return 2 * 3.14 * mR;
	}

public: // 共有权限
	double mR; // 成员变量，成员属性
};

void test01()
{
	// 数据类型定义变量
	// 类实例化对象
	Circle c;
	c.setR(100);
	cout << "C = " << c.getL() << endl;

}

void test02()
{
	char* p = (char*)"hello world";
	char buf[] = "你好 世界！";
	cout << "p = " << p << endl;
	cout << "buf[] = " << buf << endl;


	string str = "好好学习，天天向上！";
	cout << "str = " << str << endl;

}

int main()
{
	test01();
	cout << "---------------" << endl;
	test02();

	return 0;
}
