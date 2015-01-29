#ifndef DISPLAYGLWIDGET_H
#define DISPLAYGLWIDGET_H

#include <QGLWidget>
#include <QtOpenGL>
#include <GL/glu.h>

class DisplayGLWidget : public QGLWidget
{
	Q_OBJECT
public:
	explicit DisplayGLWidget(QWidget *parent = 0);


	void setPitchAngle(float angle);
	void setRollAngle(float angle);
	void setYawAngle(float angle);



private:

	float pitchAngle;
	float rollAngle;
	float yawAngle;

	QColor qtRed;
	QColor qtGray;


signals:

public slots:

protected:
	void initializeGL();
	void paintGL();
	void resizeGL(int width, int height);

};

#endif // DISPLAYGLWIDGET_H
