#include "ItemDecorator.h"


ItemDecorator::ItemDecorator(Item* item)
	: Item(item->getPosition())
	, item(item)
{}

Item* ItemDecorator::clone() const
{
	return item->clone();
}

void ItemDecorator::translate(const Point& translationPoint)
{
	//Item::translate(translationPoint);
	item->translate(translationPoint);
}

void ItemDecorator::computeBoundingBox()
{
	item->computeBoundingBox();
}

void ItemDecorator::draw(QPainter& painter)
{
	//Item::draw(painter, drawBBox);
	item->draw(painter);
}
