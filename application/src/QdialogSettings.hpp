#ifndef QDIALOGSETTINGS_HPP
#define QDIALOGSETTINGS_HPP

#include <QDialog>

namespace Ui {
class QdialogSettings;
}

class QdialogSettings : public QDialog
{
    Q_OBJECT
    
public:
    explicit QdialogSettings(QWidget *parent = 0);
    ~QdialogSettings();
    
private:
    Ui::QdialogSettings *ui;
};

#endif // QDIALOGSETTINGS_HPP
