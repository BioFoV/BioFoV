#include "faceitem.hpp"

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
}

FaceItem::~FaceItem(){
    delete face;
}

void FaceItem::setFace(Face* inface){
    face = inface;
}

Face* FaceItem::getFace(){
    return face;
}
