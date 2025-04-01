#include "ballsview.h"

BallsView::BallsView() {}

void BallsView::colorSelecting(int index, Balls *ball){
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
