#ifndef CONNECTDIALOG_H
#define CONNECTDIALOG_H

#include <QDialog>
#include <QNetworkSession>

namespace Ui {
class connectDialog;
}

class connectDialog : public QDialog
{
	Q_OBJECT

public:
	explicit connectDialog(QWidget *parent = 0);
	~connectDialog();
	QString getIp();
	int getPort();
private slots:
	void on_port_Edit_textChanged(const QString &arg1);

private:
	Ui::connectDialog *ui;
};

#endif // CONNECTDIALOG_H
