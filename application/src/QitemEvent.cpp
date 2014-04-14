#include "QitemEvent.hpp"

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
    setText(0, eventname);
    setText(1, TAG_EVENT );
}

/*******************************************************************************
 * Destructor
 ******************************************************************************/
EventItem::~EventItem(){

}

/*******************************************************************************
 * Functions
 ******************************************************************************/
void EventItem::setEvent(EventPtr inevent){
    event = inevent;
}

EventPtr EventItem::getEvent(){
    return event;
}
