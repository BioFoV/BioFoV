#include "QwindowMain.hpp"
#include "ui_mainwindow.h"

/**
 * @brief MainWindow constructor.
 * @param parent Parent of the new MainWindow.
 */
MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(openAbout()));
	nEvent = 0;
	playMode = PLAY_FRAMES;

	// Progress bar setup
	//This is here since it can not be done in the mainwindow.ui file
	progressBar = new QProgressBar(this);
	progressBar->setMaximumHeight(16);
	progressBar->setMaximumWidth(200);
	progressBar->setTextVisible(false);
	this->statusBar()->addPermanentWidget(progressBar, 0);

	progressBar->setFormat(QString("%v/%m"));
	setProgressSize(0, 100);

	// Cancel button setup
	cancelButton = new QPushButton(this);
	cancelButton->setIcon(QIcon::fromTheme("process-stop"));
	this->statusBar()->addPermanentWidget(cancelButton, 0);

	disableProgress();

	// Settings setup
	settings = new QdialogSettings();

	connect(ui->actionSave_Settings_as, SIGNAL(triggered()),
			settings, SLOT(saveSettingsAs()));
	connect(ui->actionSave_Settings, SIGNAL(triggered()),
			settings, SLOT(saveSettings()));
	connect(ui->actionLoad_Settings, SIGNAL(triggered()),
			settings, SLOT(loadSettings()));

	connect(ui->actionSettings, SIGNAL(triggered()),
			settings, SLOT(exec()));

	connect(ui->faceList, SIGNAL(showStillImage(cv::Mat)),
			ui->player, SLOT(showStillImage(cv::Mat)));

	connect(ui->faceList, SIGNAL(showMessage(QString)),
			this, SLOT(showMessage(QString)));
	connect(ui->videoList, SIGNAL(showMessage(QString)),
			this, SLOT(showMessage(QString)));

	connect(ui->videoList, SIGNAL(loadVid(PlayerPtr, int, QTreeWidgetItem*)),
			ui->player, SLOT(loadVid(PlayerPtr,int, QTreeWidgetItem*)));

	connect(ui->actionAdd_Video_File, SIGNAL(triggered()),
			ui->videoList, SLOT(on_add_video_file()));
	connect(ui->actionConvert_Video_to_Event, SIGNAL(triggered()),
			ui->videoList, SLOT(on_video_to_event()));
	connect(ui->actionAuto_Detect_Events, SIGNAL(triggered()),
			ui->videoList, SLOT(on_auto_detect_events()));

	connect(ui->videoList, SIGNAL(getSettings()),
			this, SLOT(getSettings()));

	connect(ui->videoList, SIGNAL(startProgress(uint,uint)),
			this, SLOT(enableProgress(uint,uint)));
	connect(ui->videoList, SIGNAL(progressChanged(uint)),
			this, SLOT(setProgress(uint)));
	connect(ui->videoList, SIGNAL(resetProgress()),
			this, SLOT(resetProgress()));

	connect(ui->actionDeleteFace, SIGNAL(triggered()),
			ui->faceList, SLOT(on_item_delete()));
	connect(ui->actionNew_Face_Group, SIGNAL(triggered()),
			ui->faceList, SLOT(newFaceGroup()));

	connect(ui->videoList, SIGNAL(setPlaybackEnabled(bool)),
			ui->menuPlayback_Mode, SLOT(setEnabled(bool)));

	connect(ui->action_Remove_From_Project, SIGNAL(triggered()),
			ui->videoList, SLOT(on_remove_from_project()));
	connect(ui->actionHorizontally, SIGNAL(triggered()),
			ui->videoList, SLOT(flip_horizontally()));
	connect(ui->actionVertically, SIGNAL(triggered()),
			ui->videoList, SLOT(flip_vertically()));
	connect(ui->actionCalibrate, SIGNAL(triggered()),
			ui->videoList, SLOT(on_calibrate()));
	connect(ui->actionImport_camera, SIGNAL(triggered()),
			ui->videoList, SLOT(on_import_camera()));
	connect(ui->actionExport_camera, SIGNAL(triggered()),
			ui->videoList, SLOT(on_export_camera()));
	connect(ui->actionMerge, SIGNAL(triggered()),
			ui->videoList, SLOT(on_merge()));
	connect(ui->actionDeleteEvent, SIGNAL(triggered()),
			ui->videoList, SLOT(on_delete_event()));
	connect(ui->actionDiscard_Calibration, SIGNAL(triggered()),
			ui->videoList, SLOT(on_discard_calibration()));
	connect(ui->actionHeight, SIGNAL(triggered()),
			ui->videoList, SLOT(on_height()));
	connect(ui->actionWidth, SIGNAL(triggered()),
			ui->videoList, SLOT(on_width()));
	connect(ui->actionReproject, SIGNAL(triggered()),
			ui->videoList, SLOT(on_reproject()));
	connect(ui->actionLength, SIGNAL(triggered()),
			ui->videoList, SLOT(on_length()));
	connect(ui->actionAngle, SIGNAL(triggered()),
			ui->videoList, SLOT(on_angle()));
	connect(ui->actionExclude_rectangle, SIGNAL(triggered()),
			ui->videoList, SLOT(on_exclude_rectangle()));

	connect(ui->videoList, SIGNAL(removePlayer(PlayerPtr)),
			ui->player, SLOT(unload(PlayerPtr)));
	connect(ui->videoList, SIGNAL(getPlayMode()),
			this, SLOT(getPlayMode()));
	connect(ui->videoList, SIGNAL(setPlaybackMode(int)),
			ui->player, SLOT(setPlayMode(int)));
	connect(ui->videoList, SIGNAL(playOrPause()),
			ui->player, SLOT(playOrPause()));
	connect(ui->videoList, SIGNAL(pause()),
			ui->player, SLOT(pause()));

	connect(ui->videoList, SIGNAL(refreshPlayer()),
			ui->player, SLOT(refresh()));

	connect(ui->videoList, SIGNAL(setSelectedText(QString)),
			ui->labelSelected, SLOT(setText(QString)));
	connect(ui->videoList, SIGNAL(setTotalFramesText(QString)),
			ui->labelTotalFrames, SLOT(setText(QString)));
	connect(ui->videoList, SIGNAL(setTotalTimeText(QString)),
			ui->labelTotalTime, SLOT(setText(QString)));

	connect(ui->actionPrint, SIGNAL(triggered()),
			ui->player, SLOT(print()));

	connect(ui->videoList, SIGNAL(getCurrentItem()),
			ui->player, SLOT(getCurrentItem()));
	connect(ui->videoList, SIGNAL(getFrameRef()),
			ui->player, SLOT(getCurrentFrameRef()));
	connect(ui->videoList, SIGNAL(getCurrentPlayer()),
			ui->player, SLOT(getCurrentPlayer()));

	connect(cancelButton, SIGNAL(clicked()),
			ui->videoList, SIGNAL(cancel()));
}

