#include "FLOOR.h"
#include <iostream>
Floor::Floor():goup(), godown()
{
    count = 0;
    speed = 1;
    connect(&opentimer, SIGNAL(timeout()), this, SLOT(fdooropening()));
    connect(&closetimer, SIGNAL(timeout()), this, SLOT(fdoorclosing()));
    connect(this, SIGNAL(fwait()), this, SLOT(fwaiting()));
    connect(this, SIGNAL(ffinishclose()), this, SLOT(ffinishclosing()));
    fopening = false;
    fclosing = false;
    fextend = false;
}
void Floor::set_floor(int f){
    floornum = f;
}

void Floor::set_ubutton(QPushButton &b){
    upb = &b;
}
void Floor::set_dbutton(QPushButton &b){
    dpb = &b;
}

QPushButton *Floor::get_ubutton(){
    return upb;
}
QPushButton *Floor::get_dbutton(){
    return dpb;
}
int Floor::call_ele(){
    return floornum;
}
void Floor::turn_on_up(){
    goup.turn_on();
}
void Floor::turn_on_down(){
    godown.turn_on();
}
int Floor::get_floornum(){
    return floornum;
}
void Floor::pushu(){
    upb->setStyleSheet("color:red");
    emit e_ufloor(floornum);
}
void Floor::pushd(){
    dpb->setStyleSheet("color:red");
    emit e_dfloor(floornum);
}
void Floor::closeu(){
    //std::cout<<floornum<<std::endl;
    upb->setStyleSheet("color:black");
}
void Floor::closed(){
    dpb->setStyleSheet("color:black");
}
void Floor::set_ldoor(QLabel &l){
    left = &l;
}
void Floor::set_rdoor(QLabel &r){
    right = &r;
}
QLabel *Floor::get_ldoor(){
    return left;
}
QLabel *Floor::get_rdoor(){
    return right;
}

void Floor::fopen(){
    if(fclosing){
        closetimer.stop();
        fclosing = false;
    }
    opentimer.setInterval(100/speed);
    opentimer.start();
}

void Floor::fdooropening(){
    if(count == 19){
        fopening = true;
        opentimer.stop();
        if(!fextend)
            emit fwait();
    }
    else{
        fopening = true;
        count ++;
        left->setGeometry(left->x(), left->y(), left->width()-2, left->height());
        right->setGeometry(right->x()+2, right->y(), right->width()-2, right->height());
    }
}
void Floor::fdoorclosing(){
    if(count == 0)
        emit ffinishclose();
    else{
        fclosing = true;
        count --;
        left->setGeometry(left->x(), left->y(), left->width()+2, left->height());
        right->setGeometry(right->x()-2, right->y(), right->width()+2, right->height());
    }
}
void Floor::fwaiting(){
    waittimer.singleShot(2000/speed, this, SLOT(fclose()));
}
void Floor::fclose(){
    if(fopening){
        opentimer.stop();
        fopening = false;
    }
    if(!fextend){
        closetimer.setInterval(100/speed);
        closetimer.start();
    }
}
void Floor::ffinishclosing(){
    fclosing = false;
    closetimer.stop();
}
void Floor::turn_on_upbutton(){
    upb->setStyleSheet("color:red");
}
void Floor::turn_on_dpbutton(){
    dpb->setStyleSheet("color:red");
}
void Floor::clean(){
    count = 0;
    speed = 1;
    fextend = false;
    fopening = false;
    fclosing = false;
    left->setGeometry(280, left->y(), 51, 61);
    right->setGeometry(330, right->y(), 51, 61);
    opentimer.stop();
    closetimer.stop();
    waittimer.stop();
    if(floornum != 10)
        upb->setStyleSheet("color:black");
    if(floornum != 1)
        dpb->setStyleSheet("color:black");
    QTimer *t = new QTimer;
    t->singleShot(2000, this, SLOT(total_clean()));
}
void Floor::total_clean(){
    opentimer.stop();
    closetimer.stop();
    waittimer.stop();
    left->setGeometry(280, left->y(), 51, 61);
    right->setGeometry(330, right->y(), 51, 61);
}
void Floor::change_speed(){
    speed = speed % 4 + 1;
}
void Floor::change_extend(){
    fextend ^= 1;
    if(fextend)
        fopen();
    else if(!fextend)
        fclose();
}
