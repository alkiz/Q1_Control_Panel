#ifndef CLIENT_H
#define CLIENT_H
#include <QUdpSocket>
#include <QTcpSocket>
#include <QHostAddress>


class Cubie:public QObject {
    Q_OBJECT
public:
    Cubie( QString addr, int port=26000, int tcpport=27000) {
        this->udpsocket = new QUdpSocket();
        this->tcpsocket = new QTcpSocket();
        connect(tcpsocket, SIGNAL(connected()), this,  SLOT(connected()));
        this->addr=addr;
        this->port=port;
        this->tcpport=tcpport;
        this->connection_status=false;
    }

    void connectToCubie();
    void disconnectFromCubie();
    void sendTest();
    void sendVar(const QString &key, const QString &value);
    QString getVar(const QString &key);
    bool isConnected();

private:
    QString addr;
    int port;
    int tcpport;
    bool connection_status;
    QUdpSocket *udpsocket;
    QTcpSocket *tcpsocket;
public slots:
    void connected();
signals:
    void connectionEstablished();

};
#endif // CLIENT_H
