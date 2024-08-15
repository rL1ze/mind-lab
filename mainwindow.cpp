#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "balls.h"
#include "qgraphicsitem.h"

Balls *ball1, *ball2, *ball3, *ball4, *ball5;
QVector<int> uniqueNumbers{0, 1, 2, 3, 4};
int option =1;
QRandomGenerator generator = *QRandomGenerator::global();


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    if(option == 1){
        ball1 = new Balls(this, 100, 100);
        ball2 = new Balls(this, 100, 100);
        ball3 = new Balls(this, 100, 100);
        setupBall(ball1, ui->frame_1, 200, 200);
        setupBall(ball2, ui->frame_2, 200, 200);
        setupBall(ball3, ui->frame_3, 200, 200);
    }

    if(option == 2){
        ball1 = new Balls(this, 50, 50);
        ball2 = new Balls(this, 50, 50);
        ball3 = new Balls(this, 50, 50);
        ball4 = new Balls(this, 50, 50);
        ball5 = new Balls(this, 50, 50);
        setupBall(ball1, ui->frame_1, 100, 100);
        setupBall(ball2, ui->frame_2, 100, 100);
        setupBall(ball3, ui->frame_3, 100, 100);

        QFrame *frame_4 = new QFrame(), *frame_5 = new QFrame();
        ui->gridLayout->addWidget(frame_4, 0, 3);
        ui->gridLayout->addWidget(frame_5, 0, 4);
        QComboBox *colorSelecting_4 = new QComboBox(), *colorSelecting_5  = new QComboBox();

        setupBall(ball4, frame_4, 100, 100);
        setupBall(ball5, frame_5, 100, 100);

        ui->gridLayout->addWidget(colorSelecting_4, 2, 3);
        ui->gridLayout->addWidget(colorSelecting_5, 2, 4);
    }

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
}

// Устанавливаем размер и положение в соответствии с QFrame и станавливаем родительский виджет
void MainWindow::setupBall(Balls *ball, QFrame *frame, int x, int y){
    // Установка фиксированных размеров для фрейма
    frame->setFixedSize(x, y);

    // Установка QGraphicsView как дочернего виджета фрейма
    ball->view->setParent(frame);

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

QVector<int> MainWindow::generatorUniqueNum(int option){
    if(option == 1){
        std::shuffle(uniqueNumbers.begin(), uniqueNumbers.end() - 2, generator);
        return uniqueNumbers.mid(0, 3);
    }
    if(option == 2){
        std::shuffle(uniqueNumbers.begin(), uniqueNumbers.end(), generator);
        return uniqueNumbers;
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

    if(v == uniqueNumbers.mid(0, 3)){
        QMessageBox::information(this, "Оповещение!", "Верно!");
    }
    else if(v == uniqueNumbers.mid(2, -1) && option == 2){
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
    QVector<int> uniqueNumbers = generatorUniqueNum(option);
    qDebug() << uniqueNumbers;

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

