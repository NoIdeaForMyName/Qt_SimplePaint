#pragma once

#include <QtWidgets>
#include <vector>
#include "Item.h"

class Scene : public QWidget
{
	Q_OBJECT
public:
	Scene(QWidget* parent);
	~Scene() override;

	void draw();
	void addItem(Item* it);
	void paintEvent(QPaintEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	std::list<Point>& getLastMouseClicks();
	Point* getLastTwoMousePositions();
	Item* getItemAtPosition(Point pos, Item* toIgnoreItems = nullptr, int length = 1);
	bool eraseItem(Item* item);

signals:
	void mousePressed();
	void mouseMoved();

private:
	std::vector<Item*> items;
	Item* selectedItem;
	std::list<Point> mouseClicks;
	Point* lastTwoMousePos;

	bool isInside(Point* bbox, Point p);

};
