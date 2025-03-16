#include "sudoku.h"
#include "ui_sudoku.h"
#include <QLineEdit>
#include <ctime>
#include <qlabel.h>
#include <qvalidator.h>

QVector<QVector<QLabel*>> labels(9, QVector<QLabel*>(9, nullptr));
QVector<QVector<QLineEdit*>> lines(9, QVector<QLineEdit*>(9, nullptr));
QVector<QVector<int>> sudoku(9, QVector<int>(9));
QVector<QVector<int>> tmpSudoku(9, QVector<int>(9));
QVector<int> tmp(9), tmp2(9);

Sudoku::Sudoku(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Sudoku)
{
    ui->setupUi(this);

    srand(time(0));
    initializeSudoku(sudoku, tmpSudoku, tmp);
    swap_rows(tmpSudoku, tmp, tmp2);
    swap_colums(tmpSudoku, tmp, tmp2);
    sudoku = tmpSudoku;
    //sudoku = sudoku;
    random_spotOfZero(sudoku);
    qDebug() << tmpSudoku;
    qDebug() << sudoku;
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            if (sudoku[row][col] == 0){
                lines[row][col] = new QLineEdit();
                lines[row][col]->setMaxLength(1);
                lines[row][col]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
                lines[row][col]->setAlignment(Qt::AlignCenter);
                lines[row][col]->setStyleSheet("border: 1px solid black;; font-size: 18px;");

                QRegularExpressionValidator *validator = new QRegularExpressionValidator(QRegularExpression("[1-9]"), lines[row][col]);
                lines[row][col]->setValidator(validator);

                connect(lines[row][col], &QLineEdit::textChanged, this, &Sudoku::selectSpot);

                ui->gridLayout->addWidget(lines[row][col], row, col);

            }else{
                labels[row][col] = new QLabel();
                labels[row][col]->setText(QString::number(sudoku[row][col])); // Display numbers
                labels[row][col]->setAlignment(Qt::AlignCenter);
                labels[row][col]->setStyleSheet("border: 1px solid black; font-size: 18px;");
                ui->gridLayout->addWidget(labels[row][col], row, col); // Add to grid layout
            }
        }
    }
}

Sudoku::~Sudoku()
{
    delete ui;
}

void Sudoku::initializeSudoku(QVector<QVector<int>>& sudoku, QVector<QVector<int>>& tmpSudoku, QVector<int>& tmp) {
    QVector<int> uniqueValues{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    std::random_shuffle(uniqueValues.begin(), uniqueValues.end());

    for (int i = 0; i < 9; i++) {
        sudoku[0][i] = uniqueValues[i];
    }

    for (int i = 1; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            tmpSudoku[i - 1][j] = sudoku[i - 1][j];
            sudoku[i][j] = tmpSudoku[i - 1][j];
        }
        if (i == 8)
        {
            for (int j = 0; j < 9; j++)
            {
                tmpSudoku[i][j] = sudoku[i][j];
                sudoku[i][j] = tmpSudoku[i][j];
            }
        }
    }

    for (int i = 1; i < 9; i++)
    {
        if (i != 3 && i != 6)
        {
            for (int j = 0; j < 9; j++)
            {
                tmp[j] = tmpSudoku[i - 1][j];
            }
            std::rotate(tmp.begin(), tmp.begin() + 3, tmp.end());
            for (int q = 0; q < 9; q++)
            {
                tmpSudoku[i][q] = tmp[q];
            }
        }
        else
        {
            for (int j = 0; j < 9; j++)
            {
                tmp[j] = tmpSudoku[i - 1][j];
            }
            std::rotate(tmp.begin(), tmp.begin() + 1, tmp.end());
            for (int q = 0; q < 9; q++)
            {
                tmpSudoku[i][q] = tmp[q];
            }
        }
    }
}

void Sudoku::selectSpot() {
    QLineEdit* senderLine = qobject_cast<QLineEdit*>(sender());
    if (!senderLine) return;

    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            if (lines[row][col] == senderLine) {
                answer(row, col);
                break;
            }
        }
    }
}

void Sudoku::answer(int row, int col) {
    if (!lines[row][col]) return;

    QString inputText = lines[row][col]->text();
    if (inputText.isEmpty()){
        lines[row][col]->setStyleSheet("background-color: white; border: 1px solid black; font-size: 18px;");
        return;
    }

    int userValue = inputText.toInt();

    if (userValue == tmpSudoku[row][col]) {
        lines[row][col]->setStyleSheet("background-color: lightgreen; border: 1px solid black; font-size: 18px;");
    }
    else {
        lines[row][col]->setStyleSheet("background-color: lightcoral; border: 1px solid black; font-size: 18px;");
    }
}

void Sudoku::random_spotOfZero(QVector<QVector<int>>& sudoku) {
    int rRow = 0, rCol = 0;
    for (size_t i = 0; i < 46; ++i)
    {
        do
        {
            rRow = rand() % 9;
            rCol = rand() % 9;
        } while (sudoku[rRow][rCol] == 0);
        sudoku[rRow][rCol] = 0;
    }
}

void Sudoku::swap_rows(QVector<QVector<int>>& tmpSudoku, QVector<int>& tmp, QVector<int>& tmp2) {
    int rRow = 0, rRowCopy = 0;
    for (size_t i = 2; i < 9; i += 3)
    {
        rRow = rand() % (i - (i - 2) + 1) + (i - 2);  // Генерируем случайный индекс в интервале 0-2 или 3-5
        rRowCopy = rand() % (i - (i - 2) + 1) + (i - 2); // Генерируем случайный индекс в том же интервале
        if (rRow == rRowCopy)
        {
            int generator;
            do
            {
                generator = rand() % (i - (i - 2) + 1) + (i - 2);
            } while (generator == rRowCopy);
            rRow = generator;
        }

        for (size_t j = 0; j < 9; j++)
        {
            tmp2[j] = tmpSudoku[rRow][j];
            tmp[j] = tmpSudoku[rRowCopy][j];
        }

        std::swap_ranges(tmp2.begin(), tmp2.end(), tmp.begin());

        for (size_t j = 0; j < 9; j++)
        {
            tmpSudoku[rRow][j] = tmp2[j];
            tmpSudoku[rRowCopy][j] = tmp[j];
        }
    }
}

void Sudoku::swap_colums(QVector<QVector<int>>& tmpSudoku, QVector<int>& tmp, QVector<int>& tmp2) {
    int rCol = 0, rColCopy = 0;
    for (size_t i = 2; i < 9; i += 3)
    {
        rCol = rand() % (i - (i - 2) + 1) + (i - 2);  // Генерируем случайный индекс в интервале 0-2 или 3-5
        rColCopy = rand() % (i - (i - 2) + 1) + (i - 2); // Генерируем случайный индекс в том же интервале
        if (rCol == rColCopy)
        {
            int generator;
            do
            {
                generator = rand() % (i - (i - 2) + 1) + (i - 2);
            } while (generator == rColCopy);
            rCol = generator;
        }

        for (size_t j = 0; j < 9; j++)
        {
            tmp2[j] = tmpSudoku[j][rCol];
            tmp[j] = tmpSudoku[j][rColCopy];
        }

        std::swap_ranges(tmp2.begin(), tmp2.end(), tmp.begin());

        for (size_t j = 0; j < 9; j++)
        {
            tmpSudoku[j][rCol] = tmp2[j];
            tmpSudoku[j][rColCopy] = tmp[j];
        }
    }
}
