#ifndef DRAWABLEOBJECT_H
#define DRAWABLEOBJECT_H

#include <SFML/Graphics.hpp>

using namespace sf;

class DrawableObject {
public:
	float x, y;

	~DrawableObject();
	DrawableObject();
	
	void setVisible(bool isVisible);
	bool isVisible();

	//virtual Sprite &getSprite();
	virtual void render(RenderWindow *window);
protected:
	bool visible;
};
#endif
