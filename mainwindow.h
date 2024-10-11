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
    void removeObjectsOnWindow();

    //Starting properties
    QVector<int> generatorUniqueNum();
    void updateRuleGame();
    void startColorBall();
    void startIndexBox();
    void enableElements();

    //Buttons
    void startButton_clicked();
    void checkButton_clicked();

    void colorSelecting_activated(int index);
    void colorSelecting_2_activated(int index);
    void colorSelecting_3_activated(int index);
    void colorSelecting_4_activated(int index);
    void colorSelecting_5_activated(int index);

private slots:

    void on_changeHard_checkableChanged(bool checkable);

private:

    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
