#ifndef BUILDING_H
#define BUILDING_H
#include "ELAVATOR.h"
#include "FLOOR.h"
#include "F_MONITOR.h"
#include<QObject>
#include <ui_mainwindow.h>

class Building: public QObject
{
public:
    Building();
    Floor f[10];
    Elavator e;
    F_Monitor FM;
};

#endif // BUILDING_H
