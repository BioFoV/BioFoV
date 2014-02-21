#ifndef EVENTITEM_HPP
#define EVENTITEM_HPP

#include <QTreeWidgetItem>

#ifndef INC_VIDEO
#define INC_VIDEO
#include "Event/Event.hpp"
#endif

#define TAG_EVENT "Event"

class EventItem : public QTreeWidgetItem
{
public:
    // Constructors
    explicit EventItem(QTreeWidget *parent = 0);
    EventItem(QString eventname, QTreeWidget *parent = 0);

    // Destructors
    ~EventItem();

    // Functions
    Event* getEvent();
    void setEvent(Event* inevent);
private:
    Event* event;
};

#endif // EVENTITEM_HPP
