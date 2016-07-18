#ifndef DRAWABLEOBJECT_H
#define DRAWABLEOBJECT_H

#include <SFML/Graphics.hpp>
//#include "SpriteRenderer.h"

using namespace sf;

class DrawableObject {
public:
	float x, y;

	~DrawableObject();
	DrawableObject();

	//void setRenderer(const SpriteRenderer &renderer);
	
	void setVisible(bool isVisible);
	bool isVisible();

	virtual Sprite &getSprite();
	void addToRenderer(int z);
	virtual void render(RenderWindow *window);

	static Sprite emptySprite;
	static unsigned short int drawableType;
	virtual unsigned short int getDrawableType();
protected:
	//SpriteRenderer renderer;
	bool visible;
};
#endif
