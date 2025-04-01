#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "logicalballs.h"
#include "nopeek.h"
#include "sudoku.h"
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);

    setFixedSize(size());
    setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_buttonLogicalGames_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::keyPressEvent(QKeyEvent *event)  {
    if (event->key() == Qt::Key_Escape) {
        ui->stackedWidget->setCurrentIndex(0);
    }
}

void MainWindow::on_startButtonSuduoku_clicked()
{
    Sudoku *sudoku = new Sudoku();
    connect(sudoku, &Sudoku::close, this, &MainWindow::show);
    sudoku->show();
    this->hide();
}


void MainWindow::on_startButtonLogicalBalls_clicked()
{
    LogicalBalls *logicalBalls = new LogicalBalls();
    connect(logicalBalls, &LogicalBalls::close, this, &MainWindow::show);
    logicalBalls->show();
    this->hide();
}

void MainWindow::on_startButtonNoPeek_clicked()
{
    NoPeek *nopeek = new NoPeek();
    connect(nopeek, &NoPeek::close, this, &MainWindow::show);
    nopeek->show();
    this->hide();
}

