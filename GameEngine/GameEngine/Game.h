#ifndef GAME_H
#define GAME_H

#include "InputController.h"
#include "CollisionManager.h"
#include "GameWindow.h"
#include "Player.h"

using namespace sf;

enum EntityType {
	UNKNOWN_e = -1
	, ENTITY = 0
	, PLAYER
	, SLIME
	, BABYSLIME
};

class Game {
public:
	~Game();
	Game(RenderWindow *rWindow);

	void runLoop();
	void setLetterBoxView();
	void createEntity(std::string entityName, Vector2f pos);
private:
	bool debug;
	unsigned short int eID, oID;
	int count = 0;

	ResourceManager *rm_master;
	SpriteRenderer *spr_renderer;
	InputController *controller;
	CollisionGrid *cGrid;
	CollisionManager *cMaster;
	AttackManager *at_master;
	GameWindow* window;
	Player *player;

	std::map<std::string, EntityType> entityMap;			// Map for creation of Entities by string
	std::map<unsigned short int, Entity *> entityList;		// Map for Entities
	std::map<unsigned short int, Collidable *> objectList;	// Map for static collidable objects

	void initEntityMap();
	void initManagers(RenderWindow *rWindow);
	void createWorld();
	void update();
	void render();

	Controllable *addControllable(Controllable *c);
	void addEntity(Entity *entity);
	void deleteEntity(unsigned short int _ID);
	void addObject(Collidable *object);
	void deleteObject(unsigned short int _ID);
};
#endif
