#ifndef CLIENT_H
#define CLIENT_H
#include <QUdpSocket>
#include <QHostAddress>


class Cubie {
public:
    Cubie( QString addr, int port=26000) {
        this->udpsocket = new QUdpSocket();
        this->addr=addr;
        this->port=port;
        this->connection_status=false;
    }

    void connect();
    void sendTest();
    void sendVar(char* key, char* value);
    bool isConnected();

private:
    QString addr;
    int port;
    bool connection_status;
    QUdpSocket *udpsocket;
};
#endif // CLIENT_H
