#ifndef FACEITEM_HPP
#define FACEITEM_HPP

#include <QTreeWidgetItem>

#ifndef INC_FACES
#define INC_FACES
#include "../framework/Feature/faces.hpp"
#endif

class FaceItem : public QTreeWidgetItem
{
public:
    explicit FaceItem(QTreeWidgetItem *parent = 0);
    FaceItem(QString facename, Face *inface, QTreeWidget *parent = 0);

    // Destructors
    ~FaceItem();

    // Functions
    Face* getFace();
    void setFace(Face* inface);

private:
    Face * face;
};

#endif // FACEITEM_HPP
