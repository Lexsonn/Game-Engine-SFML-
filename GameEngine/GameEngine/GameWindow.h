#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <SFML/Graphics.hpp>
#include "CollisionGrid.h"

using namespace sf;

class GameWindow {
public:
	~GameWindow(void);
	GameWindow(RenderWindow *rWindow, float width, float height, bool isLimited);

	void start();
	void end();
	RenderWindow *getNative();

	void updateView(Entity *entity);
	void setViewBounds(float width, float height);

	void renderDO(DrawableObject *d);
	void render(std::pair<Vector2f, Vector2f> line);
	void render(Collidable *c);
	void render(ResourceManager *rm);
	void render(CollisionGrid *cg);
	void render(CollisionGrid *cg, short int gridPos[]);
private:
	float wWidth, wHeight, rectW, rectH;
	bool limited;
	RenderWindow *nativeRenderer;
	View view;

	void boundViewX(float centerX);
	void boundViewY(float centerY);
};
#endif