#include "QtreeFaces.hpp"

/**
 * @brief QtreeFaces::QtreeFaces
 * @param parent
 */
QtreeFaces::QtreeFaces(QWidget *parent) :
	QTreeWidget(parent)
{
	connect(this, SIGNAL(itemPressed(QTreeWidgetItem*,int)),
			this, SLOT(on_item_pressed(QTreeWidgetItem*,int)));
	connect(this, SIGNAL(itemChanged(QTreeWidgetItem*,int)),
			this, SLOT(on_item_changed(QTreeWidgetItem*,int)));
}

/**
 * @brief QtreeFaces::on_item_pressed
 * @param item
 */
void QtreeFaces::on_item_pressed(QTreeWidgetItem *item, int /*column - unused*/){
	if(SnapshotItem* snapitem = dynamic_cast< SnapshotItem * >( item )){
		showStillImage(snapitem->getSnapshot()->getMasked());
	}
	return;
}

/**
 * @brief QtreeFaces::on_enter_pressed
 */
void QtreeFaces::on_enter_pressed(){
	if(isVisible()){
		foreach (QTreeWidgetItem* item, selectedItems()) {
			on_item_pressed(item, 0);
		}
	}
}

/**
 * @brief QtreeFaces::on_item_delete
 */
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
		updateCounts();
	}
}

/**
 * @brief QtreeFaces::newFaceGroup
 */
void QtreeFaces::newFaceGroup(){
	FaceItem * newFaceGroup = new FaceItem(tr("New Group"));
	addTopLevelItem(newFaceGroup);
}

/**
 * @brief QtreeFaces::updateCounts
 */
void QtreeFaces::updateCounts(){
	for(int a = 0; a <= topLevelItemCount(); a++){
		if(FaceItem* faceitem = dynamic_cast< FaceItem* > (topLevelItem(a))){
			faceitem->updateCounter();
		}
	}
}

/**
 * @brief QtreeFaces::on_item_changed
 */
void QtreeFaces::on_item_changed(QTreeWidgetItem*, int){
	updateCounts();
}
