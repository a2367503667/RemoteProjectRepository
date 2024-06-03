#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>


class Car
{
public:
	std::string getBrand()
	{
		return this->brand;
	}

	double getLengthStruct()
	{
		return this->lengthStruct;
	}
	std::string getColor()
	{
		return this->color;
	}
	void printQuality()
	{
		std::cout << "brand: " << getBrand() << std::endl;
		std::cout << "lengthStruct: " << getLengthStruct() << "米" << std::endl;
		std::cout << "getColor: " << getColor() << std::endl;
	}

private:
	std::string brand = "大众";
	double lengthStruct = 2.5;
	std::string color = "银白色";
};

// 注：虽然子类继承了父类，但是本质上是从父类那里拷贝一份过来的
// 也就是说“不是”和父类公用一份空间的
class Truck :public Car
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
	void setHeight(double height)
	{
		this->height = height;
	}
	double getHeight()
	{
		return this->height;
	}
	void setSize(std::string size) // 大中小型车
	{
		this->size = size;
	}
	std::string getSize()
	{
		return this->size;
	}
	void printTruck()
	{
		// 注：使用别的类需要写类名和作用域符号，如下
		Car:: printQuality();
		std::cout << "name: " << getName() << std::endl;
		std::cout << "height: " << getHeight() << "米" << std::endl;
		std::cout << "size: " << getSize() << std::endl;
	}
private:
	std::string name;
	double height;
	std::string size; // 大中小
};

void test01()
{
	Truck t;
	t.setName("家庭版卡车");
	t.setHeight(0.7);
	t.setSize("小型卡车");
	t.printTruck();
}

int main()
{
	test01();

	return 0;
}
