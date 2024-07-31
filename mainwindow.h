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

private slots:

    QString textColorBall(int Index);

    int uniqueNum(int num, int num2, int num3);
    bool isUnique(int num, int num2, int num3);

    void setupBall(Balls *ball, QFrame *frame);
    void engineStartValues();
    void updateRuleGameText();
    void on_newLvlButton_clicked();
    void on_checkButton_clicked();

    void on_colorSelecting(int index, Balls *ball);

    void on_colorSelecting_activated(int index);
    void on_colorSelecting_2_activated(int index);
    void on_colorSelecting_3_activated(int index);

private:

    Ui::MainWindow *ui;
    Balls *ball1;
    Balls *ball2;
    Balls *ball3;
    int targetColor1;
    int targetColor2;
    int targetColor3;
    QRandomGenerator *engine;
    std::uniform_int_distribution<int> distribution;
};
#endif // MAINWINDOW_H
