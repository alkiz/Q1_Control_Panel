#include "displayglwidget.h"
#include <QtWidgets>

DisplayGLWidget::DisplayGLWidget(QWidget *parent) :
	QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
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
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_CULL_FACE);
	//glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	static GLfloat lightPosition[4] = { 0.0, -5.0, -5.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.0);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.0);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.0);


}

void DisplayGLWidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(	0, 250, 500, // откуда смотрим
				0, 0, 0,	// куда смотрим
				0.0, 1.0, 0.0); // радиус-вектор указывающий, где верх

	int middleFrameVertexArray[] = {  -300, -5, 5, //0
										 300, -5, 5, //1
										 300,  5, 5, //2
										-300,  5, 5, //3
										-300, -5, -5, //4
										 300, -5, -5, //5
										 300,  5, -5, //6
										-300,  5, -5};//7
	/*int indexArray[6][4];
		indexArray[0][0]= 0;
		indexArray[0][1]= 1;
		indexArray[0][2]= 2;
		indexArray[0][3]= 3;
		indexArray[1][0]= 4;
		indexArray[1][1]= 0;
		indexArray[1][2]= 3;
		indexArray[1][3]= 7;
		indexArray[2][0]= 1;
		indexArray[2][1]= 5;
		indexArray[2][2]= 6;
		indexArray[2][3]= 2;
		indexArray[3][0]= 3;
		indexArray[3][1]= 2;
		indexArray[3][2]= 6;
		indexArray[3][3]= 7;
		indexArray[4][0]= 4;
		indexArray[4][1]= 5;
		indexArray[4][2]= 1;
		indexArray[4][3]= 0;
		indexArray[5][0]= 5;
		indexArray[5][1]= 4;
		indexArray[5][2]= 7;
		indexArray[5][3]= 6;
	*/
	int normalArray[]= {	0,0,1,  // 0 передняя
							-1,0,0, // 1 слева
							1,0,0,  // 2 справа
							0,1,0,  // 3 сверху
							0,-1,0, // 4 снизу
							0,0,1   // 5 сзади
							};
	int rearFrameVertexArray[] = {		-5, -5, 300, //0
										 5, -5, 300, //1
										 5,  5, 300, //2
										-5,  5, 300, //3
										-5, -5, 5, //4
										 5, -5, 5, //5
										 5,  5, 5, //6
										-5,  5, 5}; //7
	int frontFrameVertexArray[] = {		-5, -5, -5, //0
										5, -5, -5, //1
										5,  5, -5, //2
										-5,  5, -5, //3
										-5, -5, -300, //4
										5, -5, -300, //5
										5,  5, -300, //6
										-5,  5, -300}; //7

	const GLubyte redColor[] = {255, 0, 0};
	const GLubyte greenColor[] = {0, 255, 0};
	const GLubyte blueColor[] = {0, 0, 255};
	const GLubyte yellowColor[] = {255, 255, 0};
	const GLubyte cyanColor[] = {200, 255, 255};
	const GLubyte violetColor[] = {255, 0, 255};
	const GLubyte almostWhiteColor[] = {240, 240, 240};
	const GLubyte darkGrayColor[]={50,50,50};

	glEnableClientState(GL_VERTEX_ARRAY);

	glRotatef(pitchAngle, 1,0,0);
	glRotatef(rollAngle, 0,0,1);
	//glRotatef(yawAngle, 0,1,0);

	glVertexPointer(3, GL_INT, 0, middleFrameVertexArray);
	//glDrawElements(GL_QUADS, 24, GL_INT, indexArray);
	glColor3ubv(almostWhiteColor);
	glBegin(GL_QUADS);
		//glNormal3iv(normalArray);
		glArrayElement(0);
		glArrayElement(1);
		glArrayElement(2);
		glArrayElement(3);

		//glNormal3iv(normalArray+1*3*sizeof(int));
		glArrayElement(4);
		glArrayElement(0);
		glArrayElement(3);
		glArrayElement(7);

		//glNormal3iv(normalArray+2*3*sizeof(int));
		glArrayElement(1);
		glArrayElement(5);
		glArrayElement(6);
		glArrayElement(2);

		//glNormal3iv(normalArray+3*3*sizeof(int));
		glArrayElement(3);
		glArrayElement(2);
		glArrayElement(6);
		glArrayElement(7);

		//glNormal3iv(normalArray+4*3*sizeof(int));
		glArrayElement(4);
		glArrayElement(5);
		glArrayElement(1);
		glArrayElement(0);

		//glNormal3iv(normalArray+5*3*sizeof(int));
		glArrayElement(5);
		glArrayElement(4);
		glArrayElement(7);
		glArrayElement(6);
	glEnd();

	glVertexPointer(3, GL_INT, 0, rearFrameVertexArray);

	glColor3ubv(redColor);
	glBegin(GL_QUADS);
		//glNormal3iv(normalArray);
		glArrayElement(0);
		glArrayElement(1);
		glArrayElement(2);
		glArrayElement(3);

		//glNormal3iv(normalArray+1*3*sizeof(int));
		glArrayElement(4);
		glArrayElement(0);
		glArrayElement(3);
		glArrayElement(7);

		//glNormal3iv(normalArray+2*3*sizeof(int));
		glArrayElement(1);
		glArrayElement(5);
		glArrayElement(6);
		glArrayElement(2);

		//glNormal3iv(normalArray+3*3*sizeof(int));
		glArrayElement(3);
		glArrayElement(2);
		glArrayElement(6);
		glArrayElement(7);

		//glNormal3iv(normalArray+4*3*sizeof(int));
		glArrayElement(4);
		glArrayElement(5);
		glArrayElement(1);
		glArrayElement(0);

		//glNormal3iv(normalArray+5*3*sizeof(int));
		glArrayElement(5);
		glArrayElement(4);
		glArrayElement(7);
		glArrayElement(6);


	glEnd();

	glVertexPointer(3, GL_INT, 0, frontFrameVertexArray);
	glColor3ubv(greenColor);
	glBegin(GL_QUADS);
		//glNormal3iv(normalArray);
		glArrayElement(0);
		glArrayElement(1);
		glArrayElement(2);
		glArrayElement(3);

		//glNormal3iv(normalArray+1*3*sizeof(int));
		glArrayElement(4);
		glArrayElement(0);
		glArrayElement(3);
		glArrayElement(7);

		//glNormal3iv(normalArray+2*3*sizeof(int));
		glArrayElement(1);
		glArrayElement(5);
		glArrayElement(6);
		glArrayElement(2);

		//glNormal3iv(normalArray+3*3*sizeof(int));
		glArrayElement(3);
		glArrayElement(2);
		glArrayElement(6);
		glArrayElement(7);

		//glNormal3iv(normalArray+4*3*sizeof(int));
		glArrayElement(4);
		glArrayElement(5);
		glArrayElement(1);
		glArrayElement(0);

		//glNormal3iv(normalArray+5*3*sizeof(int));
		glArrayElement(5);
		glArrayElement(4);
		glArrayElement(7);
		glArrayElement(6);
	glEnd();

	glColor3ubv(yellowColor);
	glBegin(GL_QUADS);
		glVertex3f(-141.42, 5.01,       0);
		glVertex3f(      0, 5.01,  141.42);
		glVertex3f( 141.42, 5.01,       0);
		glVertex3f(      0, 5.01, -141.42);
	glEnd();





	//Рисую небо и землю

	glLoadIdentity();
	gluLookAt(	0, 250, 500, // откуда смотрим
				0, 0, 0,	// куда смотрим
				0.0, 1.0, 0.0); // радиус-вектор указывающий, где верх


	glColor3ubv(cyanColor);
	glBegin(GL_QUADS);
		glVertex3f(-100000, 500, -100000);
		glVertex3f(100000, 500, -100000);
		glVertex3f(100000, 500, 100000);
		glVertex3f(-100000, 500, 100000);
	glEnd();

	glColor3ubv(darkGrayColor);


	glBegin(GL_QUADS);
		glVertex3f(-100000, -500, -100000);
		glVertex3f(-100000, -500, 100000);
		glVertex3f(100000, -500, 100000);
		glVertex3f(100000, -500, -100000);
	glEnd();


}

void DisplayGLWidget::resizeGL(int width, int height)
{
	glViewport(0, 0, width, height); // установка точки обзора
	glMatrixMode(GL_PROJECTION); // установка режима матрицы
	glLoadIdentity(); // загрузка матрицы

	//glFrustum(-1.0,1.0,-1.0,1.0,1.5,10.0);

	double ratio = width/height;

	gluPerspective(60.0, ratio, 100, 100000.0);

	glMatrixMode(GL_MODELVIEW);
}




