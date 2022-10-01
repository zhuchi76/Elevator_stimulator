#ifndef GUESS_H
#define GUESS_H
#include "PEOPLE.h"

class Guess : public People
{
public:
    Guess();
    int source;
    int destination;
    bool normal_man = true;
    void setsource(int);
    void setdesti(int);
};

#endif // GUESS_H
