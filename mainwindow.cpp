#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "AIR_CONDITION_BUTTON.h"
#include "AIR_PURIFIER_BUTTON.h"
#include "BELL.h"
#include "BUILDING.h"
#include "BUTTON.h"
#include "ELAVATOR.h"
#include "EMERGENCY_BUTTON.h"
#include "FLOOR.h"
#include "FLOOR_BUTTON.h"
#include "F_MONITOR.h"
#include "INSANE_MODE_BUTTON.h"
#include "OUTSIDE_BUTTON.h"
#include "E_MONITOR.h"
#include <cmath>
#include <QPixmap>
Building b;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    buttoninput();
    picinput();
    r.setInterval(2000);
    ui->insane->setText("x" + QString::number(b.e.vel));
    ui->automove->setText("simulate");
    simulate = false;
    outpeople = 0;
    inpeople = 0;
    count = 0;
    for(int i=0; i<10; i++){
        for(int j=0; j<4; j++){
            pcontrol[i][j] = 0;
        }
    }
    for(int i=0; i<9; i++){
        b.f[i].set_ubutton(* upbuttonlist[i]);
        connect(b.f[i].get_ubutton(), SIGNAL(clicked()),&b.f[i], SLOT(pushu()));
        connect(b.f[i].get_ubutton(), SIGNAL(clicked()),&b.e, SLOT(go_or_not()));
        connect(&b.f[i], SIGNAL(e_ufloor(int)), &b.e, SLOT(turn_floorup_on(int)));
    }
    for(int i=0; i<9; i++){
        b.f[i+1].set_dbutton(* downbuttonlist[i]);
        connect(b.f[i+1].get_dbutton(), SIGNAL(clicked()),&b.f[i+1], SLOT(pushd()));
        connect(b.f[i+1].get_dbutton(), SIGNAL(clicked()),&b.e, SLOT(go_or_not()));
        connect(&b.f[i+1], SIGNAL(e_dfloor(int)), &b.e, SLOT(turn_floordown_on(int)));
    }
    for(int i=0; i<10; i++){
        b.e.fl[i].set_cbutton(* checkboxlist[i]);
        connect(b.e.fl[i].get_cbutton(), SIGNAL(clicked()),&b.e, SLOT(pushc()));
    }
    for(int i=0; i<10; i++){
        b.f[i].set_ldoor(* labellist[i+1]);
        b.f[i].set_rdoor(* labellist[i+11]);
    }
    b.e.set_inner(* labellist[0]);
    b.e.set_leftdoor(* labellist[21]);
    b.e.set_rightdoor(* labellist[22]);
    b.e.set_idbrowser(* ui->people_id);
    b.e.ap.set_pushbutton(* ui->clean);
    b.e.set_opendoor(* ui->open);
    b.e.set_closedoor(* ui->close);
    b.e.set_extend(* ui->extend);
    connect(b.e.opendoor, SIGNAL(clicked()), &b.e, SLOT(open()));
    connect(b.e.closedoor, SIGNAL(clicked()), &b.e, SLOT(close()));
    connect(b.e.extend, SIGNAL(clicked()), &b.e, SLOT(change_extend()));
    connect(&b.e, SIGNAL(dooropencontrol(int)), this, SLOT(dooropencontrolling(int)));
    connect(&b.e, SIGNAL(doorclosecontrol(int)), this, SLOT(doorclosecontrolling(int)));
    connect(&b.e, SIGNAL(doorextendcontrol(int)), this, SLOT(doorextendcontrolling(int)));
    display();
    connect(&b.e, SIGNAL(off_uflb1()), &b.f[0], SLOT(closeu()));
    connect(&b.e, SIGNAL(off_uflb2()), &b.f[1], SLOT(closeu()));
    connect(&b.e, SIGNAL(off_uflb3()), &b.f[2], SLOT(closeu()));
    connect(&b.e, SIGNAL(off_uflb4()), &b.f[3], SLOT(closeu()));
    connect(&b.e, SIGNAL(off_uflb5()), &b.f[4], SLOT(closeu()));
    connect(&b.e, SIGNAL(off_uflb6()), &b.f[5], SLOT(closeu()));
    connect(&b.e, SIGNAL(off_uflb7()), &b.f[6], SLOT(closeu()));
    connect(&b.e, SIGNAL(off_uflb8()), &b.f[7], SLOT(closeu()));
    connect(&b.e, SIGNAL(off_uflb9()), &b.f[8], SLOT(closeu()));
    connect(&b.e, SIGNAL(off_dflb2()), &b.f[1], SLOT(closed()));
    connect(&b.e, SIGNAL(off_dflb3()), &b.f[2], SLOT(closed()));
    connect(&b.e, SIGNAL(off_dflb4()), &b.f[3], SLOT(closed()));
    connect(&b.e, SIGNAL(off_dflb5()), &b.f[4], SLOT(closed()));
    connect(&b.e, SIGNAL(off_dflb6()), &b.f[5], SLOT(closed()));
    connect(&b.e, SIGNAL(off_dflb7()), &b.f[6], SLOT(closed()));
    connect(&b.e, SIGNAL(off_dflb8()), &b.f[7], SLOT(closed()));
    connect(&b.e, SIGNAL(off_dflb9()), &b.f[8], SLOT(closed()));
    connect(&b.e, SIGNAL(off_dflb10()), &b.f[9], SLOT(closed()));
    connect(&b.e, SIGNAL(on_uflb1()), &b.f[0], SLOT(turn_on_upbutton()));
    connect(&b.e, SIGNAL(on_uflb2()), &b.f[1], SLOT(turn_on_upbutton()));
    connect(&b.e, SIGNAL(on_uflb3()), &b.f[2], SLOT(turn_on_upbutton()));
    connect(&b.e, SIGNAL(on_uflb4()), &b.f[3], SLOT(turn_on_upbutton()));
    connect(&b.e, SIGNAL(on_uflb5()), &b.f[4], SLOT(turn_on_upbutton()));
    connect(&b.e, SIGNAL(on_uflb6()), &b.f[5], SLOT(turn_on_upbutton()));
    connect(&b.e, SIGNAL(on_uflb7()), &b.f[6], SLOT(turn_on_upbutton()));
    connect(&b.e, SIGNAL(on_uflb8()), &b.f[7], SLOT(turn_on_upbutton()));
    connect(&b.e, SIGNAL(on_uflb9()), &b.f[8], SLOT(turn_on_upbutton()));
    connect(&b.e, SIGNAL(on_dflb2()), &b.f[1], SLOT(turn_on_dpbutton()));
    connect(&b.e, SIGNAL(on_dflb3()), &b.f[2], SLOT(turn_on_dpbutton()));
    connect(&b.e, SIGNAL(on_dflb4()), &b.f[3], SLOT(turn_on_dpbutton()));
    connect(&b.e, SIGNAL(on_dflb5()), &b.f[4], SLOT(turn_on_dpbutton()));
    connect(&b.e, SIGNAL(on_dflb6()), &b.f[5], SLOT(turn_on_dpbutton()));
    connect(&b.e, SIGNAL(on_dflb7()), &b.f[6], SLOT(turn_on_dpbutton()));
    connect(&b.e, SIGNAL(on_dflb8()), &b.f[7], SLOT(turn_on_dpbutton()));
    connect(&b.e, SIGNAL(on_dflb9()), &b.f[8], SLOT(turn_on_dpbutton()));
    connect(&b.e, SIGNAL(on_dflb10()), &b.f[9], SLOT(turn_on_dpbutton()));
    connect(&b.e, SIGNAL(show()), this, SLOT(display()));

    connect(ui->automove, SIGNAL(clicked()), this, SLOT(startsimulate()));
    connect(&r, SIGNAL(timeout()),&b.e, SLOT(randompeople()));

    connect(&o, SIGNAL(timeout()), this, SLOT(moveout()));
    connect(&i, SIGNAL(timeout()), this, SLOT(movein()));
    connect(&b.e, SIGNAL(go_out(int)), this, SLOT(out_elavator(int)));
    connect(this, SIGNAL(outover()), &b.e, SLOT(peoplein()));
    connect(&b.e, SIGNAL(go_in(vector<People *>)), this, SLOT(in_elavator(vector<People *>)));
    connect(this, SIGNAL(inover()), this, SLOT(add_tool_man()));
    connect(ui->Emergency, SIGNAL(clicked()), this, SLOT(go_to_ini()));
    connect(this, SIGNAL(e_clean()), &b.e, SLOT(clean()));

    for(int i=0; i<10; i++)
        connect(this, SIGNAL(f_clean()), &b.f[i], SLOT(clean()));

    connect(ui->insane, SIGNAL(clicked()), &b.e, SLOT(change_speed()));
    for(int i=0; i<10; i++)
        connect(ui->insane, SIGNAL(clicked()), &b.f[i], SLOT(change_speed()));
    connect(ui->insane, SIGNAL(clicked()), this, SLOT(change_speed()));
    connect(ui->high, SIGNAL(clicked()), &b.e, SLOT(add_temp()));
    connect(ui->low, SIGNAL(clicked()), &b.e, SLOT(min_temp()));
    connect(ui->clean, SIGNAL(clicked()), &b.e, SLOT(open_ap()));
    b.e.fl[7].get_cbutton()->setCheckable(false);
    b.e.fl[8].get_cbutton()->setCheckable(false);
    b.e.fl[9].get_cbutton()->setCheckable(false);

    employeedb = QSqlDatabase::addDatabase("QMYSQL");
    employeedb.setHostName("140.113.122.247");
    employeedb.setDatabaseName("employeeinfo");
    employeedb.setUserName("demo");
    employeedb.setPassword("1234567890");
    employeedb.setPort(3306);
    bool ok=employeedb.open();
    if(ok)
        qDebug()<<"Successful connection";
    else
        qDebug()<<"Error: Cannot connect";
    //employeeq = new QSqlQuery(employeedb);
}

