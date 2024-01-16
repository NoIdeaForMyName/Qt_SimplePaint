#pragma once

#include "Primitive.h"
//#include "Item.h"

class Shape : public Primitive
{
public:
	Shape(const Point& r_point, bool filled = false);
	Shape(const Shape& toCopy);
	virtual ~Shape() = default;

	bool isFilled() const;
	void setFilled(bool filled);

	void draw(QPainter& painter) override;

protected:
	bool filled;
};
