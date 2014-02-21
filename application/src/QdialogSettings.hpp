#ifndef QDIALOGSETTINGS_HPP
#define QDIALOGSETTINGS_HPP

#include <QDialog>
#include <QFileDialog>
#include <QSettings>

namespace Ui {
class QdialogSettings;
}

class QdialogSettings : public QDialog
{
    Q_OBJECT
    
public:
    explicit QdialogSettings(QWidget *parent = 0);
    ~QdialogSettings();

    QString getCacheDir();
    QString getHaarDir();
    bool getUseGPU();

    void setHaarDir(QString newHaarDir);
    void setCacheDir(QString newHaarDir);

public slots:
    void saveSettings();
    void loadSettings();
    
private slots:
    void on_cacheButton_clicked();

    void on_haarButton_clicked();

private:
    Ui::QdialogSettings *ui;
};

#endif // QDIALOGSETTINGS_HPP
