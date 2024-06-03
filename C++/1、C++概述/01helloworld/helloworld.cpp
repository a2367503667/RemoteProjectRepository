#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std; // 标准命名空间(也就是说光有头文件不行，还得有命名空间)

int main(int argc, char* argv[])
{
	// cout标准的输出流对象
	// << 运算符重载，不是左移
	// endl是刷新缓冲区，并换行，也就是说会立即把内容显示到屏幕上面
	// 而且endl还有一个好处，因为Linux的换行是'\n'，而Windows的换行是\r\n
	// 但是使用endl后，不管是哪个系统，都是换行，也不会使文件变大变小，这就很好避免这个尴尬的事情发生
	cout << "hello world" << endl;
	return 0;
}
