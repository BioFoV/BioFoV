#include "QtreeVideos.hpp"

QtreeVideos::QtreeVideos(QWidget *parent) :
    QTreeWidget(parent)
{
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
            addTopLevelItem(last);
            showMessage(tr("Loaded ") + fileName);
        }
        if(last != NULL) {
            setPlaybackEnabled(false); //FIXME: SIGNAL SLOT
            loadVid(last->getVideo(), PLAYER_VID); //FIXME: SIGNAL SLOT
            showMessage(tr("Finished loading files"));
        }
    } else {
        showMessage(tr("No files selected"));
    }
    return;
}
