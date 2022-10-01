#include "PEOPLE.h"
#include <stdlib.h>
People::People(){
    from = rand()%10+1;
    do{
        to = rand()%10+1;
    }while(to == from);
    if(to>from)
        way = true;
    else
        way = false;
    in = false;
    dirty = rand() % 10;
    int a = rand() % 10;
    if(a == 0)
        allergy = true;
    else
        allergy = false;
    int b = rand() % 5;
    if(b == 0)
        change_temp = 0;
    else if(b == 1)
        change_temp = 1;
    else
        change_temp = 2;
}
void People::setweight(int w)
{
    weight = w;
}
