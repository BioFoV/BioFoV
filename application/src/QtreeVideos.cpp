#include "QtreeVideos.hpp"

QtreeVideos::QtreeVideos(QWidget *parent) :
    QTreeWidget(parent)
{
    nEvent = 0;

    connect(this, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),
            this, SLOT(on_item_doubleclicked(QTreeWidgetItem*,int)));
    connect(this, SIGNAL(itemSelectionChanged()),
            this, SLOT(on_item_selection_changed()));
    connect(this, SIGNAL(itemChanged(QTreeWidgetItem*,int)),
            this, SLOT(itemChanged(QTreeWidgetItem*,int)));
}

void QtreeVideos::on_add_video_file(){
    VideoItem * last = NULL;
    QFileDialog getFileDialog(this);
    getFileDialog.setDirectory(QDir::homePath());
    getFileDialog.setFileMode(QFileDialog::ExistingFiles);
    getFileDialog.setAcceptMode(QFileDialog::AcceptOpen);

    QStringList fileNames;
    if(getFileDialog.exec())
    {
        fileNames = getFileDialog.selectedFiles();
        if (fileNames.isEmpty()) {
            showMessage(tr("No files loaded"));
            return;
        } // No file name provided
        foreach (QString fileName, fileNames) {
            last = new VideoItem(fileName);
            if(last->getVideo()->getFPS() == 0){
                showMessage(tr("Failed to load %1").arg(fileName));
                delete last;
                last = NULL;
                continue;
            }
            connect(last->getVideo(),SIGNAL(getSettings()),
                    this, SIGNAL(getSettings()));
            addTopLevelItem(last);
            showMessage(tr("Loaded ") + fileName);
        }
        if(last != NULL) {
            setPlaybackEnabled(false); //FIXME: SIGNAL SLOT
            loadVid(last->getVideo(), PLAYER_VID, last); //FIXME: SIGNAL SLOT
            showMessage(tr("Finished loading files"));
        }
    } else {
        showMessage(tr("No files selected"));
    }
    return;
}

void QtreeVideos::on_video_to_event(){
    Event* event;
    EventItem* newEventItem;

    if (selectedItems().isEmpty()){
        showMessage(tr("Select at least one Video"));
        return;
    }

    foreach (QTreeWidgetItem* item, selectedItems()){
        if (VideoItem* videoiter = dynamic_cast< VideoItem * >( item )){
            showMessage(tr("Analyzing Video %1").arg(item->text(0)));

            // Progress bar signals and slots
            connect(videoiter->getVideo(), SIGNAL(startProgress(uint, uint)),
                    this, SIGNAL(startProgress(uint,uint)));
            connect(videoiter->getVideo(), SIGNAL(progressChanged(uint)),
                    this, SIGNAL(progressChanged(uint)));

            event = videoiter->getVideo()->convertToEvent(
                    (getSettings()->getCacheDir().append("/")).toStdString());

            disconnect(videoiter->getVideo(), SIGNAL(startProgress(uint, uint)),
                       this, SIGNAL(startProgress(uint,uint)));
            disconnect(videoiter->getVideo(), SIGNAL(progressChanged(uint)),
                       this, SIGNAL(progressChanged(uint)));

            resetProgress();

            showMessage(tr("Found Event %1").arg(nEvent));
            newEventItem = new EventItem(QString("E%1").arg(nEvent));;
            newEventItem->setEvent(event);
            nEvent ++;
            videoiter->addChild(newEventItem);
        } else {
            showMessage(tr("Item selected is not a video"));
            continue;
        }
    }
}

