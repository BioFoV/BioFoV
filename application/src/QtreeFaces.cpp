#include "QtreeFaces.hpp"

QtreeFaces::QtreeFaces(QWidget *parent) :
    QTreeWidget(parent)
{
    connect(this, SIGNAL(itemPressed(QTreeWidgetItem*,int)),
            this, SLOT(on_item_pressed(QTreeWidgetItem*,int)));
}

void QtreeFaces::on_item_pressed(QTreeWidgetItem *item, int column){
    if(SnapshotItem* snapitem = dynamic_cast< SnapshotItem * >( item )){
        showStillImage(snapitem->getSnapshot()->getMasked());
    }
    return;
}

void QtreeFaces::on_enter_pressed(){
    if(isVisible()){
        foreach (QTreeWidgetItem* item, selectedItems()) {
            on_item_pressed(item, 0);
        }
    }
}

void QtreeFaces::on_item_delete(){
    if(isVisible()){
        foreach(QTreeWidgetItem* item, selectedItems()){
            if(SnapshotItem* snapitem = dynamic_cast< SnapshotItem * >( item )){
                delete snapitem;
            }
            else {
                showMessage(tr("Item selected is not a Face"));
            }
        }
    }
}

void QtreeFaces::newFaceGroup(){
    FaceItem * newFaceGroup = new FaceItem(tr("New Group"));
    addTopLevelItem(newFaceGroup);
}
