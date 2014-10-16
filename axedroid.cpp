#include "axedroid.h"
#include <QDesktopServices>
#include <QUrl>
#include <QSettings>

AxeDroid::AxeDroid(QObject *parent) :
    QObject(parent)
{
    MHS = "Connecting...";
    ACC = "Connecting...";
    REJ = "Connecting...";
    HWERR = "Connecting...";

    /*
    conColor = "#03c200";
    poolColor = "#03c200";
    minColor = "#03c200";
    */

    conColor =  "#BBBBBB";
    poolColor = "#BBBBBB";
    minColor =  "#BBBBBB";

    conUp = false;
    poolUp = false;
    minUp = false;

    autoRefreshTimer = new QTimer(this);
    connect(autoRefreshTimer, SIGNAL(timeout()), this, SLOT(requestNewFortune()));
    autoRefreshTimer->start(10000);

    IP1 = getIPAddress(0);
    IP2 = getIPAddress(1);

    loadSettings();

}

QVariant AxeDroid::visitCryptAxe()
{
    //visit cryptaxe.com in browser
    QDesktopServices::openUrl(QUrl("http://www.cryptaxe.com"));

    return "42";
}

QVariant AxeDroid::getFortune()
{
    QStringList data;

    //get fortune over tcp
    requestNewFortune();

    //return fortune list
    return data;
}

void AxeDroid::requestNewFortune()
{
    qDebug() << "Requesting new fortune!\n";
    tcpSocket = new QTcpSocket(this);
    tcpSocket->abort();

    tcpSocket->connectToHost(getIPAddress(0), getPort(0).toInt());
    connect(tcpSocket, SIGNAL(disconnected()), this, SLOT(readFortune()));
    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(readSocketError(QAbstractSocket::SocketError)));
}

void AxeDroid::readFortune()
{
    QString dataString;
    qDebug() << "TcpSocket disconnected, Reading fortune!\n";

    conUp = true;

    if (tcpSocket->bytesAvailable()) {
        dataString = tcpSocket->readAll();
    } else {
        qDebug() << "This is not the data you are looking for\n";
        minUp = false;
    }

    QStringList dataList = dataString.split(",");

    QStringList accepted = dataList.filter("Accepted=");
    QStringList mhs = dataList.filter("MHS 20s=");
    QStringList rejected = dataList.filter("Rejected=");
    QStringList hwerrors = dataList.filter("Hardware Errors=");

    if (!accepted.isEmpty()){
        MHS = mhs.at(0);
        ACC = accepted.at(0);
        REJ = rejected.at(0);
        HWERR = hwerrors.at(0);

        minUp = true;
    } else {
        MHS = "Connecting...";
        ACC = "Connecting...";
        REJ = "Connecting...";
        HWERR = "Connecting...";

        minUp = false;
    }

    //check pool
    if (!accepted.isEmpty()) {
        poolUp = true;
    } else {
        poolUp = false;
    }

    qDebug() << "MHS: " << MHS << endl;

    //if connection == good set green / else red
    if (conUp) {
        qDebug() << "Set conup to green\n";
        conColor = "#03c200";
    } else {
        qDebug() << "Set conup to red\n";
        conColor = "#FF0000";
    }

    //if pool == up set green / else red
    if (poolUp) {
        poolColor = "#03c200";
    } else if (conUp) {
        poolColor = "#BBBBBB";
    } else {
        poolColor = "#FF0000";
    }

    //if miner == running set green / else red
    if (minUp) {
        minColor = "#03c200";
    } else {
        minColor = "#FF0000";
    }

    emit newMinerData();
    emit newStatusColor();
}

QString AxeDroid::getMHS()
{
    return MHS;
}

QString AxeDroid::getAcc()
{
    return ACC;
}

QString AxeDroid::getRej()
{
    return REJ;
}

QString AxeDroid::getHwerr()
{
    return HWERR;
}

QString AxeDroid::getConStatusColor()
{
    return conColor;
}

QString AxeDroid::getPoolStatusColor()
{
    return poolColor;
}

QString AxeDroid::getMinStatusColor()
{
    return minColor;
}

void AxeDroid::readSocketError(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        qDebug() << "Socket Error Occurred, Remote host closed\n";
        //conUp = false;
        break;
    case QAbstractSocket::HostNotFoundError:
        qDebug() << "Socket Error Occurred, host not found\n";
        conUp = false;
        break;
    case QAbstractSocket::ConnectionRefusedError:
        qDebug() << "Socket Error Occurred, connection refused\n";
        conUp = false;
        break;
    default:
        qDebug() << "Socket Error Occurred, unkown error\n";
        conUp = false;
        break;
    }

    //if connection == good set green / else red
    if (conUp) {
        qDebug() << "Set conup to green\n";
        conColor = "#03c200";
    } else {
        qDebug() << "Set conup to red\n";
        conColor = "#FF0000";
    }

    emit newStatusColor();
}

QString AxeDroid::getIPAddress(int miner)
{
    switch (miner) {
    case 0:
        qDebug() << "Returning IP1: " << IP1 << endl;
        return IP1;
        break;
    case 1:
        return IP2;
        break;
    default:
        return "error";
        break;
    }
}

QString AxeDroid::setIPAddress(int miner, QString IP)
{
    qDebug() << "Settings IP Address: " << IP << endl;

    switch (miner) {
    case 0:
        qDebug() << "Set to " << IP << endl;
        IP1 = IP;
        break;
    case 1:
        IP2 = IP;
        break;
    default:
        break;
    }

    saveSettings();

    return IP;
}

QVariant AxeDroid::getPort(int miner)
{

    switch (miner) {
    case 0:
        qDebug() << "Returning port: " << port1 << endl;
        return port1;
        break;
    default:
        break;
    }
}

void AxeDroid::setPort(int miner, QString port)
{
    qDebug() << "Setting port: " << port << endl;
    switch (miner) {
    case 0:
        port1 = port.toInt();
        break;
    default:
        break;
    }

    saveSettings();
}

void AxeDroid::saveSettings()
{
    QSettings settings("CryptAxe", "bfgWatcher");
    settings.beginGroup("ProgramSettings");
    settings.setValue("minerIP1", IP1);
    settings.setValue("minerIP2", IP2);
    settings.setValue("minerPort1", port1);
    settings.endGroup();

    qDebug() << "Qsettings value set: " << IP1 << endl;
}

void AxeDroid::loadSettings()
{
    QSettings settings("CryptAxe", "bfgWatcher");
    settings.beginGroup("ProgramSettings");
    IP1 = settings.value("minerIP1").toString();
    IP2 = settings.value("minerIP2").toString();
    port1 = settings.value("minerPort1", 9993).toInt();
    settings.endGroup();

    qDebug() << "QSettings value loaded: " << IP1 << endl;
}


void AxeDroid::visitAppPage()
{
    qDebug() << "Visiting app page\n";
    //visit app page in browser
    QDesktopServices::openUrl(QUrl("http://www.cryptaxe.com/?p=591"));
}
