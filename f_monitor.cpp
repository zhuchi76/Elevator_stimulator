#include "F_MONITOR.h"
#include <string>
#include <iostream>
using namespace std;

F_Monitor::F_Monitor()
{

}
void F_Monitor::display_direction(int s){
    if(s == 0){

    }
    else if(s == 1){

    }
    else{

    }
}
string F_Monitor::f_display(int p, int d){
    string s;
    s += to_string(p);
    s += "   ";
    if(!d)
        s += "▼";
    else if(d == 1)
        s += "▲";
    else
        s += "";
    return s;
}
