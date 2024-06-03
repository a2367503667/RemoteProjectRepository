#define _CRT_SECURE_NO_WARNISNG
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 总结：1、C语言中的const修饰的变量都有空间；2、C语言的const修饰的全局变量具有外部链接属性

//在常量区，一旦初始化，不能被修改(受常量区的保护)
const int a = 10;
void test()
{
	// 下面试验可以知道，全局const修饰的常量是不能被修改的，编译不会报错，但是运行会报错
	int* p = (int*)&a;
	*p = 80;
	printf("a = %d\n", a);
}
// 内部链接属性与外部链接属性
// 简单来说就是定义在全局区里，内被本项目的其他文件使用就是外部链接属性，否则是内部链接属性


int main()
{
	const int b = 20; // 在栈区 
	// b = 200; 局部变量的const不能被直接修改
	// 但是可以间接修改
	int* p = &b;
	printf("未改：b = %d\n", b);
	*p = 200; // 可以间接修改
	printf("b = %d\n", b);

	// 在ctest.c中有const int c = 300;
	// 使用前先声明
	extern const int c;
	printf("c = %d\n", c); // 结构输出成功，也就是说C语言的const修饰的全局变量具有外部链接属性

	return 0;
}
