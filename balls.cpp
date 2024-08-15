#include "balls.h"
#include "mainwindow.h"
#include "qgraphicsitem.h"

Balls::Balls(QWidget *parent, int x, int y)
    : QWidget(parent),  scene(new QGraphicsScene()),
    view(new QGraphicsView(scene)), ellipseItem(nullptr), x(x), y(y){

    view->setScene(scene);
    view->show();
    ellipseItem = new QGraphicsEllipseItem(0, 0, x, y);
    scene->addItem(ellipseItem);
}



