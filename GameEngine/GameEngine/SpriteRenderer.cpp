#include "SpriteRenderer.h"

SpriteRenderer::~SpriteRenderer() { }
SpriteRenderer::SpriteRenderer() { }

void SpriteRenderer::addSprite(int z, Sprite &spr) {
	zOrderedSpriteList.insert(std::pair<int, Sprite &>(z, spr));
}

void SpriteRenderer::clearList() {
	zOrderedSpriteList.clear();
}

void SpriteRenderer::render(RenderWindow *window) {
	std::multimap<int, Sprite &>::iterator it = zOrderedSpriteList.begin();
	while (it != zOrderedSpriteList.end())
		window->draw(it++->second);
}
