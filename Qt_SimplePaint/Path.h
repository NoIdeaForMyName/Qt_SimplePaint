#pragma once
#include "Primitive.h"

class Path : public Primitive
{
public:
	Path(const std::vector<Point>& points);
	Path(const Path& toCopy);
	~Path() override = default;

	void addPoint(Point p);
	//clone, draw, translate, computeBBox
	Item* clone() const override;
	void draw(QPainter& painter, bool drawBBox) override;
	void translate(const Point& translationPoint) override;
	void computeBoundingBox() override;

protected:
	std::vector<Point> points;
	static Point computePosition(const std::vector<Point>& points);

};
