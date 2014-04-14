#include "QitemFrame.hpp"

FrameItem::FrameItem(FramePtr pframe)
{
    frame = pframe;
    setText(0,QString("%1").arg(frame->getNumber()));
    setText(1,QString(TAG_FRAME));
}

FramePtr FrameItem::getFrameRef(){
    return frame;
}
