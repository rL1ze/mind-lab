#include "logicalballs.h"
#include "ui_logicalballs.h"
#include "balls.h"
#include <qgraphicsitem.h>

Balls *ball1, *ball2, *ball3, *ball4, *ball5;
QVector<int> uniqueNum{0, 1, 2, 3, 4};
QVector<int> uniqueNumFor3{0, 1, 2};
QVector<int> targetUniqueNum;
QVector<int> targetIndexs;
bool choiceOfAmountBall;
QRandomGenerator *generator = QRandomGenerator::global();
QComboBox *colorSelecting_4;
QComboBox *colorSelecting_5;

LogicalBalls::LogicalBalls(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LogicalBalls)
{
    ui->setupUi(this);

    ball1 = new Balls(100, 100);
    setupBall(ball1, ui->frame_1, 200, 200);
    ball2 = new Balls(100, 100);
    setupBall(ball2, ui->frame_2, 200, 200);
    ball3 = new Balls(100, 100);
    setupBall(ball3, ui->frame_3, 200, 200);

    //Выбор цвета в ComboBox   
    connect(ui->colorSelecting, &QComboBox::activated, this, [this](int index) {colorSelecting(0, index);});
    connect(ui->colorSelecting_2, &QComboBox::activated, this, [this](int index) {colorSelecting(1, index);});
    connect(ui->colorSelecting_3, &QComboBox::activated, this, [this](int index) {colorSelecting(2, index);});

    //Проверка решения, начало перезапуск игры при помощи кнопок
    connect(ui->checkButton, &QPushButton::clicked, this, &LogicalBalls::checkButton_clicked);
    connect(ui->startButton, &QPushButton::clicked, this, &LogicalBalls::startButton_clicked);

    //Смена сложности игры при помощи действий
    connect(ui->changeHard, &QAction::toggled, this, &LogicalBalls::on_changeHard_checkableChanged);

    //Фиксация окна
    setFixedSize(size());
    setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);
}

LogicalBalls::~LogicalBalls()
{
    delete ui;
}

// Устанавливаем размер и положение в соответствии с QFrame и станавливаем родительский виджет
void LogicalBalls::setupBall(Balls *ball, QFrame *frame, int x, int y){
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

void LogicalBalls::enableElements(){
    ui->colorSelecting->setEnabled(true);
    ui->colorSelecting_2->setEnabled(true);
    ui->colorSelecting_3->setEnabled(true);

    ui->menu->setEnabled(true);

    ui->checkButton->setEnabled(true);
}

void LogicalBalls::startIndexBox(){
    ui->colorSelecting->setCurrentIndex(-1);
    ui->colorSelecting_2->setCurrentIndex(-1);
    ui->colorSelecting_3->setCurrentIndex(-1);

    if(choiceOfAmountBall == true){
        colorSelecting_4->setCurrentIndex(-1);
        colorSelecting_5->setCurrentIndex(-1);
    }
}

void LogicalBalls::startColorBall(){
    ball1->ellipseItem->setBrush(Qt::transparent);
    ball2->ellipseItem->setBrush(Qt::transparent);
    ball3->ellipseItem->setBrush(Qt::transparent);

    if(choiceOfAmountBall == true){
        ball4->ellipseItem->setBrush(Qt::transparent);
        ball5->ellipseItem->setBrush(Qt::transparent);
    }
}

QVector<int> LogicalBalls::generatorUniqueNum(){
    if(choiceOfAmountBall){
        std::shuffle(uniqueNum.begin(), uniqueNum.end(), *generator);
        return uniqueNum;
    }
    else{
        std::shuffle(uniqueNumFor3.begin(), uniqueNumFor3.end(), *generator);
        return uniqueNumFor3;
    }
}

QString LogicalBalls::textColorBall(int randColor){
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
    default:
        return nullptr;
        break;
    }
}

void LogicalBalls::checkButton_clicked()
{
    targetIndexs.clear();
    targetIndexs.push_back(ui->colorSelecting->currentIndex());
    targetIndexs.push_back(ui->colorSelecting_2->currentIndex());
    targetIndexs.push_back(ui->colorSelecting_3->currentIndex());

    if(choiceOfAmountBall){
        targetIndexs.push_back(colorSelecting_4->currentIndex());
        targetIndexs.push_back(colorSelecting_5->currentIndex());
    }

    if(choiceOfAmountBall && targetIndexs == uniqueNum){
        QMessageBox::information(this, "Оповещение!", "Верно!");
    }
    else if(!choiceOfAmountBall && targetIndexs == uniqueNumFor3){
        QMessageBox::information(this, "Оповещение!", "Верно!");
    }
    else{
        QMessageBox::information(this, "Оповещение!", "Не верно!");
    }
}

