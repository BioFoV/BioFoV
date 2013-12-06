#include "eventitem.hpp"

/*******************************************************************************
 * Constructors
 ******************************************************************************/
EventItem::EventItem(QTreeWidget *parent) :
    QTreeWidgetItem(parent)
{

}

EventItem::EventItem(QString eventname, QTreeWidget *parent) :
    QTreeWidgetItem(parent)
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
