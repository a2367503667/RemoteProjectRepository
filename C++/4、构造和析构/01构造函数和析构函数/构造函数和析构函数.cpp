#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include <cstring>

/*
	初始化与清理：
	硬盘中存储的数据即使格式化了，数据还是保存在硬盘中，正确的清理方式就是把大量无用信息往硬盘上存
	覆盖掉原来的数据，这样才可以保证数据不会丢失

	构造函数就是给类的对象实例化进行数据初始化的，而析构函数是用来程序结束时给对象进行销毁的
	注：无论你是否喜欢，对象的初始化和清理工作时编译器强制我们要做的，即使你不提供初始化操作和
	清理操作，编译器也会给你增加默认的操作，只是这个默认初始化操作不会做任何事情，所以编写类就应该顺便
	提供初始化函数
*/

class Maker
{
public:	
	// 构造函数
	// 作用：初始化成员变量，是编译器去调用的
	Maker()
	{
		this->a = 10;
		std::cout << "构造函数" << std::endl;
	}
	// 析构函数(在类名前面加~)
	// 在对象销毁之前编译器会调用析构函数
	~Maker()
	{
		std::cout << "析构函数" << std::endl;
	}

public:
	int a;
};

class Maker2
{
public:
	// 有参构造函数
	Maker2(const char* name, int age)
	{
		std::cout << "有参构造函数" << std::endl;
		// 进行动态分配内存初始化
		this->pName = (char*)malloc(strlen(name)+1);
		strcpy(this->pName, name);
		this->age = age;
	}
	~Maker2()
	{
		std::cout << "析构函数" << std::endl;
		// 开辟的空间在析构函数中释放掉，析构函数就是干这个的
		if (this->pName != NULL)
		{
			free(this->pName);
			this->pName = NULL;
		}
	}

	const char* getPName()
	{
		return this->pName;
	}

	int getAge()
	{
		return this->age;
	}
private:
	char* pName;
	int age;
};

class Maker3
{
public:
	// 1、构造函数可以重载
	Maker3() // 无参构造函数
	{
		std::cout << "无参构造函数" << std::endl;
		int age = 10;
	}
	Maker3(int a) // 有参构造函数
	{
		std::cout << "有参构造函数" << std::endl;
		this->age = a;
	}
// private: 5、析构函数必须公有化，不能私有化，不然会报错
	~Maker3()
	{
		std::cout << "析构函数" << std::endl;
	}
	/*
	析构函数不能带有参数，否则报错，也就说明了析构函数不能重载
	~Maker3(int a)
	{

	}
	*/

	int getAge()
	{
		return this->age;
	}

private:
	int age;
	char* pName;
};




void test01()
{
	// 实例化对象，内部做两件事
	// 1、分配空间(局部变量在栈区分配空间)
	// 2、调用构造函数进行初始化
	// 在对象实例化之前编译器会先调用构造函数
	Maker m; 
	// 下面会出现，C4700：使用了未初始化的局部变量“m”的报错，因为a未经初始化就使用了
	// std::cout << "a = " << m.a << std::endl;
	// 初始化后使用a是没有问题的
	std::cout << "a = " << m.a << std::endl;

}

void test02()
{
	// 注：如果写了有参构造函数，无参构造函数就会默认被覆盖，就需要写变量名(xxx, xxx)其中xxx是构造函数参数
	// 但是上面那句话不完全对，因为编译器会提供拷贝构造函数，这个函数也是有参的
	// Maker2 m;  否则这个会报错 
	Maker2 m("小明", 20);
	// 但是我们发现一件事情，就是我们申请的pName空间没有free掉，这样就会出现内存泄漏的现象
	// 并且我们又不能直接去调用类里面的pName，因为pName是私有的，我们不能在类外访问
	// 因为我们就需要通过析构函数把开辟的空间释放掉
	std::cout << "name: " << m.getPName() << std::endl << "age: " << m.getAge() << std::endl;
}

void test03()
{
	// 2、当构造函数私有化之后，不能创建对象，即构造函数必须是公用的
	// 3、有对象产生必须会调用构造函数，如果有对象销毁必定会调用析构函数
	// 4、有多少个对象产生就会调用多少次构造函数，对应的有多少个对象销毁就会调用多少次析构函数
	Maker3 m;

	Maker3 m2(10);
	std::cout << "age: " << m2.getAge() << std::endl;

}



int main01()
{
	test01();
	test02();
	test03();

	Maker m2;
	// 这里不会出现"析构函数"是因为有暂停，此时main函数还没结束，意味着m2还没被销毁，所以不会出现"析构函数"
	// 如果你按下任意键后，就会跳过下面这个步骤，main函数就结束了，此时"构造函数"就出来了
	system("pause"); 
	return 0;
}
