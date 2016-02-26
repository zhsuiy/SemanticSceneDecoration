#include "mainwindow.h"
#include "DisplayGLWidget.h"
MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	resize(1400,800);	
	centralWidget = new QWidget;
	setCentralWidget(centralWidget);
	DisplayGLWidget *displaySceneWidget = new DisplayGLWidget();


	

	//ui.setupUi(this);
}

MainWindow::~MainWindow()
{

}
