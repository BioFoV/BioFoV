#include "QtreeFaces.hpp"

QtreeFaces::QtreeFaces(QWidget *parent) :
    QTreeWidget(parent)
{
    connect(this, SIGNAL(itemPressed(QTreeWidgetItem*,int)),
            this, SLOT(on_item_pressed(QTreeWidgetItem*,int)));
}

void QtreeFaces::on_item_pressed(QTreeWidgetItem *item, int column){
    if(item->parent() == NULL){
        return;
    }

    SnapshotItem* snapitem = (SnapshotItem *) item;
    emit showStillImage(snapitem->getSnapshot()->getMasked());
}

void QtreeFaces::on_enter_pressed(){
    foreach (QTreeWidgetItem* item, selectedItems()) {
        on_item_pressed(item, 0);
    }
}
