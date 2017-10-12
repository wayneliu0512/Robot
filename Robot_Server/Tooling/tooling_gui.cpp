#include "tooling_gui.h"
#include "widget.h"

Tooling_GUI::Tooling_GUI(QObject *parent) :QObject(parent)
{
}

Tooling_GUI::Tooling_GUI(Tooling *_tooling, QListWidget *_list, QLabel *_light, QLCDNumber* _clock, QTimer* _flashTimer)
{
    list = _list;
    light = _light;
    clock = _clock;
    flashTimer = _flashTimer;

    tooling = _tooling;
    connect(tooling, SIGNAL(updateGUI(Tooling::State)), this, SLOT(updateGUI(Tooling::State)));
    connect(tooling->communication, SIGNAL(update_GUI_Message(QString)), this, SLOT(update_GUI_Message(QString)));

    clockTimer = new QTimer;
    connect(clockTimer, SIGNAL(timeout()), this, SLOT(clockTimeUpdate()));
    clockTimer->setInterval(1000);

    testItemList = new QStringList;

    initializeClock();
}

Tooling_GUI::~Tooling_GUI()
{
    delete clockTimer;
    delete testItemList;
}

void Tooling_GUI::initializeClock()
{
    clockTimer->stop();

    clockTime.setHMS(0,0,0);

    QString clockText = clockTime.toString("mm:ss");

    clock->display(clockText);
}

void Tooling_GUI::update_GUI_Message(QString _str)
{
    testItemList->prepend(_str);
    list->clear();
    list->addItems(*testItemList);
}

void Tooling_GUI::updateGUI(Tooling::State _state)
{
    switch(_state)
    {
    case Tooling::ONLINE:
        clockTimer->stop();
        setLight(GREEN, false);
        testItemList->clear();
        list->clear();
        break;
    case Tooling::OFFLINE:
        clockTimer->stop();
        setLight(GREY, false);
        break;
    case Tooling::START_TESTING:
        clockTime.setHMS(0,0,0);
        clockTimer->start();
        setLight(YELLOW, true);
        break;
    }
}

void Tooling_GUI::setLight(Color _color, bool _flash)
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

void Tooling_GUI::flashYellowTimeout()
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

void Tooling_GUI::flashGreenTimeout()
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

void Tooling_GUI::flashRedTimeout()
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

void Tooling_GUI::clockTimeUpdate()
{
    clockTime = clockTime.addSecs(1);

    QString clockText = clockTime.toString("mm:ss");

    if ((clockTime.second() % 2) == 0)
        clockText[2] = ' ';

    clock->display(clockText);

//    if(clockTime >= QTime(0,15))
//    {
//        clockTimer->stop();
//        QString msgText = "Tooling" + QString::number(tooling->toolingNum) + "Timeout!";
//        QMessageBox::information(nullptr, tr("information"), msgText, QMessageBox::Ok);
//    }
}
