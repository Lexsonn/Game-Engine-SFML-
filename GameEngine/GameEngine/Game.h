#ifndef GAME_H
#define GAME_H

#include "DrawableObjectManager.h"
#include "InputController.h"
#include "CollisionManager.h"
#include "SpriteRenderer.h"
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
	void addSprite(int z, const Sprite &spr);
	Entity *createEntity(std::string entityName, Vector2f pos);
	void deleteEntity(unsigned short int _ID);
private:
	const bool debug;
	const int *level;
	unsigned short int eID, oID;
	mutable int count = 0; // fuck you const I do what I want

	ResourceManager *rm_master;
	GameWindow *window;
	Player *player;
	DrawableObjectManager do_master;
	SpriteRenderer spr_renderer;
	InputController controller;
	CollisionGrid cGrid;
	CollisionManager cMaster;
	AttackManager at_master;
	
	//std::vector<TileMap> tileMap;				// Vector for Tilemap sections (move to sprite renderer)

	std::map<std::string, EntityType> entityMap;			// Map for creation of Entities by string
	std::map<unsigned short int, Entity *> entityList;		// Map for Entities
	std::map<unsigned short int, Collidable *> objectList;	// Map for static collidable objects
	std::map<unsigned short int, Attack *> *attList;
	void initEntityMap();
	void initManagers(RenderWindow *rWindow);
	void createWorld();
	void destroyWorld();
	void update();
	void render();

	void addEntity(Entity *entity);
	void addObject(Collidable *object);
	void deleteObject(unsigned short int _ID);
};
#endif
