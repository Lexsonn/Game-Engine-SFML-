#include "Game.h"
#include "Slime.h" // Eventually make a header with all Enemy types

#define _DEBUG_MODE true

int WWIDTH(640);
int WHEIGHT(480);

Game::~Game(void) {}
Game::Game(RenderWindow* rWindow) {
	eID = 0;
	oID = 0;
	debug = _DEBUG_MODE;

	WWIDTH = 800;
	WHEIGHT = 800;

	rm_master = new ResourceManager();
	cGrid = new CollisionGrid();
	window = new GameWindow(rWindow, 640.f, 480.f, true);
	player = new Player(200, 200, rm_master);
	controller = new InputController();
	std::vector<std::pair<Vector2f, Vector2f>> lines;
	lines.push_back(std::pair<Vector2f, Vector2f>(Vector2f(100, 210), Vector2f(200, 340)));
	lines.push_back(std::pair<Vector2f, Vector2f>(Vector2f(300, 210), Vector2f(200, 340)));

	att = new Attack(0, 0, 1, 20, 30, lines);

	rm_master->setView(window->getView());
	addEntity(player);
	controller->addControllable(player);
	/* QUICK CHECKS FOR CLASS SIZES (empty lists)
	std::cout << "ResourceManager : " << sizeof(ResourceManager) << "\nCollisionGrid: " << sizeof(CollisionGrid) << "\n";
	std::cout << "GameWindow : " << sizeof(GameWindow) << "\nInputController: " << sizeof(InputController) << "\n";
	std::cout << "Player : " << sizeof(Player) << "\nEntity: " << sizeof(Entity) << "\n";
	//*/
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

void Game::setLetterBoxView() {
	if (window == nullptr)
		return;
	window->setLetterboxView();
}

void Game::update() {
	for (auto entity : entityList) entity.second->beginUpdate();// Begin update for every entity
	controller->checkKeyState();								// Get Keyboard information
	for (auto entity : entityList) {
		entity.second->update();								// Update every entity.
		cGrid->updateEntity(entity.second);						// Update CollisionGrid position
	}
	window->updateView(player);									// Update view to follow player.
	for (auto entity : entityList) entity.second->endUpdate();	// End updates for every entity.
}

void Game::render() {
	if (debug) {
		window->render(cGrid, player->gridPos);							// Render collision grid first (debug)
		window->render(cGrid, att->gridPos);
	}
	window->render(rm_master);											// Render all animations and sprite effects
	if (debug) {
		for (auto object : objectList) window->render(object.second);	// Render every static collidable (debug)
		for (auto entity : entityList) window->renderDO(entity.second);	// Render all entity collision boxes (debug)

		for (auto line : att->attackLines) window->render(line);
		/* FOR LINE INTERSECTION TESTS
		std::pair<Vector2f, Vector2f> l; l.first = Vector2f(100.0f, 20.f); l.second = Vector2f(100.0f, 90.f);
		std::pair<Vector2f, Vector2f> l2; l2.first = Vector2f(130.0f, 20.f); l2.second = Vector2f(170.0f, 90.f);
		std::pair<Vector2f, Vector2f> l3; l3.first = Vector2f(200.0f, 90.f); l3.second = Vector2f(250.0f, 20.f);
		std::pair<Vector2f, Vector2f> l4; l4.first = Vector2f(300.0f, 90.f); l4.second = Vector2f(350.0f, 90.f);
		window->render(l);
		window->render(l2);
		window->render(l3);
		window->render(l4);
		//*/
	}
}

/*
 *	Perform all necessary functions to have a newly created Entity interact in the game world.
 */
void Game::addEntity(Entity *entity) {
	entityList.insert(std::pair<unsigned short int, Entity *>(eID, entity));
	entity->ID = eID++;
	cGrid->initEntity(entity);
	entity->entityList = cGrid->getEntityList();
	entity->objectList = cGrid->getObjectList();
}

void Game::deleteEntity(unsigned short int _ID) {
	std::map<unsigned short int, Entity *>::iterator it = entityList.find(_ID);
	if (it == entityList.end())
		return;
	cGrid->deleteEntity(it->second);
	delete it->second;
	entityList.erase(it);
}

void Game::addObject(Collidable *object) {
	objectList.insert(std::pair<unsigned short int, Collidable *>(oID++, object));
	cGrid->addObject(object);
}