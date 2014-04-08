#include "QitemFace.hpp"

FaceItem::FaceItem(QTreeWidgetItem *parent) :
    QTreeWidgetItem(parent)
{
    face = NULL;
}

FaceItem::FaceItem(QString facename, QTreeWidget *parent) :
    QTreeWidgetItem(parent)
{
    setText(0, facename);
    this->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled |
                   Qt::ItemIsDropEnabled | Qt::ItemIsEditable);
    face = NULL;
}

FaceItem::FaceItem(QString facename, Face* inface, QTreeWidget *parent) :
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

FaceItem::~FaceItem(){
    if (face != NULL)
        delete face;
}

Face* FaceItem::getFace(){
    return face;
}

void FaceItem::updateCounter(){
    setCounter(childCount());
    std::cout << childCount() << std::endl;
}

void FaceItem::setCounter(uint count){
    std::ostringstream ss;
    ss << count;
    setText(1, ss.str().c_str());
}

////////////////////////////////////////////////////////////////////////////////

SnapshotItem::SnapshotItem(QTreeWidgetItem *parent) :
    QTreeWidgetItem(parent)
{

}

SnapshotItem::SnapshotItem(Snapshot *insnap, QTreeWidget *parent) :
    QTreeWidgetItem(parent)
{
    snap = insnap;
    setText(0, QString("Frame %1").arg(insnap->getCurrentFrameRef()->getNumber(),5,10,QChar('0')));
}

SnapshotItem::~SnapshotItem(){
    delete snap;
}

Snapshot* SnapshotItem::getSnapshot(){
    return snap;
}
