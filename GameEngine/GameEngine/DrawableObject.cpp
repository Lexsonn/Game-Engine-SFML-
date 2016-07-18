#include "DrawableObject.h"
#include "Game.h"

extern Game* game;

using namespace sf;

Sprite DrawableObject::emptySprite;
unsigned short int DrawableObject::drawableType = 0;

DrawableObject::~DrawableObject() {}
DrawableObject::DrawableObject() : visible(true) { }

bool DrawableObject::isVisible() {
	return visible;
}

void DrawableObject::setVisible(bool isVisible) {
	visible = isVisible;
}

unsigned short int DrawableObject::getDrawableType() {
	return drawableType;
}

Sprite &DrawableObject::getSprite() { return emptySprite; }

/*
 *	Send position and sprite information to be processed by the SpriteRenderer
 */
void DrawableObject::addToRenderer(int z) {
	game->addSprite(z, getSprite());
}

void DrawableObject::render(RenderWindow *window) {
	RectangleShape sh(Vector2f(16, 16));
	sh.setFillColor(Color::Black);
	sh.setOutlineColor(Color::Red);
	sh.setOutlineThickness(1.0f);
	sh.setPosition(x, y);
	window->draw(sh);

	RectangleShape dl(Vector2f(22.62f, 1));
	dl.setFillColor(Color::Red);
	dl.setOutlineColor(Color::Red);
	dl.setPosition(x, y);
	dl.rotate(45.0f);
	window->draw(dl);
}
