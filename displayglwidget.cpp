#include "displayglwidget.h"
#include <QtWidgets>
#include <QtOpenGL>

DisplayGLWidget::DisplayGLWidget(QWidget *parent) :
    QGLWidget(parent)
{
    pitchAngle=0.0;
    rollAngle=0.0;
    yawAngle=0.0;

    qtRed = QColor(255,100,100);
    qtGray = QColor(100,100,100);
}

void DisplayGLWidget::setPitchAngle(float angle)
{
    pitchAngle=angle;
}

void DisplayGLWidget::setRollAngle(float angle)
{
    rollAngle=angle;
}

void DisplayGLWidget::setYawAngle(float angle)
{
    yawAngle=angle;
}

void DisplayGLWidget::initializeGL()
{
    qglClearColor(Qt::white); // заполняем экран белым цветом
    glEnable(GL_DEPTH_TEST); // задаем глубину проверки пикселей
    glShadeModel(GL_FLAT); // убираем режим сглаживания цветов
    glEnable(GL_CULL_FACE); // говорим, что будем строить только внешние поверхности
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL); // фигуры будут закрашены с обеих сторон

}

void DisplayGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // очистка экрана
    glMatrixMode(GL_MODELVIEW); // задаем модельно-видовую матрицу
    glLoadIdentity();           // загрузка единичную матрицу

    QColor halfGreen(0, 255, 0, 255); // устанавливаем цвет квадрата
    qglColor(halfGreen); // задаем цвет
    glBegin(GL_QUADS); // говорим, что рисовать будем прямоугольник
    // задаем вершины многоугольника
    glVertex3f(0.5, 0.5, 0.5);
    glVertex3f(-0.5, 0.5, 0.5);
    glVertex3f(-0.5, -0.5, 0.5);
    glVertex3f(0.5, -0.5, 0.5);
    glEnd();
}

void DisplayGLWidget::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height); // установка точки обзора
    glMatrixMode(GL_PROJECTION); // установка режима матрицы
    glLoadIdentity(); // загрузка матрицы
}




