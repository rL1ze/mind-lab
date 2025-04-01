#ifndef NOPEEK_H
#define NOPEEK_H

#include <QMainWindow>
#include <qpushbutton.h>

namespace Ui {
class NoPeek;
}

class NoPeek : public QMainWindow
{
    Q_OBJECT

public:
    explicit NoPeek(QWidget *parent = nullptr);
    ~NoPeek();

    void selectPos(int row = 0, int col = 0);
    void generateSpot();
    void showRightAnswer();
    void blockField();
    void revialField();
    void createField();

    void closeEvent(QCloseEvent *event) override;
signals:
    void close();
private:
    QVector<QVector<QPushButton*>> Field;
    QVector<QVector<QPushButton*>> rightField;
    QVector<QVector<QPushButton*>> targetField;

    int counterWrongs = 0;
    bool eventFilter(QObject *object, QEvent *event) override;

    Ui::NoPeek *ui;
};

#endif // NOPEEK_H
