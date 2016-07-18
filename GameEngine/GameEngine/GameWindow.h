#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <SFML/Graphics.hpp>
#include "CollisionGrid.h"
#include "SpriteRenderer.h"
#include "TileMap.h"

using namespace sf;

class GameWindow {
public:
	~GameWindow(void);
	GameWindow(RenderWindow *rWindow, float width, float height, bool isLimited);

	void start();
	void end();
	RenderWindow *getNative();
	View *getView();

	void updateView(Entity *entity);
	void setViewBounds(float width, float height);
	void setLetterboxView();

	void renderDO(DrawableObject *d) const;
	void renderTiles(const SpriteRenderer &sr) const;
	void render(const std::pair<Vector2f, Vector2f> &line) const;
	void render(const FloatRect &rect) const;
	void render(Collidable *c) const;
	void render(const TileMap &tileMap) const;
	void render(const SpriteRenderer &sr) const;
	void render(const CollisionGrid &cg) const;
	void render(const CollisionGrid &cg, short int gridPos[]) const;
	void render(const CollisionGrid &cg, std::map<short int, unsigned short int> gridPos) const;
private:
	float rectW, rectH;
	bool limited;
	RenderWindow *nativeRenderer;
	View view;

	std::vector<DrawableObject *> *drawableList;

	void boundViewX(float centerX);
	void boundViewY(float centerY);
};
#endif
