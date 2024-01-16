#include "Point.h"

Point::Point()
	: x(0)
	, y(0)
{}

Point::Point(int x, int y)
	: x(x)
	, y(y)
{}

Point::Point(const Point& r_toCopy)
	: x(r_toCopy.x)
	, y(r_toCopy.y)
{}

void Point::shift(const Point& p)
{
	x += p.getX();
	y += p.getY();
}

int Point::getX() const
{
	return x;
}

int Point::getY() const
{
	return y;
}

void Point::setX(int newX)
{
	x = newX;
}

void Point::setY(int newY)
{
	y = newY;
}
