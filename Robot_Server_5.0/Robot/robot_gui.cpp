#include "robot_gui.h"
#include "widget.h"

Robot_GUI::Robot_GUI(QObject *parent) :QObject(parent)
{   
}

Robot_GUI::Robot_GUI(Robot *_robot, QLabel *_label, QLabel *_light, QTimer* _flashTimer)
{
    robot = _robot;
    label = _label;
    light = _light;
    flashTimer = _flashTimer;

    connect(robot, SIGNAL(updateGUI(Robot::State)), this, SLOT(updateGUI(Robot::State)));
}

Robot_GUI::~Robot_GUI()
{
}

void Robot_GUI::updateGUI(Robot::State _state)
{
    switch(_state)
    {
    case Robot::ONLINE:
        setLight(GREEN, false);
        break;
    case Robot::OFFLINE:
        setLight(GREY, false);
        break;
    case Robot::IN_ACTION:
        setLight(YELLOW, true);
        break;
    }
}

void Robot_GUI::setLight(Color _color, bool _flash)
{    
    disconnect(flashTimer, SIGNAL(timeout()), this, SLOT(flashRedTimeout()));
    disconnect(flashTimer, SIGNAL(timeout()), this, SLOT(flashGreenTimeout()));
    disconnect(flashTimer, SIGNAL(timeout()), this, SLOT(flashYellowTimeout()));

    switch(_flash)
    {
    case true:

        switch(_color)
        {
        case RED:
            connect(flashTimer, SIGNAL(timeout()), this, SLOT(flashRedTimeout()));
            break;
        case GREEN:
            connect(flashTimer, SIGNAL(timeout()), this, SLOT(flashGreenTimeout()));
            break;
        case YELLOW:
            connect(flashTimer, SIGNAL(timeout()), this, SLOT(flashYellowTimeout()));
            break;
        }

        break;

    case false:

        switch(_color)
        {
        case RED:
            light->setPixmap(QPixmap(":/new/prefix1/IMG_Red.png"));
            break;
        case GREEN:
            light->setPixmap(QPixmap(":/new/prefix1/IMG_Green.png"));
            break;
        case YELLOW:
            light->setPixmap(QPixmap(":/new/prefix1/IMG_Yellow.png"));
            break;
        case GREY:
            light->setPixmap(QPixmap(":/new/prefix1/IMG_Grey.png"));
            break;
        }

        break;
    }

}

void Robot_GUI::flashYellowTimeout()
{
    //Flashing by switch yellow and grey
    switch(Widget::flashCounter % 2)
    {
    case 0:
        light->setPixmap(QPixmap(":/new/prefix1/IMG_Grey.png"));
        break;
    case 1:
        light->setPixmap(QPixmap(":/new/prefix1/IMG_Yellow.png"));
        break;
    }
}

void Robot_GUI::flashGreenTimeout()
{
    //Flashing by switch yellow and grey
    switch(Widget::flashCounter % 2)
    {
    case 0:
        light->setPixmap(QPixmap(":/new/prefix1/IMG_Grey.png"));
        break;
    case 1:
        light->setPixmap(QPixmap(":/new/prefix1/IMG_Green.png"));
        break;

    }
}

void Robot_GUI::flashRedTimeout()
{
    //Flashing by switch yellow and grey
    switch(Widget::flashCounter % 2)
    {
    case 0:
        light->setPixmap(QPixmap(":/new/prefix1/IMG_Grey.png"));
        break;
    case 1:
        light->setPixmap(QPixmap(":/new/prefix1/IMG_Red.png"));
        break;
    }
}