void QtreeVideos::on_auto_detect_events(){
    std::deque<Event*> events;
    EventItem* newEvent;

    QElapsedTimer timer;

    unsigned int j;

    SplitDialog split;

    if (selectedItems().isEmpty()){
        showMessage(tr("Select at least one Video"));
        return;
    }

    foreach (QTreeWidgetItem* item, selectedItems()){
        if (VideoItem* videoiter = dynamic_cast< VideoItem * >( item )){
            showMessage(tr("Analyzing Video %1").arg(item->text(0)));
            split.setFPS(videoiter->getVideo()->getFPS());
            split.setWindowTitle(videoiter->text(0));
            if(!split.exec()){
                showMessage(tr("Auto detection canceled"));
                continue;
            }

            // Progress bar signals and slots
            connect(videoiter->getVideo(), SIGNAL(startProgress(uint, uint)),
                    this, SIGNAL(startProgress(uint,uint)));
            connect(videoiter->getVideo(), SIGNAL(progressChanged(uint)),
                    this, SIGNAL(progressChanged(uint)));
            timer.start();
            events = videoiter->getVideo()->autoDetectEvents(split.getThreshold()/10.0,
                                                             split.getMaxFrames(),
                                                             split.getMinFrames(),
                                                             split.getHistory(),
                                                             split.getvarThreshold(),
                                                             split.getbShadowDetection(),
                                                             (getSettings()->getCacheDir().append("/")).toStdString());

            disconnect(videoiter->getVideo(), SIGNAL(startProgress(uint, uint)),
                       this, SIGNAL(startProgress(uint,uint)));
            disconnect(videoiter->getVideo(), SIGNAL(progressChanged(uint)),
                       this, SIGNAL(progressChanged(uint)));

            resetProgress();
            for (j = 0; j < events.size(); j++) {
                showMessage(tr("Found Event %1").arg(nEvent));
                newEvent = new EventItem(QString("E%1").arg(nEvent));;
                newEvent->setEvent(events.at(j));
                nEvent ++;
                videoiter->addChild(newEvent);
            }
            if (j != 0){
                videoiter->setExpanded(true);
            }
        } else {
            showMessage(tr("Item selected is not a video"));
            continue;
        }
    }
    if(timer.elapsed()>0){
        showMessage(tr("Finished in %1s").arg(timer.elapsed()/1000));
        std::cout << timer.elapsed() << std::endl;
    }
}

void QtreeVideos::on_remove_from_project()
{
    if(isVisible()){
        foreach(QTreeWidgetItem* item, selectedItems()){
            if (VideoItem* vItem = dynamic_cast< VideoItem * >( item )){
                removePlayer((Player *) vItem->getVideo());
                delete item;
            }
            else {
                showMessage(tr("Item selected is not a Video"));
            }
        }
    }
}

void QtreeVideos::on_delete_event()
{
    if(isVisible()){
        foreach(QTreeWidgetItem* item, selectedItems()){
            if(EventItem* evItem = dynamic_cast< EventItem * >( item )){
                removePlayer((Player *) evItem->getEvent());
                delete evItem;
            }
            else {
                showMessage(tr("Item selected is not an Event"));
            }
        }
    }
}

void QtreeVideos::on_item_doubleclicked(QTreeWidgetItem *item, int /*column - unused*/){
    showMessage(tr("Loaded ") + item->text(0));
    if (VideoItem* vItem = dynamic_cast< VideoItem * >( item )){
        loadVid(vItem->getVideo(), PLAYER_VID, vItem);
        setPlaybackEnabled(false);
    } else if (EventItem* eItem = dynamic_cast< EventItem * >( item )){
        Event* ev = eItem->getEvent();
        loadVid(ev, PLAYER_EV, eItem);
        setPlaybackMode(getPlayMode());
        setPlaybackEnabled(true);
    } else if (FrameItem* fItem = dynamic_cast< FrameItem * >( item )) {
        Frame* fr = fItem->getFrameRef();
        loadVid(fr, PLAYER_FRAME, fItem);
        setPlaybackEnabled(false);
    }
    playOrPause();
}

void QtreeVideos::on_item_selection_changed()
{
    int selected = 0;
    double frames = 0;
    double time = 0;
    foreach (QTreeWidgetItem* item, selectedItems()){
        if (EventItem* eventIt = dynamic_cast< EventItem * >( item )){
            frames += eventIt->getEvent()->getLengthFrames();
            time += eventIt->getEvent()->getLengthTime();
        } else if (VideoItem* videoIt = dynamic_cast< VideoItem * >( item )) {
            frames += videoIt->getVideo()->getLengthFrames();
            time += videoIt->getVideo()->getLengthTime();
        }
        selected ++;
    }
    setSelectedText(QString("%1").arg(selected));
    setTotalFramesText(QString("%1").arg(frames));
    setTotalTimeText(QString("%1 s").arg(time));
}

