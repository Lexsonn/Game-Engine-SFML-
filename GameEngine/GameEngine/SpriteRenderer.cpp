#include "SpriteRenderer.h"

SpriteRenderer::~SpriteRenderer() { }
SpriteRenderer::SpriteRenderer() { }

void SpriteRenderer::setView(View *view) {
	this->view = view;
}

/*
 *	Adds a sprite to the z-ordered sprite list (typically ordered by y alone, but for "flying" objects
 *	a z value can be added to the y to move it forward) and returns true if the sprite is inside the view.
 *	If the sprite is outside the current view, the sprite is not inserted, and the function returns false.
 */
void SpriteRenderer::addSprite(int z, const Sprite &spr) {
	if (isInsideView(spr))
		zOrderedSpriteList.insert(std::pair<int, const Sprite &>(z, spr));
}

void SpriteRenderer::clearList() {
	zOrderedSpriteList.clear();
}

/*
 *	Returns true if the bounding box of the passed sprite is within the bounds of the view.
 *	Returns false otherwise.
 */
bool SpriteRenderer::isInsideView(const Sprite &spr) {
	FloatRect bound = spr.getGlobalBounds();
	float vcX, vcY, vsX, vsY;

	vcX = view->getCenter().x;
	vcY = view->getCenter().y;
	vsX = view->getSize().x / 2;
	vsY = view->getSize().y / 2;

	return !((bound.left > vcX + vsX) || (bound.left + bound.width < vcX - vsX) || (bound.top > vcY + vsY) || (bound.top + bound.height < vcY - vsY));
}


void SpriteRenderer::render(RenderWindow *window) {
	std::multimap<int, const Sprite &>::iterator it = zOrderedSpriteList.begin();
	while (it != zOrderedSpriteList.end())
		window->draw(it++->second);
}
