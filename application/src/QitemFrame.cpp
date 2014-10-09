#include "QitemFrame.hpp"

FrameItem::FrameItem(FramePtr pframe, QTreeWidget *parent) :
    PlayerItem(parent)
{
    frame = pframe;
    setText(0,QString("%1").arg(frame->getNumber()));
    setText(1,QString(TAG_FRAME));
}

FramePtr FrameItem::getFrameRef(){
    return frame;
}

bool FrameItem::setPlayer(PlayerPtr inPlayer){
    frame = qSharedPointerDynamicCast<Frame>(inPlayer);
    if (frame.isNull())
        return false;
    return true;
}

PlayerPtr FrameItem::getPlayer(){
    return qSharedPointerDynamicCast<Player>(frame);
}
