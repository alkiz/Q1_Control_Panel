#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "cubie.h"
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

private:
    Ui::MainWindow *ui;
    bool keyState[4];
    bool throttleUpKeyState;
    bool throttleDownKeyState;
    bool yawLeftKeyState;
    bool yawRightKeyState;
    Cubie *cubie;
    int i;
    bool connected;

    //Функции
    void keyPressEvent(QKeyEvent*);
    void keyReleaseEvent(QKeyEvent*);
    void throttle_up();
    void throttle_down();
    void yaw_left();
    void yaw_right();
    void yaw_center();
};

#endif // MAINWINDOW_H
