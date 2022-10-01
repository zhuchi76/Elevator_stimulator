#include "E_MONITOR.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <string>
using namespace std;

E_Monitor::E_Monitor()
{

}

string E_Monitor::e_display(int p, int d, int t, double pm, bool ins, bool o){
    string s;
    s += to_string(p);
    s += "   ";
    if(!d)
        s += "▼";
    else if(d == 1)
        s += "▲";
    if(o)
        s += "   Door Open\n";
    else
        s += "\n";
    s += "Temperature: ";
    s += to_string(t);
    s += " degree\n";
    s += "PM2.5: ";
    s += to_string(pm);
    s += " mg/m^3\n";
    s += "Mode: ";
    if(!ins)
        s += "Normal";
    else
        s += "Insane";
    return s;
}
