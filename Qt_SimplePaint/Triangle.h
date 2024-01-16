#pragma once

#include "Shape.h"

class Triangle : public Shape
{

public:
	Triangle(const Point& p1, const Point& p2, const Point& p3, bool filled = false);
	Triangle(const Triangle& toCopy);
	~Triangle() override = default;
	Item* clone() const override;

	Point getP1();
	Point getP2();
	Point getP3();

	void computeBoundingBox() override;
	void translate(const Point& translationPoint) override;
	void draw(QPainter& painter, bool drawBBox = false) override;

private:
	Point p1;
	Point p2;
	Point p3;

};
