#include "ItemDecorator.h"


ItemDecorator::ItemDecorator(Item* item)
	: Item(item->getPosition())
	, item(item)
	, decoratingItem(true)
{}

ItemDecorator::ItemDecorator(const ItemDecorator& toCopy)
	: Item(toCopy.item->getPosition())
	, item(toCopy.item->clone())
	, decoratingItem(true)
{}

ItemDecorator::~ItemDecorator()
{
	if (decoratingItem)
		delete item;
}

Item* ItemDecorator::clone() const
{
	return item->clone();
}

Item* ItemDecorator::undecorate(bool onlyPeaking)
{
	if (!onlyPeaking)
		decoratingItem = false;
	return item;
}

Point ItemDecorator::getPosition() const
{
	return item->getPosition();
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

Point* ItemDecorator::getBoundingBox()
{
	return item->getBoundingBox();
}

void ItemDecorator::draw(QPainter& painter)
{
	//Item::draw(painter, drawBBox);
	item->draw(painter);
}