MainWindow::~MainWindow()
{
    delete ui;   
}

void MainWindow::buttoninput(){
    upbuttonlist.push_back(ui->U1);
    upbuttonlist.push_back(ui->U2);
    upbuttonlist.push_back(ui->U3);
    upbuttonlist.push_back(ui->U4);
    upbuttonlist.push_back(ui->U5);
    upbuttonlist.push_back(ui->U6);
    upbuttonlist.push_back(ui->U7);
    upbuttonlist.push_back(ui->U8);
    upbuttonlist.push_back(ui->U9);
    downbuttonlist.push_back(ui->D2);
    downbuttonlist.push_back(ui->D3);
    downbuttonlist.push_back(ui->D4);
    downbuttonlist.push_back(ui->D5);
    downbuttonlist.push_back(ui->D6);
    downbuttonlist.push_back(ui->D7);
    downbuttonlist.push_back(ui->D8);
    downbuttonlist.push_back(ui->D9);
    downbuttonlist.push_back(ui->D10);
    checkboxlist.push_back(ui->F1);
    checkboxlist.push_back(ui->F2);
    checkboxlist.push_back(ui->F3);
    checkboxlist.push_back(ui->F4);
    checkboxlist.push_back(ui->F5);
    checkboxlist.push_back(ui->F6);
    checkboxlist.push_back(ui->F7);
    checkboxlist.push_back(ui->F8);
    checkboxlist.push_back(ui->F9);
    checkboxlist.push_back(ui->F10);
}

