#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

int main()
{
	// 这里会发生报错，因为这里不能进行隐式转换，而在C语言是可以的，因此需要注意
	// 在这里必须进行隐式转换
	// char* p = malloc(64);  会报错，正确写法如下：
	char* p = (char*)malloc(64);

	return 0;
}
