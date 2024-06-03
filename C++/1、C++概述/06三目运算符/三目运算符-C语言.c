#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void test()
{
	// (a > b ? a : b) = 100;  这句话在C语言中是会报错的，因为左边那个是属于右值也就是常量
	// 但是如果真的想改里面的值的话，就可以这样，*(a > b ? &a : &b) = 100; 返回它的地址然后修改它的值
	// 下面做出验证：
	int a = 10;
	int b = 20;
	printf("max = %d\n", a > b ? a : b);
	// 如果我想修改它返回后的值，这样写是会报错的
	// (a > b ? a : b) = 100;  会提示a > b ? a : b是左值
	// 如果真的想改可以这样写，如下：
	*(a > b ? &a : &b) = 100;
	printf("b = %d\n", 100);
}

int main06()
{
	test();
	return 0;
}
