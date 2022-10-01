#include "ELAVATOR.h"

Elavator::Elavator()
{
    capacity = 10;
    vel = 1;
    acc = 0;
    for(int i=0; i<10; i++){
        for(int j=0; j<3; j++)
        floor[i][j] = false;
    }
    state = 2;
    last_state = 2;
    place = 1;
    move = false;
    still_on = false;
    dooropen = false;
    people_in_elavator = 0;
    person_id = 0;
    count = 0;
    automove = false;
    purify_open = false;
    purify.setInterval(2000/vel);
    connect(&mtime, SIGNAL(timeout()), this, SLOT(moving()));
    connect(&dotime, SIGNAL(timeout()), this, SLOT(dooropening()));
    connect(&dctime, SIGNAL(timeout()), this, SLOT(doorclosing()));
    connect(this, SIGNAL(wait()), this, SLOT(waiting()));
    connect(this, SIGNAL(finishclose()), this, SLOT(finishclosing()));
    connect(&purify, SIGNAL(timeout()), this, SLOT(min_dirt()));
    opening = false;
    closing = false;
    extending = false;
}
int Elavator::cap()
{
    return capacity;
}
double Elavator::pm()
{
    return PM;
}
void Elavator::changeplace(int f){
    place = f;
}
void Elavator::turn_floorup_on(int f){
    floor[f-1][1] = true;
}
void Elavator::turn_floordown_on(int f){
    floor[f-1][2] = true;
}
void Elavator::pushc(){
    for(int i=0; i<10; i++){
        if(fl[i].get_cbutton()->isChecked()){
            floor[i][0] = true;
        }
    }
    go_or_not();
}
void Elavator::set_leftdoor(QLabel &l){
    leftdoor = &l;
}
void Elavator::set_rightdoor(QLabel &r){
    rightdoor = &r;
}
void Elavator::set_inner(QLabel &i){
    inner = &i;
}
void Elavator::set_idbrowser(QTextBrowser &b){
    id = &b;
}
void Elavator::set_opendoor(QPushButton &o){
    opendoor = &o;
}
void Elavator::set_closedoor(QPushButton &c){
    closedoor = &c;
}
void Elavator::set_extend(QPushButton &e){
    extend = &e;
}
void Elavator::go_or_not(){ //a little bit strange
    emit show();
    if(state == 2){
        if(last_state == 0 || last_state == 2){
            for(int i=1; i<=10; i++){
                if(floor[i-1][0]||floor[i-1][1]||floor[i-1][2]){
                    if(!move && !dooropen)
                        change(i);
                }
            }
        }
        else if(last_state == 1){
            for(int i=10; i>=1; i--){
                if(floor[i-1][0]||floor[i-1][1]||floor[i-1][2]){
                    if(!move && !dooropen)
                        change(i);
                }
            }
        }
    }
    else if(state == 1){
        for(int i=place; i<10; i++){
            if(floor[i][0]||floor[i][1]||floor[i][2]){
                if(!move && !dooropen)
                    change(i+1);
                still_on = true;
            }
        }
        if(!still_on){
            state = 2;
            last_state = 1;
            go_or_not();
        }
    }
    else if(state == 0){
        for(int i=place; i>=2; i--){
            if(floor[i-2][0]||floor[i-2][1]||floor[i-2][2]){
                if(!move && !dooropen)
                    change(i-1);
                still_on = true;
            }
        }
        if(!still_on){
            state = 2;
            last_state = 0;
            go_or_not();
        }
    }
}
void Elavator::change(int i){
    move = true;
    //timer = new QTimer();                                     // this   
    mtime.setInterval(100/vel);
    if(place<i){
        state = 1;
        mtime.start();
        timer.singleShot(1100/vel, this, SLOT(go_up()));             // this
    }
    else if(place>i){
        state = 0;
        mtime.start();
        timer.singleShot(1100/vel, this, SLOT(go_down()));           // this
    }
    else if(place == i){
        if(floor[i-1][1])
            state = 1;
        else if(floor[i-1][2])
            state = 0;
        move = false;
        still_on = false;
        arrive();
    }
}
void Elavator::go_up(){
    mtime.stop();
    place++;
    switch(place){
    case 1:
        inner->setGeometry(inner->x(), 770, inner->width(), inner->height());
        break;
    case 2:
        inner->setGeometry(inner->x(), 690, inner->width(), inner->height());
        break;
    case 3:
        inner->setGeometry(inner->x(), 610, inner->width(), inner->height());
        break;
    case 4:
        inner->setGeometry(inner->x(), 530, inner->width(), inner->height());
        break;
    case 5:
        inner->setGeometry(inner->x(), 450, inner->width(), inner->height());
        break;
    case 6:
        inner->setGeometry(inner->x(), 370, inner->width(), inner->height());
        break;
    case 7:
        inner->setGeometry(inner->x(), 290, inner->width(), inner->height());
        break;
    case 8:
        inner->setGeometry(inner->x(), 210, inner->width(), inner->height());
        break;
    case 9:
        inner->setGeometry(inner->x(), 130, inner->width(), inner->height());
        break;
    case 10:
        inner->setGeometry(inner->x(), 50, inner->width(), inner->height());
        break;
    }
    emit show();
    if(floor[place-1][0]||floor[place-1][1]){
        move = false;
        arrive();
    }
    else{
        move = false;
        still_on = false;
        go_or_not();        
    }
}
void Elavator::go_down(){
    mtime.stop();
    place--;
    switch(place){
    case 1:
        inner->setGeometry(inner->x(), 770, inner->width(), inner->height());
        break;
    case 2:
        inner->setGeometry(inner->x(), 690, inner->width(), inner->height());
        break;
    case 3:
        inner->setGeometry(inner->x(), 610, inner->width(), inner->height());
        break;
    case 4:
        inner->setGeometry(inner->x(), 530, inner->width(), inner->height());
        break;
    case 5:
        inner->setGeometry(inner->x(), 450, inner->width(), inner->height());
        break;
    case 6:
        inner->setGeometry(inner->x(), 370, inner->width(), inner->height());
        break;
    case 7:
        inner->setGeometry(inner->x(), 290, inner->width(), inner->height());
        break;
    case 8:
        inner->setGeometry(inner->x(), 210, inner->width(), inner->height());
        break;
    case 9:
        inner->setGeometry(inner->x(), 130, inner->width(), inner->height());
        break;
    case 10:
        inner->setGeometry(inner->x(), 50, inner->width(), inner->height());
        break;
    }
    emit show();
    if(floor[place-1][0]||floor[place-1][2]){
        move = false;
        arrive();
    }
    else{
        move = false;
        still_on = false;
        go_or_not();
    }
}
void Elavator::arrive(){
    floor[place-1][0] = false;
    fl[place-1].get_cbutton()->setCheckState(Qt::Unchecked);
    dooropen = true;
    if(state == 0){
        floor[place-1][2] = false;
        switch(place){
        case 2:
            emit off_dflb2();
            break;
        case 3:
            emit off_dflb3();
            break;
        case 4:
            emit off_dflb4();
            break;
        case 5:
            emit off_dflb5();
            break;
        case 6:
            emit off_dflb6();
            break;
        case 7:
            emit off_dflb7();
            break;
        case 8:
            emit off_dflb8();
            break;
        case 9:
            emit off_dflb9();
            break;
        case 10:
            emit off_dflb10();
            break;
        default:
            break;
        }
        if(!automove){
            if(place == 10){
                fl[9].get_cbutton()->setCheckable(false);
                if(!floor[8][0] && !floor[7][0]){
                    fl[8].get_cbutton()->setCheckable(false);
                    fl[7].get_cbutton()->setCheckable(false);
                }
            }
            if(place == 9){
                fl[9].get_cbutton()->setCheckable(false);
                fl[8].get_cbutton()->setCheckable(false);
                if(!floor[7][0])
                    fl[7].get_cbutton()->setCheckable(false);
            }
            if(place == 8){
                fl[9].get_cbutton()->setCheckable(false);
                fl[8].get_cbutton()->setCheckable(false);
                fl[7].get_cbutton()->setCheckable(false);
            }
        }
    }
    if(state == 1){
        floor[place-1][1] = false;
        switch(place){
        case 1:
            emit off_uflb1();
            break;
        case 2:
            emit off_uflb2();
            break;
        case 3:
            emit off_uflb3();
            break;
        case 4:
            emit off_uflb4();
            break;
        case 5:
            emit off_uflb5();
            break;
        case 6:
            emit off_uflb6();
            break;
        case 7:
            emit off_uflb7();
            break;
        case 8:
            emit off_uflb8();
            break;
        case 9:
            emit off_uflb9();
            break;
        default:
            break;
        }
        if(!automove){
            if(place == 8){
                fl[7].get_cbutton()->setCheckable(false);
                if(!floor[8][0] && !floor[9][0]){
                    fl[8].get_cbutton()->setCheckable(false);
                    fl[9].get_cbutton()->setCheckable(false);
                }
            }
            if(place == 9){
                fl[7].get_cbutton()->setCheckable(false);
                fl[8].get_cbutton()->setCheckable(false);
                if(!floor[9][0])
                    fl[9].get_cbutton()->setCheckable(false);
            }
            if(place == 10){
                fl[7].get_cbutton()->setCheckable(false);
                fl[8].get_cbutton()->setCheckable(false);
                fl[9].get_cbutton()->setCheckable(false);
            }
        }
    }
    open();
    emit show();
}
void Elavator::moving(){
    if(state == 1){
        inner->setGeometry(inner->x(), inner->y() - 8, inner->width(), inner->height());
    }
    else if(state == 0){
        inner->setGeometry(inner->x(), inner->y() + 8, inner->width(), inner->height());
    }
}

