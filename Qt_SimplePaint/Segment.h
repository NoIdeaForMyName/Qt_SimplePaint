#pragma once
#include "Primitive.h"

class Segment : public Primitive
{

public:
	Segment(const Point& startPoint, const Point& endPoint);
	Segment(const Segment& toCopy);
	~Segment() override = default;
	Item* clone() const override;

	Point getStart() const;
	Point getEnd() const;
	int getLength() const;

	void computeBoundingBox() override;
	void translate(const Point& translationPoint) override;
	void draw(QPainter& painter, bool drawBBox = false) override;

private:
	Point start;
	Point end;
	int length;

};
