#include "SpriteRenderer.h"

SpriteRenderer::~SpriteRenderer() { }
SpriteRenderer::SpriteRenderer() { }

void SpriteRenderer::addSprite(int z, const Sprite &spr) {
	zOrderedSpriteList.insert(std::pair<int, const Sprite &>(z, spr));
}

void SpriteRenderer::clearList() {
	zOrderedSpriteList.clear();
}

//Sprite &SpriteRenderer::getSprite() { }

void SpriteRenderer::render(RenderWindow *window) {
	std::multimap<int, const Sprite &>::iterator it = zOrderedSpriteList.begin();
	while (it != zOrderedSpriteList.end())
		window->draw(it++->second);
}
