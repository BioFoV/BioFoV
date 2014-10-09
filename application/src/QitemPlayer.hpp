#ifndef QPLAYERITEM_HPP
#define QPLAYERITEM_HPP

#ifndef INC_PLAYER
#define INC_PLAYER
#include <player.hpp>
#endif

#include <QTreeWidgetItem>

class PlayerItem : public QTreeWidgetItem
{
public:
    explicit PlayerItem(QTreeWidget *parent = 0);

    virtual bool setPlayer(PlayerPtr inPlayer) = 0;
    virtual PlayerPtr getPlayer() = 0;
signals:

public slots:

};

#endif // QPLAYERITEM_HPP
