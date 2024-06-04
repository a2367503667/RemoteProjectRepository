#ifndef __TEST_H__
#define __TEST_H__

// 这个头文件只是用来验证头文件重复包含的问题(具体情况看main文件)
#include <iostream>
inline void func()
{
	for (int i = 0; i < 10; ++i)
	{
		std::cout << "func()" << std::endl;
	}
}


#endif
