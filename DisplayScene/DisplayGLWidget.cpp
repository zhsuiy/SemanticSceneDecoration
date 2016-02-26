#include "DisplayGLWidget.h"
#include <GL/GLU.h>

DisplayGLWidget::DisplayGLWidget(QWidget* parent)
	: QGLWidget(parent)
{
	
}

DisplayGLWidget::~DisplayGLWidget()
{
	
}

void DisplayGLWidget::initializeGL()
{
	glShadeModel(GL_SMOOTH);		// ������Ӱ�⻬
	glClearColor(0.2,0.2,0.2,0);	// ���������Ļ����ɫ
	glClearDepth(1.0);				// ������Ȼ���
	glEnable(GL_DEPTH_TEST);		// ��Ȳ���
	glDepthFunc(GL_LEQUAL);			// ������Ȳ���
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);	// ������õ�͸�����������ܻ�Ӱ������
}

void DisplayGLWidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);	// �����Ļ����Ȼ���
	glLoadIdentity();									// ���õ�ǰģ�͵Ĺ۲����
}

void DisplayGLWidget::resizeGL(int width, int height)
{
	if (height == 0)							// �涨��Ļ�߶Ȳ��õ���20
	{
		height = 20;
	}
	glViewport(0,0,(GLint)width,(GLint)height);	// ���õ�ǰ���ӿ�
	glMatrixMode(GL_PROJECTION);				// ѡ��ͶӰ����
	glLoadIdentity();							// ����ͶӰ����
	gluPerspective(45.0,(GLfloat)width/(GLfloat)height,0.1,100.0); // ����͸��ͶӰ����
	glMatrixMode(GL_MODELVIEW); // ѡ��ģ�͹۲����
	glLoadIdentity();			// ����ģ�͹۲����
}

//void DisplayGLWidget::keyPressEvent(QKeyEvent* e)
//{
//	switch (e->key())
//	{
//	default:
//		break;
//	}
//}


void DisplayGLWidget::mouseMoveEvent(QMouseEvent* event)
{
	
}

void DisplayGLWidget::mousePressEvent(QMouseEvent* event)
{
	
}


