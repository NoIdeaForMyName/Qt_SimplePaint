#include "Scene.h"

#include "SelectionDecorator.h"

Scene::Scene(QWidget* parent = nullptr)
	: QWidget(parent)
	, lastTwoMousePos(new Point[2])
{
	//setObjectName("MyScene");
	//QPalette pal = QPalette();
	//// Qt::black / "#000000" / "black"
	//pal.setColor(QPalette::Window, Qt::black);
	//setAutoFillBackground(true);
	//setPalette(pal);
	//show();

	setMouseTracking(true); // mouse is being tracked even if button is not clicked
	setStyleSheet("background-color: white");
}

Scene::~Scene()
{
	for (auto& item : items)
		delete item;
	delete[] lastTwoMousePos;
}


void Scene::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);

	QStyleOption o;
	o.initFrom(this);
	style()->drawPrimitive(QStyle::PE_Widget, &o, &painter, this);

	for (Item* it : items)
	{
		it->draw(painter);
		//it->drawBoundingBox(painter);
	}
}

void Scene::draw()
{
	update();
}

void Scene::addItem(Item* it)
{
	items.push_back(it);
}

std::list<Point>& Scene::getLastMouseClicks()
{
	return mouseClicks;
}

Point* Scene::getLastTwoMousePositions()
{
	return lastTwoMousePos;
}

void Scene::mousePressEvent(QMouseEvent* event)
{
	Point clickPos(event->position().x(), event->position().y());
	mouseClicks.push_front(clickPos);
	lastTwoMousePos[0] = clickPos;
	emit mousePressed();
}

void Scene::mouseMoveEvent(QMouseEvent* event)
{
	Point mousePos(event->position().x(), event->position().y());

	// part for moving, path drawing etc.
	if (event->buttons() == Qt::LeftButton)
	{
		lastTwoMousePos[1] = lastTwoMousePos[0];
		lastTwoMousePos[0] = mousePos;
		emit mouseMoved();
	}
	// end
	
	// part for "checking" an Item on Scene:
	if (event->buttons() != Qt::LeftButton && event->buttons() != Qt::RightButton)
	{
		Item* newlySelectedItem = getItemAtPosition(mousePos);
		if (newlySelectedItem != nullptr) newlySelectedItem = newlySelectedItem->undecorate(true);
		if (newlySelectedItem != selectedItem)
		{
			for (int i = 0; i < items.size(); i++)
			{
				if (items[i]->undecorate(true) == selectedItem)
				{ // UNDECORATING
					items[i]->undecorate();
					delete items[i];
					items[i] = selectedItem;
				} // DECORATING
				if (items[i] == newlySelectedItem)
					items[i] = new SelectionDecorator(newlySelectedItem);
			}
			selectedItem = newlySelectedItem;
			draw();
		}
	}
	// end
}

Item* Scene::getItemAtPosition(Point pos, Item* toIgnoreItems, int length)
{// item found at position is automatically taken to the beginning of the item list
 // didn't want to change vector to list but i know i should
	//for (auto it = items.begin(); it != items.end(); ++it)
	//{
	//	bool ignore = false;
	//	for (int i = 0; i < length && !ignore; i++)
	//		if (*it == toIgnoreItems + i)
	//			ignore = true;

	//	if (!ignore && isInside((*it)->getBoundingBox(), pos))
	//	{
	//		Item* found = *it;
	//		if (where != 0) items.erase(it);
	//		if (where == -1) items.insert(items.begin(), found);
	//		if (where == 1) items.push_back(found);
	//		return found;
	//	}
	//}
	//return nullptr;
	for (auto item : items)
	{
		bool ignore = false;
		for (int i = 0; i < length && !ignore; i++)
			if (item == toIgnoreItems + i)
				ignore = true;

		if (!ignore && isInside(item->getBoundingBox(), pos))
			return item;
	}
	return nullptr;
}

bool Scene::isInside(Point* bbox, Point p)
{
	return p.getX() >= bbox[0].getX() && p.getX() <= bbox[2].getX() && p.getY() >= bbox[0].getY() && p.getY() <= bbox[2].getY();
}

bool Scene::eraseItem(Item* item)
{
	if (item == nullptr) return false;
	for (auto i = items.begin(); i != items.end(); ++i)
	{
		if (*i == item)
		{
			//delete* i; if you want to delete it - you have to do it OUTSIDE the method
			items.erase(i); // i - INVALIDATED ITERATOR
			//selectedItem = nullptr;
			return true;
		}
	}
	return false;
}
