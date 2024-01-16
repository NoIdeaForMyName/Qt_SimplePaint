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

	Point getPosition() const;
	virtual void translate(const Point& translationPoint);
	virtual void computeBoundingBox() = 0;
	Point* getBoundingBox();
	virtual void draw(QPainter& painter, bool drawBBox = false);
	void drawBoundingBox(QPainter& painter);

protected:
	Point position;
	Point* boundingBox;
	bool updateBoundingBox;

};
