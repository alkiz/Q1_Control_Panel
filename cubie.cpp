#include <QUdpSocket>
#include <QHostAddress>
#include "cubie.h"

void Cubie::connect(){
    connection_status = this->udpsocket->bind(QHostAddress(this->addr),this->port);
    connection_status=true;
}

void Cubie::sendTest(){
    this->udpsocket->writeDatagram("test=3\n", QHostAddress(this->addr), this->port);
}
void Cubie::sendVar(char* key, char* value){
    char data[80];
    sprintf (data, "%s=%s\n", key, value);
    this->udpsocket->writeDatagram(data, QHostAddress(this->addr), this->port );
}
bool Cubie::isConnected(){
    return this->connection_status;
}
