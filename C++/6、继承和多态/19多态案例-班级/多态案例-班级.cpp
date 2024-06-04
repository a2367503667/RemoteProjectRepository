#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>

/*
	这个示例只给了一个Student类，其实应该多给几个类的，但是就不给了
*/

class People
{
public:
	virtual void show() = 0;
};

class Student :public People
{
public:
	Student(std::string name, std::string skill) :name(name), skill(skill) {}

	virtual void show()
	{
		std::cout << this->name << "展现" << this->skill << "技能" << std::endl;
	}

private:
	std::string name;
	std::string skill;
};

class MyClass
{
public:
	MyClass(int mCapacity)
	{
		this->mSize = 0;
		this->mCapacity = mCapacity;
		this->p = new People * [this->mCapacity];
		for (int i = 0; i < this->mCapacity; ++i)
		{
			this->p[i] = nullptr;
		}
	}

	void addPeople(People* peo)
	{
		if (this->mCapacity == this->mSize)
		{
			return;
		}
		this->p[this->mSize++] = peo;
	}

	void printPeople()
	{
		for (int i = 0; i < this->mSize; ++i)
		{
			this->p[i]->show();
		}
	}

	~MyClass()
	{
		if (this->p != nullptr)
		{
			for (int i = 0; i < this->mSize; ++i)
			{
				if (this->p[i] != nullptr)
				{
					delete this->p[i];
					this->p[i] = nullptr;
				}
			}
			delete[] this->p;
			this->p = nullptr;
		}
	}

private:
	People** p;
	int mSize;
	int mCapacity;
};

void test01()
{
	MyClass* mc = new MyClass(50);
	mc->addPeople(new Student("张三", "编写C++程序"));
	mc->addPeople(new Student("李四", "编写Java程序"));
	mc->addPeople(new Student("王五", "编写Python程序"));
	mc->addPeople(new Student("赵六", "编写C语言"));
	mc->addPeople(new Student("老八", "打王者"));

	mc->printPeople();
	delete mc;
	mc = nullptr;
}


int main()
{
	test01();

	return 0;
}
