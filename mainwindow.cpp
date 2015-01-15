#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cubie.h"
#include "connectdialog.h"

#include <QKeyEvent>
#include <QMessageBox>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->statusBar->showMessage("Нет соединения");
    keyState[0]=false; // вверх
    keyState[1]=false; // вниз
    keyState[2]=false; // вправо
    keyState[3]=false; // влево

    throttleUpKeyState = false;
    throttleDownKeyState = false;
    yawLeftKeyState = false;
    yawRightKeyState = false;



    connected=false;

    ui->label_up_blue->hide();
    ui->label_right_blue->hide();
    ui->label_down_blue->hide();
    ui->label_left_blue->hide();
    ui->label_up_right_blue->hide();
    ui->label_up_left_blue->hide();
    ui->label_down_left_blue->hide();
    ui->label_down_right_blue->hide();

    this->sendedPackets = 1;
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(20);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update(){
    //QMessageBox::information(0, "Information", "Прошла секунда");
    ui->label_up_blue->hide();
    ui->label_right_blue->hide();
    ui->label_down_blue->hide();
    ui->label_left_blue->hide();
    ui->label_up_right_blue->hide();
    ui->label_up_left_blue->hide();
    ui->label_down_left_blue->hide();
    ui->label_down_right_blue->hide();




    // разбор клавиш-стрелок (тангаж и крен)
    if(keyState[0] && keyState[2]){
        if (connected){
            cubie->sendVar("up","1");
            cubie->sendVar("right","1");
        }
        ui->label_up_right_blue->show();
    }
    else if(keyState[0] && keyState[3]) {
        if (connected){
            cubie->sendVar("up","1");
            cubie->sendVar("left","1");
        }
        ui->label_up_left_blue->show();
    }
    else if(keyState[1] && keyState[2]) {
        if (connected) {
            cubie->sendVar("down","1");
            cubie->sendVar("right","1");
        }
        ui->label_down_right_blue->show();
    }
    else if(keyState[1] && keyState[3]) {
        if (connected){
            cubie->sendVar("down","1");
            cubie->sendVar("left","1");
        }
        ui->label_down_left_blue->show();
    }
    else if(keyState[0]) {
        if (connected){
            cubie->sendVar("up","1");
        }
        ui->label_up_blue->show();
    }
    else if(keyState[1]) {
        if (connected){
            cubie->sendVar("down","1");
        }
        ui->label_down_blue->show();
    }
    else if(keyState[2]) {
        if (connected){
            cubie->sendVar("right","1");
        }
        ui->label_right_blue->show();
    }
    else if(keyState[3]) {
        if (connected){
            cubie->sendVar("left","1");
        }
        ui->label_left_blue->show();
    }
    // разбор клавиш тяги
    if(throttleUpKeyState && !throttleDownKeyState ){
        throttle_up();
        if (connected){
            char throttle_text[4];
            sprintf(throttle_text,"%d",ui->throttleSlider->value());
            cubie->sendVar("throttle",throttle_text);
        }
    } else if(throttleDownKeyState && !throttleUpKeyState){
        throttle_down();
        if (connected){
            char throttle_text[4];
            sprintf(throttle_text,"%d",ui->throttleSlider->value());
            cubie->sendVar("throttle",throttle_text);
        }

    }
    // разбор клавиш рыскания
    char yaw_text[4];
    if(yawLeftKeyState && !yawRightKeyState){

        yaw_left();
        if (connected){
            sprintf(yaw_text,"%d",ui->yawSlider->value());
            cubie->sendVar("yaw",yaw_text);
        }
    } else if(yawRightKeyState && !yawLeftKeyState){
        yaw_right();
        if (connected){
            sprintf(yaw_text,"%d",ui->yawSlider->value());
            cubie->sendVar("yaw",yaw_text);
        }
    } else if(yawRightKeyState && yawLeftKeyState){
        // нажаты обе клавиши, ничего не делаем
    }else if(ui->yawSlider->value()!=0){
        yaw_center();
        if (connected){
            sprintf(yaw_text,"%d",ui->yawSlider->value());
            cubie->sendVar("yaw",yaw_text);
        }
    }



    if(connected){
       // cubie->sendVar("testd","yuhhu");
        ui->statusBar->showMessage("Отправлено пакетов: " + QString::number(sendedPackets));
        //i++;
    }
}

