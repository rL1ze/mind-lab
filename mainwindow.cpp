#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "balls.h"
#include "qgraphicsitem.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow),
    ball1(new Balls(this, 50, 50)), ball2(new Balls(this, 50, 50)), ball3(new Balls(this, 50, 50)), uniqueNumbers(QVector<int>{0, 1, 2, 3, 4}), generator(QRandomGenerator::global())
{
    ui->setupUi(this);

    ui->frame_1->setFixedSize(150, 150);
    setupBall(ball1, ui->frame_1);
    ui->frame_2->setFixedSize(150, 150);
    setupBall(ball2, ui->frame_2);
    ui->frame_3->setFixedSize(150, 150);
    setupBall(ball3, ui->frame_3);

    connect(ui->colorSelecting, &QComboBox::activated, this, &MainWindow::on_colorSelecting_activated);
    connect(ui->colorSelecting_2, &QComboBox::activated, this, &MainWindow::on_colorSelecting_2_activated);
    connect(ui->colorSelecting_3, &QComboBox::activated, this, &MainWindow::on_colorSelecting_3_activated);

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
    QComboBox *colorSelecting_4 = new QComboBox();
    ui->gridLayout->addWidget(colorSelecting_4, 9, 5);

    QFrame *frame = new QFrame(this);

    // Настраиваем фрейм
    frame->setFrameShape(QFrame::StyledPanel);
    frame->setFrameShadow(QFrame::Raised);
    frame->setFixedSize(150, 150);
    //ui->gridLayout->addWidget(frame);
    //setupBall(ball3, frame);
}

void MainWindow::startColorBall(){
    ball1->ellipseItem->setBrush(Qt::transparent);
    ball2->ellipseItem->setBrush(Qt::transparent);
    ball3->ellipseItem->setBrush(Qt::transparent);
}

QVector<int> MainWindow::generatorUniqueNum(int option){
    if(option == 1){
        uniqueNumbers.resize(3);
        std::shuffle(uniqueNumbers.begin(), uniqueNumbers.end(), *generator);
        return uniqueNumbers;
    }
    else if(option == 2){
        uniqueNumbers.resize(5);
        std::shuffle(uniqueNumbers.begin(), uniqueNumbers.end(), *generator);
        return uniqueNumbers;
    }
    std::shuffle(uniqueNumbers.begin(), uniqueNumbers.end(), *generator);
    return uniqueNumbers;
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
    case 3:
        color = Qt::green;
        break;
    case 4:
        color = QColorConstants::Svg::purple;
        break;
    default:
        color = Qt::transparent;
        return;
    }
    ball->ellipseItem->setBrush(color);
}

void MainWindow::on_checkButton_clicked()
{
    QVector<int> v;
    v.push_back(ui->colorSelecting->currentIndex());
    v.push_back(ui->colorSelecting_2->currentIndex());
    v.push_back(ui->colorSelecting_3->currentIndex());

    if(v == uniqueNumbers){
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

void MainWindow::on_newLvlButton_clicked()
{
    startIndexBox();
    startColorBall();
    int option = 1;
    QVector<int> uniqueNumbers = generatorUniqueNum(option);
    qDebug() << uniqueNumbers;
    //targetColor1 = uniqueNum(targetColor1, targetColor2, targetColor3);
    //targetColor2 = uniqueNum(targetColor2, targetColor1, targetColor3);
    //targetColor3 = uniqueNum(targetColor3, targetColor2, targetColor1);

    updateRuleGame();
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

