#ifndef __CIRCLE_H__
#define __CIRCLE_H__
#include "Point.h"
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
class Circle
{
public:
	void setPoint(Point circleHead);
	Point getPoint();
	void setR(double r);
	double getR();
	void distance(Point& p);
	
private:
	Point circleHead;
	double r;
};
#endif
