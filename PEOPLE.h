#ifndef PEOPLE_H
#define PEOPLE_H
#include <QObject>
#include <ui_mainwindow.h>

class People: public QObject
{
    Q_OBJECT
private:
    QLabel *man;
public:
    People();
    int from;       //from which place
    int to;         //to which place
    bool way;       //up or down (to - from)
    bool in;        //whether people is in the elavator or not
    int weight;
    int dirty;
    bool allergy;
    int change_temp;
    void setweight(int);
    void setlabel(QLabel &);
   // ~People();
};

#endif // PEOPLE_H
