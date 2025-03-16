#ifndef BALLS_H
#define BALLS_H

#include <QGraphicsView>
#include <QGraphicsScene>

class Balls
{
private:

    int x, y;

public:
    QGraphicsScene *scene;
    QGraphicsEllipseItem *ellipseItem;
    QGraphicsView *view;

    Balls(int x = 0, int y = 0);
    static void colorSelecting(int index, Balls *ball);

protected:

};

#endif // BALLS_H
