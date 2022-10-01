#include "BUTTON.h"

Button::Button()
{
    active = false;
}

void Button::turn_on(){
    active = true;
}

void Button::turn_off(){
    active = false;
}

void Button::shinning(){
    for(int i=0; i<5; i++){
        turn_on();
        turn_off();
    }
}

bool Button::get_button_active(){
    return active;
}
