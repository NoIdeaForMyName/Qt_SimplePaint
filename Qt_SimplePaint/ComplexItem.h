#pragma once

#include "Item.h"

class ComplexItem : public Item
{

public:
	ComplexItem(std::vector<Item*>& items);
	ComplexItem(const ComplexItem& toCopy);
	~ComplexItem() override;
	Item* clone() const override;

	std::vector<Item*> getChildren() const;
	void computeBoundingBox() override;
	void translate(const Point& translationPoint) override;
	void draw(QPainter& painter) override;

private:
	std::vector<Item*> items;

	static Point getInitialPosition(const std::vector<Item*>& it);
	std::vector<Item*>& undecorateAll(std::vector<Item*>& initItems);

};
