#include "Path.h"


Path::Path(const std::vector<Point>& points)
	: Primitive(Path::computePosition(points))
	, points(points)
{}

Path::Path(const Path& toCopy)
	: Primitive(toCopy.position)
	, points(toCopy.points)
{}

Item* Path::clone() const
{
	return new Path(*this);
}

void Path::addPoint(Point p)
{
	points.push_back(p);
	updateBoundingBox = true;
}

void Path::draw(QPainter& painter)
{
	Primitive::draw(painter);
	for (const Point& point : points)
		painter.drawPoint(point.getX(), point.getY());
}

void Path::translate(const Point& translationPoint)
{
	Primitive::translate(translationPoint);
	for (Point& point : points)
		point.shift(translationPoint);
}

void Path::computeBoundingBox()
{
	position = computePosition(points);
	Point maxPoint = points[0];
	for (const Point& point : points)
	{
		if (point.getX() > maxPoint.getX())
			maxPoint.setX(point.getX());
		if (point.getY() > maxPoint.getY())
			maxPoint.setY(point.getY());
	}

	boundingBox[0] = position;
	boundingBox[1] = Point(position.getX(), maxPoint.getY());
	boundingBox[2] = maxPoint;
	boundingBox[3] = Point(maxPoint.getX(), position.getY());

	updateBoundingBox = false;
}

Point Path::computePosition(const std::vector<Point>& points)
{
	Point minPoint(points[0]);
	for (const Point& point : points)
	{
		if (point.getX() < minPoint.getX())
			minPoint.setX(point.getX());
		if (point.getY() < minPoint.getY())
			minPoint.setY(point.getY());
	}
	return minPoint;
}

