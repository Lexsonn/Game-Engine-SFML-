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

	virtual Sprite &getSprite();
	void addToRenderer(int z);
	virtual void render(RenderWindow *window);

	static Sprite emptySprite;
	static unsigned short int drawableType;
	virtual unsigned short int getDrawableType();
protected:
	bool visible;
};
#endif
