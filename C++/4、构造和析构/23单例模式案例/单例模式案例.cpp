#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>

// 目标：使用单例模式统计打印机使用次数(因为统计打印人数是调用同一个打印机，也就
//       是使用同一个对象，这个就是一个典型的单例模式案例)
class MyPrinter
{
private:
	MyPrinter() :count(0) {}
	MyPrinter(const MyPrinter& mp) {}
public:

	// 用来获取对象
	static MyPrinter* getInstance()
	{
		return myPrinterInstance;
	}

	// 每个人打印就将打印次数加一(也就是每打印一次就调用这个函数一次)
	void printCount(std::string name)
	{
		std::cout << name << "：使用打印机" << std::endl;
		++(this->count);
	}

	// 获取打印次数
	int getCount()
	{
		return count;
	}

private:
	int count; // 用于记录使用打印机的次数
	static MyPrinter* myPrinterInstance;
};
MyPrinter* MyPrinter::myPrinterInstance = new MyPrinter;

void test01()
{
	// 销售部
	MyPrinter* sell = MyPrinter::getInstance();
	sell->printCount("销售部");

	// 技术部
	MyPrinter* tec = MyPrinter::getInstance();
	tec->printCount("技术部");

	// 公关部
	MyPrinter* pub = MyPrinter::getInstance();
	pub->printCount("公关部");

	std::cout << "打印机一共使用的次数为：" << MyPrinter::getInstance()->getCount() << std::endl;

}



int main()
{
	test01();

	return 0;
}
