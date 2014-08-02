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


    connected=false;

    ui->label_up_blue->hide();
    ui->label_right_blue->hide();
    ui->label_down_blue->hide();
    ui->label_left_blue->hide();
    ui->label_up_right_blue->hide();
    ui->label_up_left_blue->hide();
    ui->label_down_left_blue->hide();
    ui->label_down_right_blue->hide();

    this->i = 1;
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

    if(keyState[0] && keyState[2] && connected){
        cubie->sendVar("up","1");
        cubie->sendVar("right","1");
        ui->label_up_right_blue->show();
    }
    else if(keyState[0] && keyState[3] && connected) {
        cubie->sendVar("up","1");
        cubie->sendVar("left","1");
        ui->label_up_left_blue->show();
    }
    else if(keyState[1] && keyState[2] && connected) {
        cubie->sendVar("down","1");
        cubie->sendVar("right","1");
        ui->label_down_right_blue->show();
    }
    else if(keyState[1] && keyState[3] && connected) {
        cubie->sendVar("down","1");
        cubie->sendVar("left","1");
        ui->label_down_left_blue->show();
    }
    else if(keyState[0] && connected) {
        cubie->sendVar("up","1");
        ui->label_up_blue->show();
    }
    else if(keyState[1] && connected) {
        cubie->sendVar("down","1");
        ui->label_down_blue->show();
    }
    else if(keyState[2] && connected) {
        cubie->sendVar("right","1");
        ui->label_right_blue->show();
    }
    else if(keyState[3] && connected) {
        cubie->sendVar("left","1");
        ui->label_left_blue->show();
    }


    if(connected){
       // cubie->sendVar("testd","yuhhu");
        ui->statusBar->showMessage("Отправлено пакетов: " + QString::number(i));
        i++;
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
        throttle_up();
    }
    else if(keyEvent->key()==Qt::Key_S)
    {
        throttle_down();
    }
    else if(keyEvent->key()==Qt::Key_C)
    {
        yaw_left();
    }
    else if(keyEvent->key()==Qt::Key_V)
    {
        yaw_right();
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
}


void MainWindow::on_action_connect_triggered()
{
    connectDialog connectDialog;

    if (connectDialog.exec() == QDialog::Accepted) {
        this->cubie = new Cubie(connectDialog.getIp(), 26000);
        this->cubie->connect();
        if(cubie->isConnected()){
            QMessageBox::information(0, "Information", "Соединено c " + connectDialog.getIp());
            ui->statusBar->showMessage("Соединение установлено");
            ui->label_2->setText("Соединено c " + connectDialog.getIp());
            ui->action_connect->setText("Разъеденить");
            this->showFullScreen();
            connected=true;
        } else {
            QMessageBox::information(0, "Information", "Соединение не установлено с " + connectDialog.getIp());
        }


    }

    //Cubie *cubie = new Cubie("91.123.151.230", 26000);
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

}
void MainWindow::yaw_right(){

}


void MainWindow::on_throttleSlider_valueChanged(int value)
{
    char text[4];
    sprintf(text, "%d", value);
    QString valText(text);
    ui->label_throttle_set->setText(valText);
}
