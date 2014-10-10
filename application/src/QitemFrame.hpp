#ifndef QITEMFRAME_HPP
#define QITEMFRAME_HPP

#ifndef INC_FRAME
#define INC_FRAME
#include "Frame/Frame.hpp"
#endif

#ifndef INC_PLAYERITEM
#define INC_PLAYERITEM
#include <QitemPlayer.hpp>
#endif

#define TAG_FRAME "Frame"

#include <QTreeWidgetItem>

/**
 * @brief The FrameItem class
 */
class FrameItem : public PlayerItem
{
public:
    FrameItem(FramePtr pframe, QTreeWidget *parent = 0);

    FramePtr getFrameRef();

    bool setPlayer(PlayerPtr inPlayer);
    PlayerPtr getPlayer();
private:
    /**
     * @brief frame
     */
    FramePtr frame;
};

#endif // QITEMFRAME_HPP
