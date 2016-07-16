#include "DrawableObject.h"

using namespace sf;

unsigned short int DrawableObject::drawableType = 0;

DrawableObject::~DrawableObject() {}
DrawableObject::DrawableObject() : visible(true) {}

void DrawableObject::setRenderer(SpriteRenderer *renderer) {
	this->renderer = renderer;
}

bool DrawableObject::isVisible() {
	return visible;
}

void DrawableObject::setVisible(bool isVisible) {
	visible = isVisible;
}

unsigned short int DrawableObject::getDrawableType() {
	return drawableType;
}

Sprite &DrawableObject::getSprite() { return Sprite(); }

void DrawableObject::addToRenderer(int z) {
	if (renderer == nullptr)
		return;
	renderer->addSprite(z, getSprite());
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
