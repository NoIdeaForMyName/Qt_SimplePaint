#include "Item.h"

Item::Item(const Point& r_point)
	: position(r_point)
	, boundingBox(new Point[4])
	, updateBoundingBox(true)
{}

Item::~Item()
{
	delete[] boundingBox;
}

Item::Item(const Item& toCopy)
	: position(toCopy.position)
	, boundingBox(new Point[4])
	, updateBoundingBox(toCopy.updateBoundingBox)
{
	for (int i = 0; i < 4; i++)
		boundingBox[i] = toCopy.boundingBox[i];
}

Point Item::getPosition() const
{
	return position;
}

void Item::translate(const Point& translationPoint)
{
	position.shift(translationPoint);
	if (!updateBoundingBox)
	{
		for (int i = 0; i < 4; i++)
			boundingBox[i].shift(translationPoint);
	}
	else
		updateBoundingBox = true;
}

Point* Item::getBoundingBox()
{
	if (updateBoundingBox)
		computeBoundingBox();
	return boundingBox;
}

void Item::draw(QPainter& painter, bool drawBBox)
{
	if (drawBBox) drawBoundingBox(painter);
}

void Item::drawBoundingBox(QPainter& painter)
{
	QPen pen;
	pen.setColor(Qt::red);
	pen.setWidth(1);
	painter.setPen(pen);
	painter.setBrush(Qt::NoBrush);

	if (updateBoundingBox)
		computeBoundingBox();

	painter.drawRect(QRect(boundingBox[0].getX(), boundingBox[0].getY(),
		boundingBox[2].getX() - boundingBox[0].getX(),
		boundingBox[2].getY() - boundingBox[0].getY()));
}