void QtreeVideos::flip_horizontally(){
    foreach (QTreeWidgetItem* item, selectedItems()){
        if (NULL != dynamic_cast< EventItem * >( item )){
            showMessage(tr("Flip Videos, not events."));
        } else if (VideoItem* videoIt = dynamic_cast< VideoItem * >( item )) {
            videoIt->getVideo()->flip_horizontally();
            showMessage(tr("Flipped selected Video."));
        }
    }
    refreshPlayer();
}

void QtreeVideos::flip_vertically(){
    foreach (QTreeWidgetItem* item, selectedItems()){
        if (NULL != dynamic_cast< EventItem * >( item )){
            showMessage(tr("Flip Videos, not events."));
        } else if (VideoItem* videoIt = dynamic_cast< VideoItem * >( item )) {
            videoIt->getVideo()->flip_vertically();
            showMessage(tr("Flipped selected Video."));
        }
    }
    refreshPlayer();
}

void QtreeVideos::on_calibrate()
{
    if (selectedItems().size() == 0){
        showMessage(tr("Select a Video first"));
        return;
    }

    CalibrationDialog calibDiag;
    if(!calibDiag.exec()){
        showMessage(tr("Calibration canceled"));
        return;
    }

    foreach (QTreeWidgetItem* item, selectedItems()){
        if (VideoItem* videoIt = dynamic_cast< VideoItem * >( item )){
            videoIt->getVideo()->calibrate(calibDiag.getNBoards(),
                                           calibDiag.getFrameStep(),
                                           calibDiag.getWidth(),
                                           calibDiag.getHeight(),
                                           calibDiag.getIterations());
            if(videoIt->getVideo()->isCalibrated()){
                showMessage(tr("Video Calibrated"));
                playOrPause();
            } else {
                showMessage(tr("Failed Calibration"));
            }
        }
    }
}

void QtreeVideos::on_discard_calibration(){
    if (selectedItems().size() == 0){
        showMessage(tr("Select a calibrated Video first"));
        return;
    }
    foreach (QTreeWidgetItem* item, selectedItems()){
        if (VideoItem* videoIt = dynamic_cast< VideoItem * >( item )){
            if(videoIt->getVideo()->isCalibrated()){
                videoIt->getVideo()->deleteCalibration();
                showMessage(tr("Calibration discarded"));
                playOrPause();
            } else {
                showMessage(tr("Video is not calibrated"));
            }
        }
    }
}

void QtreeVideos::on_import_camera(){
    int i = 0;

    foreach (QTreeWidgetItem* item, selectedItems()){
        if(VideoItem* videoIt = dynamic_cast< VideoItem * >( item )){
            videoIt->getVideo()->importCamera();
            i++;
        } else {
            showMessage(tr("Export camera only implemented for Videos"));
            continue;
        }
    }
    if (!i){
        showMessage(tr("Select at least one video first"));
    }
}

void QtreeVideos::on_export_camera(){
    foreach (QTreeWidgetItem* item, selectedItems()){
        if(VideoItem* vidIt = dynamic_cast< VideoItem * >( item )){
            if(vidIt->getVideo()->getCamera()->write_file()){
                showMessage(tr("Camera saved to file"));
            } else {
                showMessage(tr("Failed to save camera to file"));
            }
        } else {
            showMessage(tr("Export camera only implemented for Videos, not Events"));
            continue;
        }
    }
}

void QtreeVideos::on_merge()
{
    unsigned int count = 0;
    EventItem* it0, * it1;
    foreach (QTreeWidgetItem* item, selectedItems()){
        if(EventItem* eventIt = dynamic_cast< EventItem * >( item )){
            switch (count){
                case 0:
                    it0 = eventIt;
                    break;
                case 1:
                    it1 = eventIt;
                    break;
                case 2:
                    showMessage(tr("Events can only be merged in pairs"));
                    return;
            }
            count++;
        }
        else{
            showMessage(tr("Merging Videos is not supported"));
            return;
        }
    }
    if (count == 0 || count == 1){
        showMessage(tr("Select two events to be merged"));
        return;
    }
    showMessage(tr("Merging events %1 and %2").arg(it0->text(0), it1->text(0)));
    *(it0->getEvent()) += *(it1->getEvent());
    showMessage(tr("Merged events %1 and %2 into event %1").arg(it0->text(0), it1->text(0)));

    delete(it1);
}

