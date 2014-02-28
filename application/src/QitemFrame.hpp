#ifndef QITEMFRAME_HPP
#define QITEMFRAME_HPP

#ifndef INC_FRAME
#define INC_FRAME
#include "Frame/Frame.hpp"
#endif

#define TAG_FRAME "Frame"

#include <QTreeWidgetItem>

class FrameItem : public QTreeWidgetItem
{
public:
    FrameItem(Frame* pframe);

    Frame* getFrameRef();

private:
    Frame* frame;
};

#endif // QITEMFRAME_HPP
