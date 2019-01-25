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
 *
 * Due to the way the class was programmed, the Event class takes a single
 * template parameter to indicate the type of parameter that is passed with an
 * event. If multiple parameters are required they have to be grouped in a
 * class. Also, if no parameters are required, we must use the stub-type
 * EVENT_VOID. This still passes a parameter to the callback functions but
 * it is an indicator that the parameter is unused. This distinction is needed
 * because the Event type takes a template T and std::functions are declared
 * like std::function<void(T)> to use 1 parameter but to use it without
 * parameters we must omit the T entirely, setting it to void, for example like
 * std::function<void(void)> does not work. Must be std::function<void()>.
 * It must be possible to have a solution due to SFINAE but I have to work out
 * the specifics.
 */

struct EVENT_VOID
{
    unsigned int stub;
};

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
