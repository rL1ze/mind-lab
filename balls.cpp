#include "balls.h"
#include "qgraphicsitem.h"

Balls::Balls(int x, int y)
    : scene(new QGraphicsScene()),
    view(new QGraphicsView(scene)), ellipseItem(nullptr), x(x), y(y){

    view->setScene(scene);
    ellipseItem = new QGraphicsEllipseItem(0, 0, x, y);
    scene->addItem(ellipseItem);
}

void Balls::colorSelecting(int index, Balls *ball){
    QColor color;
    switch (index) {
    case 0:
        color = Qt::blue;
        break;
    case 1:
        color = Qt::red;
        break;
    case 2:
        color = Qt::yellow;
        break;
    case 3:
        color = Qt::green;
        break;
    case 4:
        color = QColorConstants::Svg::purple;
        break;
    default:
        color = Qt::transparent;
        return;
    }
    ball->ellipseItem->setBrush(color);
}







