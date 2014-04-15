#ifndef EVENTITEM_HPP
#define EVENTITEM_HPP

#include <QTreeWidgetItem>

#ifndef INC_VIDEO
#define INC_VIDEO
#include "Event/Event.hpp"
#endif

#ifndef INC_PLAYERITEM
#define INC_PLAYERITEM
#include <QitemPlayer.hpp>
#endif

#define TAG_EVENT "Event"

class EventItem : public PlayerItem
{
public:
    // Constructors
    explicit EventItem(QTreeWidget *parent = 0);
    EventItem(QString eventname, QTreeWidget *parent = 0);

    // Destructors
    ~EventItem();

    // Functions
    EventPtr getEvent();
    void setEvent(EventPtr inevent);

    bool setPlayer(PlayerPtr inPlayer);
    PlayerPtr getPlayer();
private:
    EventPtr event;
};

#endif // EVENTITEM_HPP
