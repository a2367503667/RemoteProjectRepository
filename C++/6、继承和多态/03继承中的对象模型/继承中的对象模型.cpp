#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

/*
	我们如何看到继承的对象模型呢？

	我们先打开VS2022的开发人员命令提示程序(可以在电脑"Win"键的"所有应用"中找到"Visual Studio 2022"
	的文件夹，然后找到"Developer Command Prompt for VS 2022"即是"VS2022的开发人员命令提示程序")
	在本电脑的路径是"C:\ProgramData\Microsoft\Windows\Start Menu\Programs\
	Visual Studio 2022\Visual Studio Tools"

	然后打开"VS2022的开发人员命令提示程序"后，接着cd切换到你需要查看继承模型的工程目录，最后
	再输入命令：cl /d1 reportSingleClassLayout(类名) (类所在的文件名)
	在这里则是输入：cl /d1 reportSingleClassLayoutSon 07继承中的对象模型.cpp

	查看结果如下：

	07继承中的对象模型.cpp
	class Son       size(20):
			+---
	 0      | +--- (base class Father)
	 0      | | a
	 4      | | b
	 8      | | c
			| +---
	12      | x
	16      | y
			+---


	其中我们可以看出，从父类中继承了三个(a、b和c)
*/

class Father
{
public:
	int a;
protected:
	int b;
private:
	int c;
};

class Son :public Father
{
public:
	int x;
	int y;
};


int main()
{

	return 0;
}