void MainWindow::picinput(){
    QPixmap door(":/image/../door.png");
    QPixmap inner(":/image/../white.png");
    QPixmap background(":/image/../background.png");
    QPixmap noperson(":/image/../noperson.png");
    ui->leftdoor->setPixmap(door);
    ui->rightdoor->setPixmap(door);
    ui->l1->setPixmap(door);
    ui->l2->setPixmap(door);
    ui->l3->setPixmap(door);
    ui->l4->setPixmap(door);
    ui->l5->setPixmap(door);
    ui->l6->setPixmap(door);
    ui->l7->setPixmap(door);
    ui->l8->setPixmap(door);
    ui->l9->setPixmap(door);
    ui->l10->setPixmap(door);
    ui->r1->setPixmap(door);
    ui->r2->setPixmap(door);
    ui->r3->setPixmap(door);
    ui->r4->setPixmap(door);
    ui->r5->setPixmap(door);
    ui->r6->setPixmap(door);
    ui->r7->setPixmap(door);
    ui->r8->setPixmap(door);
    ui->r9->setPixmap(door);
    ui->r10->setPixmap(door);
    ui->elavator->setPixmap(inner);
    ui->background->setPixmap(background);
    ui->p0->setPixmap(noperson);
    ui->p1->setPixmap(noperson);
    ui->p2->setPixmap(noperson);
    ui->p3->setPixmap(noperson);
    ui->p4->setPixmap(noperson);
    ui->p5->setPixmap(noperson);
    ui->p6->setPixmap(noperson);
    ui->p7->setPixmap(noperson);
    ui->p8->setPixmap(noperson);
    ui->p9->setPixmap(noperson);
    labellist.push_back(ui->elavator);      //0
    labellist.push_back(ui->l1);            //1
    labellist.push_back(ui->l2);
    labellist.push_back(ui->l3);
    labellist.push_back(ui->l4);
    labellist.push_back(ui->l5);
    labellist.push_back(ui->l6);
    labellist.push_back(ui->l7);
    labellist.push_back(ui->l8);
    labellist.push_back(ui->l9);
    labellist.push_back(ui->l10);           //10
    labellist.push_back(ui->r1);            //11
    labellist.push_back(ui->r2);
    labellist.push_back(ui->r3);
    labellist.push_back(ui->r4);
    labellist.push_back(ui->r5);
    labellist.push_back(ui->r6);
    labellist.push_back(ui->r7);
    labellist.push_back(ui->r8);
    labellist.push_back(ui->r9);
    labellist.push_back(ui->r10);           //20
    labellist.push_back(ui->leftdoor);      //21
    labellist.push_back(ui->rightdoor);     //22
    peoplelist.push_back(ui->p0);           //0
    peoplelist.push_back(ui->p1);
    peoplelist.push_back(ui->p2);
    peoplelist.push_back(ui->p3);
    peoplelist.push_back(ui->p4);
    peoplelist.push_back(ui->p5);
    peoplelist.push_back(ui->p6);
    peoplelist.push_back(ui->p7);
    peoplelist.push_back(ui->p8);
    peoplelist.push_back(ui->p9);           //9
}

