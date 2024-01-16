#include "Rect.h"

Rect::Rect(const Point& position, int width, int height, bool filled)
	: Shape(position, filled)
	, width(width)
	, height(height)
{}

Rect::Rect(const Rect& toCopy)
	: Shape(toCopy.position, toCopy.filled)
	, width(toCopy.width)
	, height(toCopy.height)
{}

Item* Rect::clone() const
{
	return new Rect(position, width, height, filled);
}

int Rect::getWidth() const
{
	return width;
}

int Rect::getHeight() const
{
	return height;
}

void Rect::computeBoundingBox()
{
	boundingBox[0] = Point(position);
	boundingBox[1] = Point(position.getX(), position.getY() + height);
	boundingBox[2] = Point(position.getX() + width, position.getY() + height);
	boundingBox[3] = Point(position.getX() + width, position.getY());

	updateBoundingBox = false;
}

void Rect::draw(QPainter& painter)
{
	Shape::draw(painter);
	painter.drawRect(QRect(position.getX(), position.getY(), width, height));
}
