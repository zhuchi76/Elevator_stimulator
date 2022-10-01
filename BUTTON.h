#ifndef BUTTON_H
#define BUTTON_H
#include<QObject>
#include <ui_mainwindow.h>



class Button: public QObject
{
    Q_OBJECT
private:
    bool active;
    bool on;
    bool off;
public:
    Button();
    void turn_on();
    void turn_off();
    void shinning();
    bool get_button_active();
};

#endif // BUTTON_H