void MainWindow::display(){
    ui->M1->setText(QString::fromStdString(b.FM.f_display(b.e.place, b.e.state)));
    ui->M2->setText(QString::fromStdString(b.FM.f_display(b.e.place, b.e.state)));
    ui->M3->setText(QString::fromStdString(b.FM.f_display(b.e.place, b.e.state)));
    ui->M4->setText(QString::fromStdString(b.FM.f_display(b.e.place, b.e.state)));
    ui->M5->setText(QString::fromStdString(b.FM.f_display(b.e.place, b.e.state)));
    ui->M6->setText(QString::fromStdString(b.FM.f_display(b.e.place, b.e.state)));
    ui->M7->setText(QString::fromStdString(b.FM.f_display(b.e.place, b.e.state)));
    ui->M8->setText(QString::fromStdString(b.FM.f_display(b.e.place, b.e.state)));
    ui->M9->setText(QString::fromStdString(b.FM.f_display(b.e.place, b.e.state)));
    ui->M10->setText(QString::fromStdString(b.FM.f_display(b.e.place, b.e.state)));
    ui->EM->setText(QString::fromStdString(b.e.EM.e_display(b.e.place, b.e.state, b.e.ac.get_temp(), b.e.ap.get_dirt(), b.e.ins.get_button_active(), b.e.dooropen)));
    ui->p_in_e->setText("Total: " + QString::number(b.e.people_in_elavator));
    ui->w1->setText(QString::number(b.e.waitingpeople[0]));
    ui->w2->setText(QString::number(b.e.waitingpeople[1]));
    ui->w3->setText(QString::number(b.e.waitingpeople[2]));
    ui->w4->setText(QString::number(b.e.waitingpeople[3]));
    ui->w5->setText(QString::number(b.e.waitingpeople[4]));
    ui->w6->setText(QString::number(b.e.waitingpeople[5]));
    ui->w7->setText(QString::number(b.e.waitingpeople[6]));
    ui->w8->setText(QString::number(b.e.waitingpeople[7]));
    ui->w9->setText(QString::number(b.e.waitingpeople[8]));
    ui->w10->setText(QString::number(b.e.waitingpeople[9]));
}

