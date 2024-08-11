#ifndef BALLS_H
#define BALLS_H

#include <QGraphicsView>
#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <Qt>
#include <QGraphicsScene>

class Balls : public QWidget
{
    Q_OBJECT

private:
    QGraphicsScene *scene;

public:

    QGraphicsEllipseItem *ellipseItem;
    QGraphicsView *view;
    explicit Balls(QWidget *parent = nullptr, int x = 0, int y = 0);
protected:

};

#endif // BALLS_H