/**
 * @brief MainWindow destructor.
 */
MainWindow::~MainWindow()
{
	delete ui;
}

/**
 * @brief Opens the about window.
 * This was a test for the exec function and opening new windows/dialogs, but
 * in the end it stayed.
 */
void MainWindow::openAbout()
{
	About about;
	about.exec();
}

/**
 * @brief Shows a message in the status bar.
 * @param text Message as a QString.
 */
void MainWindow::showMessage(QString text){
	ui->statusBar->showMessage(text);
}

/**
 * @brief Shows a message in the status bar.
 * @param text Message as a normal C string.
 */
void MainWindow::showMessage(const char *text){
	ui->statusBar->showMessage(QString(text));
}

/**
 * @brief Changes the limits of progressBar.
 * @param min Minimum value of progressBar.
 * @param max Maximum value of progressBar.
 * @param val Current value to set progressBar to.
 */
void MainWindow::setProgressSize(unsigned int min, unsigned int max,
								 unsigned int val) {
	progressBar->setMinimum(min);
	progressBar->setMaximum(max);
	setProgress(val);
}

/**
 * @brief Enable the progress bar.
 * @param min Minimum value of progressBar.
 * @param max Maximum value of progressBar.
 */
void MainWindow::enableProgress(unsigned int min, unsigned int max){
	progressBar->setEnabled(true);
	cancelButton->setEnabled(true);
	setProgressSize(min, max, min);
}

/**
 * @brief Sets progress bar value.
 * @param val New value for progressBar.
 */
void MainWindow::setProgress(uint val){
	progressBar->setValue(val);
}

/**
 * @brief Disables the progress bar.
 */
void MainWindow::disableProgress(){
	progressBar->setEnabled(false);
	cancelButton->setEnabled(false);
}

/**
 * @brief Disables and empties the progress bar.
 */
void MainWindow::resetProgress(){
	setProgressSize(0, 100, 0);
	disableProgress();
}

/**
 * @brief RGB video playback triggered.
 * Disables all the other playback options if enabled. If disabled,
 * re-enable, since at least one playback option should be enabled.
 */
