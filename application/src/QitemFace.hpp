#ifndef FACEITEM_HPP
#define FACEITEM_HPP

#include <QTreeWidgetItem>

#ifndef INC_FACES
#define INC_FACES
#include <Feature/faces.hpp>
#endif

#ifndef INC_SNAPSHOT
#define INC_SNAPSHOT
#include <Snapshot/Snapshot.hpp>
#endif

class FaceItem : public QTreeWidgetItem
{
public:
    explicit FaceItem(QTreeWidgetItem *parent = 0);
    FaceItem(QString facename, QTreeWidget *parent = 0);
    FaceItem(QString facename, FacePtr inface, QTreeWidget *parent = 0);

    // Destructors
    ~FaceItem();

    // Functions
    FacePtr getFace();

    void updateCounter();
    void setCounter(uint count);

private:
    FacePtr face;
};

class SnapshotItem : public QTreeWidgetItem
{
public:
    explicit SnapshotItem(QTreeWidgetItem *parent = 0);
    SnapshotItem(SnapshotPtr insnap, QTreeWidget *parent = 0);

    ~SnapshotItem();

    SnapshotPtr getSnapshot();

private:
    SnapshotPtr snap;
};

#endif // FACEITEM_HPP
