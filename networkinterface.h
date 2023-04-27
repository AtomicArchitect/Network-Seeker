#ifndef NETWORKINTERFACE_H
#define NETWORKINTERFACE_H

#include <QString>
#include <QList>
#include <QMessageBox>
#include <QProcess>
#include <QStringList>

#include <sys/types.h>
#include <dirent.h>
#include <fstream>
#include <string>
#include <cmath>

#define INTERFACE_DIR ("/sys/class/net/")
#define MAC_PATH ("/address")
#define BROADCAST_PATH ("/broadcast")
#define MTU_PATH ("/mtu")
#define OPERSTATE_PATH ("/operstate")
#define FLAGS_PATH ("/flags")
#define RX_BYTES_PATH ("/statistics/rx_bytes")
#define TX_BYTES_PATH ("/statistics/tx_bytes")

class NetworkInterface {
private:
    QString name;
    QList<QString> *list_interfaces;
    QString read_line(std::string *path);
    QString exec_command(QString command, QStringList arguments);
    long rx_bytes_base = 0;
    long tx_bytes_base = 0;

public:
    NetworkInterface();
    ~NetworkInterface();
    QList<QString>* load_interfaces();
    void set_name(QString interface_name);
    bool exist(const QString &interface_name);
    QString get_name();
    QString mac();
    QString broadcast();
    QString mtu();
    QString operstate();
    QString flags();
    QString local_ip();
    QString global_ip();
    QString rx_bytes();
    QString tx_bytes();

};

#endif // NETWORKINTERFACE_H
