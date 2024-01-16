#include "Primitive.h"

Primitive::Primitive(const Point& p_point)
	: Item(p_point)
{}

Primitive::Primitive(const Primitive& toCopy)
	: Item(toCopy.position)
{}

void Primitive::draw(QPainter& painter)
{
	QPen pen;
	pen.setColor(Qt::black);
	pen.setWidth(2);
	painter.setPen(pen);
}

