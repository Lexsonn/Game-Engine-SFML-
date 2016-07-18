#include "SpriteRenderer.h"

// A list of TileMaps
std::vector<TileMap> SpriteRenderer::tileList;
// A list of sprites ordered by their "z" value, to create the illusion of depth
std::multimap<int, const Sprite &> SpriteRenderer::zOrderedSpriteList;

void SpriteRenderer::setView(View *view) {
	this->view = view;
}

void SpriteRenderer::addTile(const TileMap &tmap) {
	tileList.push_back(tmap);
}

/*
 *	Adds a sprite to the z-ordered sprite list (typically ordered by y alone, but for "flying" objects
 *	a z value can be added to the y to move it forward) and returns true if the sprite is inside the view.
 *	If the sprite is outside the current view, the sprite is not inserted, and the function returns false.
 */
bool SpriteRenderer::addSprite(int z, const Sprite &spr) {
	if (isInsideView(spr)) {
		zOrderedSpriteList.insert(std::pair<int, const Sprite &>(z, spr));
		return true;
	}
	return false;
}

void SpriteRenderer::clearList() {
	zOrderedSpriteList.clear();
}

void SpriteRenderer::clearAll() {
	zOrderedSpriteList.clear();
	tileList.clear();
}

/*
 *	Returns true if the bounding box of the passed sprite is within the bounds of the view.
 *	Returns false otherwise.
 */
bool SpriteRenderer::isInsideView(const Sprite &spr) const {
	if (view == nullptr)
		return false;
	FloatRect bound = spr.getGlobalBounds();
	float vcX, vcY, vsX, vsY;

	vcX = view->getCenter().x;
	vcY = view->getCenter().y;
	vsX = view->getSize().x / 2;
	vsY = view->getSize().y / 2;
	
	return !((bound.left > vcX + vsX) || (bound.left + bound.width < vcX - vsX) || (bound.top > vcY + vsY) || (bound.top + bound.height < vcY - vsY));
}

bool SpriteRenderer::isInsideView(const TileMap &tmap) const {
	float left, top, right, bottom;
	left = tmap.getPosition().x;
	top = tmap.getPosition().y;
	right = left + SSX * TILESIZE_X;
	bottom = top + SSY * TILESIZE_Y;
	
	float vcX, vcY, vsX, vsY;
	vcX = view->getCenter().x;
	vcY = view->getCenter().y;
	vsX = view->getSize().x / 2;
	vsY = view->getSize().y / 2;

	return !((left > vcX + vsX) || (right < vcX - vsX) || (top > vcY + vsY) || (bottom < vcY - vsY));
}

void SpriteRenderer::renderTiles(RenderWindow *window) const {
	for (const TileMap tmap : tileList) {
		if (isInsideView(tmap))
			window->draw(tmap);
	}
}

void SpriteRenderer::render(RenderWindow *window) const {
	std::multimap<int, const Sprite &>::iterator it = zOrderedSpriteList.begin();
	while (it != zOrderedSpriteList.end())
		window->draw(it++->second);
}
