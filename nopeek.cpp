#include "nopeek.h"
#include "ui_nopeek.h"
#include <qevent.h>
#include <qmessagebox.h>
#include <qpushbutton.h>
#include <qrandom.h>
#include <QTimer>
#include <QThread>

int counterWrongs = 0;

NoPeek::NoPeek(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::NoPeek)
{
    Field = QVector<QVector<QPushButton*>>(9, QVector<QPushButton*>(9, nullptr));
    rightField = QVector<QVector<QPushButton*>>(9, QVector<QPushButton*>(9, nullptr));
    targetField = QVector<QVector<QPushButton*>>(9, QVector<QPushButton*>(9, nullptr));
    int counterWrongs = 0;
    ui->setupUi(this);
    createField();
}

NoPeek::~NoPeek()
{
    delete ui;
}

void NoPeek::createField(){

    for(int row = 0; row < 9; ++row){
        for(int col = 0; col < 9; ++col){
            Field[row][col] = new QPushButton();
            Field[row][col]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            Field[row][col]->setEnabled(0);

            connect(Field[row][col], &QPushButton::clicked, this, [this, row, col]() { selectPos(row, col); });
            ui->gridLayout->addWidget(Field[row][col], row, col);
        }
    }

    generateSpot();
}

void NoPeek::generateSpot(){
    revialField();

    for(int i = 0; i < 10; ++i){
        int randRow = QRandomGenerator::global()->bounded(9);
        int randCol = QRandomGenerator::global()->bounded(9);

        Field[randRow][randCol]->setEnabled(1);
        rightField[randRow][randCol] = Field[randRow][randCol];
    }

    QTimer::singleShot(5000, this, &NoPeek::blockField);
}

void NoPeek::selectPos(int row, int col){
    QPushButton* senderButton = qobject_cast<QPushButton*>(sender());

    if(rightField[row][col] == senderButton){
        targetField[row][col] = senderButton;
        Field[row][col]->setEnabled(0);
        if(targetField == rightField){
            QMessageBox::information(this, "Оповещение!", "Верно!");
            createField();
        }
    }
    else{
        counterWrongs++;
    }

    if(counterWrongs == 3){
        showRightAnswer();
    }
}

bool NoPeek::eventFilter(QObject *obj, QEvent *event)  {

    QKeyEvent *ke = static_cast<QKeyEvent*>(event);
    if (event->type() == QEvent::MouseButtonPress) {
        return true;
    }
    else if(event->type() == QEvent::MouseMove){
        return true;
    }
    else if(event->type() == QEvent::MouseButtonDblClick){
        return true;
    }
    else if(event->type() == QEvent::MouseButtonRelease){
        return true;
    }
    else if(event->type() == QEvent::KeyPress){
        if(ke->key() == Qt::Key_Space) return true;
    }
    return QMainWindow::eventFilter(obj, event);
}

void NoPeek::blockField(){
    for(int row = 0; row < 9; ++row){
        for(int col = 0; col < 9; ++col){
            Field[row][col]->removeEventFilter(this);
            if(Field[row][col] != rightField[row][col]){
                Field[row][col]->setEnabled(1);
            }           
        }
    }
}

void NoPeek::revialField(){
    for(int row = 0; row < 9; ++row){
        for(int col = 0; col < 9; ++col){
            Field[row][col]->installEventFilter(this);
            if(Field[row][col] != rightField[row][col]){
                Field[row][col]->setEnabled(0);
            }        
        }
    }
}

void NoPeek::showRightAnswer(){
    revialField();
    QTimer::singleShot(5000, this, &NoPeek::blockField);
    counterWrongs = 0;
}

void NoPeek::closeEvent(QCloseEvent *event)
{
    emit close();
}


