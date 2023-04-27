#include "networkinterface.h"

QString NetworkInterface::read_line(std::string *path) {
    std::ifstream file;
    file.open(*path);

    if(file.is_open()) {
        std::string line;
        getline(file, line);
        QString result = QString::fromStdString(line);
        return result;
    } return QString("Не удалось открыть файл: ").append(path->c_str());
}

QString NetworkInterface::exec_command(QString command, QStringList arguments) {
    QProcess process;
    process.start(command, arguments);
    if(!process.waitForStarted() || !process.waitForFinished()) {
        return "Ошибка запуска процесса";
    }
    return process.readAllStandardOutput();
}

NetworkInterface::NetworkInterface() {
    list_interfaces = new QList<QString>();
    DIR *dir;
    struct dirent *entry;

    dir = opendir(INTERFACE_DIR);
    if(!dir) {
        throw "Не удалось открыть папку";
    }

    while((entry = readdir(dir)) != NULL) {
        QString name_ = QString(entry->d_name);
        if(!name_.startsWith(".")) {
            list_interfaces->append(name_);
            if(name.isEmpty()) name = name_;
        }
    }
}

NetworkInterface::~NetworkInterface() {
    delete list_interfaces;
}

QList<QString> *NetworkInterface::load_interfaces() {
    return list_interfaces;
}

void NetworkInterface::set_name(QString interface_name) {
    name = interface_name;
}

bool NetworkInterface::exist(const QString &interface_name) {
    return list_interfaces->contains(interface_name);
}

QString NetworkInterface::get_name() {
    return name;
}

QString NetworkInterface::mac() {
    std::string path(INTERFACE_DIR);
    path.append(name.toStdString());
    path.append(MAC_PATH);
    return read_line(&path);
}

QString NetworkInterface::broadcast() {
    std::string path(INTERFACE_DIR);
    path.append(name.toStdString());
    path.append(BROADCAST_PATH);
    return read_line(&path);
}

QString NetworkInterface::mtu() {
    std::string path(INTERFACE_DIR);
    path.append(name.toStdString());
    path.append(MTU_PATH);
    return read_line(&path);
}

QString NetworkInterface::operstate() {
    std::string path(INTERFACE_DIR);
    path.append(name.toStdString());
    path.append(OPERSTATE_PATH);
    return read_line(&path);
}

QString NetworkInterface::flags() {
    std::string path(INTERFACE_DIR);
    path.append(name.toStdString());
    path.append(FLAGS_PATH);
    return read_line(&path);
}

QString NetworkInterface::local_ip() {
    QString string = exec_command("ip", QStringList() << "address" << "show" << "dev" << name);
    QStringList items = string.split(" ");
    for(int i = 0; i < items.size(); i++) {
        if(items[i].contains("inet")) return items[i+1];
    }
    return "no connection";
}

QString NetworkInterface::global_ip() {
    QString ip = exec_command("curl", QStringList("2ip.ru")).simplified();
    if(!ip.isEmpty()) return ip;
    else return "no network";
}

QString NetworkInterface::rx_bytes() {
    std::string path(INTERFACE_DIR);
    path.append(name.toStdString());
    path.append(RX_BYTES_PATH);
    long new_value = read_line(&path).toLong();
    double division = new_value - rx_bytes_base;
    rx_bytes_base = new_value;

    if(division < 1024) return QString::number(std::round(division * 10) / 10) + " b/s";
    else if(division >= 1024 && division < 1048576) return QString::number(std::round((division / 1024) * 10) / 10) + " Kb/s";
    else if(division >= 1048576) return QString::number(std::round((division / 1048576) * 10) / 10) + " Mb/s";
}

QString NetworkInterface::tx_bytes() {
    std::string path(INTERFACE_DIR);
    path.append(name.toStdString());
    path.append(TX_BYTES_PATH);
    long new_value = read_line(&path).toLong();
    double division = new_value - tx_bytes_base;
    tx_bytes_base = new_value;

    if(division < 1024) return QString::number(std::round(division * 10) / 10) + " b/s";
    else if(division >= 1024 && division < 1048576) return QString::number(std::round((division / 1024) * 10) / 10) + " Kb/s";
    else if(division >= 1048576) return QString::number(std::round((division / 1048576) * 10) / 10) + " Mb/s";
}
