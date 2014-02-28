#include "QitemFrame.hpp"

FrameItem::FrameItem(Frame* pframe)
{
    frame = pframe;
    setText(0,QString("%1").arg(frame->getNumber()));
    setText(1,QString(TAG_FRAME));
}

Frame* FrameItem::getFrameRef(){
    return frame;
}
