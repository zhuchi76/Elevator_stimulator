#ifndef REPAIRMAN_H
#define REPAIRMAN_H
#include"EMPLOYEE.h"
//#include <QMainWindow>

class Repairman:public Employee
{
private:
    bool work;
//private slots:
public:
    //void check_operating(); //check which item needs repairing
    Repairman();
    void repair_monitor();
    void repair_botton();
    void repair_bell();
};

#endif // REPAIRMAN_H