void MainWindow::on_actionNormal_triggered()
{
	if (ui->actionNormal->isChecked()) {
		ui->actionMask->setChecked(false);
		ui->actionMasked_Video->setChecked(false);
	} else {
		ui->actionNormal->setChecked(true);
	}
}

/**
 * @brief Mask playback triggered.
 * Disables all the other playback options if enabled. If disabled,
 * return to normal playback mode.
 */
void MainWindow::on_actionMask_triggered()
{
	if (ui->actionMask->isChecked()) {
		ui->actionNormal->setChecked(false);
		ui->actionMasked_Video->setChecked(false);
	} else {
		ui->actionNormal->setChecked(true);
	}
}

/**
 * @brief Masked video playback triggered.
 * Disables all the other playback options if enabled. If disabled,
 * return to normal playback mode.
 */
void MainWindow::on_actionMasked_Video_triggered()
{
	if (ui->actionMasked_Video->isChecked()) {
		ui->actionNormal->setChecked(false);
		ui->actionMask->setChecked(false);
	} else {
		ui->actionNormal->setChecked(true);
	}
}

/**
 * @brief MainWindow::getPlayMode
 * @return
 */
int MainWindow::getPlayMode(){
	return playMode;
}

/**
 * @brief Event playback as RGB video toggled.
 * @param arg1 Event playback as RGB video?
 */
void MainWindow::on_actionNormal_toggled(bool arg1)
{
	if (arg1) {
		playMode = PLAY_FRAMES;
		ui->player->setPlayMode(playMode);
		ui->player->refresh();
	}
}

/**
 * @brief Event playback of the mask toggled.
 * @param arg1 Event playback as mask only?
 */
void MainWindow::on_actionMask_toggled(bool arg1)
{
	if (arg1) {
		playMode = PLAY_MASK;
		ui->player->setPlayMode(playMode);
		ui->player->refresh();
	}
}

/**
 * @brief Event playback of the masked RGB video toggled.
 * @param arg1 Event playback as masked video?
 */
void MainWindow::on_actionMasked_Video_toggled(bool arg1)
{
	if (arg1) {
		playMode = PLAY_MASKED_FRAMES;
		ui->player->setPlayMode(playMode);
		ui->player->refresh();
	}
}

/**
 * @brief MainWindow::on_actionDetect_Faces_triggered
 */
void MainWindow::on_actionDetect_Faces_triggered()
{
	uint i0, i1;

	QFileDialog getFileDialog(this);
	getFileDialog.setDirectory(QDir(settings->getHaarDir()));
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
			FacePtr face = FacePtr(new Face(fileName.toStdString()));

			foreach (QTreeWidgetItem* item, ui->videoList->selectedItems()){
				PlayerPtr tmp_player = ((PlayerItem*)item)->getPlayer();
				FramePtr face_frame;

				// tmp_player is a frame
				if (!qSharedPointerDynamicCast<Frame>(tmp_player).isNull()){
					face_frame = qSharedPointerDynamicCast<Frame>(tmp_player);
					face->findFaces(face_frame);
				}
				else{
					// rewind event
					tmp_player->setFramePos(0);
					enableProgress(0, tmp_player->getLengthFrames());
					toCancel = false;
					connect(cancelButton, SIGNAL(clicked()),
							this, SLOT(cancel()));
					i0 = 2;
					for (;;){
						QCoreApplication::processEvents();
						if (toCancel){
							canceled();
							break;
						}
						i1 = tmp_player->getCurrentFrameNumber();
						if(i0==i1)
							break;
						i0 = i1;

						face_frame = tmp_player->getCurrentFrameRef();
						if(face_frame.isNull())
							break;
						setProgress(tmp_player->getFramePos());
						face->findFaces(face_frame);
						if(!tmp_player->stepForward())
							break;
					}
					disconnect(cancelButton, SIGNAL(clicked()),
							this, SLOT(cancel()));
					resetProgress();
				}
				if (face->faceNumber() == 0){
					showMessage(tr("No faces found"));
					return;
				} else {
					FaceItem * newFaceItem = new FaceItem(tr("face"), face);
					ui->faceList->addTopLevelItem(newFaceItem);
					showMessage(tr("Found %1 faces").arg(face->faceNumber()));
				}
				// rewind event again
				tmp_player->setFramePos(0);
			}
		}
	}
}

/**
 * @brief MainWindow::keyPressEvent
 * @param ev
 */
