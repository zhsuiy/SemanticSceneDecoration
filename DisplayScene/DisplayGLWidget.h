#ifndef DISPLAYWIDGET_H
#define DISPLAYWIDGET_H

#include <QGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
class DisplayGLWidget:public QGLWidget
{
	Q_OBJECT
public:
	DisplayGLWidget(QWidget *parent = 0);
	~DisplayGLWidget();
public slots:
	//void CompileAndLinkVertexShader(const QString& shaderText);
	//void CompileAndLinkFragmentShader(const QString& shaderText);
	
protected:
	
	void initializeGL() override;
	void paintGL() override;
	void resizeGL(int width, int height) override; 

	//void keyPressEvent(QKeyEvent *event) override;
	void mousePressEvent(QMouseEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;

private:
	QOpenGLBuffer m_VertexBuffer,m_ColorBuffer;
	QOpenGLVertexArrayObject vao;
	
	QOpenGLShader *m_pVertexShader, *m_pFragmentShader;
	QOpenGLShaderProgram m_shaderProgram;


};


#endif

