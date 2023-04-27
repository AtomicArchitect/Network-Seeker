#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    settings = new Settings();
    connect(settings->saveButton, &QPushButton::clicked, this, &MainWindow::settings_updated);
    connect(ui->interfaces, &QMenu::triggered, this, &MainWindow::interface_selection);
    update_interfaces();

    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &MainWindow::update);
    timer->start(settings->get_timeout());
}

MainWindow::~MainWindow() {
    delete ui;
    delete interface;
    delete timer;
    delete settings;
}

void MainWindow::settings_updated() {
    timer->stop();
    timer->start(settings->get_timeout());
}

void MainWindow::update_interfaces() {
    ui->interfaces->clear();
    try {
        interface = new NetworkInterface();
        for(QString interface_name: *interface->load_interfaces()) {
            ui->interfaces->addAction(interface_name);
        }
        ui->interfaces->actions().at(0)->trigger();
    } catch (const char* message) {
        QMessageBox::warning(this, "Ошибка!", message);
    }
}

void MainWindow::interface_selection(QAction *action) {
    if(interface->exist(action->text())) interface->set_name(action->text());
    ui->name->setText(interface->get_name());
    ui->mac->setText(interface->mac());
    ui->broadcast->setText(interface->broadcast());
    ui->mtu->setText(interface->mtu());
    ui->flags->setText(interface->flags());
    ui->operstate->setText(interface->operstate());
    ui->local_ip->setText(interface->local_ip());
    ui->global_ip->setText(interface->global_ip());
}

void MainWindow::update() {
    DIR *dir;
    std::string path(INTERFACE_DIR);
    path.append(interface->get_name().toStdString());
    dir = opendir(path.c_str());
    if(!dir) {
        update_interfaces();
    }

    ui->rx_bytes->setText(interface->rx_bytes());
    ui->tx_bytes->setText(interface->tx_bytes());
}

void MainWindow::on_actionUpdate_triggered() {
    update_interfaces();
}


void MainWindow::on_actionSettings_triggered() {
    settings->show();
}

