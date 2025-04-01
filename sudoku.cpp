#include "sudoku.h"
#include "ui_sudoku.h"
#include <qmessagebox.h>
#include <qrandom.h>
#include <ctime>
#include <qvalidator.h>
#include <QLineEdit>
#include <QCloseEvent>

Sudoku::Sudoku(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Sudoku)
{
    ui->setupUi(this);

    lines = QVector<QVector<QLineEdit*>>(9, QVector<QLineEdit*>(9, nullptr));
    targetFullAnswer = QVector<QVector<int>>(9, QVector<int>(9)),
    fullAnswer = QVector<QVector<int>>(9, QVector<int>(9));
    sudoku = QVector<QVector<int>>(9, QVector<int>(9));
    tmpSudoku =  QVector<QVector<int>> (9, QVector<int>(9));
    tmp = QVector<int> (9), tmp2 = QVector<int>(9);

    for (int row = 0; row < 11; ++row) {
        for (int col = 0; col < 11; ++col) {
            // Добавление вертикальной линии (разделяет блоки)
            if (col == 3 || col == 7) {
                QFrame *verticalLine = new QFrame();
                verticalLine->setFrameShape(QFrame::VLine);
                verticalLine->setFrameShadow(QFrame::Sunken);
                verticalLine->setFixedWidth(3); // Толщина линии
                ui->gridLayout->addWidget(verticalLine, row, col);
            }
            // Добавление горизонтальной линии (разделяет блоки)
            if (row == 3 || row == 7) {
                QFrame *horizontalLine = new QFrame();
                horizontalLine->setFrameShape(QFrame::HLine);
                horizontalLine->setFrameShadow(QFrame::Sunken);
                horizontalLine->setFixedHeight(3); // Толщина линии
                ui->gridLayout->addWidget(horizontalLine, row, col);
            }
        }
    }

    createSudoku();

    //Фиксация окна
    setFixedSize(size());
    setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);
}

Sudoku::~Sudoku()
{
    delete ui;
}

void Sudoku::createSudoku()
{
    srand(time(0));
    generateSudoku(sudoku, tmpSudoku, tmp);
    swap_rows(tmpSudoku, tmp, tmp2);
    swap_colums(tmpSudoku, tmp, tmp2);
    sudoku = tmpSudoku;
    random_spotOfZero(sudoku);
    intelizateSudoku();
    qDebug() << "==============================";
    for (const auto& row : tmpSudoku) {
        qDebug() << row;
    }
    qDebug() << "==============================";
    for (const auto& row : fullAnswer) {
        qDebug() << row;
    }
}

void Sudoku::closeEvent(QCloseEvent *event)
{
    emit close();
}

void Sudoku::intelizateSudoku(){
    targetFullAnswer.fill(QVector<int>(9, 0));
    fullAnswer.fill(QVector<int>(9, 0));
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            // Заполнение ячеек судоку
            lines[row][col] = new QLineEdit();
            lines[row][col]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            lines[row][col]->setAlignment(Qt::AlignCenter);
            lines[row][col]->setStyleSheet("border: 1px solid black; font-size: 18px;");

            // Заполнение пустых ячеек с возможностью ввода
            if (sudoku[row][col] == 0) {
                fullAnswer[row][col] = tmpSudoku[row][col];
                lines[row][col]->setText(NULL);
                lines[row][col]->setReadOnly(0);
                lines[row][col]->setMaxLength(1);

                QRegularExpressionValidator *validator = new QRegularExpressionValidator(QRegularExpression("[1-9]"), lines[row][col]);
                lines[row][col]->setValidator(validator);


            } else {
                lines[row][col]->setText(QString::number(sudoku[row][col]));
                lines[row][col]->setReadOnly(1);
            }

            // Смещение для учета линий-разделителей
            int gridRow = row + (row / 3);  // Увеличение индекса строки на 1 после каждых 3 строк
            int gridCol = col + (col / 3);  // Увеличение индекса столбца на 1 после каждых 3 столбцов

            ui->gridLayout->addWidget(lines[row][col], gridRow, gridCol);
            connect(lines[row][col], &QLineEdit::textChanged, this, [this, row, col]() { selectSpot(row, col); });
        }
    }
}

void Sudoku::generateSudoku(QVector<QVector<int>>& sudoku, QVector<QVector<int>>& tmpSudoku, QVector<int>& tmp) {
    QVector<int> uniqueValues{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    std::random_device rd;
    std::default_random_engine generator(rd());
    std::shuffle(uniqueValues.begin(), uniqueValues.end(), generator);

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

void Sudoku::selectSpot(int row, int col) {
    QLineEdit* senderLine = qobject_cast<QLineEdit*>(sender());
    if (!senderLine) return;

    QString inputText = lines[row][col]->text();
    if (inputText.isEmpty()){
        lines[row][col]->setStyleSheet("background-color: white; border: 1px solid black; font-size: 18px;");
        return;
    }

    int userValue = inputText.toInt();

    if (userValue == tmpSudoku[row][col]) {
        targetFullAnswer[row][col] = userValue;
        lines[row][col]->setStyleSheet("background-color: lightgreen; border: 1px solid black; font-size: 18px;");
        lines[row][col]->setReadOnly(1);
        if(targetFullAnswer == fullAnswer){
            QMessageBox::information(this, "Оповещение!", "Верно!");
            createSudoku();
        }
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
