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
	glShadeModel(GL_SMOOTH);		// 启用阴影光滑
	glClearColor(0.2,0.2,0.2,0);	// 设置清除屏幕的颜色
	glClearDepth(1.0);				// 设置深度缓存
	glEnable(GL_DEPTH_TEST);		// 深度测试
	glDepthFunc(GL_LEQUAL);			// 启用深度测试
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);	// 进行最好的透视修正，可能会影响性能
}

void DisplayGLWidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);	// 清除屏幕和深度缓存
	glLoadIdentity();									// 重置当前模型的观察矩阵
}

void DisplayGLWidget::resizeGL(int width, int height)
{
	if (height == 0)							// 规定屏幕高度不得低于20
	{
		height = 20;
	}
	glViewport(0,0,(GLint)width,(GLint)height);	// 重置当前的视口
	glMatrixMode(GL_PROJECTION);				// 选择投影矩阵
	glLoadIdentity();							// 重置投影矩阵
	gluPerspective(45.0,(GLfloat)width/(GLfloat)height,0.1,100.0); // 建立透视投影矩阵
	glMatrixMode(GL_MODELVIEW); // 选择模型观察矩阵
	glLoadIdentity();			// 重置模型观察矩阵
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


