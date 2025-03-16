#ifndef SUDOKU_H
#define SUDOKU_H

#include <QMainWindow>

namespace Ui {
class Sudoku;
}

class Sudoku : public QMainWindow
{
    Q_OBJECT

public:
    explicit Sudoku(QWidget *parent = nullptr);
    ~Sudoku();

    void selectSpot();
    void answer(int row = 0, int col = 0);

    void random_spotOfZero(QVector<QVector<int>>& sudoku);
    void swap_rows(QVector<QVector<int>>& tmp, QVector<int>& tmp2, QVector<int>& tmp3);
    void swap_colums(QVector<QVector<int>>& tmp, QVector<int>& tmp2, QVector<int>& tmp3);
    void initializeSudoku(QVector<QVector<int>>& transposing, QVector<QVector<int>>& tmp, QVector<int>& tmp2);
private slots:


private:
    Ui::Sudoku *ui;
};

#endif // SUDOKU_H