void Elavator::change_extend(){
    extending ^= 1;
    if(extending){
        extend->setStyleSheet("color:red");
        emit doorextendcontrol(place);
        open();
    }
    else if(!extending){
        extend->setStyleSheet("color:black");
        emit doorextendcontrol(place);
        close();
    }
}

void Elavator::open(){
    if(closing){
        dctime.stop();
        closing = false;
    }
    if(!move){
        dotime.setInterval(100/vel);
        dotime.start();
        emit dooropencontrol(place);
    }
}
void Elavator::dooropening(){
    if(count == 19){
        dotime.stop();
        opening = false;
        if(!extending)
            emit wait();
    }
    else{
        opening = true;
        count ++;
        leftdoor->setGeometry(leftdoor->x(), leftdoor->y(), leftdoor->width()-10, leftdoor->height());
        rightdoor->setGeometry(rightdoor->x()+10, rightdoor->y(), rightdoor->width()-10, rightdoor->height());
    }
}
void Elavator::waiting(){
    //wtime = new QTimer();                              //this
    wtime.singleShot(2000/vel, this, SLOT(close()));         //this
    if(automove)
        peopleout();
}
void Elavator::close(){
    if(opening){
        dotime.stop();
        opening = false;
    }
    if(!move && !extending){
        dctime.setInterval(100/vel);
        dctime.start();
        emit doorclosecontrol(place);
    }
}
void Elavator::doorclosing(){
    if(count == 0)
        emit finishclose();
    else{
        closing = true;
        count--;
        leftdoor->setGeometry(leftdoor->x(), leftdoor->y(), leftdoor->width()+10, leftdoor->height());
        rightdoor->setGeometry(rightdoor->x()-10, rightdoor->y(), rightdoor->width()+10, rightdoor->height());
    }
}
void Elavator::finishclosing(){
    dctime.stop();
    closing = false;
    dooropen = false;
    move = false;
    still_on = false;
    go_or_not();
}

