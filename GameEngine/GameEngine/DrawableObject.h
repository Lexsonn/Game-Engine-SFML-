#ifndef DRAWABLEOBJECT_H
#define DRAWABLEOBJECT_H

#include <SFML/Graphics.hpp>

#define DO_BASE 0

using namespace sf;

class DrawableObject {
public:
	float x, y;

	~DrawableObject();
	DrawableObject();

	virtual void render(RenderWindow *window);
	void setVisible(bool isVisible);
	bool isVisible();
	virtual int getType();

protected:
	bool visible;
};
#endif