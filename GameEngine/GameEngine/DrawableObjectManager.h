#ifndef DRAWABLEOBJECTMANAGER_H
#define DRAWABLEOBJECTMANAGER_H

#include "DrawableObject.h"

using namespace sf;

struct DrawableObjectManager {
	void addDrawableObject(DrawableObject *drawObj);
	void clearDrawableList();
	void update();

	static std::vector<DrawableObject *> drawableList;
};

#endif
