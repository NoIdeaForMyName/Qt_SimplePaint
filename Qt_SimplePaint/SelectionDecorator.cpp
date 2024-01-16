#include "SelectionDecorator.h"


SelectionDecorator::SelectionDecorator(Item* item)
	: ItemDecorator(item)
{}

void SelectionDecorator::draw(QPainter& painter)
{
	ItemDecorator::draw(painter);

	// BOUNDING BOX PAINTING...
	QPen pen;
	pen.setColor(Qt::red);
	pen.setWidth(1);
	painter.setPen(pen);
	painter.setBrush(Qt::NoBrush);

	if (updateBoundingBox)
		computeBoundingBox();

	Point* bBox = item->getBoundingBox();
	painter.drawRect(QRect(bBox[0].getX(), bBox[0].getY(),
		bBox[2].getX() - bBox[0].getX(),
		bBox[2].getY() - bBox[0].getY()));
}
