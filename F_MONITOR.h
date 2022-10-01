#ifndef F_MONITOR_H
#define F_MONITOR_H
#include <iostream>
#include <string>
#include <QObject>
using namespace std;

class F_Monitor: public QObject
{
public:
    F_Monitor();
    void display_direction(int);
    string f_display(int, int);
};

#endif // F_MONITOR_H
