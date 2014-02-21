#include "QitemFace.hpp"

FaceItem::FaceItem(QTreeWidgetItem *parent) :
    QTreeWidgetItem(parent)
{

}

FaceItem::FaceItem(QString facename, Face* inface, QTreeWidget *parent) :
    QTreeWidgetItem(parent)
{
    setText(0, facename);
    std::ostringstream ss;
    ss << inface->faceNumber();
    setText(1, ss.str().c_str());

    for (unsigned int i=0; i<inface->faceNumber()-1; i++){
        SnapshotItem * newsnap = new SnapshotItem(inface->getFaceAt(i));
        this->addChild(newsnap);
    }
}

FaceItem::~FaceItem(){
    delete face;
}

Face* FaceItem::getFace(){
    return face;
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
    setText(0, QString("Frame %1").arg(insnap->getFrame()->getNumber()));
}

SnapshotItem::~SnapshotItem(){
    delete snap;
}

Snapshot* SnapshotItem::getSnapshot(){
    return snap;
}
