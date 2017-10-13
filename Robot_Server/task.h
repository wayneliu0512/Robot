#ifndef TASK_H
#define TASK_H
#include<QString>
#include<base.h>
#include<command.h>
#include<base.h>

class Task
{
public:
    enum Target{ Tooling, Robot, CCD, Center, UI};

    Task(Target _target, QString _command);

    Task(Target _target, QString _command, Task *_nextTask);

    ~Task();

    QString command;  //要執行的任務
    QString ID;  //任務ID(TimeStamp,13字元)

    int targetID; //執行任務的對象中的第幾個
    Target target; //執行任務的對象類型

    Task *nextTask; //任務完成後會執行這個任務

    QString targetToString();

    Task* Next(Task *);
};

#endif // TASK_H
