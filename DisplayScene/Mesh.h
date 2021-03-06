#ifndef MESH_H
#define MESH_H

#include <QtCore/qvector.h>
#include <QtWidgets/QAction>
#include "Vertex.h"
#include <QtGui/QOpenGLBuffer>
#include <QtGui/QOpenGLVertexArrayObject>

class Mesh
{
public:
	/* Mesh Data*/
	QVector<Vertex> Vertices;
	QVector<GLuint> Indices;
	QVector<Texture> Textures;

	/* Functions */
	Mesh(QVector<Vertex> vertices, QVector<GLuint> indices, QVector<Texture> textures);
	//void Draw(Shader shader);
private:
	/* Render data */
	QOpenGLBuffer VBO;
	QOpenGLVertexArrayObject VAO;
	
	void setupMesh();
};


#endif

