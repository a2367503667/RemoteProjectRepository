#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

int main()
{
	// 普通引用
	int a = 10;
	int& aRef = a;
	aRef = 20;

	// 首先，10是没有空间的，因为它是属于编码表的字符(不在栈区也不在常量区)
	// int& ref1 = 10; // 不能给字面量取别名  这是错误的
	const int& ref2 = 10;  // 这个又可以了，可以给const修饰的引用赋予字面量
	// 其实编译器底层做这样的事：int tmp = 10;  const int &ref2 = tmp;
	// 只能赋一次值，再赋值就会报错   ref2 = 200; 会报错

	// 这里本质上就是拿到了tmp的地址，对tmp的地址进行操作
	// 这里的值变成了200，是因为tmp空间的值被改变了，并不是编译器没有做优化
	// int tmp = 10;  const int &ref2 = tmp;
	// 本质上我们拿到的是tmp的地址，即p就是tmp的地址，我们本质上就是通过tmp地址修改tmp的值
	// 当我们把*p改成200，就是将tmp的值改成200，所以输出肯定是200
	int* p = (int*)&ref2;
	*p = 200;

	cout << "p = " << p << endl; // p的值与&ref2值相同
	cout << "&ref2 = " << &ref2 << endl;
	cout << "ref2 = " << ref2 << endl; // 200

	volatile const int b = 30;
	int* p2 = (int*)&b;

	// 这里也是同样的道理，本质上我们拿到的是tmp的内存，p2存储的是tmp的地址
	// 修改的也是tmp的值，因此输出结果才为300
	*p2 = 300;
	cout << "b = " << b << endl; // 300


	// bool类型
	// bool类型定义的变量只有两个值，true和false，真和假，0和1
	bool is = 1; // 注意：is的值除0以外，都是真
	if (is)
	{
		cout << "真" << endl;
	}
	else 
	{
		cout << "假" << endl;
	}

	return 0;
}
