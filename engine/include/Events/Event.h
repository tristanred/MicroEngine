#pragma once

#ifdef _WIN32
/**
 * Disable the warning about "std::function<void(T)> targetFunction;" not being exported
 * with a dll-interface. This is ok in this case because it is a private member as referenced here
 * https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-1-c4251
 */
#pragma warning(disable:4251)
#endif

/* < Event System >
 * Events allow classes to expose internal events of the class to outside
 * callers. When an event is declared, other classes can add a callback method
 * to be called when the event is raised. The Event class will call each
 * callback one after the other with an argument.
 *
 * When a caller uses the .Listen method to attach a callback, a handle of type
 * EventHandle is returned. This object can be .Disposed() to stop listening
 * to that particular event. It also releases resources taken by the listener.
 */


#include "core.h"
#include <libtech/arraylist.h>
#include <functional>

/*
 * Since both classes depend on each other, I am forward-declaring them both
 * as early as possible.
 */
template <class T>
class EventHandle;
template <>
class EventHandle<void>;

template <class T>
class Event;
template <>
class Event<void>;


template <class T>
class ENGINE_CLASS EventHandle
{
    friend class Event<T>;
public:
    EventHandle(Event<T>* target, std::function<void(T)> func)
    {
        this->isDisposed = false;
        this->targetEvent = target;
        this->targetFunction = func;
    };
    
    ~EventHandle()
    {
    };
    
    void Dispose()
    {
        assert(targetEvent != NULL);
        
        if(this->isDisposed == false)
        {
            targetEvent->Listeners->RemoveObject(this);
            this->isDisposed = true;
        }
    };
    
private:
    bool isDisposed;
    Event<T>* targetEvent;
    std::function<void(T)> targetFunction;
};

template <>
class ENGINE_CLASS EventHandle<void>
{
    friend class Event<void>;
public:
    EventHandle(Event<void>* target, std::function<void()> func)
    {
        this->isDisposed = false;
        this->targetEvent = target;
        this->targetFunction = func;
    };
    
    ~EventHandle()
    {
    };
    
    void Dispose();
    
private:
    bool isDisposed;
    Event<void>* targetEvent;
    std::function<void()> targetFunction;
};



template <class T>
class ENGINE_CLASS Event
{
    friend class EventHandle<T>;
public:
    Event()
    {
        this->Listeners = new ArrayList<EventHandle<T>*>();
    };

    ~Event()
    {
        this->Listeners->Clear();
        delete(this->Listeners);
    };
    
    EventHandle<T>* Listen(std::function<void(T)> listenFunction)
    {
        EventHandle<T>* handle = new EventHandle<T>(this, listenFunction);

        this->Listeners->Add(handle);

        return handle;
    };
    
    void Dispatch(T argument)
    {
        for(int i = 0; i < this->Listeners->Count(); i++)
        {
            EventHandle<T>* handel = this->Listeners->Get(i);
            handel->targetFunction(argument);
        }
    };

private:
    ArrayList<EventHandle<T>*>* Listeners;
};

template <>
class ENGINE_CLASS Event<void>
{
    friend class EventHandle<void>;
public:
    Event()
    {
        this->Listeners = new ArrayList<EventHandle<void>*>();
    };
    
    ~Event()
    {
        this->Listeners->Clear();
        delete(this->Listeners);
    };
    
    EventHandle<void>* Listen(std::function<void()> listenFunction)
    {
        EventHandle<void>* handle = new EventHandle<void>(this, listenFunction);
        
        this->Listeners->Add(handle);
        
        return handle;
    };
    
    void Dispatch()
    {
        for(int i = 0; i < this->Listeners->Count(); i++)
        {
            EventHandle<void>* handel = this->Listeners->Get(i);
            handel->targetFunction();
        }
    };
    
private:
    ArrayList<EventHandle<void>*>* Listeners;
};

void EventHandle<void>::Dispose()
{
    assert(targetEvent != NULL);
    
    if(this->isDisposed == false)
    {
        targetEvent->Listeners->RemoveObject(this);
        this->isDisposed = true;
    }
}
