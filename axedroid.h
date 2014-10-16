#ifndef AXEDROID_H
#define AXEDROID_H

#include <QObject>
#include <QVariant>
#include <QStringList>
#include <QTcpSocket>
#include <QTimer>

class AxeDroid : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QVariant visitCryptAxe READ visitCryptAxe)
    Q_PROPERTY(QVariant getFortune READ getFortune)

    Q_PROPERTY(QString getMHS READ getMHS NOTIFY newMinerData)
    Q_PROPERTY(QString getAcc READ getAcc NOTIFY newMinerData)
    Q_PROPERTY(QString getRej READ getRej NOTIFY newMinerData)
    Q_PROPERTY(QString getHwerr READ getHwerr NOTIFY newMinerData)

    Q_PROPERTY(QString getConStatusColor READ getConStatusColor NOTIFY newStatusColor)
    Q_PROPERTY(QString getPoolStatusColor READ getPoolStatusColor NOTIFY newStatusColor)
    Q_PROPERTY(QString getMinStatusColor READ getMinStatusColor NOTIFY newStatusColor)


public:
    explicit AxeDroid(QObject *parent = 0);

    QString getMHS();
    QString getAcc();
    QString getRej();
    QString getHwerr();
    QString getConStatusColor();
    QString getPoolStatusColor();
    QString getMinStatusColor();
    QString getIPpropFuntion();


signals:
    void newMinerData();
    void newStatusColor();
    void newIPaddress();

public slots:
    void requestNewFortune();
    void readFortune();
    void readSocketError(QAbstractSocket::SocketError socketError);
    QString getIPAddress(int miner);
    QString setIPAddress(int miner, QString IP);
    QVariant getPort(int miner);
    void setPort(int miner, QString port);
    void visitAppPage();
    QVariant visitCryptAxe();

    QVariant getFortune();

private:
    QTcpSocket *tcpSocket;
    QTimer *autoRefreshTimer;
    QString MHS;
    QString ACC;
    QString REJ;
    QString HWERR;
    QString conColor;
    QString poolColor;
    QString minColor;
    bool conUp;
    bool poolUp;
    bool minUp;
    QStringList ipAddressList;
    QString IP1;
    QString IP2;
    int port1;
    //save ALL settings
    void saveSettings();
    //load ALL settings
    void loadSettings();

};

#endif // AXEDROID_H
