#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

/*
	1、默认的拷贝构造函数只是做为简单的赋值操作(也称浅拷贝)
	2、浅拷贝的问题：就是对于我们动态申请空间的变量，如果直接复制地址的话，在调用
	   析构函数的时候，一个空间就会被释放两次
*/

class Maker
{
public:
	Maker(int id, int age)
	{
		this->id = id;
		this->age = age;
	}
	~Maker()
	{

	}
public:
	int id;
	int age;
};


void test01()
{
	Maker m1(1, 18);
	Maker m2(m1);

	/*
		上面其实就是简单的赋值操作，如下：
		m1.id = m2.id;
		m1.age = m2.age;
	*/

	std::cout << "m1.id = " << m1.id << std::endl << "m1.age = " << m1.age << std::endl;
	std::cout << "m2.id = " << m2.id << std::endl << "m1.age = " << m2.age << std::endl;
}

// 浅拷贝
class Student
{
public:
	Student(const char* name, int age)
	{
		this->pName = (char*)malloc(strlen(name) + 1);
		strcpy(pName, name);
		this->age = age;
	}
	~Student()
	{
		if (this->pName != NULL)
		{
			free(this->pName);
			this->pName = NULL;
		}
	}

public:
	int age;
	char* pName;

};

void test02()
{
	Student s1("小花", 18);
	Student s2(s1);

	// 浅拷贝会有一个问题，就是当test02函数结束后，会先释放s1的pName所申请的指向的空间
	// 但是s2还指向那个s1申请的空间(因为s2是简单复制s1的pName的值)，然后s2又发现它的pName不为空
	// 就又释放了空间，这就导致了一个空间被释放两边，就出现了报错，这也就是浅拷贝出现的bug
	// 浅拷贝如果用在动态申请空间里，就会出现问题，会使程序崩溃，下面代码就是错误的：
	// std::cout << "s1.pName = " << s1.pName << std::endl << "s1.age = " << s1.age << std::endl;
	// std::cout << "s2.pName = " << s2.pName << std::endl << "s2.age = " << s2.age << std::endl;
}

// 深拷贝(本质就是在拷贝构造函数中自己申请空间，不要直接复制已有的对象的空间，否则就会出现一个空间重复释放的现象)
class Student1
{
public:
	Student1(const char *name ,int age)
	{
		this->pName = (char*)malloc(strlen(name) + 1);
		strcpy(this->pName, name);
		this->age = age;
	}
	// 我们不使用默认编译器给的拷贝构造函数，我们自己写一个新的拷贝构造函数
	Student1(const Student1 &s)
	{
		// 其实深拷贝就是在拷贝构造函数中分配新的空间，然后把已有的对象的字符串拷贝到这
		// 个分配好的空间里面，到时候释放也是释放自己的空间，就不会重复再去释放传进来那个对象分配过的空间了
		std::cout << "自己写的拷贝构造函数" << std::endl;
		this->pName = (char*)malloc(strlen(s.pName) + 1);
		strcpy(this->pName, s.pName);
		this->age = s.age;
	}
	~Student1()
	{
		if (this->pName != NULL)
		{
			free(this->pName);
			this->pName = NULL;
		}
	}

public:
	int age;
	char* pName;
};

void test03()
{
	Student1 s1("小花", 18);
	Student1 s2(s1);

	std::cout << "s1.pName = " << s1.pName << std::endl << "s1.age = " << s1.age << std::endl;
	std::cout << "s2.pName = " << s2.pName << std::endl << "s2.age = " << s2.age << std::endl;
}


int main()
{
	// test01();
	// test02();
	test03();

	return 0;
}
