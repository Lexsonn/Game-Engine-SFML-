#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <SFML/Graphics.hpp>
#include "CollisionGrid.h"

using namespace sf;

class GameWindow {
public:
	GameWindow(RenderWindow *rWindow);
	~GameWindow(void);

	void start();
	void end();

	RenderWindow *getNative();

	void renderDO(DrawableObject *d);
	void render(std::pair<Vector2f, Vector2f> line);
	void render(Collidable *c);
	void render(ResourceManager *rm);
	void render(CollisionGrid *cg);
	void render(CollisionGrid *cg, short int gridPos[]);
private:
	RenderWindow *nativeRenderer;
};
#endif