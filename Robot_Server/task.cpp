#include "task.h"
#include "QTime"
#include "QDebug"
Task::Task(Target _target, QString _command)
{
    target = _target;
    command = _command;
    nextTask = nullptr;

    ID = QString::number(QDateTime::currentMSecsSinceEpoch());
}

Task::Task(Target _target, QString _command, Task *_nextTask = nullptr)
{
    target = _target;
    command = _command;
    nextTask = _nextTask;

    ID = QString::number(QDateTime::currentMSecsSinceEpoch());

}

Task::~Task()
{
    //delete nextTask;
}

Task* Task::Next(Task *_nextTask)
{
    nextTask = _nextTask;
    return _nextTask;
}

QString Task::targetToString()
{
    switch(target)
    {
    case Robot:
        return "Robot";
    case CCD:
        return "CCD";
    case Tooling:
        return "Tooling";
    case Center:
        return "Center";
    case UI:
        return "UI";
    }

    return "error";
}
