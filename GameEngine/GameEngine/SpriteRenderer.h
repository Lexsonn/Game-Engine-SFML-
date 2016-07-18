#ifndef SPRITERENDERER_H
#define SPRITERENDERER_H

#include <SFML/Graphics.hpp>
#include "TileMap.h"
#include <map>

using namespace sf;

struct SpriteRenderer {
public:
	static std::vector<TileMap> tileList;

	void setView(View *view);

	void addTile(const TileMap &tmap);
	bool addSprite(int z, const Sprite &spr);
	void clearList();
	void clearAll();

	void render(RenderWindow *window) const;
	void renderTiles(RenderWindow *window) const;
private:
	View *view;
	static std::multimap<int, const Sprite &> zOrderedSpriteList;
	
	bool isInsideView(const Sprite &spr) const;
	bool isInsideView(const TileMap &tmap) const;
	
};
#endif
