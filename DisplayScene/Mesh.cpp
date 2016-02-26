#include "Mesh.h"

Mesh::Mesh(QVector<Vertex> vertices, QVector<GLuint> indices, QVector<Texture> textures)
{
	this->Vertices = vertices;
	this->Indices = indices;
	this->Textures = textures;
	this->setupMesh();
}


void Mesh::setupMesh()
{
	
}

