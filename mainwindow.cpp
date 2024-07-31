#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "balls.h"
#include "qgraphicsitem.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow),
    ball1(nullptr), ball2(nullptr), ball3(nullptr), targetColor1(0), targetColor2(0),targetColor3(0)
{
    ui->setupUi(this);

    ball1 = new Balls(this);
    ball1->view->setGeometry(ui->frame->geometry());  // Устанавливаем размер и положение в соответствии с QFrame
    ball1->view->setParent(ui->frame);  // Устанавливаем родительский виджет
    ball2 = new Balls(this);
    ball2->view->setGeometry(ui->frame_2->geometry());
    ball2->view->setParent(ui->frame_2);
    ball3 = new Balls(this);
    ball3->view->setGeometry(ui->frame_3->geometry());
    ball3->view->setParent(ui->frame_3);

    connect(ui->colorSelecting, &QComboBox::activated, this, &MainWindow::on_colorSelecting_activated);
    connect(ui->colorSelecting_2, &QComboBox::activated, this, &MainWindow::on_colorSelecting_2_activated);
    connect(ui->colorSelecting_3, &QComboBox::activated, this, &MainWindow::on_colorSelecting_3_activated);
    connect(ui->newLvlButton, &QPushButton::clicked, this, &MainWindow::on_newLvlButton_clicked);

    on_newLvlButton_clicked();

    setFixedSize(size());
    setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);
}

MainWindow::~MainWindow()
{
   delete ui;
   delete ball1;
   delete ball2;
   delete ball3;
}

int MainWindow::uniqueNum(int num, int num2, int num3){
    std::uniform_int_distribution<int> distribution(0, 2);
    while (num == num2 || num == num3) {
        num = distribution(*QRandomGenerator::global());
    }
    return num;
}

bool MainWindow::isUnique(int num, int num2, int num3){
    if(num == num2 || num == num3)
        return true;
    else
        return false;
}

QString MainWindow::textColorBall(int randColor){
    switch(randColor){
    case 0:
        return "синий";
        break;
    case 1:
        return "красный";
        break;
    case 2:
        return "жёлтый";
        break;
    }
}

void MainWindow::on_colorSelecting(int index, Balls *ball){
    QColor color;
    switch (index) {
    case 0:
        color = Qt::blue;
        break;
    case 1:
        color = Qt::red;
        break;
    case 2:
        color = Qt::yellow;
        break;
    default:
        return;
    }
    ball->ellipseItem->setBrush(color);
}

void MainWindow::on_checkButton_clicked()
{
    if(targetColor1 == ui->colorSelecting->currentIndex()){
        if(targetColor2 == ui->colorSelecting_2->currentIndex()){
            if(targetColor3 == ui->colorSelecting_3->currentIndex()){
                QMessageBox::information(this, "Оповещение!", "Верно!");
                return;
            }
        }
    }
    QMessageBox::information(this, "Оповещение!", "Неверно!");
}

void MainWindow::on_newLvlButton_clicked()
{
    ui->colorSelecting->setCurrentIndex(-1);
    ui->colorSelecting_2->setCurrentIndex(-1);
    ui->colorSelecting_3->setCurrentIndex(-1);

    ball1->ellipseItem->setBrush(Qt::transparent);
    ball2->ellipseItem->setBrush(Qt::transparent);
    ball3->ellipseItem->setBrush(Qt::transparent);

    std::uniform_int_distribution<int> distribution(0, 2);
    targetColor1 = distribution(*QRandomGenerator::global());
    //qDebug() << targetColor1;
    targetColor2 = distribution(*QRandomGenerator::global());
    //qDebug() << targetColor2;
    targetColor3 = distribution(*QRandomGenerator::global());
    //qDebug() << targetColor3;
    //qDebug() << Qt::endl;
    if(isUnique(targetColor1, targetColor2, targetColor3)){
        targetColor1 = uniqueNum(targetColor1, targetColor2, targetColor3);
    }
    if(isUnique(targetColor2, targetColor1, targetColor3)){
        targetColor2 = uniqueNum(targetColor2, targetColor1, targetColor3);
    }
    if(isUnique(targetColor3, targetColor1, targetColor2)){
        targetColor3 = uniqueNum(targetColor3, targetColor1, targetColor2);
    }

    //qDebug() << targetColor1;
    //qDebug() << targetColor2;
    //qDebug() << targetColor3;

    QString startStatementText = "Если первый шар не ";
    startStatementText += textColorBall(targetColor3);
    startStatementText += ", а второй ";
    startStatementText += textColorBall(targetColor2);
    ui->ruleGame->setText(startStatementText);
}

void MainWindow::on_colorSelecting_activated(int index)
{
    on_colorSelecting(index, ball1);
}

void MainWindow::on_colorSelecting_2_activated(int index)
{
    on_colorSelecting(index, ball2);
}

void MainWindow::on_colorSelecting_3_activated(int index)
{
    on_colorSelecting(index, ball3);
}

