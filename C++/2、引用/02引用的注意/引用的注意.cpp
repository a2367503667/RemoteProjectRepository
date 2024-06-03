#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

// 注意：int &b = a;这里的&并不是取地址操作符，而是引用的标记作用(也就是给a变量取了个别名b)
// 除了引用创建时必须初始化，常量也必须初始化，即const int c;(在全局区即为常量)如果不初始化就会编译报错
// const修饰必须初始化
int main11()
{
	// 1、引用创建时必须初始化
	// 其实引用的本质是常量(以后会介绍)
	// int& pRef; 这个是错误的

	// 2、引用一旦初始化就不能改变它的指向
	int a = 10;
	int& pRef = a; // 给a的空间取别名操作
	int b = 20;
	// &pRef = b; 这个显示报错
	pRef = b; // 注：这个是赋值操作
	cout << "a = " << a << endl; // 会发现a的值被改为20

	// 结果是两个地址一样
	cout << "&a = " << &a << endl;
	cout << "&pRef = " << &pRef << endl;

	// 3、引用必须引用一块合法的内存空间(也就是说内存必须是自己的，是系统分配给你的空间)



	return 0;
}