void MainWindow::dooropencontrolling(int p){
    b.f[p-1].fopen();
}
void MainWindow::doorclosecontrolling(int p){
    b.f[p-1].fclose();
}
void MainWindow::doorextendcontrolling(int p){
    b.f[p-1].change_extend();
}
void MainWindow::startsimulate(){
    if(!simulate){
        ui->automove->setText("stop simulate");
        simulate = true;
        r.start();
        b.e.fl[7].get_cbutton()->setCheckable(true);
        b.e.fl[8].get_cbutton()->setCheckable(true);
        b.e.fl[9].get_cbutton()->setCheckable(true);
        b.e.automove = true;
    }
    else if(simulate){
        ui->automove->setText("simulate");
        simulate = false;
        r.stop();
    }
}
void MainWindow::add_tool_man(){
    //QPixmap toolman(":/image/../toolman.png");
    //QPixmap noperson(":/image/../noperson.png");
    for(int i=0; i<10; i++){
        if(i<5)
            peoplelist[i]->setGeometry(peoplelist[i]->x(), 440, peoplelist[i]->width(), peoplelist[i]->height());
        else
            peoplelist[i]->setGeometry(peoplelist[i]->x(), 380, peoplelist[i]->width(), peoplelist[i]->height());
        /*if(i<total)
            peoplelist[i]->setPixmap(toolman);
        else
            peoplelist[i]->setPixmap(noperson);*/
    }
}

void MainWindow::out_elavator(int p){
    for(int i=0; i<10; i++){
        if(pcontrol[i][0] == p)
            outpeople++;
    }
    if(outpeople != 0){
        o.setInterval(100/b.e.vel);
        o.start();
    }
    else
        emit outover();
}
void MainWindow::in_elavator(vector<People *> p){
    QPixmap toolman(":/image/../toolman.png");
    QPixmap toolmantemp(":/image/../toolman_temp.png");
    QPixmap toolmanallerge(":/image/../toolman_allerge.png");
    QPixmap toolmanallergetemp(":/image/../toolman_allerge_temp.png");
    //inpeople = p;
    //total = t;
    if(p.size() != 0){
        for(int i=0; i<p.size(); i++){
            for(int j=0; j<10; j++){
                if(pcontrol[j][0] == 0){
                    pcontrol[j][0] = p[i]->to;
                    if(p[i]->allergy)
                        pcontrol[j][2] = 1;
                    if(p[i]->change_temp == 1 || p[i]->change_temp == 0)
                        pcontrol[j][3] = 1;
                    if(pcontrol[j][2] && pcontrol[j][3])
                        peoplelist[j]->setPixmap(toolmanallergetemp);
                    else if(pcontrol[j][2])
                        peoplelist[j]->setPixmap(toolmanallerge);
                    else if(pcontrol[j][3])
                        peoplelist[j]->setPixmap(toolmantemp);
                    else
                        peoplelist[j]->setPixmap(toolman);
                    peoplelist[j]->setGeometry(peoplelist[j]->x(), 550, peoplelist[j]->width(), peoplelist[j]->height());
                    temp.push_back(j);
                    break;
                }
            }
        }
        i.setInterval(100/b.e.vel);
        i.start();
    }
    else
        emit inover();
}

