#include <QUdpSocket>
#include <QHostAddress>
#include <QString>
#include "cubie.h"

void Cubie::connectToCubie(){
    this->udpsocket->connectToHost(QHostAddress(this->addr),this->port);
    //udpsocket->waitForConnected(5000);
    tcpsocket->connectToHost(QHostAddress(this->addr),this->tcpport);
    //tcpsocket->waitForConnected(5000);
}

void Cubie::sendTest(){
    this->udpsocket->writeDatagram("test=3\n", QHostAddress(this->addr), this->port);
    this->tcpsocket->write("tcpconnected=1\n");
}
void Cubie::sendVar(const QString &key, const QString &value){
    QString data= QString("%1=%2\n").arg(key).arg(value);
    //QString::sprintf (data, "%s=%s\n", &key, &value);
    this->udpsocket->writeDatagram(data.toLatin1(), QHostAddress(this->addr), this->port );
    emit packetSent();
}
QString Cubie::getVar(const QString &key){

}
bool Cubie::isConnected(){
    return connection_status;
}
void Cubie::connected(){
    if (tcpsocket->state()==QAbstractSocket::ConnectedState){
        connection_status=true;
        emit connectionEstablished();
    }
}
void Cubie::disconnectFromCubie(){
    udpsocket->disconnectFromHost();
    tcpsocket->disconnectFromHost();
    connection_status=false;
}
