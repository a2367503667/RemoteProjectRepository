#include "Circle.h"
#include "Point.h"


void Circle::setPoint(Point circleHead)
{
	this->circleHead = circleHead;
}
Point Circle::getPoint()
{
	return this->circleHead;
}
void Circle::setR(double r)
{
	this->r = r;
}
double Circle::getR()
{
	return this->r;
}
void Circle::distance(Point& p)
{
	if (getR() * getR() == (p.getX() - getPoint().getX()) * (p.getX() - getPoint().getX()) + (p.getY() - getPoint().getY()) * (p.getY() - getPoint().getY()))
	{
		std::cout << "点在圆上" << std::endl;
	}
	else if (getR() * getR() > (p.getX() - getPoint().getX()) * (p.getX() - getPoint().getX()) + (p.getY() - getPoint().getY()) * (p.getY() - getPoint().getY()))
	{
		std::cout << "点在圆内" << std::endl;
	}
	else
	{
		std::cout << "点在圆外" << std::endl;
	}

}

