#include "balls.h"
#include "qgraphicsitem.h"

Balls::Balls(QWidget *parent)
    : QWidget(parent),  scene(new QGraphicsScene(this)),
    view(new QGraphicsView(scene, this)), ellipseItem(nullptr){

    view->setScene(scene);
    view->show();
    ellipseItem = new QGraphicsEllipseItem(0, 0, 100, 100);
    scene->addItem(ellipseItem);
}




