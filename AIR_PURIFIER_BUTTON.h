#ifndef AIR_PURIFIER_BUTTON_H
#define AIR_PURIFIER_BUTTON_H
#include "BUTTON.h"
#include <iostream>
using namespace std;

class Air_Purifier_Button: public Button
{
private:
    double dirt;
    QPushButton *cl;
public:
    Air_Purifier_Button();
    void set_dirt();
    double get_dirt();
    void add_dirt(int);
    void set_pushbutton(QPushButton &);
    QPushButton *get_pushbutton();
public slots:
    void min_dirt();
};

#endif // AIR_PURIFIER_H
