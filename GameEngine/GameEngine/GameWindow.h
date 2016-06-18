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
	View *getView();

	void updateView(Entity *entity);
	void setViewBounds(float width, float height);
	void setLetterboxView();

	void renderDO(DrawableObject *d);
	void render(std::pair<Vector2f, Vector2f> line);
	void render(Collidable *c);
	void render(SpriteRenderer *sr);
	void render(CollisionGrid *cg);
	void render(CollisionGrid *cg, short int gridPos[]);
	void render(CollisionGrid *cg, std::map<short int, unsigned short int> gridPos);
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
