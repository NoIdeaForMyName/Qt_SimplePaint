#pragma once
#include "Item.h"

class ItemDecorator: public Item
{

public:
	ItemDecorator(Item* item);
	//ItemDecorator(const ItemDecorator& toCopy);
	//virtual ~ItemDecorator();
	Item* clone() const override;

	virtual void translate(const Point& translationPoint);
	virtual void computeBoundingBox();
	virtual void draw(QPainter& painter);

protected:
	Item* item;
};
/*
Item(const Point& r_point);
	Item(const Item& toCopy);
	virtual ~Item();
	virtual Item* clone() const = 0;

	Point getPosition() const;
	virtual void translate(const Point& translationPoint);
	virtual void computeBoundingBox() = 0;
	Point* getBoundingBox();
	virtual void draw(QPainter& painter, bool drawBBox = false);
	void drawBoundingBox(QPainter& painter);
*/