FrameItem* QtreeVideos::getFrame(){
    FrameItem* fitem ;
    QTreeWidgetItem* qitem = getCurrentItem();
    if (dynamic_cast< FrameItem * >( qitem ) == NULL){
        fitem = new FrameItem((Frame*)getFrameRef());
        qitem->addChild(fitem);
        loadVid(fitem->getFrameRef(), PLAYER_FRAME, fitem);
        qitem->setExpanded(true);
    } else {
        fitem = (FrameItem*) qitem;
    }
    connect(fitem->getFrameRef(), SIGNAL(updateValues()),
            this, SLOT(updateValues()));
    return fitem;
}

void QtreeVideos::on_crop() {
    pause();
    FrameItem* fitem = getFrame();
    showMessage(tr("Select the area to crop in the player"));
}

void QtreeVideos::on_height()
{
    pause();
    FrameItem* fitem = getFrame();
    showMessage(tr("Select 4 points in the player"));
    fitem->getFrameRef()->addDrawable((Drawable*)new DrawHeight());
}

void QtreeVideos::on_length() {
    pause();
    FrameItem* fitem = getFrame();
    showMessage(tr("Select 2 points in the player"));
    fitem->getFrameRef()->addDrawable((Drawable*)new DrawLength());
}

void QtreeVideos::on_exclude_rectangle()
{
    pause();
    QTreeWidgetItem* current = getCurrentItem();
    if (VideoItem* videoIt = dynamic_cast< VideoItem * >(current)){
        videoIt->getVideo()->addDrawable((Drawable*)new RectangleMask());
        showMessage(tr("Select a rectangle to zoneout in the player"));
    } else {
        showMessage(tr("Exclude areas in Videos"));
        return;
    }
}

void QtreeVideos::updateValues(){
    QitemDrawable* newChild;
    QTreeWidgetItem* newSubChild;
    std::string buffer;
    Drawable* drawBuff;
    Qt::CheckState checkedState;

    TStrDoubleMap valuesBuff;

    QTreeWidgetItem* current = getCurrentItem();
    current->takeChildren();

    std::deque<Drawable*> map = ((Frame*)getFrameRef())->getDrawables();
    for (std::deque<Drawable*>::iterator iter = map.begin();
         iter != map.end();
         iter ++) {
        drawBuff = (*iter);
        newChild = new QitemDrawable(drawBuff);
        newChild->setText(0, QString(drawBuff->getDescription().c_str()));
        newChild->setFlags(newChild->flags() | Qt::ItemIsUserCheckable);
        if(drawBuff->isVisible()){
            checkedState = Qt::Checked;
        } else {
            checkedState = Qt::Unchecked;
        }
        newChild->setCheckState(1,checkedState);
        valuesBuff = drawBuff->getValues();
        for (TStrDoubleMap::iterator iterVal= valuesBuff.begin();
             iterVal != valuesBuff.end();
             iterVal ++){
            newSubChild = new QTreeWidgetItem();
            buffer = iterVal->first;
            newSubChild->setText(0,QString(buffer.c_str()));
            newSubChild->setText(1,QString("%1").arg(iterVal->second));
            newChild->addChild(newSubChild);
        }
        current->addChild(newChild);
        newChild->setExpanded(true);
    }
    current->setExpanded(true);
}

void QtreeVideos::itemChanged(QTreeWidgetItem *item, int){
    if(QitemDrawable* drawIt = dynamic_cast< QitemDrawable * >(item)){
        if (drawIt->checkState(1) == Qt::Checked)
            drawIt->getDrawable()->setVisible(true);
        else
            drawIt->getDrawable()->setVisible(false);
        refreshPlayer();
    }
}
