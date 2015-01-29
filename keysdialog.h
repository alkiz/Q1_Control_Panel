#ifndef KEYSDIALOG_H
#define KEYSDIALOG_H

#include <QDialog>

namespace Ui {
class keysDialog;
}

class keysDialog : public QDialog
{
	Q_OBJECT

public:
	explicit keysDialog(QWidget *parent = 0);
	~keysDialog();

private:
	Ui::keysDialog *ui;
};

#endif // KEYSDIALOG_H
