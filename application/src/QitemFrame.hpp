#ifndef QITEMFRAME_HPP
#define QITEMFRAME_HPP

#ifndef INC_FRAME
#define INC_FRAME
#include "Frame/Frame.hpp"
#endif

#define TAG_FRAME "Frame"

#include <QTreeWidgetItem>

class QitemFrame : public QTreeWidgetItem
{
public:
    QitemFrame(Frame* pframe);

    Frame* getFrameRef();

private:
    Frame* frame;
};

#endif // QITEMFRAME_HPP
