#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include "PEOPLE.h"
#include<string>
using namespace std;
class Employee : public People
{
public:
    Employee();
    string name;
    int id;
    void setname(string);
    void setid(int);
};

#endif // EMPLOYEE_H
