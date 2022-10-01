#ifndef INSANE_MODE_BUTTON_H
#define INSANE_MODE_BUTTON_H
#include "BUTTON.h"

class Insane_Mode_Button: public Button
{
private:
    Button insane;
public:
    Insane_Mode_Button();
    bool insane_or_not();
};

#endif // INSANE_MODE_H
