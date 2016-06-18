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

	ResourceManager *rm_master;
	SpriteRenderer *spr_renderer;
	InputController *controller;
	CollisionGrid *cGrid;
	AttackManager *at_master;
	GameWindow* window;
	Player *player;
	Attack *att;

	std::map<unsigned short int, Entity *> entityList;		// Map for Entities
	std::map<unsigned short int, Collidable *> objectList;	// Map for static collidable objects
	//std::map<unsigned short int, Attack *> attackList;		// Map for attacks

	void initVars(RenderWindow *rWindow);
	void createWorld();
	void update();
	void render();

	void addEntity(Entity *entity);
	void deleteEntity(unsigned short int _ID);
	void addObject(Collidable *object);
};
#endif
