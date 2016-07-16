#ifndef GAME_H
#define GAME_H

#include "InputController.h"
#include "CollisionManager.h"
#include "GameWindow.h"
#include "TileMap.h"
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
	void addDrawable(DrawableObject *drawObj);
	Entity *createEntity(std::string entityName, Vector2f pos);
	void deleteEntity(unsigned short int _ID);
private:
	const bool debug;
	const int *level;
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

	std::vector<TileMap> tileMap;				// Vector for Tilemap sections (move to sprite renderer)
	std::vector<DrawableObject *> drawableList;	// Vector for DrawableObjects that don't belong to other groups

	std::map<std::string, EntityType> entityMap;			// Map for creation of Entities by string
	std::map<unsigned short int, Entity *> entityList;		// Map for Entities
	std::map<unsigned short int, Collidable *> objectList;	// Map for static collidable objects

	void initEntityMap();
	void initManagers(RenderWindow *rWindow);
	void createWorld();
	void destroyWorld();
	void update();
	void updateDrawable();
	void render();

	void addEntity(Entity *entity);
	void addObject(Collidable *object);
	void deleteObject(unsigned short int _ID);
};
#endif
