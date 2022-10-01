#ifndef AIR_CONDITION_BUTTON_H
#define AIR_CONDITION_BUTTON_H
#include "BUTTON.h"

class Air_Condition_Button: public Button
{
private:
    int temp;
public:
    Air_Condition_Button();
    void set_temp();
    int get_temp();
public slots:
    void add_temp();      //add the temp
    void min_temp();      //minus the temp
};

#endif // AIR_CONDITION_H