void LogicalBalls::updateRuleGame()
{
    QString lastWords;
    QString statementText;
    if(choiceOfAmountBall){
        statementText.clear();
        statementText = "Если первый шар не ";
        statementText += textColorBall(targetUniqueNum[3]);
        statementText += ", а второй ";
        statementText += textColorBall(targetUniqueNum[1]);
        statementText += ", последний не ";
        statementText += textColorBall(targetUniqueNum[3]) + ".";
        statementText += " " + textColorBall(targetUniqueNum[2]).replace(0 , 1, textColorBall(targetUniqueNum[2]).first(1).toUpper()) + " между ";
        statementText += textColorBall(targetUniqueNum[4]).removeLast() + "м";
        statementText += " и " + textColorBall(targetUniqueNum[1]).removeLast() + "м.";
        lastWords = ", последний не";
    }
    else if(!choiceOfAmountBall){
        statementText.clear();
        statementText = "Если первый шар не ";
        statementText += textColorBall(targetUniqueNum[2]);
        statementText += ", а второй ";
        statementText += textColorBall(targetUniqueNum[1]);
    }
    else{
        statementText.remove(lastWords);
    }
    ui->ruleGame->setText(statementText);
}

void LogicalBalls::startButton_clicked()
{
    enableElements();
    targetIndexs.clear();
    targetUniqueNum = generatorUniqueNum();
    updateRuleGame();
    startIndexBox();
    startColorBall();
    qDebug() << targetUniqueNum;
}

void LogicalBalls::colorSelecting(int ballIndex, int colorIndex) {
    QVector<Balls*> balls = { ball1, ball2, ball3, ball4, ball5 };

    if (ballIndex >= 0 && ballIndex < balls.size()) {
        Balls::colorSelecting(colorIndex, balls[ballIndex]);
    }
}

void LogicalBalls::createObjects(){

    QLabel *selectColorText_4 = new QLabel("Выберите цвет:");
    QLabel *selectColorText_5 = new QLabel("Выберите цвет:");

    colorSelecting_4 = new QComboBox();
    colorSelecting_5 = new QComboBox();

    QStringList colorSlectingList{"Синий", "Красный", "Жёлтый", "Зелённый", "Фиолетовый"};
    ui->colorSelecting->addItems(colorSlectingList.mid(3));
    ui->colorSelecting_2->addItems(colorSlectingList.mid(3));
    ui->colorSelecting_3->addItems(colorSlectingList.mid(3));
    colorSelecting_4->addItems(colorSlectingList);
    colorSelecting_5->addItems(colorSlectingList);

    connect(colorSelecting_4, &QComboBox::activated, this, [this](int index) {colorSelecting(3, index);});
    connect(colorSelecting_5, &QComboBox::activated, this, [this](int index) {colorSelecting(4, index);});

    QFrame *frame_4 = new QFrame();
    QFrame *frame_5 = new QFrame();

    ball4 = new Balls(50, 50);
    setupBall(ball4, frame_4, 100, 100);
    ball5 = new Balls(50, 50);
    setupBall(ball5, frame_5, 100, 100);

    ui->gridLayout->addWidget(frame_4, 0, 3);
    ui->gridLayout->addWidget(frame_5, 0, 4);

    ui->gridLayout->addWidget(colorSelecting_4, 2, 3);
    ui->gridLayout->addWidget(colorSelecting_5, 2, 4);

    ui->gridLayout->addWidget(selectColorText_4, 1, 3);
    ui->gridLayout->addWidget(selectColorText_5, 1, 4);

}

void LogicalBalls::on_changeHard_checkableChanged(bool checkabled)
{
    if(checkabled == true){
        choiceOfAmountBall = checkabled;

        ball1->ellipseItem->setRect(14, 15, 50, 50);
        ball2->ellipseItem->setRect(14, 15, 50, 50);
        ball3->ellipseItem->setRect(14, 15, 50, 50);

        ui->frame_1->setFixedSize(100, 100);
        ui->frame_2->setFixedSize(100, 100);
        ui->frame_3->setFixedSize(100, 100);

        createObjects();
        startButton_clicked();

        ui->gridLayout->addWidget(ui->checkButton, 3, 2);

        targetIndexs.clear();
    }
    else if(checkabled == false){
        choiceOfAmountBall = checkabled;
        startButton_clicked();
        removeObjects();

        ball1->ellipseItem->setRect(0, 0, 100, 100);
        ball2->ellipseItem->setRect(0, 0, 100, 100);
        ball3->ellipseItem->setRect(0, 0, 100, 100);

        ui->frame_1->setFixedSize(200, 200);
        ui->frame_2->setFixedSize(200, 200);
        ui->frame_3->setFixedSize(200, 200);

        ui->gridLayout->addWidget(ui->checkButton, 3, 1);
        targetIndexs.clear();
    }
}

void LogicalBalls::removeObjects() {
    delete ball4->ellipseItem;
    delete ball5->ellipseItem;

    ui->colorSelecting->removeItem(3);
    ui->colorSelecting->removeItem(3);

    ui->colorSelecting_2->removeItem(3);
    ui->colorSelecting_2->removeItem(3);

    ui->colorSelecting_3->removeItem(3);
    ui->colorSelecting_3->removeItem(3);

    for(int i = 0; i <= 2; i++){
        for(int j = 3; j <= 4; j++){
            delete ui->gridLayout->itemAtPosition(i,j)->widget();
        }
    }
}
