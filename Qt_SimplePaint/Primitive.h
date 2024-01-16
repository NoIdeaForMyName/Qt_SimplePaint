#pragma once

#include "Item.h"

class Primitive : public Item
{
public:
	Primitive(const Point& p_point);
	Primitive(const Primitive& toCopy);
	virtual ~Primitive() = default;

	void draw(QPainter& painter) override;
};

