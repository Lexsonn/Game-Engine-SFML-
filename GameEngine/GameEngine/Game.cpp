#include "Game.h"
#include "Enemies.h"
#include <iostream>
#include <fstream>

#define _DEBUG_MODE 0x1
#define _CHECK_PLAYER_FLAG if (newEntity->getType() & 0X80000000) player = dynamic_cast<Player *>(newEntity);
#define _CHECK_CONTROLLABLE_FLAG if (newEntity->getType() & 0X00000001) controller.addControllable(dynamic_cast<Controllable *>(newEntity));

int WWIDTH(160);
int WHEIGHT(160);
Game *game(nullptr);
int globalSeed = int(time(NULL));

Game::~Game() { }
Game::Game(RenderWindow* rWindow) : debug(_DEBUG_MODE) {
	game = this;
	eID = 0;
	oID = 0;

	initEntityMap();
	initManagers(rWindow);
	createWorld("Resources/maps/map.vhmap", 2);
	/* QUICK CHECKS FOR CLASS SIZES (empty lists)
	std::cout << "ResourceManager : " << sizeof(ResourceManager) << "\tCollisionGrid: " << sizeof(CollisionGrid) << "\n";
	std::cout << "GameWindow : " << sizeof(GameWindow) << "\tInputController: " << sizeof(InputController) << "\n";
	std::cout << "AttackManager : " << sizeof(AttackManager) << "\tAttack: " << sizeof(Attack) << "\n";
	std::cout << "Player : " << sizeof(Player) << "\t\tEntity: " << sizeof(Entity) << "\n";
	std::cout << "Game : " << sizeof(Game) << "\t\tTileMap " << sizeof(TileMap) << "\n";
	std::cout << "UID : " << sizeof(std::uniform_int_distribution<int>) << "\t\tRandom device : " << sizeof(std::random_device) << "\n";
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
	// Setup manager relationships
	spr_renderer.setView(window->getView());
	cMaster.initialize(&entityList);
}

/*
 *	Load map by file and position in file.
 */
void Game::createWorld(const std::string &filename, const int &levelnum) {
	std::fstream mapfile(filename, std::ios::binary | std::ios::in);
	if (mapfile.is_open()) {
		std::cout << "Reading from " << filename << "... level=" << levelnum << "\n";
		
		int mapnum, tileset;
		std::vector<long> mapsize;
		mapfile.read((char*)&mapnum, sizeof(int));
		mapsize.resize(mapnum);
		mapfile.read((char*)mapsize.data(), mapnum * sizeof(long));

		if (levelnum > 0) mapfile.seekg(mapsize.at(std::max(0, levelnum - 1)), std::ios::beg);

		std::vector<int> level;
		int size;
		// Read level information first and foremost
		mapfile.read((char*)&size, sizeof(int));
		level.resize(size);
		mapfile.read((char*)level.data(), size * sizeof(int));
		mapfile.read((char*)&tileset, sizeof(int));

		// Resize world and set cGrid to proper size
		WWIDTH = level.at(0) * TILESIZE_X;
		WHEIGHT = level.at(1) * TILESIZE_Y;
		cGrid.build();

		window->updateView(Vector2f(WWIDTH / 2.f, WHEIGHT / 2.f));

		// Create tiles from level info
		for (int i = 0; i <= level.at(0) / SSX; i++)
			for (int j = 0; j <= level.at(1) / SSY; j++)
				spr_renderer.addTile(TileMap("Tilesets/tileset1.png", Vector2u(TILESIZE_X, TILESIZE_Y), (int*)&level[0], Vector2u(i, j), rm_master));

		int toDo;
		while ((mapfile.tellg() < mapsize.at(levelnum)) && !mapfile.eof()) {
			int l, t, w, h;
			float x, y; //boundx, boundy, bsizex, bsizey;
			std::string name;
			int slen;
			mapfile.read((char*)&toDo, sizeof(int));
			switch (toDo) {
			//case 3: // Create AI entity with bounds
			case 2:
				mapfile.read((char*)&slen, sizeof(slen));
				name.resize(slen);
				mapfile.read((char*)&name[0], slen);
				mapfile.read((char*)&x, sizeof(float));
				mapfile.read((char*)&y, sizeof(float));
				createEntity(name, Vector2f(x, y));
				break;
			case 1:
				mapfile.read((char*)&l, sizeof(int));
				mapfile.read((char*)&t, sizeof(int));
				mapfile.read((char*)&w, sizeof(int));
				mapfile.read((char*)&h, sizeof(int));
				std::cout << "Creating collidable pos=(" << l << ", " << t << ") size=(" << w << ", " << h << ")\n";
				addObject(new Collidable(l, t, w, h));
				break;
			default: std::cout << "invalid toDo.";
			}
		}
		mapfile.close();
		std::cout << "Finished reading map file.\n";
	} else std::cout << "Error reading from " << filename << "\n";
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
	std::cout << "Adding " << entityName << "... ";
	Entity *newEntity = nullptr;
	EntityType type = ENTITY;
	std::map<std::string, EntityType>::iterator it = entityMap.find(entityName);
	if (it != entityMap.end())
		type = it->second;
	switch (type) {
	case PLAYER: newEntity = new Player(pos.x, pos.y, rm_master); break;
	case SLIME: newEntity = new Slime(pos.x, pos.y, rm_master); break;
	case BABYSLIME: newEntity = new BabySlime(pos.x, pos.y, rm_master); break;
	default: std::cout << "Unable to create entity: " << entityName << "\n"; return nullptr;
	}
	_CHECK_PLAYER_FLAG
	_CHECK_CONTROLLABLE_FLAG
	addEntity(newEntity);
	return newEntity;
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
	if (entity == nullptr)
		return;
	entityList.insert(std::pair<unsigned short int, Entity *>(eID, entity));
	entity->ID = eID++;
	std::cout << "initialized with ID=" << eID - 1 << "\n";
}

Entity *Game::getEntityById(unsigned short int &id) {
	std::map<unsigned short int, Entity *>::iterator it = entityList.find(id);
	if (it != entityList.end())
		return it->second;
	return nullptr;
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
