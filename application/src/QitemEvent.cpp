#include "QitemEvent.hpp"

/*******************************************************************************
 * Constructors
 ******************************************************************************/
EventItem::EventItem(QTreeWidget *parent) :
    PlayerItem(parent)
{

}

EventItem::EventItem(QString eventname, QTreeWidget *parent) :
    PlayerItem(parent)
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

bool EventItem::setPlayer(PlayerPtr inPlayer){
    event = qSharedPointerDynamicCast<Event>(inPlayer);
    if (event.isNull())
        return false;
    return true;
}

PlayerPtr EventItem::getPlayer(){
    return qSharedPointerDynamicCast<Player>(event);
}
