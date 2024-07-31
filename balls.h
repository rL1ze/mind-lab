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
    int pos{};
    QGraphicsEllipseItem *ellipseItem;
    QGraphicsView *view;
    explicit Balls(QWidget *parent = nullptr);
protected:
};

#endif // BALLS_H
