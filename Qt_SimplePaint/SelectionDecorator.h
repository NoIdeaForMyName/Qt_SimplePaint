#pragma once
#include "ItemDecorator.h"

class SelectionDecorator: public ItemDecorator
{
public:
	SelectionDecorator(Item* item);

	void draw(QPainter& painter) override;
};
