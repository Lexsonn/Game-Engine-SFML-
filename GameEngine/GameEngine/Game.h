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
private:
	bool debug;
	unsigned short int eID, oID;

	ResourceManager *rm_master;
	InputController *controller;
	CollisionGrid *cGrid;
	GameWindow* window;
	Player *player;

	std::map<unsigned short int, Entity *> entityList;
	std::map<unsigned short int, Collidable *> objectList;

	void update();
	void render();

	void addEntity(Entity *entity);
	void addObject(Collidable *object);
};
#endif