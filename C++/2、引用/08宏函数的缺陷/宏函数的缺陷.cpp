#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
#define ADD(x,y) x+y
// 这个就是内联函数
// 在普通函数前面加上inline是向编译器申请成为内联函数
// 如果变成内联函数的话，运行速度就很快，效率就很高，就跟宏函数一样
// 如果没有加inline但是长期使用这个函数的话，也会把这个函数变成内联函数
// 也就是说，这样就会使得内联函数不可控，加了inline也不一定成为内联函数(因为需要看编译器的情况)
// 但是加了inline就更大可能成为内联函数
inline int Add(int x, int y)
{
	return x + y;
}

void test01()
{
	// 缺陷一：宏函数本质上其实就是复制下去而已，下面的计算就是10 + 20 * 2 = 50，如果想求出60，就需要加括号
	// 即 #define ADD(x,y) (x+y) 
	int ref = ADD(10, 20) * 2;
	cout << "ADD(10,20) = " << ref << endl;

	int ref2 = Add(10, 20) * 2;
	cout << "Add(10,20) = " << ref2 << endl;

}

#define COMAPD(x,y) ((x)<(y)?(x):(y))
inline int Comapd(int x, int y)
{
	return x < y ? x : y;
}
// 缺陷二：就是宏函数对应的x和y只要你把值赋进去，那么所有的内容都会按照里面的改变
// 也就是像下面那样，((++a)<(b)?(++a):(b))，所有x的位置都替换成++a
void test02()
{
	int a = 1;
	int b = 3;
	// 结果为3
	// 过程：					((++a)<(b)?(++a):(b))
	// 也就是说a这个位置全部都替换成++a，先加一次1，a=2，再加一次1，a=3结果就返回a，因此结果为3
	// cout << "COMAPD(x,y) = " << COMAPD(++a, b) << endl;

	// 而这个地方就是先在外面计算完++a，得出来++a的值之后，再传到Comapd函数当中，所以值是没有问题的
	cout << "Comapd(++a,b) = " << Comapd(++a, b) << endl;
}

// 什么情况不会成为内联函数？
// 1、存在过多的条件判断语句
// 2、函数提过大(超过50、60行就不会了)
// 3、对函数进行取址操作
// 4、不能存在任何形式的循环语句

// 内联函数的好处
// 1、有函数的效率，但没有宏函数的缺点
// 2、类的成员函数默认加上inline

int main()
{
	// test01();
	test02();


	return 0;
}
