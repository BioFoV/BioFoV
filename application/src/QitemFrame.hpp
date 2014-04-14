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
    FrameItem(FramePtr pframe);

    FramePtr getFrameRef();

private:
    FramePtr frame;
};

#endif // QITEMFRAME_HPP
