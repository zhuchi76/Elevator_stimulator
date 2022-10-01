#include "FLOOR_BUTTON.h"

Floor_Button::Floor_Button():Button()
{

}
void Floor_Button::set_cbutton(QCheckBox &c){
    chb = &c;
}
QCheckBox *Floor_Button::get_cbutton(){
    return chb;
}
void Floor_Button::turn_on_cbutton(){
    chb->setCheckState(Qt::Checked);
}
