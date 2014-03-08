#ifndef BASEELEMENT_H
#define BASEELEMENT_H

#include <QObject>
#include <QLinkedList>

template <class B>
class BaseElement
{
public:
    class PushListener
    {
    public:
        virtual void onPush(B& buffer) = 0;
    };

private:
    QLinkedList<PushListener*> _listeners;

public:
    void addPushListener(PushListener &element);
    void removePushListener(PushListener &element);

protected:
    void notify(B&);
};

template <class B>
void BaseElement<B>::addPushListener(PushListener &element)
{
    _listeners.append(&element);
}

template <class B>
void BaseElement<B>::removePushListener(PushListener &element)
{
    _listeners.removeOne(&element);
}

template <class B>
void BaseElement<B>::notify(B& buffer)
{
    typename QLinkedList<BaseElement::PushListener*>::iterator it;
    for(it = _listeners.begin(); it != _listeners.end(); ++it)
    {
        (*it)->onPush(buffer);
    }
}

#endif // BASEELEMENT_H
