#ifndef SAFE_SYSTEM_H
#define SAFE_SYSTEM_H
#include"ELAVATOR.h"

class Safe_system: public Elavator
{
public:
    Safe_system();
    void call_manager();
    void call_repairman();
};

#endif // SAFE_SYSTEM_H
