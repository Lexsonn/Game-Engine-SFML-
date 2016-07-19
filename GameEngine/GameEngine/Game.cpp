#include "Game.h"
#include "Enemies.h"
#include <iostream>

#define _DEBUG_MODE 0x1
#define _CHECK_CONTROLLABLE_FLAG if (newEntity->getType() & 1) controller.addControllable(dynamic_cast<Controllable *>(newEntity));

int WWIDTH(800);
int WHEIGHT(800);
Game *game(nullptr);

Game::~Game() { }
Game::Game(RenderWindow* rWindow) : debug(_DEBUG_MODE) {
	game = this;
	eID = 0;
	oID = 0;
	
	const int l[] = { 25, 25, // load dis from txt file pls ty
		0,  4,  8,  4,  4,  4,  8,  12, 0,  4,  4,  4,  8,  0,  4,  8,  3,  3,  3,  3,  3,  3,  3,  3,  1,
		1,  5,  9,  5,  5,  5,  9,  12, 1,  5,  5,  5,  9,  1,  5,  9,  3,  3,  3,  3,  3,  3,  3,  3,  1,
		2,  6,  10, 5,  5,  5,  9,  12, 1,  5,  5,  5,  9,  1,  5,  9,  3,  3,  3,  3,  3,  3,  3,  3,  1,
		1,  5,  5,  5,  5,  5,  9,  12, 1,  5,  5,  5,  9,  1,  5,  9,  3,  3,  3,  3,  3,  3,  3,  3,  1,
		1,  5,  5,  5,  5,  6,  10, 12, 2,  6,  6,  6,  10, 2,  5,  9,  3,  3,  3,  3,  3,  3,  3,  3,  1,
		1,  5,  5,  5,  9,  12, 12, 12, 13, 13, 13, 13, 13, 14, 2,  10, 3,  3,  3,  3,  3,  3,  3,  3,  1,
		2,  6,  6,  6,  10, 12, 12, 13, 13, 13, 13, 14, 14, 14, 14, 14, 3,  3,  3,  3,  3,  3,  3,  3,  1,
		12, 12, 12, 12, 12, 12, 12, 13, 13, 13, 13, 14, 14, 14, 14, 14, 3,  3,  3,  3,  3,  3,  3,  3,  1,
		12, 12, 12, 12, 12, 12, 12, 0,  4,  4,  4,  8,  14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 1,
		12, 12, 12, 12, 12, 12, 12, 1,  5,  5,  5,  9,  14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 1,
		12, 12, 12, 12, 12, 12, 12, 1,  5,  5,  5,  5,  8,  13, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 1,
		12, 12, 12, 12, 12, 12, 12, 1,  5,  5,  5,  5,  9,  13, 13, 14, 14, 14, 14, 14, 14, 14, 14, 14, 1,
		12, 12, 12, 12, 12, 12, 12, 1,  5,  5,  5,  5,  9,  13, 13, 13, 14, 14, 14, 14, 14, 14, 14, 14, 1,
		12, 12, 12, 12, 12, 12, 12, 2,  6,  6,  6,  6,  10, 13, 13, 13, 14, 14, 14, 14, 14, 14, 14, 14, 1,
		12, 12, 12, 12, 12, 12, 12, 12, 13, 13, 13, 13, 13, 13, 13, 13, 14, 14, 14, 14, 14, 14, 14, 14, 1,
		12, 12, 12, 12, 12, 12, 12, 12, 13, 13, 13, 13, 13, 13, 13, 13, 14, 14, 14, 14, 14, 14, 14, 14, 1,
		4,  4,  4,  4,  4,  4,  8,  13, 13, 13, 13, 13, 13, 13, 13, 14, 14, 14, 14, 14, 14, 14, 14, 0,  8,
		5,  5,  5,  5,  5,  5,  5,  4,  4,  8,  13, 13, 13, 13, 14, 14, 14, 14, 14, 14, 14, 14, 14, 1,  9,
		5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  4,  4,  4,  4,  4,  4,  4,  4,  4,  8,  14, 14, 14, 1,  9,
		5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  4,  4,  4,  1,  9,
		5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  1,  9,
		5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  1,  9,
		5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  1,  9,
		5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  1,  9,
		6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  2,  10
	};

	level = l;

	WWIDTH = level[0] * TILESIZE_X;
	WHEIGHT = level[1] * TILESIZE_Y;

	initEntityMap();
	initManagers(rWindow);
	createWorld();
	/* QUICK CHECKS FOR CLASS SIZES (empty lists)
	std::cout << "ResourceManager : " << sizeof(ResourceManager) << "\tCollisionGrid: " << sizeof(CollisionGrid) << "\n";
	std::cout << "GameWindow : " << sizeof(GameWindow) << "\tInputController: " << sizeof(InputController) << "\n";
	std::cout << "AttackManager : " << sizeof(AttackManager) << "\tAttack: " << sizeof(Attack) << "\n";
	std::cout << "Player : " << sizeof(Player) << "\t\tEntity: " << sizeof(Entity) << "\n";
	std::cout << "Game : " << sizeof(Game) << "\t\tTileMap " << sizeof(TileMap) << "\n";
	//*/
}

