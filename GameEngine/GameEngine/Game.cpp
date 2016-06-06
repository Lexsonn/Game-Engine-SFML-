#include "Game.h"
#include "Slime.h" // Eventually make a header with all Enemy types

#define _DEBUG_MODE true;

Game::~Game(void) {}
Game::Game(RenderWindow* rWindow) {
	eID = 0;
	oID = 0;
	debug = _DEBUG_MODE;

	cGrid = new CollisionGrid();
	rm_master = new ResourceManager();
	cGrid = new CollisionGrid(640, 640);
	window = new GameWindow(rWindow);
	player = new Player(200, 200, rm_master);
	controller = new InputController();
	
	addEntity(player);
	controller->addControllable(player);

	// Eventually, these will be moved into a map creator function, that will take a file/string
	// and create all background tiles, entities, and static collision boxes.
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

	addObject(new Collidable(370, 140, 40, 240));
	addObject(new Collidable(80, 290, 210, 20));
	addObject(new Collidable(140, 270, 60, 60));
}
//https://www.etsy.com/listing/211967784/bulbasaur-life-sized-plush
void Game::runLoop() {
	update();				// Update all entities
	window->start();		// Clear the window
	render();				// Draw everything
	window->end();			// Update the window
	rm_master->clearList(); // Clear list of drawable sprites
}

void Game::update() {
	for (auto entity : entityList) {
		entity.second->beginUpdate();							// Begin update for every entity
		cGrid->updateEntity(entity.second);						// Update Collision Grid position
	}
	controller->checkKeyState();								// Get Keyboard information
	for (auto entity : entityList) entity.second->update();		// update every entity.
	for (auto entity : entityList) entity.second->endUpdate();	// End updates for every entity.
}

void Game::render() {
	if (debug) 
		window->render(cGrid, player->gridPos);							// Render collision grid first (debug)
	window->render(rm_master);											// Render all animations and sprite effects
	if (debug) {
		for (auto object : objectList) window->render(object.second);	// Render every static collidable (debug)
		for (auto entity : entityList) window->renderDO(entity.second);	// Render all entity collision boxes (debug)
	}
}

void Game::addEntity(Entity *entity) {
	entityList.insert(std::pair<unsigned short int, Entity *>(eID, entity));
	entity->ID = eID++;
	cGrid->initEntity(entity);
	entity->entityList = cGrid->getEntityList();
	entity->objectList = cGrid->getObjectList();
}

void Game::addObject(Collidable *object) {
	objectList.insert(std::pair<unsigned short int, Collidable *>(oID++, object));
	cGrid->addObject(object);
}