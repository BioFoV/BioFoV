#include "QitemEvent.hpp"

/*******************************************************************************
 * Constructors
 ******************************************************************************/
/**
 * @brief EventItem::EventItem
 * @param parent
 */
EventItem::EventItem(QTreeWidget *parent) :
	PlayerItem(parent)
{

}

/**
 * @brief EventItem::EventItem
 * @param eventname
 * @param parent
 */
EventItem::EventItem(QString eventname, QTreeWidget *parent) :
	PlayerItem(parent)
{
	setText(0, eventname);
	setText(1, TAG_EVENT );
}

/*******************************************************************************
 * Destructor
 ******************************************************************************/
/**
 * @brief EventItem::~EventItem
 */
EventItem::~EventItem(){

}

/*******************************************************************************
 * Functions
 ******************************************************************************/
/**
 * @brief EventItem::setEvent
 * @param inevent
 */
void EventItem::setEvent(EventPtr inevent){
	event = inevent;
}

/**
 * @brief EventItem::getEvent
 * @return
 */
EventPtr EventItem::getEvent(){
	return event;
}

/**
 * @brief EventItem::setPlayer
 * @param inPlayer
 * @return
 */
bool EventItem::setPlayer(PlayerPtr inPlayer){
	event = qSharedPointerDynamicCast<Event>(inPlayer);
	if (event.isNull())
		return false;
	return true;
}

/**
 * @brief EventItem::getPlayer
 * @return
 */
PlayerPtr EventItem::getPlayer(){
	return qSharedPointerDynamicCast<Player>(event);
}
