#ifndef E_MONITOR_H
#define E_MONITOR_H
#include <iostream>
#include <string>
#include <QObject>
using namespace std;

class E_Monitor: public QObject
{
public:
    E_Monitor();
    string e_display(int, int, int, double, bool, bool);
};

#endif // E_MONITOR_H
