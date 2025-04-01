#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

    void keyPressEvent(QKeyEvent *event) override;

private slots:

    void on_buttonLogicalGames_clicked();

    void on_startButtonSuduoku_clicked();

    void on_startButtonLogicalBalls_clicked();

    void on_startButtonNoPeek_clicked();

private:

    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
