#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "cubie.h"
#include "connectdialog.h"
#include "keysdialog.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();



private slots:

    void on_action_connect_triggered();
    void update();

    void on_throttleSlider_valueChanged(int value);
    void on_action_keys_triggered();

    void on_pushButton_clicked();

    void on_P_SpinBox_valueChanged(const QString &arg1);

    void on_I_SpinBox_valueChanged(const QString &arg1);

    void on_D_SpinBox_valueChanged(const QString &arg1);

public slots:
    void connectionEstablished();
    void packetSent();
    void feedbackConnectionEstablished();
    void feedbackUpdate();
    void graphUpdate();
private:
    Ui::MainWindow *ui;
    bool keyState[4];
    bool throttleUpKeyState;
    bool throttleDownKeyState;
    bool yawLeftKeyState;
    bool yawRightKeyState;
    Cubie *cubie;
    int sendedPackets;
    bool connected;
    connectDialog cDialog;
    keysDialog kDialog;
    QVector<double> x, pitchData, rollData, yawData;


    //Функции
    void keyPressEvent(QKeyEvent*);
    void keyReleaseEvent(QKeyEvent*);
    void throttle_up();
    void throttle_down();
    void yaw_left();
    void yaw_right();
    void yaw_center();
    void graphInit();

};

#endif // MAINWINDOW_H
