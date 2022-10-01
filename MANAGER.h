#ifndef MANAGER_H
#define MANAGER_H
#include"EMPLOYEE.h"

class Manager:public Employee
{
private:
    bool work;
public:
    Manager();
    void kill_the_brat();
    void call_the_repairman();

};

#endif // MANAGER_H
