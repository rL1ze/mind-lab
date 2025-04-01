#ifndef LOGICALBALLS_H
#define LOGICALBALLS_H

#include "balls.h"
#include <QMainWindow>
#include <QMessageBox>
#include <QRandomGenerator64>
#include <qcombobox.h>

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

    void closeEvent(QCloseEvent *event) override;
    void colorSelecting(int ballIndex, int colorIndex);

signals:
    void close();
private slots:
    void on_changeHard_checkableChanged(bool checkabled);

private:
    Balls *ball1, *ball2, *ball3, *ball4, *ball5;
    QVector<int> uniqueNum{0, 1, 2, 3, 4};
    QVector<int> uniqueNumFor3{0, 1, 2};
    QVector<int> targetUniqueNum;
    QVector<int> targetIndexs;
    bool choiceOfAmountBall;
    QRandomGenerator *generator = QRandomGenerator::global();
    QComboBox *colorSelecting_4;
    QComboBox *colorSelecting_5;

    Ui::LogicalBalls *ui;
};

#endif // LOGICALBALLS_H
