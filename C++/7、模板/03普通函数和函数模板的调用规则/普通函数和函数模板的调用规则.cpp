#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

// 普通函数
void myAdd(int a, int b)
{
	std::cout << "普通函数结果(a, b)：" << a + b << std::endl;
}

// 函数模板
template<typename T>
void myAdd(T a, T b)
{
	std::cout << "函数模板结果(a, b)：" << a + b << std::endl;
}

// 函数模板与函数模板可以进行重载
template<typename T>
void myAdd(T a, T b, T c)
{
	std::cout << "函数模板结果(a, b, c)：" << a + b + c << std::endl;
}


// 1、函数模板和普通函数可以同名(即可以重载)
void test01()
{
	int a = 10;
	int b = 20;

	// 2、当普通函数和函数模板重载时，会适时先调用普通函数
	// 因为如果普通函数可以正常使用的话，普通函数只需要编译一次，而函数模板需要编译两次
	// 显然普通函数执行会更快
	myAdd(a, b);

	// 3、可以使用参数列表<>强制调用函数模板
	myAdd<>(a, b);

	// 4、函数模板和函数模板可以进行重载
	myAdd<>(a, b);
	myAdd<>(a, b, a);

	// 5、如果函数模板调用过程中有更合适的匹配，就会优先调用函数模板
	char c1 = 'a';
	char c2 = 'b';

	// 这时是调用函数模板(因为没有char类型参数的函数，只有int类型的，如果调用普通函数还需要强
	// 转，这显然会存在风险，此时就只能是函数模板更加合适匹配)
	myAdd(c1, c2); // 函数模板


}


int main()
{
	test01();

	return 0;
}
