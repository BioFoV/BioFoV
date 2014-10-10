#include "QitemFace.hpp"

/**
 * @brief FaceItem::FaceItem
 * @param parent
 */
FaceItem::FaceItem(QTreeWidgetItem *parent) :
    QTreeWidgetItem(parent)
{
}

/**
 * @brief FaceItem::FaceItem
 * @param facename
 * @param parent
 */
FaceItem::FaceItem(QString facename, QTreeWidget *parent) :
    QTreeWidgetItem(parent)
{
    setText(0, facename);
    this->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled |
                   Qt::ItemIsDropEnabled | Qt::ItemIsEditable);
}

/**
 * @brief FaceItem::FaceItem
 * @param facename
 * @param inface
 * @param parent
 */
FaceItem::FaceItem(QString facename, FacePtr inface, QTreeWidget *parent) :
    QTreeWidgetItem(parent)
{
    setText(0, facename);
    setCounter(inface->faceNumber());

    for (unsigned int i=0; i<inface->faceNumber(); i++){
        SnapshotItem * newsnap = new SnapshotItem(inface->getFaceAt(i));
        newsnap->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable |
                          Qt::ItemIsDragEnabled | Qt::ItemIsEnabled);
        this->addChild(newsnap);
    }
    this->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled |
                   Qt::ItemIsDropEnabled | Qt::ItemIsEditable);
}

/**
 * @brief FaceItem::~FaceItem
 */
FaceItem::~FaceItem(){
}

/**
 * @brief FaceItem::getFace
 * @return
 */
FacePtr FaceItem::getFace(){
    return face;
}

/**
 * @brief FaceItem::updateCounter
 */
void FaceItem::updateCounter(){
    setCounter(childCount());
    std::cout << childCount() << std::endl;
}

/**
 * @brief FaceItem::setCounter
 * @param count
 */
void FaceItem::setCounter(uint count){
    std::ostringstream ss;
    ss << count;
    setText(1, ss.str().c_str());
}

/******************************************************************************/

/**
 * @brief SnapshotItem::SnapshotItem
 * @param parent
 */
SnapshotItem::SnapshotItem(QTreeWidgetItem *parent) :
    QTreeWidgetItem(parent)
{

}

/**
 * @brief SnapshotItem::SnapshotItem
 * @param insnap
 * @param parent
 */
SnapshotItem::SnapshotItem(SnapshotPtr insnap, QTreeWidget *parent) :
    QTreeWidgetItem(parent)
{
    snap = insnap;
    setText(0, QString("Frame %1").arg(insnap->getCurrentFrameRef()->getNumber(),5,10,QChar('0')));
}

/**
 * @brief SnapshotItem::~SnapshotItem
 */
SnapshotItem::~SnapshotItem(){
}

/**
 * @brief SnapshotItem::getSnapshot
 * @return
 */
SnapshotPtr SnapshotItem::getSnapshot(){
    return snap;
}
