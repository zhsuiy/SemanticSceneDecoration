#ifndef BASE_OBJECT_H
#define BASE_OBJECT_H
#include <QtCore/qstring.h>

class BaseObject
{
public:
	BaseObject();
	~BaseObject();

	int ID;
	QString Name;
};

#endif
