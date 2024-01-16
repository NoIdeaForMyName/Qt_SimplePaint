#include "Qt_SimplePaint.h"
#include <qpainter.h>

#include <iostream>

#include "Circle.h"
#include "ComplexItem.h"
#include "Item.h"
#include "Rect.h"
#include "Segment.h"
#include "TextItem.h"
#include "Triangle.h"
#include "TextParametersSelector.h"
#include <QtWidgets/QApplication>

#include "Path.h"
#include "Spiral.h"
#include "SpiralParametersSelector.h"

Qt_SimplePaint::Qt_SimplePaint(QWidget* parent)
    : QMainWindow(parent)
    , itemType(noItem)
{
    ui.setupUi(this);
    lowerRightScenePoint = Point(ui.SceneWidget_placeholder->width(), ui.SceneWidget_placeholder->height());

    connect(ui.SceneWidget_placeholder, &Scene::mousePressed, this, &Qt_SimplePaint::sceneClicked);
    connect(ui.SceneWidget_placeholder, &Scene::mouseMoved, this, &Qt_SimplePaint::sceneDragged);

    connect(ui.RectButton, &QPushButton::clicked, this, &Qt_SimplePaint::createRectangle);
    connect(ui.CircleButton, &QPushButton::clicked, this, &Qt_SimplePaint::createCircle);
    connect(ui.TriangleButton, &QPushButton::clicked, this, &Qt_SimplePaint::createTriangle);
    connect(ui.PathButton, &QPushButton::clicked, this, &Qt_SimplePaint::createPath);
    connect(ui.SpiralButton, &QPushButton::clicked, this, &Qt_SimplePaint::createSpiral);
    connect(ui.SegmentButton, &QPushButton::clicked, this, &Qt_SimplePaint::createSegment);
    connect(ui.TextItemButton, &QPushButton::clicked, this, &Qt_SimplePaint::createTextItem);
    connect(ui.ComplexItemButton, &QPushButton::clicked, this, &Qt_SimplePaint::createComplexItem);
    connect(ui.MoveButton, &QPushButton::clicked, this, &Qt_SimplePaint::moveItem);
    connect(ui.DeleteButton, &QPushButton::clicked, this, &Qt_SimplePaint::deleteItem);

    connect(ui.Check_BBox, &QCheckBox::stateChanged, this, &Qt_SimplePaint::setShowBoundingBox);

    /*
    Rect* rect = new Rect(Point(20, 20), 20, 20);
    Circle* circle = new Circle(Point(20, 40), 20, true);
    Triangle* triangle = new Triangle(Point(130, 0), Point(60, 20), Point(95, 80), true);
    Segment* segment = new Segment(Point(0, 0), Point(60, 20));

    std::vector<Item*> items = { new Rect(*rect), new Circle(*circle), new Triangle(*triangle), new Segment(*segment)};
    ComplexItem* complexItem = new ComplexItem(items);
    complexItem->translate(Point(130, 130));

    ui.SceneWidget_placeholder->addItem(complexItem);
    ui.SceneWidget_placeholder->addItem(rect);
    ui.SceneWidget_placeholder->addItem(circle);
    ui.SceneWidget_placeholder->addItem(triangle);
    ui.SceneWidget_placeholder->addItem(segment);

    TextItem* textItem = new TextItem(Point(0, 80), "Hello World!", QFont("Arial", 50));
    ui.SceneWidget_placeholder->addItem(textItem);

    ui.SceneWidget_placeholder->draw();
    */
}

Qt_SimplePaint::~Qt_SimplePaint()
{}

void Qt_SimplePaint::createRectangle()
{
    itemType = rectangle;
    ui.SceneWidget_placeholder->getLastMouseClicks().clear();
}

void Qt_SimplePaint::createCircle()
{
    itemType = circle;
    ui.SceneWidget_placeholder->getLastMouseClicks().clear();
}

void Qt_SimplePaint::createTriangle()
{
    itemType = triangle;
    ui.SceneWidget_placeholder->getLastMouseClicks().clear();
}

