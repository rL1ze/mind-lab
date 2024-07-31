#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "balls.h"
#include "qgraphicsitem.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow),
    ball1(new Balls(this)), ball2(new Balls(this)), ball3(new Balls(this)), targetColor1(0), targetColor2(0),targetColor3(0),generator(QRandomGenerator::global()),distribution(0,2)
{
    ui->setupUi(this);

    setupBall(ball1, ui->frame_1);
    setupBall(ball2, ui->frame_2);
    setupBall(ball3, ui->frame_3);

    connect(ui->colorSelecting, &QComboBox::activated, this, &MainWindow::on_colorSelecting_activated);
    connect(ui->colorSelecting_2, &QComboBox::activated, this, &MainWindow::on_colorSelecting_2_activated);
    connect(ui->colorSelecting_3, &QComboBox::activated, this, &MainWindow::on_colorSelecting_3_activated);

    updateRuleGameText();
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

// Устанавливаем размер и положение в соответствии с QFrame и станавливаем родительский виджет
void MainWindow::setupBall(Balls *ball, QFrame *frame){
    ball->view->setGeometry(frame->geometry());
    ball->view->setParent(frame);
}

void MainWindow::startIndexBox(){
    ui->colorSelecting->setCurrentIndex(-1);
    ui->colorSelecting_2->setCurrentIndex(-1);
    ui->colorSelecting_3->setCurrentIndex(-1);
}

void MainWindow::startColorBall(){
    ball1->ellipseItem->setBrush(Qt::transparent);
    ball2->ellipseItem->setBrush(Qt::transparent);
    ball3->ellipseItem->setBrush(Qt::transparent);
}

void MainWindow::generatorColors(){
    targetColor1 = distribution(*generator);
    targetColor2 = distribution(*generator);
    targetColor3 = distribution(*generator);
}

int MainWindow::uniqueNum(int num, int num2, int num3){
    if(isUnique(num, num2, num3)){
        while (num == num2 || num == num3) {
            num = distribution(*generator);
        }
    }
    return num;
}

bool MainWindow::isUnique(int num, int num2, int num3){
    if(num == num2 || num == num3){
        return true;
    }
    else{
        return false;
    }
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
        color = Qt::transparent;
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

void MainWindow::updateRuleGameText()
{
    QString startStatementText = "Если первый шар не ";
    startStatementText += textColorBall(targetColor3);
    startStatementText += ", а второй ";
    startStatementText += textColorBall(targetColor2);
    ui->ruleGame->setText(startStatementText);
}

void MainWindow::on_newLvlButton_clicked()
{
    generatorColors();
    startIndexBox();
    startColorBall();

    targetColor1 = uniqueNum(targetColor1, targetColor2, targetColor3);
    targetColor2 = uniqueNum(targetColor2, targetColor1, targetColor3);
    targetColor3 = uniqueNum(targetColor3, targetColor2, targetColor1);

    updateRuleGameText();
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

