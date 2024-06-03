#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;

// 把属性设置为私有权限的好处：
// 1、可以控制属性的读写权限(让你只能读就只能读，让你只能写就只能写，如果设置public就可以给别人任意读写，很不安全)
// 2、可以保证客户访问数据的一致性(假如类里面有一个公有权限int变量名叫func(下面有写)，但是在你点(.)的时候你并不清楚
// 是不是函数那你就没办法正确调用，因此，我们把属性都设置为私有，能点(.)出来的都是方法，就能够确保客户调用成员的一致性)
// 3、可以确保属性的合法性(假如我们调用了setAge()在里面写1000，那么我们正常人的岁数不会超过1000岁，这样就不符合
// 我们的要求，那么我们可以在成员方法里面加一些条件判断(setAge里面有写))


class Maker
{
public:
	// 写，姓名
	void setName(string name)
	{
		this->name = name;
	}
	// 读，姓名
	string getName()
	{
		return this->name;
	}
	// 写，年龄
	void setAge(int age)
	{
		// 加上判断后就可以确保属性的合法
		if (age < 0 && age>120)
		{
			this->age = age;
		}
	}
	// 读，年龄
	int getAge()
	{
		return this->age;
	}
	// 写，学号
	void setId(int id)
	{
		this->id = id;
	}
	// 读，学号
	int getId()
	{
		return this->id;
	}
private: // 私有(外面访问不到)
	string name;
	int age;
	int id;

public: // 如果把这个公有的话，func会干扰用户的判断(误以为是函数)，因此要把属性设置为私有
	int func;
};

int main()
{
	Maker m;

	return 0;
}
