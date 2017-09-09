#-------------------------------------------------
#
# Project created by QtCreator 2017-06-16T13:51:06
#
#-------------------------------------------------

QT       += core gui \
            network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Arm_Server_5.0
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        widget.cpp \
    task.cpp \
    base.cpp \
    taskmanager.cpp \
    command.cpp \
    actionmanager.cpp \
    Robot/robot.cpp \
    Robot/robot_communication.cpp \
    Tooling/tooling.cpp \
    Tooling/tooling_communication.cpp \
    CCD/ccd.cpp \
    Event/EventManager.cpp \
    Event/eventmessage.cpp \
    Tooling/tooling_gui.cpp \
    Robot/robot_gui.cpp \
    CCD/ccd_communication.cpp \
    CCD/ccd_gui.cpp \
    snprescandialog.cpp \
    startupsetting.cpp

HEADERS += \
        widget.h \
    task.h \
    base.h \
    taskmanager.h \
    command.h \
    actionmanager.h \
    Robot/robot.h \
    Robot/robot_communication.h \
    Tooling/tooling.h \
    Tooling/tooling_communication.h \
    CCD/ccd.h \
    Event/EventManager.h \
    Event/eventmessage.h \
    Tooling/tooling_gui.h \
    Robot/robot_gui.h \
    CCD/ccd_communication.h \
    CCD/ccd_gui.h \
    snprescandialog.h \
    startupsetting.h

FORMS += \
        widget.ui \
    snprescandialog.ui

DISTFILES +=

RESOURCES += \
    myresourse.qrc
