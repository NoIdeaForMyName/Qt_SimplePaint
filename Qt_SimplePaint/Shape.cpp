#include "Shape.h"

Shape::Shape(const Point& r_point, bool filled)
	: Primitive(r_point), filled(filled)
{}

Shape::Shape(const Shape& toCopy)
	: Primitive(toCopy.position), filled(toCopy.filled)
{}

bool Shape::isFilled() const
{
	return filled;
}

void Shape::setFilled(bool filled)
{
	this->filled = filled;
}

void Shape::draw(QPainter& painter, bool drawBBox)
{
	Primitive::draw(painter, drawBBox);
	if (filled) painter.setBrush(Qt::black);
	else painter.setBrush(Qt::NoBrush);
}
