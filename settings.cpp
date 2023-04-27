#include "settings.h"
#include "ui_settings.h"

Settings::Settings(QWidget *parent) : QDialog(parent), ui(new Ui::Settings) {
    ui->setupUi(this);
    ui->timeoutLineEdit->setText(QString::number(timeout));
    saveButton = ui->saveButton;
}

Settings::~Settings() {
    delete ui;
}

int Settings::get_timeout() {
    return timeout;
}

void Settings::on_timeoutLineEdit_editingFinished() {
    bool state;
    int new_value = ui->timeoutLineEdit->text().toInt(&state);
    if(!state) ui->log->setText("Update time: invalid value");
    else {
        timeout = new_value;
        ui->log->setText("Update time:" + QString::number(timeout));
    }
}

void Settings::on_cancelButton_clicked() {
    this->close();
}