void Elavator::randompeople(){
    int r;
    r = rand()%3+1;
    for(int i=0; i<r; i++){
        person_id++;
        People *man = new People;
        p.push_back(man);
        if(!man->way){
            turn_floordown_on(man->from);
        }
        else if(man->way){
            turn_floorup_on(man->from);
        }
        if(man->way){
            switch(man->from){
            case 1:
                emit on_uflb1();
                break;
            case 2:
                emit on_uflb2();
                break;
            case 3:
                emit on_uflb3();
                break;
            case 4:
                emit on_uflb4();
                break;
            case 5:
                emit on_uflb5();
                break;
            case 6:
                emit on_uflb6();
                break;
            case 7:
                emit on_uflb7();
                break;
            case 8:
                emit on_uflb8();
                break;
            case 9:
                emit on_uflb9();
                break;
            default:
                break;
            }
        }
        else{
            switch(man->from){
            case 2:
                emit on_dflb2();
                break;
            case 3:
                emit on_dflb3();
                break;
            case 4:
                emit on_dflb4();
                break;
            case 5:
                emit on_dflb5();
                break;
            case 6:
                emit on_dflb6();
                break;
            case 7:
                emit on_dflb7();
                break;
            case 8:
                emit on_dflb8();
                break;
            case 9:
                emit on_dflb9();
                break;
            case 10:
                emit on_dflb10();
                break;
            default:
                break;
            }
        }
        waitingpeople[man->from-1]++;
        emit show();
        id->append(QString::fromStdString(print_id(man->from, man->to)));
    }
    go_or_not();
}