void Qt_SimplePaint::createPath()
{
    itemType = path;
    ui.SceneWidget_placeholder->getLastMouseClicks().clear();

    currentItem = new Path({ lowerRightScenePoint });
    ui.SceneWidget_placeholder->addItem(currentItem);
}

void Qt_SimplePaint::createSpiral()
{
    SpiralParametersSelector dialog;
    dialog.exec();
    if (dialog.isStored())
    {
        itemType = spiral;
        double a = dialog.getA();
        double b = dialog.getB();
        double start = dialog.getStart();
        double end = dialog.getEnd();
        currentItem = new Spiral(lowerRightScenePoint, a, b, start, end);
        ui.SceneWidget_placeholder->addItem(currentItem);
        ui.SceneWidget_placeholder->getLastMouseClicks().clear();
    }
    else
        itemType = noItem;
}

void Qt_SimplePaint::createSegment()
{
    itemType = segment;
    ui.SceneWidget_placeholder->getLastMouseClicks().clear();
}

void Qt_SimplePaint::createTextItem()
{
    TextParametersSelector dialog;
    dialog.exec();
    if (dialog.isDataStored())
    {
        itemType = textItem;
        QString text = dialog.getText();
        QFont font(dialog.getFont(), dialog.getFontSize());
        currentItem = new TextItem(lowerRightScenePoint, text, font);
        ui.SceneWidget_placeholder->addItem(currentItem);
        ui.SceneWidget_placeholder->getLastMouseClicks().clear();
    }
    else
        itemType = noItem;
}

void Qt_SimplePaint::createComplexItem()
{
    itemType = complexItem;
    ui.SceneWidget_placeholder->getLastMouseClicks().clear();
}

void Qt_SimplePaint::moveItem()
{
    itemType = toMoveItem;
}

void Qt_SimplePaint::deleteItem()
{
    itemType = toDeleteItem;
}

void Qt_SimplePaint::setShowBoundingBox()
{
    ui.SceneWidget_placeholder->setShowBoundingBox(ui.Check_BBox->checkState());
    ui.SceneWidget_placeholder->draw();
}

