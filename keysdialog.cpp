#include "keysdialog.h"
#include "ui_keysdialog.h"

keysDialog::keysDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::keysDialog)
{
    ui->setupUi(this);
}

keysDialog::~keysDialog()
{
    delete ui;
}