void MainWindow::moveout(){
    QPixmap noperson(":/image/../noperson.png");
    count++;
    for(int i=0; i<10; i++){
        if(pcontrol[i][0] == b.e.place){
            peoplelist[i]->setGeometry(peoplelist[i]->x(), peoplelist[i]->y()+10, peoplelist[i]->width(), peoplelist[i]->height());
        }
    }
    if(count == 10){
        o.stop();
        count = 0;
        for(int i=0; i<10; i++){
            if(pcontrol[i][0] == b.e.place){
                peoplelist[i]->setPixmap(noperson);
                if(i<5)
                    peoplelist[i]->setGeometry(peoplelist[i]->x(), 440, peoplelist[i]->width(), peoplelist[i]->height());
                else
                    peoplelist[i]->setGeometry(peoplelist[i]->x(), 380, peoplelist[i]->width(), peoplelist[i]->height());
                pcontrol[i][0] = 0;
                pcontrol[i][1] = 0;
                pcontrol[i][2] = 0;
                pcontrol[i][3] = 0;
            }
        }
        emit outover();
    }
}
void MainWindow::movein(){
    count++;
    for(int i=0; i<temp.size(); i++){
        peoplelist[temp[i]]->setGeometry(peoplelist[temp[i]]->x(), peoplelist[temp[i]]->y()-10, peoplelist[temp[i]]->width(), peoplelist[temp[i]]->height());
    }
    if(count == 10){
        i.stop();
        count = 0;
        temp.clear();
        emit inover();
    }
}

void MainWindow::change_speed(){
    ui->insane->setText("x" + QString::number(b.e.vel));
}

void MainWindow::go_to_ini(){
    QPixmap noperson(":/image/../noperson.png");
    r.stop();
    o.stop();
    i.stop();
    simulate = false;
    outpeople = 0;
    inpeople = 0;
    for(int i=0; i<10; i++){
        peoplelist[i]->setPixmap(noperson);
        if(i<5)
            peoplelist[i]->setGeometry(peoplelist[i]->x(), 440, peoplelist[i]->width(), peoplelist[i]->height());
        else
            peoplelist[i]->setGeometry(peoplelist[i]->x(), 380, peoplelist[i]->width(), peoplelist[i]->height());
    }
    emit e_clean();
    emit f_clean();
    ui->insane->setText("x" + QString::number(b.e.vel));
}



void MainWindow::on_loginButton_clicked()
{
    employeeq = new QSqlQuery(employeedb);
    bool exist = false;
    if(mg == true && rp == false)
    {

        displaydata = "Manager information\n";
        mgtempid = ui->idinput->text();
        employeeq->exec("select * from mginfo");
        while(employeeq->next()){
            displaydata += (employeeq->value(0).toString()+" "+employeeq->value(1).toString()+"\n");
            if(employeeq->value(0).toString()==mgtempname && employeeq->value(1).toString()==mgtempid)
            {
                exist = true;
                ui->messagetext->setText("login successfully.");
            }
        }
        if(!exist)
        {
            ui->messagetext->setText("login failed.\nNo id named "+mgtempid+" found.");
            b.e.fl[7].get_cbutton()->setCheckable(false);
            b.e.fl[8].get_cbutton()->setCheckable(false);
            b.e.fl[9].get_cbutton()->setCheckable(false);
            cout<<"into false"<<endl;
        }
        else
        {
            b.e.fl[7].get_cbutton()->setCheckable(true);
            b.e.fl[8].get_cbutton()->setCheckable(true);
        }
        ui->displaytext->setText(displaydata);
        displaydata = "";
    }

    else if(mg == false && rp == true)
    {

        displaydata = "Repairman information\n";
        rptempid = ui->idinput->text();
        employeeq->exec("select * from rpinfo");
        while(employeeq->next()){
            displaydata += (employeeq->value(0).toString()+" "+employeeq->value(1).toString()+"\n");
            if(employeeq->value(0).toString()==rptempname && employeeq->value(1).toString()==rptempid)
            {
                exist = true;
                ui->messagetext->setText("login successfully.");
            }
        }
        if(!exist)
        {
            ui->messagetext->setText("login failed.\nNo id named "+rptempid+" found.");
            b.e.fl[7].get_cbutton()->setCheckable(false);
            b.e.fl[8].get_cbutton()->setCheckable(false);
            b.e.fl[9].get_cbutton()->setCheckable(false);
        }
        else
        {
            b.e.fl[8].get_cbutton()->setCheckable(true);
            b.e.fl[9].get_cbutton()->setCheckable(true);
        }

        ui->displaytext->setText(displaydata);
        displaydata = "";
    }

    else
        ui->messagetext->setText("Are you a manager or a repaiman?");
}

