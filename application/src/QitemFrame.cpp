#include "QitemFrame.hpp"

/**
 * @brief FrameItem::FrameItem
 * @param pframe
 * @param parent
 */
FrameItem::FrameItem(FramePtr pframe, QTreeWidget *parent) :
	PlayerItem(parent)
{
	frame = pframe;
	setText(0,QString("%1").arg(frame->getNumber()));
	setText(1,QString(TAG_FRAME));
}

/**
 * @brief FrameItem::getFrameRef
 * @return
 */
FramePtr FrameItem::getFrameRef(){
	return frame;
}

/**
 * @brief FrameItem::setPlayer
 * @param inPlayer
 * @return
 */
bool FrameItem::setPlayer(PlayerPtr inPlayer){
	frame = qSharedPointerDynamicCast<Frame>(inPlayer);
	if (frame.isNull())
		return false;
	return true;
}

/**
 * @brief FrameItem::getPlayer
 * @return
 */
PlayerPtr FrameItem::getPlayer(){
	return qSharedPointerDynamicCast<Player>(frame);
}
