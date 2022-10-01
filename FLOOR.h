#ifndef FLOOR_H
#define FLOOR_H
#include "OUTSIDE_BUTTON.h"
#include <QObject>
#include <QTimer>

class Floor: public QObject
{
    Q_OBJECT
private:
    int count;
    int floornum;
    int speed;
    Outside_Button goup, godown;
    QPushButton *upb, *dpb;
    QLabel *left, *right;
    QTimer opentimer;
    QTimer closetimer;
    QTimer waittimer;
    bool fopening, fclosing, fextend;
public:
    Floor();
    void set_floor(int);
    void set_ubutton(QPushButton &);
    void set_dbutton(QPushButton &);
    void set_ldoor(QLabel &);
    void set_rdoor(QLabel &);
    QPushButton *get_ubutton();
    QPushButton *get_dbutton();
    QLabel *get_ldoor();
    QLabel *get_rdoor();
    int call_ele();
    void turn_on_up();
    void turn_on_down();
    int get_floornum();
public slots:
    void pushu();
    void pushd();
    void closeu();
    void closed();
    void fopen();
    void fdooropening();
    void fdoorclosing();
    void fwaiting();
    void fclose();
    void ffinishclosing();
    void turn_on_upbutton();
    void turn_on_dpbutton();
    void clean();
    void total_clean();
    void change_speed();
    void change_extend();
signals:
    void e_ufloor(int floornum);
    void e_dfloor(int floornum);
    void fwait();
    void ffinishclose();
};

#endif // FLOOR_H
