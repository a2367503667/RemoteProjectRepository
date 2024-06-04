#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

class Father
{
public:
	virtual void work()
	{
		std::cout << "在公司上班" << std::endl;
	}

};

class Son :public Father
{
public:
	virtual void work()
	{
		std::cout << "在学校上学" << std::endl;
	}
private:
	int a;
};

void test01()
{
	// 注意：这种写法是错误的，相当于int &a = 10; 因为Son()相当于一个常量对象
	// Father& fa = Son(); // err
	// 这个才是正确写法
	const Father& fa = Son();

	// 还有就是上面这种写法，我们也只能在当前区域使用，因为它属于局部变量，在栈区
	// 下面用堆区申请方式写：

	// 一般不会这么写，因为更加复杂了
	// 1、先开辟空间
	Father* son = new Son;

	// 2、然后再创建新的引用
	Father*& f = son;

	// 3、就可以访问数据了
	f->work(); 

	delete son;
	son = nullptr;
}

int main()
{
	test01();

	return 0;
}
