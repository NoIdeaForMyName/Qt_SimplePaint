#include "ComplexItem.h"


ComplexItem::ComplexItem(std::vector<Item*>& items)
	: Item(getInitialPosition(undecorateAll(items)))
	, items(items)
{}

ComplexItem::ComplexItem(const ComplexItem& toCopy)
	: Item(toCopy.position)
{
	for (auto& item_p : toCopy.items)
		items.push_back(item_p->clone());
}

ComplexItem::~ComplexItem()
{
	for (auto& item : items)
		delete item;
}

Item* ComplexItem::clone() const
{
	return new ComplexItem(*this);
}

std::vector<Item*> ComplexItem::getChildren() const
{
	return items;
}

void ComplexItem::computeBoundingBox()
{
	Point downLeftPoint = position;
	for (auto& item : items)
	{
		if (item->getBoundingBox()[2].getX() > downLeftPoint.getX())
			downLeftPoint.setX(item->getBoundingBox()[2].getX());
		if (item->getBoundingBox()[2].getY() > downLeftPoint.getY())
			downLeftPoint.setY(item->getBoundingBox()[2].getY());
	}
	boundingBox[0] = position;
	boundingBox[1] = Point(position.getX(), downLeftPoint.getY());
	boundingBox[2] = downLeftPoint;
	boundingBox[1] = Point(downLeftPoint.getX(), position.getY());

	updateBoundingBox = false;
}

void ComplexItem::translate(const Point& translationPoint)
{
	Item::translate(translationPoint);
	for (auto item : items)
		item->translate(translationPoint);
}

void ComplexItem::draw(QPainter& painter)
{
	for (auto item : items)
	{
		item->draw(painter);
	}
}

Point ComplexItem::getInitialPosition(const std::vector<Item*>& it)
{
	Point minPoint(it[0]->getPosition());
	for (auto i : it)
	{
		if (i->getPosition().getX() < minPoint.getX())
			minPoint.setX(i->getPosition().getX());
		if (i->getPosition().getY() < minPoint.getY())
			minPoint.setY(i->getPosition().getY());
	}
	return minPoint;
}

std::vector<Item*>& ComplexItem::undecorateAll(std::vector<Item*>& initItems)
{
	for (int i = 0; i < initItems.size(); i++)
	{
		Item* undecorated = initItems[i]->undecorate();
		if (undecorated != initItems[i])
		{
			delete initItems[i];
			initItems[i] = undecorated;
		}
	}
	return initItems;
}