void Elavator::peopleout(){
    for(int i=p.size()-1; i>=0; i--){
        if(p[i]->to == place && p[i]->in){
            people_in_elavator--;
            delete p[i];
            p.erase(p.begin()+i);
        }
    }
    emit go_out(place);
}
void Elavator::peoplein(){
    int total = 0, in = 0;
    if(state == 1){
        for(int i=0; i<p.size(); i++){
            if(p[i]->from == place && p[i]->way == 1 && !p[i]->in){
                total++;
                if(people_in_elavator<capacity){
                    ap.add_dirt(p[i]->dirty);           //make elavator dirty
                    if(p[i]->allergy && !purify_open){  //allergy people clean elavator
                        purify_open = true;
                        purify.start();
                        ap.get_pushbutton()->setStyleSheet("color:red");
                    }
                    if(p[i]->change_temp == 0)          //people want to make air conditioner low
                        ac.min_temp();
                    else if(p[i]->change_temp == 1)     //people want to make air conditioner high
                        ac.add_temp();
                    in++;
                    p[i]->in = true;
                    people_in_elavator++;
                    floor[p[i]->to-1][0] = true;
                    fl[p[i]->to-1].turn_on_cbutton();
                    waitingpeople[place-1]--;
                    pin.push_back(p[i]);
                }
            }
        }
        if(total>in){
            switch(place){
            case 1:
                emit on_uflb1();
                break;
            case 2:
                emit on_uflb2();
                break;
            case 3:
                emit on_uflb3();
                break;
            case 4:
                emit on_uflb4();
                break;
            case 5:
                emit on_uflb5();
                break;
            case 6:
                emit on_uflb6();
                break;
            case 7:
                emit on_uflb7();
                break;
            case 8:
                emit on_uflb8();
                break;
            case 9:
                emit on_uflb9();
                break;
            default:
                break;
            }
            floor[place-1][1] = true;
        }
    }
    else if(state == 0){
        for(int i=0; i<p.size(); i++){
            if(p[i]->from == place && p[i]->way == 0){
                total++;
                if(people_in_elavator<capacity){
                    ap.add_dirt(p[i]->dirty);
                    if(p[i]->allergy && !purify_open){
                        purify_open = true;
                        purify.start();
                        ap.get_pushbutton()->setStyleSheet("color:red");
                    }
                    if(p[i]->change_temp == 0)
                        ac.min_temp();
                    else if(p[i]->change_temp == 1)
                        ac.add_temp();
                    in++;
                    p[i]->in = true;
                    people_in_elavator++;
                    floor[p[i]->to-1][0] = true;
                    fl[p[i]->to-1].turn_on_cbutton();
                    waitingpeople[place-1]--;
                    pin.push_back(p[i]);
                }
            }
        }
        if(total>in){
            switch(place){
            case 2:
                emit on_dflb2();
                break;
            case 3:
                emit on_dflb3();
                break;
            case 4:
                emit on_dflb4();
                break;
            case 5:
                emit on_dflb5();
                break;
            case 6:
                emit on_dflb6();
                break;
            case 7:
                emit on_dflb7();
                break;
            case 8:
                emit on_dflb8();
                break;
            case 9:
                emit on_dflb9();
                break;
            case 10:
                emit on_dflb10();
                break;
            default:
                break;
            }
            floor[place-1][2] = true;
        }
    }
    emit show();
    emit go_in(pin);
    pin.clear();
}
string Elavator::print_id(int f, int t){
    string s = "";
    s += to_string(person_id);
    s += "  from:  ";
    s += to_string(f);
    s += "  to  :  ";
    s += to_string(t);
    return s;
}

