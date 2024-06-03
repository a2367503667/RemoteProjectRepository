#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>

class Maker
{
public:
	void setName(std::string name)
	{
		this->name = name;
	}
	std::string getName()
	{
		return this->name;
	}
	void setAge(int age)
	{
		if (age >= 0 && age <= 100)
		{
			this->age = age;
		}
	}
	int getAge()
	{
		return this->age;
	}
	void init()
	{
		this->name = "小华";
		this->age = 20;
	}
	void printMessage()
	{
		std::cout << "name: " << getName() << std::endl << "age: " << getAge() << std::endl;
	}

private:
	std::string name;
	int age;
};


int main()
{
	Maker m;
	m.init();
	m.printMessage();
	m.setName("晓晓");
	m.setAge(18);
	m.printMessage();

	return 0;
}
