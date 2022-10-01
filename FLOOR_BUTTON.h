#ifndef FLOOR_BUTTON_H
#define FLOOR_BUTTON_H
#include "BUTTON.h"

class Floor_Button: public Button
{
private:
    Button open, close, exopen;
    Button f;
    QCheckBox *chb;
public:
    Floor_Button();
    Floor_Button(int);
    void set_cbutton(QCheckBox &);
    QCheckBox *get_cbutton();
    void turn_off(int);   //cancel the button
    void set_open();
    void set_close();
    void set_extend();
    void turn_on_cbutton();
};

#endif // FLOOR_BUTTON_H