void Elavator::clean(){
    mtime.stop();
    dctime.stop();
    dotime.stop();
    atime.stop();                               // this
    timer.stop();                               // this
    wtime.stop();                               // this
    inner->setGeometry(inner->x(), 770, inner->width(), inner->height());
    leftdoor->setGeometry(670, 230, 211, 281);
    rightdoor->setGeometry(880, 230, 211, 281);
    p.clear();
    id->clear();
    count = 0;
    for(int i=0; i<10; i++){
        for(int j =0;j<3; j++)
            floor[i][j] = false;
    }
    for(int i=0; i<10; i++){
        fl[i].get_cbutton()->setCheckState(Qt::Unchecked);
        waitingpeople[i] = 0;
    }
    count = 0;
    state = 2;
    temp = 25;
    PM = 50;
    vel = 1;
    last_state = 2;
    place = 1;
    move = false;
    still_on = false;
    dooropen = false;
    people_in_elavator = 0;
    automove = false;
    person_id = 0;
    ac.set_temp();
    ap.set_dirt();
    purify_open = false;
    purify.stop();
    ap.get_pushbutton()->setStyleSheet("color:black");
    opening = false;
    closing = false;
    extending = false;
    extend->setStyleSheet("color:black");
    QTimer *t = new QTimer;
    t->singleShot(2000, this, SLOT(total_clean()));
}
void Elavator::total_clean(){
    mtime.stop();
    dctime.stop();
    dotime.stop();
    atime.stop();                               // this
    timer.stop();                               // this
    wtime.stop();
    inner->setGeometry(inner->x(), 770, inner->width(), inner->height());
    leftdoor->setGeometry(670, 230, 211, 281);
    rightdoor->setGeometry(880, 230, 211, 281);
    count = 0;
    state = 2;
    temp = 25;
    PM = 50;
    vel = 1;
    last_state = 2;
    place = 1;
    move = false;
    still_on = false;
    dooropen = false;
    people_in_elavator = 0;
    emit show();
}
void Elavator::change_speed(){
    vel = vel % 4 + 1;
}
void Elavator::add_temp(){
    if(ac.get_temp()<30)
        ac.add_temp();
    emit show();
}
void Elavator::min_temp(){
    if(ac.get_temp()>15)
        ac.min_temp();
    emit show();
}
void Elavator::min_dirt(){
    ap.min_dirt();
    if(ap.get_dirt() <= 50){
        purify_open = false;
        purify.stop();
        ap.get_pushbutton()->setStyleSheet("color:black");
    }
    emit show();
}
void Elavator::open_ap(){
    if(!purify_open){
        purify.start();
        ap.get_pushbutton()->setStyleSheet("color:red");
    }
    min_dirt();
}
