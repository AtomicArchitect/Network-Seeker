#ifndef SETTINGS_H
#define SETTINGS_H

#include "qpushbutton.h"
#include <QDialog>

namespace Ui {
class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = nullptr);
    ~Settings();
    int get_timeout();
    QPushButton *saveButton;

private slots:
    void on_timeoutLineEdit_editingFinished();
    void on_cancelButton_clicked();

private:
    Ui::Settings *ui;
    int timeout = 1000;
};

#endif // SETTINGS_H
