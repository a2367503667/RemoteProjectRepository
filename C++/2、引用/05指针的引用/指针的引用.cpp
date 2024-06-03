#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
using namespace std;

void test01()
{
	// 指针的引用是给指针变量的空间取别名
	char* p = (char*)"张三"; // 注意：字符串常量赋值给char* 需要强制类型转换，因为指针类型不一致
	char*& p1 = p;
	cout << "p1 = " << p1 << endl;
}

// 被调函数
// C语言的使用方法，要二级指针才能给一级指针赋值
// void func01(char **tmp) 原C语言的方法
// 使用指针的引用后，就不需要传过来一个二级指针了，直接在变量面前加&就可以
void func01(char *&tmp)
{
	char* p = (char*)malloc(64);
	memset(p, 0, sizeof(char) * 64);
	strcpy(p, "李四");
	tmp = p; // 原C语言的方法：*tmp = p; 省了*
}

// 主调函数
void test02()
{
	char* p = NULL;
	// 有引用符之后，就不需要传过去一个&p，直接传p即可
	func01(p); // 原C语言的方法：func01(&p);  省了*
	cout << "p = [" << p << "]" << endl;

}


int main()
{
	// test01();
	test02();


	return 0;
}
