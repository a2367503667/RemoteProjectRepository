#include "test.h"

// 虽然实现了func但是两个命名空间有相同名字的函数，会导致系统无法识别到底是哪个命名空间
// 的函数，所以最后链接会出现错误
// void func()  这样写会报错，正确应该像下面那样写
// 加上对应的命名空间myMaker1::
void myMaker1::func()
{
	cout << "myMaker1::func" << endl;
}
