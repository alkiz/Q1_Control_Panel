#include <QUdpSocket>
#include <QHostAddress>
#include <QString>
#include "cubie.h"

void Cubie::connectToCubie(){
    this->udpsocket->connectToHost(QHostAddress(this->addr),this->port);
    this->tcpsocket->connectToHost(QHostAddress(this->addr),this->tcpport);
    //Открываю локальный сервер для получения обратной связи. Если забиндить не удалось - показываю ошибку
    if (!tcpserver->listen(QHostAddress::Any, this->feedback_tcpport)) {
            QMessageBox::critical(0,
                                  "Server Error",
                                  "Unable to start the server:"
                                  + tcpserver->errorString()
                                 );
            tcpserver->close();
            return;
    }
    connect(this->tcpserver, SIGNAL(newConnection()),this, SLOT(slotNewConnection()));

}

void Cubie::sendTest(){
    //this->udpsocket->writeDatagram("test=3\n", QHostAddress(this->addr), this->port);
    this->tcpsocket->write("tcpconnected=1\n");
}
void Cubie::slotNewConnection(){
    feedbackClientSocket = tcpserver->nextPendingConnection(); // Создаю сокет для получения данных от куби
    connect(feedbackClientSocket, SIGNAL(disconnected()), feedbackClientSocket, SLOT(deleteLater())); // после отсоединения удаляем сокет
    connect(feedbackClientSocket, SIGNAL(readyRead()), this, SLOT(slotReadClient()));
    emit newFeedbackConnection();
     //QMessageBox::information(0, "new connection", "hello");
}

void Cubie::slotReadClient() {
    QTcpSocket* pClientSocket = (QTcpSocket*)sender();
    char data[128];
    pClientSocket->read(data,128);

    QString strData = QString(data);

    parseIncomingData(strData);
   // QMessageBox::information(0, "Recieved", strData);

    emit dataReady();
}

void Cubie::sendVar(const QString &key, const QString &value){
    QString data= QString("%1=%2\n").arg(key).arg(value);
    this->tcpsocket->write(data.toLatin1());
    emit packetSent();
}

float Cubie::getFeedbackPitch(){

    return feedback_pitch/1000.0;
}
float Cubie::getFeedbackRoll(){

    return feedback_roll/1000.0;
}
float Cubie::getFeedbackYaw(){

    return feedback_yaw/1000.0;
}
int Cubie::getFeedbackThrottle(){
    return feedback_throttle;
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
    tcpserver->close();
    connection_status=false;
}

void Cubie::parseIncomingData(QString &data){
    //QMessageBox::information(0, "Recieved", data);
    int eqPosition=0;
    int dataLength=data.length();
    eqPosition=data.indexOf(QString("="));
    QString key = data.section("=",0,0);
    QString value= data.section("=",1,1);


    if (key.compare("roll")==0) {
        this->feedback_roll=value.toInt();
        return;
    }
    if (key.compare("pitch")==0) {
        this->feedback_pitch=value.toInt();
        return;
    }
    if (key.compare("yaw")==0) {
        this->feedback_yaw=value.toInt();
        return;
    }
    if (key.compare("throttle")==0) {
        this->feedback_throttle=value.toInt();
        return;
    }


}
