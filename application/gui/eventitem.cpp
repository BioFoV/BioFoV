#include "eventitem.hpp"

/*******************************************************************************
 * Constructors
 ******************************************************************************/
EventItem::EventItem(QListWidget *parent) :
    QListWidgetItem(parent)
{

}

EventItem::EventItem(QString eventname, QListWidget *parent) :
    QListWidgetItem(eventname, parent)
{

}

/*******************************************************************************
 * Destructor
 ******************************************************************************/
EventItem::~EventItem(){
    delete event;
}

/*******************************************************************************
 * Functions
 ******************************************************************************/
void EventItem::setEvent(Event* inevent){
    event = inevent;
}

Event* EventItem::getEvent(){
    return event;
}
