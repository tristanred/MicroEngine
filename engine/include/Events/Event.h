#pragma once

/**
 * Disable the warning about "std::function<void(T)> targetFunction;" not being exported
 * with a dll-interface. This is ok in this case because it is a private member as referenced here
 * https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-1-c4251
 */
#pragma warning(disable:4251)

#include "core.h"
#include <libtech/arraylist.h>
#include <functional>

template <class T>
class EventHandle;

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
