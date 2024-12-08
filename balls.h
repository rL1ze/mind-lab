#ifndef BALLS_H
#define BALLS_H

#include <QGraphicsView>
#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <Qt>
#include <QGraphicsScene>
#include <QVBoxLayout>

class Balls
{
private:  
    QGraphicsScene *scene;

public:
    int x, y;

    QGraphicsEllipseItem *ellipseItem;
    QGraphicsView *view;

    explicit Balls(int x = 0, int y = 0);

    static void colorSelecting(int index, Balls *ball);

protected:

};

#endif // BALLS_H
