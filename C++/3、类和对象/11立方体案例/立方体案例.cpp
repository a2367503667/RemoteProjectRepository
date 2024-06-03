#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

class Cube
{
public:
	void setLength(double length)
	{
		this->length = length;
	}
	double getLength()
	{
		return this->length;
	}
	void setBroad(double broad)
	{
		this->broad = broad;
	}
	double getBroad()
	{
		return this->broad;
	}
	void setHeight(double height)
	{
		this->height = height;
	}
	double getHeight()
	{
		return this->height;
	}
	double calcArea()
	{
		return 2 * ((this->broad) * (this->length) + (this->broad) * (this->height) + (this->length) * (this->height));
	}
	double calcVolume()
	{
		return (this->broad) * (this->length) * (this->height);
	}
	void init()
	{
		// 对立方体进行初始化
		this->length = 0;
		this->broad = 0;
		this->height = 0;
	}
	// 成员函数判断两个立方体是否相等
	bool compareCube(Cube& c)
	{
		if (this->length == c.length && this->broad == c.broad && this->height == c.length)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
private:
	double length;
	double broad;
	double height;
};

void test01()
{
	Cube c1, c2;
	c1.init();
	c2.init();
	double length1, length2, broad1, broad2, height1, height2;
	std::cout << "请输入c1的长：";
	std::cin >> length1;
	std::cout << "请输入c1的宽：";
	std::cin >> broad1;
	std::cout << "请输入c1的高：";
	std::cin >> height1;
	std::cout << "请输入c2的长：";
	std::cin >> length2;
	std::cout << "请输入c2的宽：";
	std::cin >> broad2;
	std::cout << "请输入c2的高：";
	std::cin >> height2;
	if (c1.compareCube(c2))
	{
		std::cout << "两个立方体相等" << std::endl;
	}
	else
	{
		std::cout << "两个立方体不相等" << std::endl;
	}
}

// 全局函数判断两个立方体是否相等
bool compareCube(Cube &c1, Cube &c2)
{
	double length1, length2, broad1, broad2, height1, height2;
	std::cout << "请输入c1的长：";
	std::cin >> length1;
	c1.setLength(length1);
	std::cout << "请输入c1的宽：";
	std::cin >> broad1;
	c1.setBroad(broad1);
	std::cout << "请输入c1的高：";
	std::cin >> height1;
	c1.setHeight(height1);
	std::cout << "请输入c2的长：";
	std::cin >> length2;
	c2.setLength(length2);
	std::cout << "请输入c2的宽：";
	std::cin >> broad2;
	c2.setBroad(broad2);
	std::cout << "请输入c2的高：";
	std::cin >> height2;
	c2.setLength(height2);
	if (c1.getLength() == c2.getLength() && c1.getBroad() == c2.getBroad() && c1.getHeight() == c2.getHeight())
	{
		return true;
	}
	return false;
}



int main()
{
	Cube c1, c2;
	if (compareCube(c1, c2))
	{
		std::cout << "全局：这两个立方体相等！" << std::endl;
	}
	else
	{
		std::cout << "全局：这两个立方体不相等！" << std::endl;
	}

	return 0;
}
