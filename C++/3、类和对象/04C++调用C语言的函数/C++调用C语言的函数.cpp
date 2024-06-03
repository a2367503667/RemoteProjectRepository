#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
#include "test.h"


int main()
{
	// 报错了
	// 因为C++在编译时，去找func函数，就会去找__Z4funcv这个别名的函数
	// 但是C语言中的func的名字是_func，没有__Z4funcv这个别名，因此在运行后会报错
	// 解决办法就是用extern "C"，解决方式写在头文件test.h里面
	func(); // test.h解决后就可以用了

	return 0;
}
