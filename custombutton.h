#ifndef CustomButton_H
#define CUSTOMBUTTONS_H

#include <qpushbutton.h>

class CustomButton : public QPushButton
{
public:
    CustomButton(int row = 0, int col = 0);

    int const row();
    int const col();

private:
    int _row , _col;
};

#endif // CUSTOMBUTTONS_H
