#pragma once

#include "Shape.h"

class Circle : public Shape
{

public:
	Circle(const Point& r_position, int radius, bool filled = false);
	Circle(const Circle& toCopy);
	~Circle() override = default;
	Item* clone() const override;

	int getRadius() const;

	void computeBoundingBox() override;
	void draw(QPainter& painter) override;

private:
	//Point center;
	int r;

};
