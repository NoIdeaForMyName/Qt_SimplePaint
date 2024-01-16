#include "Segment.h"


Segment::Segment(const Point& startPoint, const Point& endPoint)
	: Primitive(Point(std::min(startPoint.getX(), endPoint.getX()),
		std::min(startPoint.getY(), endPoint.getY())))
	, start(startPoint), end(endPoint)
{
	length = static_cast<int>(round(sqrt(pow(abs(start.getX() - end.getX()), 2) + pow(abs(start.getY() - end.getY()), 2))));
}

Segment::Segment(const Segment& toCopy)
	: Primitive(toCopy.position)
	, start(toCopy.start), end(toCopy.end), length(toCopy.length)
{}

Item* Segment::clone() const
{
	return new Segment(start, end);
}

Point Segment::getStart() const
{
	return start;
}

Point Segment::getEnd() const
{
	return end;
}

int Segment::getLength() const
{
	return length;
}

void Segment::computeBoundingBox()
{
	Point bbDownRight(std::max(start.getX(), end.getX()), std::max(start.getY(), end.getY()));
	boundingBox[0] = Point(position);
	boundingBox[1] = Point(position.getX(), bbDownRight.getY());
	boundingBox[2] = Point(bbDownRight);
	boundingBox[3] = Point(bbDownRight.getX(), position.getY());

	updateBoundingBox = false;
}

void Segment::translate(const Point& translationPoint)
{
	Item::translate(translationPoint);
	start.shift(translationPoint);
	end.shift(translationPoint);
}

void Segment::draw(QPainter& painter)
{
	Primitive::draw(painter);
	QPoint points[2] = { QPoint(start.getX(), start.getY()), QPoint(end.getX(), end.getY()) };
	painter.drawPolygon(points, 2);
}
