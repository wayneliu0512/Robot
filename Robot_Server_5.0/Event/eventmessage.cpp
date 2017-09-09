#include "eventmessage.h"

EventMessage::EventMessage(QString _data, int _toolingNum, ACK_Type _ackType, Object_Type _objectType)
{
    data = _data;
    toolingNum = _toolingNum;
    ackType = _ackType;
    objectType = _objectType;
}

EventMessage::EventMessage(QString _ID, ACK_Type _ackType, Object_Type _objectType)
{
    ID = _ID;
    ackType = _ackType;
    objectType = _objectType;
}

EventMessage::EventMessage(Task *_task)
{
    task = _task;
}
