#define CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
// const修饰全局变量，直接和间接修改都不行
const int a = 10; // 在C语言中，是放在常量区里面，但是这里是没有空间，即没有内存


// 由这些测试可知，C++const修饰的变量有时候有空间，有时候没有空间(即发生常量折叠)
void test01()
{
	// 为什么没有内存？因为编译器在编译阶段会把下面代码改成 cout << "a = " << 10 << endl;
	// 会优化代码，这个优化又称，常量折叠，这样会更加节省内存，其次运行速度快，因为不需要对a进行寻址
	cout << "a = " << a << endl;

	// 不过也可以不让编译器优化，加volatile关键字
	// const int b = 20; // 在栈区里，有空间
	volatile const int b = 20;
	// 注意：只要有对const变量有取址操作，那么就会有地址(编译器会发现，对变量取地址，那么就说明这个变量还要)
	int* p = (int*)&b;
	*p = 200;
	// 下面这一行显示的b还是20，因为编译器做了优化，在编译过程中遇到这行代码会把b替换成20，和上面的一样
	// 如果上面加了volatile编译器就不会优化
	cout << "b = " << b << endl;
	cout << "*p = " << *p << endl;

	// 结果显示地址是一样的
	// 注意：如果加上volatile，即编译器不优化的话，那么&b就会返回一个布尔值，真则1，假则0
	// 如果还想看地址是否与p相同，那么可以直接强转为int类型，即如下：
	// cout << "&b = " << (int)&b << endl;
	// cout << "p = " << (int)p << endl;

	cout << "验证地址是否一样？" << endl;
	cout << "&b = " << &b << endl;
	cout << "p = " << p << endl;

}


int main08()
{
	test01();

	// Cpptest.cpp文件里面有const int c = 20;
	// 注意：下面那个是不行的，因为C++中const修饰的全局变量只有内部链接属性，因此会报错
	// 为什么会这么做？
	// 因为全局变量定义后，别的文件就不能使用相同名字的变量，所以C++规定，const修饰的全局变量没有外部链接属性
	// 但是要想有外部链接属性，就需要在Cpptest.cpp文件中加extern，即：
	// extern const int c = 20; 这行代码写到Cpptest.cpp中
	extern const int c;
	cout << "c = " << c << endl;


	return 0;
}