void MainWindow::keyPressEvent(QKeyEvent *ev){
	// DELETE
	if(ev->key() == Qt::Key_Delete){
		ui->videoList->on_delete_event();
		ui->actionDeleteFace->trigger();
	}
	// ENTER
	else if ( ev->key() == Qt::Key_Enter || ev->key() == Qt::Key_Return ){

		if(ui->videoList->isVisible()){
			foreach (QTreeWidgetItem* item, ui->videoList->selectedItems()){
				ui->videoList->on_item_doubleclicked(item, 0);
			}
		}
		ui->faceList->on_enter_pressed();
	}
}

/**
 * @brief MainWindow::getSettings
 * @return
 */
QdialogSettings* MainWindow::getSettings(){
	return settings;
}

/**
 * @brief MainWindow::on_actionExport_Event_triggered
 */
void MainWindow::on_actionExport_Event_triggered()
{
	QFileDialog getDirDialog(this);
	getDirDialog.setDirectory(QDir::homePath());
	getDirDialog.setAcceptMode(QFileDialog::AcceptSave);

	QStringList encoders;
	encoders << tr("XVID") << tr("HFYU");
	bool ok;

	QStringList fileNames;

	QList<QTreeWidgetItem*> items = ui->videoList->selectedItems();
	EventItem* evItem;

	if (items.length() == 0){
		showMessage(tr("Select one event."));
		return;
	}

	if(getDirDialog.exec()) {
		fileNames = getDirDialog.selectedFiles();
		QString encoder = QInputDialog::getItem(this, tr("Choose an Encoder"),
											 tr("Encoder"), encoders, 0, false,
											 &ok);
		if (!ok) {
			showMessage(tr("Export action canceled!"));
			return;
		}

		foreach (QString fileName, fileNames) {
			foreach (QTreeWidgetItem* item, items){
				if (dynamic_cast<EventItem*>(item) == NULL){
					showMessage(tr("Selection is not an Event"));
					continue;
				}
				evItem = (EventItem*)item;
				showMessage(tr("Saving %1").arg(evItem->text(0)));

				evItem->getEvent()->saveAsVideo(
							fileName.toStdString() + "-" +
							evItem->text(0).toStdString(),
							encoder.toStdString());
			}
		}
	} else {
		showMessage(tr("Action canceled"));
	}
	showMessage(tr("Done saving Event(s)"));
}

/**
 * @brief MainWindow::on_actionSave_Current_Player_Image_triggered
 */
void MainWindow::on_actionSave_Current_Player_Image_triggered()
{
	if (!ui->player->getCurrentPlayer()){
		showMessage(tr("Nothing loaded in the player"));
		return;
	}
	QFileDialog getDirDialog(this);
	getDirDialog.setDirectory(QDir::homePath());
	getDirDialog.setAcceptMode(QFileDialog::AcceptSave);
	QStringList fileNames;

	if(getDirDialog.exec()) {
		fileNames = getDirDialog.selectedFiles();

		foreach (QString fileName, fileNames) {
			ui->player->getCurrentPlayer()->saveFrame(fileName.toStdString() + ".png");
		}
	} else {
		showMessage(tr("Action canceled"));
	}
	showMessage(tr("Done saving Image"));
}

/**
 * @brief MainWindow::on_actionSave_Faces_As_Images_triggered
 */
void MainWindow::on_actionSave_Faces_As_Images_triggered()
{
	QFileDialog getDirDialog(this);
	getDirDialog.setDirectory(QDir::homePath());
	getDirDialog.setAcceptMode(QFileDialog::AcceptSave);

	QStringList fileNames;

	QList<QTreeWidgetItem*> items = ui->faceList->selectedItems();
	SnapshotItem* snapItem;

	int ind = 0;

	if(getDirDialog.exec()) {
		fileNames = getDirDialog.selectedFiles();

		foreach (QString fileName, fileNames) {
			foreach (QTreeWidgetItem* item, items){
				if (dynamic_cast<SnapshotItem*>(item) == NULL){
					showMessage(tr("Selection is not an Face"));
					continue;
				}
				snapItem = (SnapshotItem*)item;
				showMessage(tr("Saving %1").arg(snapItem->text(0)));

				snapItem->getSnapshot()->save((fileName
					+ QString("-%1").arg(snapItem->getSnapshot()->getCurrentFrameNumber())
					+ QString("-%1").arg(ind)
					+ ".png").toStdString());
				ind++;
			}
		}
	} else {
		showMessage(tr("Action canceled"));
	}
	showMessage(tr("Done saving Event(s)"));
}

/**
 * @brief MainWindow::cancel
 */
void MainWindow::cancel() {
	toCancel = true;
}

/**
 * @brief MainWindow::canceled
 */
void MainWindow::canceled() {
	toCancel = false;
}