void Qt_SimplePaint::sceneClicked()
{
    std::list<Point>& lastClicks = ui.SceneWidget_placeholder->getLastMouseClicks();

    switch (itemType)
    {

    case noItem:
    {
        lastClicks.clear();
    }
    break;

    case toMoveItem:
    {
        currentItem = ui.SceneWidget_placeholder->getItemAtPosition(lastClicks.front());
    }
    break;

    case toDeleteItem:
    {
        Item* toDelete = ui.SceneWidget_placeholder->getItemAtPosition(lastClicks.front());
        ui.SceneWidget_placeholder->eraseItem(toDelete);
        delete toDelete;
        ui.SceneWidget_placeholder->draw();
    }
    break;

    case rectangle:
    {
        if (lastClicks.size() == 2)
        {
            Point click_1 = lastClicks.front(); lastClicks.pop_front();
            Point click_2 = lastClicks.front(); lastClicks.pop_front();
            int width = abs(click_2.getX() - click_1.getX());
            int height = abs(click_2.getY() - click_1.getY());
            Point position = click_1;
            if (click_2.getX() < position.getX()) position.setX(click_2.getX());
            if (click_2.getY() < position.getY()) position.setY(click_2.getY());

            ui.SceneWidget_placeholder->addItem(new Rect(position, width,
                height, ui.Check_Filled->checkState()));
            ui.SceneWidget_placeholder->draw();
        }
    }
    break;

    case circle:
    {
        if (lastClicks.size() == 2)
        {
            Point position = lastClicks.back();
            Point downRight = lastClicks.front();
            lastClicks.clear();
            int dx = downRight.getX() - position.getX();
            int dy = downRight.getY() - position.getY();
            int r;
            if (abs(dx) > abs(dy)) r = dx / 2;
            else r = dy / 2;

            if (r < 0) r *= -1;
            if (dx < 0) position.shift(Point(-2 * r, 0));
            if (dy < 0) position.shift(Point(0, -2 * r));

            ui.SceneWidget_placeholder->addItem(new Circle(position, r, ui.Check_Filled->checkState()));
            ui.SceneWidget_placeholder->draw();
        }
    }
    break;

    case triangle:
    {
        if (lastClicks.size() == 3)
        {
            Point p1 = lastClicks.back(); lastClicks.pop_back();
            Point p2 = lastClicks.back();
            Point p3 = lastClicks.front();
            lastClicks.clear();
            ui.SceneWidget_placeholder->addItem(new Triangle(p1, p2, p3, ui.Check_Filled->checkState()));
            ui.SceneWidget_placeholder->draw();
        }
    }
    break;

    case path:
    {
        if (lastClicks.size() == 1 && currentItem->getPosition().getX() == lowerRightScenePoint.getX() && currentItem->getPosition().getY() == lowerRightScenePoint.getY())
        {
            currentItem->translate(Point(lastClicks.front().getX() - lowerRightScenePoint.getX(), lastClicks.front().getY() - lowerRightScenePoint.getY()));
            lastClicks.clear();
        }
    }
    break;

    case spiral:
    {
        if (lastClicks.size() == 1 && currentItem != nullptr)
        {
            currentItem->translate(Point(lastClicks.front().getX() - lowerRightScenePoint.getX(), lastClicks.front().getY() - lowerRightScenePoint.getY()));
            lastClicks.clear();
            ui.SceneWidget_placeholder->draw();
            currentItem = nullptr;
        }
    }
    break;

    case segment:
    {
        if (lastClicks.size() == 2)
        {
            Point start = lastClicks.back();
            Point end = lastClicks.front();
            lastClicks.clear();

            ui.SceneWidget_placeholder->addItem(new Segment(start, end));
            ui.SceneWidget_placeholder->draw();
        }
    }
    break;

    case textItem:
    {
        if (lastClicks.size() == 1 && currentItem != nullptr)
        {
            //ui.SceneWidget_placeholder->addItem(new TextItem(lastClicks.front(), textItem_text, textItem_font));
            currentItem->translate(Point(lastClicks.front().getX() - lowerRightScenePoint.getX(), lastClicks.front().getY() - lowerRightScenePoint.getY()));
            //ui.SceneWidget_placeholder->addItem(currentItem);
            lastClicks.clear();
            ui.SceneWidget_placeholder->draw();
            currentItem = nullptr;
        }
    }
    break;

    case complexItem:
    {
        if (lastClicks.size() == 2)
        {
            Item* fst = ui.SceneWidget_placeholder->getItemAtPosition(lastClicks.front());
            if (fst == nullptr)
            {
                lastClicks.clear();
            }
            else
            {
                Item* nd = ui.SceneWidget_placeholder->getItemAtPosition(lastClicks.back(), fst);
                lastClicks.clear();
                if (nd != nullptr && nd != fst)
                {
                    std::vector<Item*> items = { fst, nd };
                    ui.SceneWidget_placeholder->addItem(new ComplexItem(items));
                    ui.SceneWidget_placeholder->eraseItem(fst);
                    ui.SceneWidget_placeholder->eraseItem(nd);
                    ui.SceneWidget_placeholder->draw();
                }
            }
        }
    }
    break;

    }
}

void Qt_SimplePaint::sceneDragged()
{
    if (itemType == toMoveItem && currentItem != nullptr)
    {
        Point* lastTwo = ui.SceneWidget_placeholder->getLastTwoMousePositions();
        Point shift(lastTwo[0].getX() - lastTwo[1].getX(), lastTwo[0].getY() - lastTwo[1].getY());
        currentItem->translate(shift);
        ui.SceneWidget_placeholder->draw();
    }

    if (itemType == path)
    {
        Point lastMousePos = ui.SceneWidget_placeholder->getLastTwoMousePositions()[0];
        static_cast<Path*>(currentItem)->addPoint(lastMousePos);
        ui.SceneWidget_placeholder->draw();
    }
}
