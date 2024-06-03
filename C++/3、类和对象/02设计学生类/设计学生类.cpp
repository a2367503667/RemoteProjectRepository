#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;


class Student
{
// 成员函数(成员行为)
public: // 公有权限

	// 注：类中的函数编译器都默认在前面加inline(即为内联函数)
	void setName(string name)
	{
		this->name = name;
	}
	void setId(int id)
	{
		this->id = id;
	}
	string getName()
	{
		return this->name;
	}
	int getId()
	{
		return this->id;
	}

// 成员变量(成员属性)
private: // 私有权限(只能在类中访问)

	string name;
	int id;

};

void test01()
{
	Student s;
	s.setId(1001);
	s.setName("小明");
	cout << "id: " << s.getId() << endl;
	cout << "name: " << s.getName() << endl;
}

int main()
{
	test01();

	return 0;
}
