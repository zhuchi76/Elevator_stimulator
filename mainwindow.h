#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QList>
#include <QTimer>
#include <QMainWindow>
#include "FLOOR.h"
#include <ui_mainwindow.h>
#include <QTimer>
#include <QDebug>
#include <QSqlResult>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>
#include <string>
#include "PEOPLE.h"
using namespace std;
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool mg=false,rp=false;
private:
    void buttoninput();
    void picinput();
    QTimer r;           //timer for random people
    QTimer o;           //people go out elavator
    QTimer i;           //people go in elavator
    bool simulate;      //simulate mode
    int outpeople;      //how many people go out
    int inpeople;       //how many people go in
    int total;          //how many people in elavator
    int count;
    int pcontrol[10][4];
    vector<int> temp;
private slots:
    void display();
    void dooropencontrolling(int);
    void doorclosecontrolling(int);
    void doorextendcontrolling(int);
    void on_loginButton_clicked();
    void on_registerButton_clicked();
    void on_mgButton_clicked();
    void on_rpButton_clicked();
    void on_deleteButton_clicked();
    void startsimulate();
    void add_tool_man();
    void out_elavator(int);
    void in_elavator(vector<People *>);
    void moveout();
    void movein();
    void change_speed();
    void go_to_ini();
private:
    Ui::MainWindow *ui;
    QList <QPushButton *> upbuttonlist;
    QList <QPushButton *> downbuttonlist;
    QList <QCheckBox *> checkboxlist;
    QList <QLabel *> labellist;
    QList <QLabel *> peoplelist;
    QSqlDatabase employeedb;
    QSqlQuery *employeeq;
    QString mgtempid;
    QString mgtempname;
    QString rptempid;
    QString rptempname;
    QString displaydata;
signals:
    void outover();
    void inover();
    void e_clean();
    void f_clean();
};
#endif // MAINWINDOW_H
