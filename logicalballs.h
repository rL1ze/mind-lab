#ifndef LOGICALBALLS_H
#define LOGICALBALLS_H

#include "balls.h"
#include <QMainWindow>
#include <QMessageBox>
#include <QRandomGenerator64>

namespace Ui {
class LogicalBalls;
}

class LogicalBalls : public QMainWindow
{
    Q_OBJECT

public:
    explicit LogicalBalls(QWidget *parent = nullptr);
    ~LogicalBalls();
public slots:

    QString textColorBall(int Index);

    //Setup balls
    void setupBall(Balls *ball, QFrame *frame, int x, int y);
    void removeObjects();
    void createObjects();

    //Starting properties
    QVector<int> generatorUniqueNum();
    void updateRuleGame();
    void startColorBall();
    void startIndexBox();
    void enableElements();

    //Buttons
    void startButton_clicked();
    void checkButton_clicked();

    void colorSelecting(int ballIndex, int colorIndex);

private slots:

    void on_changeHard_checkableChanged(bool checkabled);

private:
    Ui::LogicalBalls *ui;
};

#endif // LOGICALBALLS_H
