#ifndef GAME_H
#define GAME_H

#include "InputController.h"
#include "GameWindow.h"
#include "Player.h"

using namespace sf;

class Game {
public:
	Game(RenderWindow *rWindow);
	~Game(void);

	void runLoop();
	void setLetterBoxView();
private:
	bool debug;
	unsigned short int eID, oID;
	int count;

	ResourceManager *rm_master;
	InputController *controller;
	CollisionGrid *cGrid;
	GameWindow* window;
	Player *player;

	std::map<unsigned short int, Entity *> entityList;		// Map for Entities
	std::map<unsigned short int, Collidable *> objectList;	// Map for static collidable objects
	std::vector<DrawableObject *> drawableList;				// Vector for all Drawable objects

	void update();
	void render();

	void addEntity(Entity *entity);
	void addObject(Collidable *object);
	void addDrawable(DrawableObject *drawable);
};
#endif