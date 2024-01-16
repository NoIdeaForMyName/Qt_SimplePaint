#pragma once

#include "Shape.h"

class Rect : public Shape
{

public:
	Rect(const Point& position, int width, int height, bool filled = false);
	Rect(const Rect& toCopy);
	~Rect() override = default;
	Item* clone() const override;

	int getWidth() const;
	int getHeight() const;

	void computeBoundingBox() override;
	void draw(QPainter& painter) override;

private:
	int width;
	int height;

};
