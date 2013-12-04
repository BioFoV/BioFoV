#include "eventitem.hpp"

EventItem::EventItem(QListWidget *parent) :
    QListWidgetItem(parent)
{

}

EventItem::EventItem(QString eventname, QListWidget *parent) :
    QListWidgetItem(eventname, parent)
{

}

void EventItem::setEvent(Event* inevent){
    event = inevent;
}

Event* EventItem::getEvent(){
    return event;
}
