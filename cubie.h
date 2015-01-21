#ifndef CLIENT_H
#define CLIENT_H
#include <QUdpSocket>
#include <QTcpSocket>
#include <QTcpServer>
#include <QHostAddress>
#include <QMessageBox>


class Cubie:public QObject {
    Q_OBJECT
public:
    Cubie( QString addr, int port=26000, int tcpport=27000) {
        this->udpsocket = new QUdpSocket();
        this->tcpsocket = new QTcpSocket();
        this->tcpserver = new QTcpServer();
        connect(tcpsocket, SIGNAL(connected()), this,  SLOT(connected()));
        this->addr=addr;
        this->port=port;
        this->tcpport=tcpport;
        this->feedback_tcpport=tcpport+1; // Порт обратной связи всегда на единичку больше
        this->connection_status=false;
    }

    void connectToCubie();
    void disconnectFromCubie();
    void sendTest();
    void sendVar(const QString &key, const QString &value);
    float getFeedbackPitch();
    float getFeedbackRoll();
    float getFeedbackYaw();
    int getFeedbackThrottle();
    bool isConnected();

private:
    QString addr;
    int port;
    int tcpport;
    int feedback_tcpport;
    bool connection_status;
    QUdpSocket *udpsocket;
    QTcpSocket *tcpsocket;
    QTcpServer *tcpserver;
    QTcpSocket *feedbackClientSocket;
    int feedback_pitch=0; // тангаж*1000; для упрощения передачи по сети чисел с плавающей точкой
    int feedback_roll=0; // крен*1000
    int feedback_yaw=0; // рыскание*1000
    int feedback_throttle=0; // реальная тяга
    quint16     m_nNextBlockSize;


    void parseIncomingData(QString &data);


public slots:
    void connected();
    void slotNewConnection();
    void slotReadClient();
signals:
    void connectionEstablished();
    void packetSent();
    void newFeedbackConnection();
    void dataReady();

};
#endif // CLIENT_H
