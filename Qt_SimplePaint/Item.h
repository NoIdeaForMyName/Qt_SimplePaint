#pragma once

#include <memory>

#include "Point.h"
#include <vector>

#include <QPainter>

class Item
{
public:
	Item(const Point& r_point);
	Item(const Item& toCopy);
	virtual ~Item();
	virtual Item* clone() const = 0;
	virtual Item* undecorate(bool onlyPeaking = false);

	virtual Point getPosition() const;
	virtual void translate(const Point& translationPoint);
	virtual void computeBoundingBox() = 0;
	virtual Point* getBoundingBox();
	virtual void draw(QPainter& painter) = 0;

protected:
	Point position;
	Point* boundingBox;
	bool updateBoundingBox;

};
