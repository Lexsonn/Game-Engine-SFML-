#ifndef DRAWABLEOBJECT_H
#define DRAWABLEOBJECT_H

#include <SFML/Graphics.hpp>

using namespace sf;

class DrawableObject {
public:
	float x, y;

	~DrawableObject();
	DrawableObject();

	virtual void render(RenderWindow *window);
	
	void setVisible(bool isVisible);
	bool isVisible();
protected:
	bool visible;
};
#endif
