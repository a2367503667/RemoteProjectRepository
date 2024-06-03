#include "Circle.h"
#include "Point.h"

// 一般情况下类都是分文件编写的，还有把类的声明放头文件里面，函数的实现放在对应的类cpp文件里
//class Point
//{
//public:
//	void setX(double x)
//	{
//		this->x = x;
//	}
//	double getX()
//	{
//		return this->x;
//	}
//	void setY(double y)
//	{
//		this->y = y;
//	}
//	double getY()
//	{
//		return this->y;
//	}
//private:
//	double x;
//	double y;
//};
//
//class Circle
//{
//public:
//	void setPoint(Point circleHead)
//	{
//		this->circleHead = circleHead;
//	}
//	Point getPoint()
//	{
//		return this->circleHead;
//	}
//	void setR(double r)
//	{
//		this->r = r;
//	}
//	double getR()
//	{
//		return this->r;
//	}
//	void distance(Point &p)
//	{
//		if (getR() * getR() == (p.getX() - getPoint().getX()) * (p.getX() - getPoint().getX()) + (p.getY() - getPoint().getY()) * (p.getY() - getPoint().getY()))
//		{
//			std::cout << "点在圆上" << std::endl;
//		}
//		else if (getR() * getR() > (p.getX() - getPoint().getX()) * (p.getX() - getPoint().getX()) + (p.getY() - getPoint().getY()) * (p.getY() - getPoint().getY()))
//		{
//			std::cout << "点在圆内" << std::endl;
//		}
//		else
//		{
//			std::cout << "点在圆外" << std::endl;
//		}
//
//	}
//private:
//	Point circleHead;
//	double r;
//};

void test01()
{
	Point p1, p2;
	p1.setX(8);
	p1.setY(15);
	Circle c;
	p2.setX(5);
	p2.setY(19);
	c.setPoint(p2);
	c.setR(5);
	c.distance(p1);
}

int main()
{
	test01();

	return 0;
}