void Game::initEntityMap() {
	entityMap["Entity"] = ENTITY;
	entityMap["Player"] = PLAYER;
	entityMap["Slime"] = SLIME;
	entityMap["BabySlime"] = BABYSLIME;
}

/*
 *	Initialize all necessary Game world objects, and set up their relationships.
 */
void Game::initManagers(RenderWindow *rWindow) {
	rm_master = new ResourceManager();
	window = new GameWindow(rWindow, 640.f, 480.f, true);
	player = new Player(200, 200, rm_master);
	// Setup manager relationships
	spr_renderer.setView(window->getView());
	controller.addControllable(player);
	cMaster.initialize(&entityList);
}

/*
 *	Eventually, this will load a world from a file. maybe?
 */
void Game::createWorld() {
	// All dis gon b loaded in txt file <3 <3 <3
	for (int i = 0; i <= level[0] / SSX; i++) {
		for (int j = 0; j <= level[1] / SSY; j++) {
			Vector2u offset = Vector2u(i, j);
			spr_renderer.addTile(TileMap("Tilesets/tileset1.png", Vector2u(TILESIZE_X, TILESIZE_Y), level, offset, rm_master));
		}
	}

	cGrid.build(); // build after setting level size.

	addEntity(player);
	addEntity(new Slime(100, 100, rm_master));
	addEntity(new Slime(50, 100, rm_master));
	addEntity(new Slime(150, 100, rm_master));
	addEntity(new Slime(200, 100, rm_master));
	addEntity(new Slime(250, 100, rm_master));
	addEntity(new Slime(300, 100, rm_master));
	addEntity(new Slime(140, 140, rm_master));
	addEntity(new Slime(40, 140, rm_master));
	addEntity(new Slime(250, 140, rm_master));
	addEntity(new Slime(300, 140, rm_master));
	addEntity(new Slime(190, 250, rm_master));
	addEntity(new Slime(340, 340, rm_master));

	addEntity(new BabySlime(300, 160, rm_master));
	addEntity(new BabySlime(300, 170, rm_master));
	addEntity(new BabySlime(300, 180, rm_master));
	addEntity(new BabySlime(300, 190, rm_master));
	addEntity(new BabySlime(320, 160, rm_master));
	addEntity(new BabySlime(320, 170, rm_master));
	addEntity(new BabySlime(320, 180, rm_master));
	addEntity(new BabySlime(320, 190, rm_master));
	addEntity(new BabySlime(340, 160, rm_master));
	addEntity(new BabySlime(340, 170, rm_master));
	addEntity(new BabySlime(340, 180, rm_master));
	addEntity(new BabySlime(340, 190, rm_master));

	addObject(new Collidable(370, 140, 40, 240));
	addObject(new Collidable(80, 290, 210, 20));
	addObject(new Collidable(140, 270, 60, 60));
}

/*
 *	Destroy all objects related to the current level.
 */
void Game::destroyWorld() {
	WWIDTH = 160;
	WHEIGHT = 160;
	cGrid.clearLists();
	do_master.clearDrawableList();
	spr_renderer.clearAll();
	player = nullptr;
	while (!objectList.empty()) {
		std::map<unsigned short int, Collidable *>::iterator it = objectList.begin();
		delete it->second;
		objectList.erase(it);
	}
	while (!entityList.empty()) {
		std::map<unsigned short int, Entity *>::iterator it = entityList.begin();
		delete it->second;
		entityList.erase(it);
	}
	at_master.clearAttacks();
}

/*
 *	Create an entity from a passed in string, and position.
 */
Entity *Game::createEntity(std::string entityName, Vector2f pos) {
	Entity *newEntity = nullptr;
	EntityType type = UNKNOWN_e;
	std::map<std::string, EntityType>::iterator it = entityMap.find(entityName);
	if (it != entityMap.end())
		type = it->second;
	switch (type) {
	case PLAYER: newEntity = new Player(pos.x, pos.y, rm_master); break;
	case SLIME: newEntity = new Slime(pos.x, pos.y, rm_master); break;
	case BABYSLIME: newEntity = new BabySlime(pos.x, pos.y, rm_master); break;
	default: std::cout << "Unable to create entity: " + entityName + "\n";
	}
	if (newEntity != nullptr) {
		_CHECK_CONTROLLABLE_FLAG
		addEntity(newEntity);
		return newEntity;
	}
	return nullptr;
}

