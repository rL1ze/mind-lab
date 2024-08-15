#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "balls.h"
#include <QMainWindow>
#include <QMessageBox>
#include <QRandomGenerator64>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:

    QString textColorBall(int Index);

    //Setup balls
    void setupBall(Balls *ball, QFrame *frame, int x, int y);

    //Starting properties
    QVector<int> generatorUniqueNum(int targetSize);
    void updateRuleGame();
    void startColorBall();
    void startIndexBox();

    //Buttons
    void on_newLvlButton_clicked();
    void on_checkButton_clicked();

    //Change color of the balls
    void on_colorSelecting(int index, Balls *ball);

    void on_colorSelecting_activated(int index);
    void on_colorSelecting_2_activated(int index);
    void on_colorSelecting_3_activated(int index);

private:

    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
