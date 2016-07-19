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
	if (insideView(spr.getGlobalBounds(), view)) {
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

void SpriteRenderer::renderTiles(RenderWindow *window) const {
	for (const TileMap tmap : tileList) {
		FloatRect bound = FloatRect(tmap.getPosition(), Vector2f(SSX * TILESIZE_X, SSY * TILESIZE_Y));
		if (insideView(bound, view))
			window->draw(tmap);
	}
}

void SpriteRenderer::render(RenderWindow *window) const {
	std::multimap<int, const Sprite &>::iterator it = zOrderedSpriteList.begin();
	while (it != zOrderedSpriteList.end())
		window->draw(it++->second);
}
