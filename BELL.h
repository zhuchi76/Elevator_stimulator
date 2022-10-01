#ifndef BELL_H
#define BELL_H
#include"BUTTON.h"
#include<string>
#include<iostream>
#include<QObject>

using namespace std;
class Bell: public QObject
{
private:
    bool mal;     //broken
    Button ring;
    int vol;      //for volume
    string music_name;
public:
    Bell();
    void ringing();
};

#endif // BELL_H
