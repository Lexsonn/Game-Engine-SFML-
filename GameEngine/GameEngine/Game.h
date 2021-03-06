#ifndef GAME_H
#define GAME_H

#include "DrawableObjectManager.h"
#include "InputController.h"
#include "CollisionManager.h"
#include "SpriteRenderer.h"
#include "GameWindow.h"
#include "Player.h"

using namespace sf;

enum EntityType {
	ENTITY = 0
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
	void addSprite(int z, const Sprite &spr);
	Entity *createEntity(std::string entityName, Vector2f pos);
	Entity *getEntityById(unsigned short int &id);
	void deleteEntity(unsigned short int _ID);
private:
	const bool debug;
	const int *level;
	unsigned short int eID, oID;
	mutable int count = 0;

	ResourceManager *rm_master;
	GameWindow *window;
	Player *player;
	DrawableObjectManager do_master;
	SpriteRenderer spr_renderer;
	InputController controller;
	CollisionGrid cGrid;
	CollisionManager cMaster;
	AttackManager at_master;

	std::map<std::string, EntityType> entityMap;			// Map for creation of Entities by string
	std::map<unsigned short int, Entity *> entityList;		// Map for Entities
	std::map<unsigned short int, Collidable *> objectList;	// Map for static collidable objects
	
	void initEntityMap();
	void initManagers(RenderWindow *rWindow);
	void createWorld(const std::string &filename, const int &levelnum);
	void destroyWorld();
	void update();
	void render();

	void addEntity(Entity *entity);
	void addObject(Collidable *object);
	void deleteObject(unsigned short int _ID);
};
#endif
