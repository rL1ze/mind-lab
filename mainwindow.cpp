#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "balls.h"
#include "qgraphicsitem.h"

Balls *ball1, *ball2, *ball3, *ball4, *ball5;
QVector<int> uniqueNumbers{0, 1, 2, 3, 4};
QRandomGenerator generator = *QRandomGenerator::global();

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ball1 = new Balls(100, 100);
    setupBall(ball1, ui->frame_1, 200, 200);
    ball2 = new Balls(100, 100);
    setupBall(ball2, ui->frame_2, 200, 200);
    ball3 = new Balls(100, 100);
    setupBall(ball3, ui->frame_3, 200, 200);

    connect(ui->colorSelecting, &QComboBox::activated, this, &MainWindow::colorSelecting_activated);
    connect(ui->colorSelecting_2, &QComboBox::activated, this, &MainWindow::colorSelecting_2_activated);
    connect(ui->colorSelecting_3, &QComboBox::activated, this, &MainWindow::colorSelecting_3_activated);
    connect(ui->checkBox, &QCheckBox::clicked, this, &MainWindow::checkBox_clicked);

    newLvlButton_clicked();

    setFixedSize(size());
    setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Устанавливаем размер и положение в соответствии с QFrame и станавливаем родительский виджет
void MainWindow::setupBall(Balls *ball, QFrame *frame, int x, int y){
    // Установка фиксированных размеров для фрейма
    frame->setFixedSize(x, y);

    // Установка QGraphicsView как дочернего виджета фрейма
    ball->view->setParent(frame);

    ball->view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ball->view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Использование layout для размещения QGraphicsView внутри фрейма
    QVBoxLayout *layout = new QVBoxLayout(frame);
    layout->addWidget(ball->view);
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

QVector<int> MainWindow::generatorUniqueNum(int targetSize){
    if(targetSize == 5){
        std::shuffle(uniqueNumbers.begin(), uniqueNumbers.end(), generator);
        return uniqueNumbers;
    }
    else{
        std::shuffle(uniqueNumbers.begin(), uniqueNumbers.end() - 2, generator);
        return uniqueNumbers.mid(0, 3);
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
    case 3:
        return "зелённый";
        break;
    case 4:
        return "фиолетовый";
        break;
    }
}

void MainWindow::checkButton_clicked()
{
    QVector<int> v;
    v.push_back(ui->colorSelecting->currentIndex());
    v.push_back(ui->colorSelecting_2->currentIndex());
    v.push_back(ui->colorSelecting_3->currentIndex());

    if(v == uniqueNumbers.mid(0, 3)){
        QMessageBox::information(this, "Оповещение!", "Верно!");
    }
    else if(v == uniqueNumbers.mid(2) ){
        QMessageBox::information(this, "Оповещение!", "Верно!");
    }
    else{
        QMessageBox::information(this, "Оповещение!", "Неверно!");
    }
}

void MainWindow::updateRuleGame()
{
    QString startStatementText = "Если первый шар не ";
    startStatementText += textColorBall(uniqueNumbers[2]);
    startStatementText += ", а второй ";
    startStatementText += textColorBall(uniqueNumbers[1]);
    ui->ruleGame->setText(startStatementText);
}

void MainWindow::newLvlButton_clicked()
{
    startIndexBox();
    startColorBall();
    QVector<int> uniqueNumbers = generatorUniqueNum(3);
    qDebug() << uniqueNumbers;

    updateRuleGame();
}

void MainWindow::colorSelecting_activated(int index)
{
    Balls::colorSelecting(index, ball1);
}

void MainWindow::colorSelecting_2_activated(int index)
{
    Balls::colorSelecting(index, ball2);
}

void MainWindow::colorSelecting_3_activated(int index)
{
    Balls::colorSelecting(index, ball3);
}

void MainWindow::colorSelecting_4_activated(int index)
{
    Balls::colorSelecting(index, ball4);
}

void MainWindow::colorSelecting_5_activated(int index)
{
    Balls::colorSelecting(index, ball5);
}

void MainWindow::checkBox_clicked(bool checked)
{
    if(checked == true){
        startIndexBox();
        startColorBall();
        ball1->ellipseItem->setRect(14, 15, 50, 50);
        ball2->ellipseItem->setRect(14, 15, 50, 50);
        ball3->ellipseItem->setRect(14, 15, 50, 50);

        ui->frame_1->setFixedSize(100, 100);
        ui->frame_2->setFixedSize(100, 100);
        ui->frame_3->setFixedSize(100, 100);

        QFrame *frame_4 = new QFrame();
        QFrame *frame_5 = new QFrame();
        ui->gridLayout->addWidget(frame_4, 0, 3);
        ui->gridLayout->addWidget(frame_5, 0, 4);

        ball4 = new Balls(50, 50);
        setupBall(ball4, frame_4, 100, 100);
        ball5 = new Balls(50, 50);
        setupBall(ball5, frame_5, 100, 100);

        QComboBox *colorSelecting_4 = new QComboBox();
        QComboBox *colorSelecting_5 = new QComboBox();

        connect(colorSelecting_4, &QComboBox::activated, this, &MainWindow::colorSelecting_4_activated);
        connect(colorSelecting_5, &QComboBox::activated, this, &MainWindow::colorSelecting_5_activated);

        QStringList colorSlectingList{"Синий", "Красный", "Жёлтый", "Зелённый", "Фиолетовый"};
        ui->colorSelecting->addItems(colorSlectingList.mid(3));
        ui->colorSelecting_2->addItems(colorSlectingList.mid(3));
        ui->colorSelecting_3->addItems(colorSlectingList.mid(3));
        colorSelecting_4->addItems(colorSlectingList);
        colorSelecting_5->addItems(colorSlectingList);

        colorSelecting_4->setCurrentIndex(-1);
        colorSelecting_5->setCurrentIndex(-1);

        ui->gridLayout->addWidget(colorSelecting_4, 2, 3);
        ui->gridLayout->addWidget(colorSelecting_5, 2, 4);

        QLabel *selectColorText_4 = new QLabel("Выберите цвет:");
        QLabel *selectColorText_5 = new QLabel("Выберите цвет:");

        ui->gridLayout->addWidget(selectColorText_4, 1, 3);
        ui->gridLayout->addWidget(selectColorText_5, 1, 4);
    }
    else if(checked == false){
        startIndexBox();
        startColorBall();
        removeExtraBalls();

        ball1->ellipseItem->setRect(0, 0, 100, 100);
        ball2->ellipseItem->setRect(0, 0, 100, 100);
        ball3->ellipseItem->setRect(0, 0, 100, 100);

        ui->frame_1->setFixedSize(200, 200);
        ui->frame_2->setFixedSize(200, 200);
        ui->frame_3->setFixedSize(200, 200);

        ui->colorSelecting->removeItem(3);
        ui->colorSelecting->removeItem(3);

        ui->colorSelecting_2->removeItem(3);
        ui->colorSelecting_2->removeItem(3);

        ui->colorSelecting_3->removeItem(3);
        ui->colorSelecting_3->removeItem(3);
    }
}

void MainWindow::removeExtraBalls() {
    delete ball4->ellipseItem;
    delete ball5->ellipseItem;

    delete ui->gridLayout->itemAtPosition(1,3)->widget();
    delete ui->gridLayout->itemAtPosition(1,4)->widget();
    delete ui->gridLayout->itemAtPosition(0,3)->widget();
    delete ui->gridLayout->itemAtPosition(0,4)->widget();
    delete ui->gridLayout->itemAtPosition(2,3)->widget();
    delete ui->gridLayout->itemAtPosition(2,4)->widget();
}



