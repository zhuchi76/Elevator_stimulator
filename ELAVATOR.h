#ifndef ELAVATOR_H
#define ELAVATOR_H

#include "AIR_CONDITION_BUTTON.h"
#include "AIR_PURIFIER_BUTTON.h"
#include "EMERGENCY_BUTTON.h"
#include "FLOOR_BUTTON.h"
#include "INSANE_MODE_BUTTON.h"
#include "E_MONITOR.h"
#include "PEOPLE.h"
#include <QMainWindow>
#include <QTimer>
#include <QObject>
class Elavator: public QObject
{
    Q_OBJECT
private:
    Emergency_Button em;
    int capacity;
    int temp;
    double PM;
    int person_id;
    int count;        //count door open times;
    QTimer timer;    //timer for elavator's total moving time
    QTimer atime;    //timer for elavator's total door opening time
    QTimer mtime;     //timer for elavator moving
    QTimer dotime;    //timer for elavator's door opening
    QTimer dctime;    //timer for elavator's door closing
    QTimer wtime;     //timer for waiting time between door opening and closing
    QTimer purify;    //timer for air purify
    QLabel *leftdoor;
    QLabel *rightdoor;
    QLabel *inner;
    vector<People *> p;             //waiting people
    vector<People *> pin;
    QTextBrowser *id;
    void peopleout();             //peoplego out
    string print_id(int ,int);
    bool purify_open;
    bool opening, closing, extending;
public:
    Air_Condition_Button ac;
    Air_Purifier_Button ap;
    Insane_Mode_Button ins;
    E_Monitor EM;
    Floor_Button fl[10];
    int vel;
    double acc;
    bool floor[10][3];   //elavator botton, up button, down button
    int state;    //determine up, down or stay down = 0, up = 1, stay = 2
    int last_state;   //record the last state
    int place;    //elevator place
    bool move;    //moving or not
    bool still_on;       //determine whether any floor still on;
    bool dooropen;       //elavator door is open or not
    int people_in_elavator;
    int waitingpeople[10];
    bool automove;
    Elavator();
    void go_place(bool[], int);   //floor & state  trash
    void change(int);
    int cap();
    double pm();
    void arrive();
    void set_leftdoor(QLabel &);
    void set_rightdoor(QLabel &);
    void set_inner(QLabel &);
    void set_idbrowser(QTextBrowser &);
    void set_closedoor(QPushButton &);
    void set_opendoor(QPushButton &);
    void set_extend(QPushButton &);
    QPushButton *opendoor, *closedoor, *extend;
public slots:
    void changeplace(int);
    void turn_floorup_on(int);
    void turn_floordown_on(int);
    void pushc();
    void go_up();
    void go_down();
    void go_or_not();
    void moving();          //for inner elavator moving, changing its y axis
    void dooropening();     //for the movement of door opening
    void doorclosing();     //for the movement of door closing
    void open();            //start opening timer
    void waiting();         //stop opening timer, and wait for one second
    void close();           //start closing timer
    void finishclosing();   //stop closing timer, and change dooropen into false
    void randompeople();
    void peoplein();        //people go in
    void clean();           //go to initial
    void total_clean();
    void change_speed();
    void add_temp();      //add the temp
    void min_temp();      //minus the temp
    void min_dirt();      //minus the dirt
    void open_ap();
    void change_extend();
signals:
    void show();
    void off_uflb1();
    void off_uflb2();
    void off_uflb3();
    void off_uflb4();
    void off_uflb5();
    void off_uflb6();
    void off_uflb7();
    void off_uflb8();
    void off_uflb9();
    void off_dflb2();
    void off_dflb3();
    void off_dflb4();
    void off_dflb5();
    void off_dflb6();
    void off_dflb7();
    void off_dflb8();
    void off_dflb9();
    void off_dflb10();
    void on_uflb1();
    void on_uflb2();
    void on_uflb3();
    void on_uflb4();
    void on_uflb5();
    void on_uflb6();
    void on_uflb7();
    void on_uflb8();
    void on_uflb9();
    void on_dflb2();
    void on_dflb3();
    void on_dflb4();
    void on_dflb5();
    void on_dflb6();
    void on_dflb7();
    void on_dflb8();
    void on_dflb9();
    void on_dflb10();
    void wait();
    void finishclose();
    void dooropencontrol(int place);
    void doorclosecontrol(int place);
    void doorextendcontrol(int place);
    void go_out(int);
    void go_in(vector<People *>);
    void go_total(int);
};

#endif // ELAVATOR_H
