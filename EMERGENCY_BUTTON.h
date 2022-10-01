#ifndef EMERGENCY_BUTTON_H
#define EMERGENCY_BUTTON_H

#include "BUTTON.h"

class Emergency_Button: public Button
{
public:
    Emergency_Button();
    bool call_manager();
};

#endif // EMERGENCY_BUTTON_H
