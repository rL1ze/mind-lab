#ifndef SUDOKU_H
#define SUDOKU_H

#include <QMainWindow>
#include <qlineedit.h>

namespace Ui {
class Sudoku;
}

class Sudoku : public QMainWindow
{
    Q_OBJECT

public:
    explicit Sudoku(QWidget *parent = nullptr);
    ~Sudoku();

    void selectSpot(int row, int col);

    void createSudoku();

    void intelizateSudoku();
    void random_spotOfZero(QVector<QVector<int>>& sudoku);
    void swap_rows(QVector<QVector<int>>& tmp, QVector<int>& tmp2, QVector<int>& tmp3);
    void swap_colums(QVector<QVector<int>>& tmp, QVector<int>& tmp2, QVector<int>& tmp3);
    void generateSudoku(QVector<QVector<int>>& transposing, QVector<QVector<int>>& tmp, QVector<int>& tmp2);
signals:
    void close();
private slots:
    void closeEvent(QCloseEvent *event) override;

private:
    QVector<QVector<QLineEdit*>> lines;
    QVector<QVector<int>> targetFullAnswer, fullAnswer;
    QVector<QVector<int>> sudoku;
    QVector<QVector<int>> tmpSudoku;
    QVector<int> tmp, tmp2;
    Ui::Sudoku *ui;
};

#endif // SUDOKU_H
