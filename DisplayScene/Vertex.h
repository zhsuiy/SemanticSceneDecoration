#ifndef VERTEX_H
#define VERTEX_H
#include <GL/glew.h>
#include <QtGui/qvector3d.h>
#include <QtGui/qvector2d.h>
#include <QtCore/qstring.h>

struct Vertex
{
	QVector3D Position;
	QVector3D Normal;
	QVector2D TexCoords;
};

struct Texture
{
	GLuint Id;
	QString Type;	// store texture type, e.g. a diffuse texture or a specular texture

};

#endif


