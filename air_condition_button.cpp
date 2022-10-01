#include "AIR_CONDITION_BUTTON.h"

Air_Condition_Button::Air_Condition_Button()
{
    temp = 25;
    turn_off();
}
void Air_Condition_Button::add_temp(){
    temp++;
}
void Air_Condition_Button::min_temp(){
    temp--;
}
void Air_Condition_Button::set_temp(){
    temp = 25;
}
int Air_Condition_Button::get_temp(){
    return temp;
}
