#ifndef FACEITEM_HPP
#define FACEITEM_HPP

#include <QTreeWidgetItem>

#ifndef INC_FACES
#define INC_FACES
#include "Feature/faces.hpp"
#endif

#include "Snapshot/Snapshot.hpp"

class FaceItem : public QTreeWidgetItem
{
public:
    explicit FaceItem(QTreeWidgetItem *parent = 0);
    FaceItem(QString facename, QTreeWidget *parent = 0);
    FaceItem(QString facename, Face *inface, QTreeWidget *parent = 0);

    // Destructors
    ~FaceItem();

    // Functions
    Face* getFace();

    void updateCounter();
    void setCounter(uint count);

private:
    Face * face;
};

class SnapshotItem : public QTreeWidgetItem
{
public:
    explicit SnapshotItem(QTreeWidgetItem *parent = 0);
    SnapshotItem(Snapshot *insnap, QTreeWidget *parent = 0);

    ~SnapshotItem();

    Snapshot* getSnapshot();

private:
    SnapshotPtr snap;
};

#endif // FACEITEM_HPP
