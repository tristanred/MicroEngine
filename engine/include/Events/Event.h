#pragma once

#include "core.h"
#include <libtech/arraylist.h>
#include <functional>

template <class T>
class EventHandle;

template <class T>
class ENGINE_CLASS Event
{
public:
    Event()
    {
        this->Listeners = new ArrayList<std::function<void(T)>>();
    };

    ~Event()
    {
        this->Listeners->Clear();
    };

    EventHandle<T>* Listen(std::function<void(T)> listenFunction)
    {
        EventHandle<T>* handle = new EventHandle<T>(this, listenFunction);
        
        this->Listeners->Add(listenFunction);
        
        return handle;
    };

private:
    ArrayList<std::function<void(T)>>* Listeners;
};

template <class T>
class ENGINE_CLASS EventHandle
{
    friend class Event<T>;
public:
    EventHandle(Event<T>* target, std::function<T> func)
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
            targetEvent->Listeners->RemoveObject(targetFunction);
            this->isDisposed = true;
        }
    };

private:
    bool isDisposed;
    Event<T>* targetEvent;
    std::function<T> targetFunction;
};
