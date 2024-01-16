#include "Scene.h"
#include "Singleton.h"

Scene::Scene(QWidget* parent = nullptr)
	: QWidget(parent)
	, showBoundingBox(false)
	, lastTwoMousePos(new Point[2])
{
	//setObjectName("MyScene");
	//QPalette pal = QPalette();
	//// Qt::black / "#000000" / "black"
	//pal.setColor(QPalette::Window, Qt::black);
	//setAutoFillBackground(true);
	//setPalette(pal);
	//show();

	// SINGLETON INITIALIZATION
	Singleton<Item>::setItemsOnScene(items);

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
		it->draw(painter, showBoundingBox);
		//it->drawBoundingBox(painter);
	}

	//TEST
	//QPen pen;
	//pen.setColor(Qt::green);
	//pen.setWidth(5);
	//painter.setPen(pen);
	//painter.drawRect(0, 0, 50, 50);
	QString text = "Hello World!";
	//painter.drawText(QPoint(0, 80), "Hello World!");
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
	Point clickPos(event->position().x(), event->position().y());
	lastTwoMousePos[1] = lastTwoMousePos[0];
	lastTwoMousePos[0] = clickPos;
	emit mouseMoved();
}

Item* Scene::getItemAtPosition(Point pos, Item* toIgnoreItems, int length)
{
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
			return true;
		}
	}
	return false;
}

void Scene::setShowBoundingBox(bool show)
{
	showBoundingBox = show;
}

