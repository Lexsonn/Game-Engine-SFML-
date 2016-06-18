#ifndef SPRITERENDERER_H
#define SPRITERENDERER_H

#include <SFML/Graphics.hpp>
#include <map>

using namespace sf;

class SpriteRenderer {
public:
	~SpriteRenderer();
	SpriteRenderer();

	void addSprite(int z, Sprite &spr);
	void clearList();
	void render(RenderWindow *window);
private:
	std::multimap<int, Sprite &> zOrderedSpriteList;
};

#endif
