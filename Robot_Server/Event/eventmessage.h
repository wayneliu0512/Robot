#ifndef EVENTMESSAGE_H
#define EVENTMESSAGE_H

#include <task.h>
#include <QString>

class EventMessage
{
public:
    //通訊種類是屬於ACK , 或是NOACK
    enum ACK_Type{ ACK, NOACK};
    enum Object_Type{ FromRobot, FromTooling, FromCCD};

    EventMessage(QString _data, int _toolingNum, ACK_Type _ackType, Object_Type _objectType);

    EventMessage(QString _ID, ACK_Type _ackType, Object_Type _objectType);

    EventMessage(Task* _task);

    EventMessage(){}

    ~EventMessage(){}

    Task *task;

    ACK_Type ackType;

    Object_Type objectType;

    int toolingNum;

    QString data, ID;
};

#endif // EVENTMESSAGE_H
