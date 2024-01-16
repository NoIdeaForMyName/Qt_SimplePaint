#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Qt_SimplePaint.h"
#include "Scene.h"

#include <QVBoxLayout>
#include <QFrame>

enum ItemType
{
    noItem,
    toMoveItem,
    toDeleteItem,
    rectangle,
    circle,
    triangle,
    path,
    spiral,
    segment,
    textItem,
    complexItem
};

class Qt_SimplePaint : public QMainWindow
{
    Q_OBJECT

public:
    Qt_SimplePaint(QWidget* parent = nullptr);
    ~Qt_SimplePaint();

    //virtual void paintEvent(QPaintEvent* event) override;

public slots:
    void sceneClicked();
    void sceneDragged();

    void createRectangle();
    void createCircle();
    void createTriangle();
    void createPath();
    void createSpiral();
    void createSegment();
    void createTextItem();
    void createComplexItem();
    void moveItem();
    void deleteItem();

    //void setShowBoundingBox();

private:
    Ui::Qt_SimplePaintClass ui;
    ItemType itemType;
    Point lowerRightScenePoint;
    Item* currentItem;
};
