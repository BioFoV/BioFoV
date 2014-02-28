#include "QitemFrame.hpp"

QitemFrame::QitemFrame(Frame* pframe)
{
    frame = pframe;
    setText(0,QString("%1").arg(frame->getNumber()));
    setText(1,QString(TAG_FRAME));
}

Frame* QitemFrame::getFrameRef(){
    return frame;
}