void MainWindow::keyPressEvent(QKeyEvent *keyEvent)
{

    if(keyEvent->key()==Qt::Key_Up)
    {
        keyState[0]=true;
    }
    else if(keyEvent->key()==Qt::Key_Down)
    {
        keyState[1]=true;
    }
    else if(keyEvent->key()==Qt::Key_Right)
    {
        keyState[2]=true;
    }
    else if(keyEvent->key()==Qt::Key_Left)
    {
        keyState[3]=true;
    }
    else if(keyEvent->key()==Qt::Key_W)
    {
        throttleUpKeyState=true;
    }
    else if(keyEvent->key()==Qt::Key_S)
    {
        throttleDownKeyState=true;
    }
    else if(keyEvent->key()==Qt::Key_C)
    {
        yawLeftKeyState=true;
    }
    else if(keyEvent->key()==Qt::Key_V)
    {
        yawRightKeyState=true;
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *keyEvent)
{

    if(keyEvent->key()==Qt::Key_Up)
    {
        keyState[0]=false;
    }
    else if(keyEvent->key()==Qt::Key_Down)
    {
        keyState[1]=false;
    }
    else if(keyEvent->key()==Qt::Key_Right)
    {
        keyState[2]=false;
    }
    else if(keyEvent->key()==Qt::Key_Left)
    {
        keyState[3]=false;
    }
    else if(keyEvent->key()==Qt::Key_W)
    {
        throttleUpKeyState=false;
    }
    else if(keyEvent->key()==Qt::Key_S)
    {
        throttleDownKeyState=false;
    }
    else if(keyEvent->key()==Qt::Key_C)
    {
        yawLeftKeyState=false;
    }
    else if(keyEvent->key()==Qt::Key_V)
    {
        yawRightKeyState=false;
    }
}



void MainWindow::on_action_connect_triggered()
{
    if(connected){
        cubie->disconnectFromCubie();
        QMessageBox::information(0, "Information", "Отключено от " + cDialog.getIp() + ":" + QString::number(cDialog.getPort()));
        ui->statusBar->showMessage("Соединение разорвано");
        ui->label_2->setText("Нет соединения");
        ui->action_connect->setText("Подключится к ...");
        connected=false;
    } else{
        if (cDialog.exec() == QDialog::Accepted) {
            this->cubie = new Cubie(cDialog.getIp(), 26000, cDialog.getPort());
            this->cubie->connectToCubie();
            connect(cubie, SIGNAL(packetSent()), this, SLOT(packetSent()));
            qDebug() << "test";
            connect(cubie, SIGNAL(connectionEstablished()), this, SLOT(connectionEstablished()));
        }
    }

    //Cubie *cubie = new Cubie("91.123.151.230", 26000);
}
void MainWindow::connectionEstablished() {
    QMessageBox::information(0, "Information", "Соединено c " + cDialog.getIp() + ":" + QString::number(cDialog.getPort()));
    ui->statusBar->showMessage("Соединение установлено");
    ui->label_2->setText("Соединено c " + cDialog.getIp() + ":" + QString::number(cDialog.getPort()));
    ui->action_connect->setText("Разъеденить");
    //this->showFullScreen();
    connected=true;
    cubie->sendTest();
}

void MainWindow::packetSent() {
    sendedPackets++;
}

void MainWindow::throttle_up(){
    int old_value =ui->throttleSlider->value();
    int new_value = old_value+ui->throttle_sesitivity_spinBox->value();
    ui->throttleSlider->setValue(new_value);
}

void MainWindow::throttle_down(){
    int old_value =ui->throttleSlider->value();
    int new_value = old_value-ui->throttle_sesitivity_spinBox->value();
    ui->throttleSlider->setValue(new_value);
}
void MainWindow::yaw_left(){
    int old= ui->yawSlider->value();
    int new_val = old-ui->yaw_sesitivity_spinBox->value();
    ui->yawSlider->setValue(new_val);
}
void MainWindow::yaw_right(){
    int old= ui->yawSlider->value();
    int new_val = old+ui->yaw_sesitivity_spinBox->value();
    ui->yawSlider->setValue(new_val);
}

void MainWindow::yaw_center(){
    int old= ui->yawSlider->value();
    int new_val=0;
    if(old>0){
        if (old >= ui->yaw_sesitivity_spinBox->value()){
            new_val = old-ui->yaw_sesitivity_spinBox->value();
        }
    }
    else if(old<0){
        if ((0-old) >= ui->yaw_sesitivity_spinBox->value()){
            new_val = old+ui->yaw_sesitivity_spinBox->value();
        }
    }
    //char test[3];
    //sprintf(test,"%d", new_val);
    //ui->statusBar->showMessage(test);
    ui->yawSlider->setValue(new_val);
}


void MainWindow::on_throttleSlider_valueChanged(int value)
{
    char text[4];
    sprintf(text, "%d", value);
    QString valText(text);
    ui->label_throttle_set->setText(valText);
}

void MainWindow::on_action_keys_triggered()
{
    kDialog.exec();
}

void MainWindow::on_pushButton_clicked()
{

}

void MainWindow::on_P_SpinBox_valueChanged(const QString &arg1)
{
    //Посылаем коэффициенты
    if (connected){
        cubie->sendVar("p",QString::number(ui->P_SpinBox->value()*1000));
    }
}

void MainWindow::on_I_SpinBox_valueChanged(const QString &arg1)
{
    //Посылаем коэффициенты
    if (connected){
        cubie->sendVar("i",QString::number(ui->I_SpinBox->value()*1000));
    }
}

void MainWindow::on_D_SpinBox_valueChanged(const QString &arg1)
{
    //Посылаем коэффициенты
    if (connected){
        cubie->sendVar("d",QString::number(ui->D_SpinBox->value()*1000));
    }
}
