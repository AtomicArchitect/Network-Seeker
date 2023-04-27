#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QString>
#include <QMessageBox>
#include <QTimer>
#include "settings.h"
#include "networkinterface.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    void extracted();
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void settings_updated();

private:
    Ui::MainWindow *ui;
    NetworkInterface *interface;
    QTimer *timer;
    Settings *settings;

    void update_interfaces();

private slots:
    void interface_selection(QAction *action);
    void update();
    void on_actionUpdate_triggered();
    void on_actionSettings_triggered();
};
#endif // MAINWINDOW_H