//https://www.etsy.com/listing/211967784/bulbasaur-life-sized-plush
void Game::runLoop() {
	update();					// Update all entities
	window->start();			// Clear the window
	render();					// Draw everything
	window->end();				// Update the window
	spr_renderer.clearList();	// Clear list of drawable sprites
}

/*
 *	Called when the window has been resized. Sets the View to letterbox itself accordingly.
 */
void Game::setLetterBoxView() {
	if (window == nullptr)
		return;
	window->setLetterboxView();
}

void Game::addSprite(int z, const Sprite &spr) {
	spr_renderer.addSprite(z, spr);
}

/*
 *	Add DrawableObject to the drawable list, and set its renderer.
 */
void Game::addDrawable(DrawableObject *drawObj) {
	if (drawObj == nullptr)
		return;
	do_master.addDrawableObject(drawObj);
}

/*
 *	The game update step. All game logic goes in here.
 */
void Game::update() {
	/* TEST DESTROY WORLD (and rebuild grid of size 1 and add a player)
	if (count++ == 120) {
		destroyWorld();
		cGrid->build();
		player = dynamic_cast<Player *>(createEntity("Player", Vector2f(100.f, 100.f)));
	}
	//*/
	std::vector<int> toDelete;
	for (auto entity : entityList) entity.second->beginUpdate();	 // Begin update for every entity
	controller.update();											 // Update keyboard information
	for (auto entity : entityList) {
		entity.second->update();									 // Update every entity
		if (entity.second->isDead) toDelete.push_back(entity.first); // Mark entity for deletion if dead
		else cGrid.updateEntity(entity.second);						 // Update CollisionGrid position if not dead
	}
	for (int i : toDelete) deleteEntity(i);							 // Delete all Entities that have been marked for deletion
	at_master.updateAttacks();										 // Update all Attacks
	cMaster.update();												 // Resolve collisions for every entity
	window->updateView(player);										 // Update view to follow player
	for (auto entity : entityList) entity.second->endUpdate();		 // End updates for every entity
	do_master.update();												 // Update all Drawable Objects, deleting if necessary
}

/*
 *	Render all Game objects that require rendering.
 */
void Game::render() {
	window->renderTiles(spr_renderer);									// Render all tile sections currently in view
	if (debug) {
		window->render(cGrid, player->gridPos);							// Render collision grid positions of player
		window->render(cGrid);											// Render collision grid lines
	}
	window->render(spr_renderer);										// Render all animations and sprite effects
	if (debug) {
		for (auto object : objectList) window->render(object.second);	// Render every static collidable
		for (auto entity : entityList) window->renderDO(entity.second);	// Render all entity collision boxes
		for (auto att : AttackManager::attackList)						// Render all attack collision lines
			for (auto line : att.second->attackLines) 
				window->render(line);
	}
	/* DRAW RECTANGLE FOR CHECKING IF RENDERING OBJECTS OUTSIDE VIEW
	Vector2f lt, wh;
	lt = window->getView()->getCenter() - window->getView()->getSize()/4.f;
	wh = window->getView()->getSize()/2.f;
	window->render(FloatRect(lt, wh));
	//*/
}

/*
 *	Perform all necessary functions to have a newly created Entity interact in the game world.
 */
void Game::addEntity(Entity *entity) {
	entityList.insert(std::pair<unsigned short int, Entity *>(eID, entity));
	entity->ID = eID++;
}

/*
 *	Delete an Entity from all lists related to the Entity.
 */
void Game::deleteEntity(unsigned short int _ID) {
	std::map<unsigned short int, Entity *>::iterator it = entityList.find(_ID);
	if (it == entityList.end())
		return;
	cGrid.deleteEntity(it->second);
	delete it->second;
	entityList.erase(it);
}

/*
 *	Add a static Collidable to the game world, and the collision grid.
 */
void Game::addObject(Collidable *object) {
	object->ID = oID;
	objectList.insert(std::pair<unsigned short int, Collidable *>(oID++, object));
	cGrid.addObject(object);
}

/*
*	Delete a static Collidable from all lists related to the Collidable.
*/
void Game::deleteObject(unsigned short int _ID) {
	std::map<unsigned short int, Collidable *>::iterator it = objectList.find(_ID);
	if (it == objectList.end())
		return;
	cGrid.deleteObject(it->second);
	delete it->second;
	objectList.erase(it);
}
