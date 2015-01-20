#include "connectdialog.h"
#include "ui_connectdialog.h"

connectDialog::connectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::connectDialog)
{
    ui->setupUi(this);
    //currentSession = QNetworkSession();
    //currentInterface = currentSession->interface();
    //ui->ip_info_label->setText(currentInterface->humanReadableName());

}

connectDialog::~connectDialog()
{
    delete ui;
}

QString connectDialog::getIp(){
    return ui->lineEdit->text();
}

int connectDialog::getPort(){
    return ui->port_Edit->text().toInt();
}

void connectDialog::on_port_Edit_textChanged(const QString &arg1) // функция, которая постоянно подстаривает порт обратной связи большим на еденичку
{
    int port=0;
    int feedback_port=0;
    port = ui->port_Edit->text().toInt();
    feedback_port=port+1;
    ui->feedback_port_Edit->setText(QString::number(feedback_port));
}
