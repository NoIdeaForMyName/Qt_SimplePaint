#include "Circle.h"

Circle::Circle(const Point& r_position, int radius, bool filled)
	: Shape(r_position, filled)
	//, center(Point(r_position.getX() - radius, r_position.getY() - radius))
	, r(radius)
{}

Circle::Circle(const Circle& toCopy)
	: Shape(toCopy.position, toCopy.filled)
	, r(toCopy.r)
{}

Item* Circle::clone() const
{
	return new Circle(position, r, filled);
}

int Circle::getRadius() const
{
	return r;
}

void Circle::computeBoundingBox()
{
	boundingBox[0] = Point(position);
	boundingBox[1] = Point(position.getX(), position.getY() + 2 * r);
	boundingBox[2] = Point(position.getX() + 2 * r, position.getY() + 2 * r);
	boundingBox[3] = Point(position.getX() + 2 * r, position.getY());

	updateBoundingBox = false;
}

void Circle::draw(QPainter& painter)
{
	Shape::draw(painter);
	painter.drawEllipse(position.getX(), position.getY(), 2 * r, 2 * r);
}