void MainWindow::on_registerButton_clicked()
{
    employeeq = new QSqlQuery(employeedb);
    bool exist = false;
    if(mg == true && rp == false)
    {
        displaydata = "Manager information\n";
        mgtempid = ui->idinput->text();
        mgtempname = ui->nameinput->text();
        employeeq->exec("select * from mginfo");
        while(employeeq->next()){
            displaydata += (employeeq->value(0).toString()+" "+employeeq->value(1).toString()+"\n");
            if(employeeq->value(0).toString()==mgtempname || employeeq->value(1).toString()==mgtempid)
            {
                exist = true;
                ui->messagetext->setText("Not valid id.\nId named "+mgtempid+" has already existed.");
            }
        }
        if(!exist)
        {
            ui->messagetext->setText("Registration is successful.\nNo id named "+mgtempid+" exists.");
            employeeq->prepare("insert into mginfo(n,id) values(:n,:id)");
            employeeq->bindValue(":n",mgtempname);
            employeeq->bindValue(":id",mgtempid);
            employeeq->exec();

            displaydata += (mgtempname+" "+mgtempid+"\n");
        }

        ui->displaytext->setText(displaydata);
        displaydata = "";
    }

    else if(mg == false && rp == true)
    {
        displaydata = "Repairman information\n";
        rptempid = ui->idinput->text();
        rptempname = ui->nameinput->text();
        employeeq->exec("select * from rpinfo");
        while(employeeq->next()){
            displaydata += (employeeq->value(0).toString()+" "+employeeq->value(1).toString()+"\n");
            if(employeeq->value(0).toString()==rptempname || employeeq->value(1).toString()==rptempid)
            {
                exist = true;
                ui->messagetext->setText("Not valid id.\nId named "+rptempid+" has already existed.");
            }
        }
        if(!exist)
        {
            ui->messagetext->setText("Registration is successful.\nNo id named "+rptempid+" exists.");
            employeeq->prepare("insert into rpinfo(n,id) values(:n,:id)");
            employeeq->bindValue(":n",rptempname);
            employeeq->bindValue(":id",rptempid);
            employeeq->exec();

            displaydata += (rptempname+" "+rptempid+"\n");
        }

        ui->displaytext->setText(displaydata);
        displaydata = "";
    }
    else
        ui->messagetext->setText("Are you a manager or a repaiman?");
}


//shanjie: what are you doing now? Jolin? Where are you?

void MainWindow::on_mgButton_clicked()
{
    ui->mgButton->setStyleSheet("color:red");
    ui->rpButton->setStyleSheet("color:black");
    ui->messagetext->setText("You are selecting manager!");

    displaydata = "Manager information\n";
    employeeq = new QSqlQuery(employeedb);
    employeeq->exec("select * from mginfo");
    while(employeeq->next())
        displaydata += (employeeq->value(0).toString()+" "+employeeq->value(1).toString()+"\n");
    ui->displaytext->setText(displaydata);
    displaydata = "";

    mg = true;
    rp = false;
}

void MainWindow::on_rpButton_clicked()
{
    ui->rpButton->setStyleSheet("color:red");
    ui->mgButton->setStyleSheet("color:black");
    ui->messagetext->setText("You are selecting repairman!");

    displaydata = "Repairman information\n";
    employeeq = new QSqlQuery(employeedb);
    employeeq->exec("select * from rpinfo");
    while(employeeq->next())
        displaydata += (employeeq->value(0).toString()+" "+employeeq->value(1).toString()+"\n");
    ui->displaytext->setText(displaydata);
    displaydata = "";

    mg = false;
    rp = true;
}



void MainWindow::on_deleteButton_clicked()
{


    employeeq = new QSqlQuery(employeedb);
    if(mg == true && rp == false)
    {
        employeeq->exec("delete from mginfo");
        ui->displaytext->setText("Manager information\n");
        ui->messagetext->setText("Delete all manager data successfully!");
    }
    else if(mg == false && rp == true)
    {
        employeeq->exec("delete from rpinfo");
        ui->displaytext->setText("Repairman information\n");
        ui->messagetext->setText("Delete all repairman data successfully!");
    }
    else
        ui->messagetext->setText("Are you a manager or a repaiman?");
}
