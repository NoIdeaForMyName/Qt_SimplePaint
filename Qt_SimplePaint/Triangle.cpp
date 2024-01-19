#include "Triangle.h"


Triangle::Triangle(const Point& p1, const Point& p2, const Point& p3, bool filled)
	: Shape(Point(std::min({ p1.getX(), p2.getX(), p3.getX() }),
	              std::min({ p1.getY(), p2.getY(), p3.getY() })), filled)
	, p1(p1), p2(p2), p3(p3)
{}

Triangle::Triangle(const Triangle& toCopy)
	: Shape(toCopy.position, toCopy.filled)
	, p1(toCopy.p1), p2(toCopy.p2), p3(toCopy.p3)
{}

Item* Triangle::clone() const
{
	return new Triangle(p1, p2, p3, filled);
}

Point Triangle::getP1()
{
	return p1;
}

Point Triangle::getP2()
{
	return p2;
}

Point Triangle::getP3()
{
	return p3;
}

void Triangle::computeBoundingBox()
{
	Point bbRightDown(std::max({ p1.getX(), p2.getX(), p3.getX() }),
		std::max({ p1.getY(), p2.getY(), p3.getY() }));
	boundingBox[0] = Point(position);
	boundingBox[1] = Point(position.getX(), bbRightDown.getY());
	boundingBox[2] = Point(bbRightDown);
	boundingBox[3] = Point(bbRightDown.getX(), position.getY());

	updateBoundingBox = false;
}

void Triangle::translate(const Point& translationPoint)
{
	Item::translate(translationPoint);
	p1.shift(translationPoint);
	p2.shift(translationPoint);
	p3.shift(translationPoint);
}

void Triangle::draw(QPainter& painter)
{
	Shape::draw(painter);
	QPoint points[3] =
	{
		QPoint(p1.getX(), p1.getY()),
		QPoint(p2.getX(), p2.getY()),
		QPoint(p3.getX(), p3.getY())
	};
	painter.drawPolygon(points, 3);
}
