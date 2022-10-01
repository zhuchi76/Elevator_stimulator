QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    air_condition_button.cpp \
    air_purifier_button.cpp \
    bell.cpp \
    building.cpp \
    button.cpp \
    e_monitor.cpp \
    elavator.cpp \
    emergency_button.cpp \
    employee.cpp \
    f_monitor.cpp \
    floor.cpp \
    floor_button.cpp \
    guess.cpp \
    insane_mode_button.cpp \
    main.cpp \
    mainwindow.cpp \
    manager.cpp \
    outside_button.cpp \
    people.cpp \
    repairman.cpp \
    safe_system.cpp

HEADERS += \
    AIR_CONDITION_BUTTON.h \
    AIR_PURIFIER_BUTTON.h \
    BELL.h \
    BUILDING.h \
    BUTTON.h \
    ELAVATOR.h \
    EMERGENCY_BUTTON.h \
    EMPLOYEE.h \
    E_MONITOR.h \
    FLOOR.h \
    FLOOR_BUTTON.h \
    F_MONITOR.h \
    GUESS.h \
    INSANE_MODE_BUTTON.h \
    MANAGER.h \
    OUTSIDE_BUTTON.h \
    PEOPLE.h \
    REPAIRMAN.h \
    SAFE_SYSTEM.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    image.qrc

DISTFILES +=
