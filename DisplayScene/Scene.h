#ifndef SCENE_H
#define SCENE_H
#include <QVector>
#include "Furniture.h"
class Scene
{
public:
	Scene();
	~Scene();

private:
	QVector<Furniture> m_furnitures;

};

#endif
