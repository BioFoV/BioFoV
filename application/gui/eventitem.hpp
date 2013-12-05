#ifndef EVENTITEM_HPP
#define EVENTITEM_HPP

#include <QListWidgetItem>

#ifndef INC_VIDEO
#define INC_VIDEO
#include "../framework/Event/Event.hpp"
#endif

class EventItem : public QListWidgetItem
{
public:
    // Constructors
    explicit EventItem(QListWidget *parent = 0);
    EventItem(QString eventname, QListWidget *parent = 0);

    // Destructors
    ~EventItem();

    // Functions
    Event* getEvent();
    void setEvent(Event* inevent);
private:
    Event* event;
};

#endif // EVENTITEM_HPP
