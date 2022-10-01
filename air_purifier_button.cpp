#include "AIR_PURIFIER_BUTTON.h"
#include <iostream>
using namespace std;

Air_Purifier_Button::Air_Purifier_Button()
{
    dirt = 50;
    turn_off();
}

void Air_Purifier_Button::set_dirt(){
    dirt = 50;
}
double Air_Purifier_Button::get_dirt(){
    return dirt;
}
void Air_Purifier_Button::add_dirt(int d){
    dirt += d;
}
void Air_Purifier_Button::min_dirt(){
    dirt -= 3;
}
void Air_Purifier_Button::set_pushbutton(QPushButton &c){
    cl = &c;
}
QPushButton *Air_Purifier_Button::get_pushbutton(){
    return cl;
}
