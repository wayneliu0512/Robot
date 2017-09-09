//
//  EventManager.h
//  EventManager
//
//  Created by Mayank Saini on 15/12/12.
//  Copyright (c) 2012 Hashstash Studios. All rights reserved.
//

#ifndef EventManager_EventManager_h
#define EventManager_EventManager_h

#include <vector>
#include <map>
#include <string>
#include <Event/eventmessage.h>

using namespace std;
namespace Mage {
    #define TEMPLATE template <typename Class> 
    
    // Abstract Class for EventHandler to notify of a change
    class EventHandlerBase {
    public:
        virtual void execute(const EventMessage& msg) = 0;
    };
    
    // Event Handler Class : Handles Callback
    template <typename Class>
    class EventHandler : public EventHandlerBase{
        // Defining type for function pointer
        typedef void (Class::*_fptr)(const EventMessage&);
        
        
        
    public:
        // Object of the Listener
        Class *object;
        // Function for callback
        _fptr function;
        
        EventHandler(Class *obj, _fptr func) {
            object = obj;
            function = func;
        }
        
        void execute(const EventMessage& msg) {
            (object->*function)(msg);
        }
    };
    
    // Class to create a event
    class Event {
        // To store all listeners of the event
        typedef std::map<int, EventHandlerBase*> EventHandlerMap;
        EventHandlerMap handlers;
        int count;
    public:
        
        template <typename Class>
        void addListener(Class *obj, void (Class::*func)(const EventMessage&)) {
            handlers[count] = new EventHandler<Class>(obj, func);
            count++;
        }
        
        void execute(const EventMessage & msg) {
            for (EventHandlerMap::iterator it = handlers.begin(); it != handlers.end(); ++it) {
                it->second->execute(msg);
            }
        }

    };
    
    class EventManager {
        struct EventType {
            Event *event;
            string name;
        };
        
        std::vector<EventType> _events;
        
        static EventManager *_Instance;
        
        EventManager(){}
    public:
        static EventManager* Instance() {
            if (!_Instance) {
                _Instance = new EventManager();
            }
            return _Instance;
        }
        
        void createEvent(QString name) {
			for(vector<EventType>::iterator it = _events.begin(); it != _events.end(); ++it) {
				EventType e = *it;
                if(e.name.compare(name.toStdString()) == 0)
					return;
			}
            EventType e;
            e.event = new Event();
            e.name = name.toStdString();
            _events.push_back(e);
        }
        
        template <typename Class>
        bool subscribe(QString name, Class *obj, void (Class::*func)(const EventMessage &)) {
            for (vector<EventType>::iterator it = _events.begin(); it != _events.end(); ++it) {
                EventType e = *it;
                if (e.name.compare(name.toStdString()) == 0) {
                    e.event->addListener(obj, func);
                    return true;
                }
            }
            return false;
        }
        
        void execute(QString name, const EventMessage& msg) {
            for (vector<EventType>::iterator it = _events.begin(); it != _events.end(); ++it) {
                EventType e = *it;
                if (e.name.compare(name.toStdString()) == 0) {
                    e.event->execute(msg);
                }
            }
        }
    };

}
#endif
