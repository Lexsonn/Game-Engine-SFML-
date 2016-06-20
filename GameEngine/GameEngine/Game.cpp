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

	initVars(rWindow);
	createWorld();

	std::vector<std::pair<Vector2f, Vector2f>> lines;
	lines.push_back(std::pair<Vector2f, Vector2f>(Vector2f(130, 250), Vector2f(420, 110)));
	lines.push_back(std::pair<Vector2f, Vector2f>(Vector2f(330, 150), Vector2f(330, 410)));
	Animation *anim = new Animation(rm_master->getTexture("playerAtt1.png"), 0, 0, 50, 50, 5, 0.4f, true);
	std::cout << "Adding... ";
	//Attack * att = new Attack(0, 0, 1, 60, 23, lines);
	at_master->addAttack(1, 1, 320, 23, lines, anim);
	at_master->attackList.at(0)->setPosition(210, 190);
	at_master->attackList.at(0)->setForce(2, 2);
	/* QUICK CHECKS FOR CLASS SIZES (empty lists)
	std::cout << "ResourceManager : " << sizeof(ResourceManager) << "\nCollisionGrid: " << sizeof(CollisionGrid) << "\n";
	std::cout << "GameWindow : " << sizeof(GameWindow) << "\nInputController: " << sizeof(InputController) << "\n";
	std::cout << "Player : " << sizeof(Player) << "\nEntity: " << sizeof(Entity) << "\n";
	//*/
	// Eventually, these will be moved into a map creator function, that will take a file/string
	// and create all background tiles, entities, and static collision boxes.
}

void Game::initVars(RenderWindow *rWindow) {
	rm_master = new ResourceManager();
	spr_renderer = new SpriteRenderer();
	at_master = new AttackManager();
	cGrid = new CollisionGrid();
	cMaster = new CollisionManager();
	window = new GameWindow(rWindow, 640.f, 480.f, false);
	player = new Player(200, 200, rm_master);
	controller = new InputController();
	
	at_master->setResourceManager(rm_master);
	rm_master->setSpriteRenderer(spr_renderer);
	rm_master->setView(window->getView());
	controller->addControllable(player);
	player->setEntityList(cGrid->getEntityList());
	// CollisionManager setup
	cMaster->setAttackManager(at_master);
	cMaster->setEntityList(&entityList);
	cMaster->setObjectList(&objectList);
	cMaster->setEntityPosList(cGrid->getEntityList());
	cMaster->setObjectPosList(cGrid->getObjectList());
}

void Game::createWorld() {
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

	addObject(new Collidable(370, 140, 40, 240));
	addObject(new Collidable(80, 290, 210, 20));
	addObject(new Collidable(140, 270, 60, 60));
}

//https://www.etsy.com/listing/211967784/bulbasaur-life-sized-plush
void Game::runLoop() {
	update();					// Update all entities
	window->start();			// Clear the window
	render();					// Draw everything
	window->end();				// Update the window
	spr_renderer->clearList();	// Clear list of drawable sprites
}

void Game::setLetterBoxView() {
	if (window == nullptr)
		return;
	window->setLetterboxView();
}

void Game::update() {
	for (auto entity : entityList) entity.second->beginUpdate();// Begin update for every entity
	controller->checkKeyState();								// Get Keyboard information
	at_master->updateAttacks();									// Update all Attacks
	for (auto entity : entityList) {
		entity.second->update();								// Update every entity
		cGrid->updateEntity(entity.second);						// Update CollisionGrid position
	}
	window->updateView(player);									// Update view to follow player
	cMaster->resolveEntityCollisions();							// Resolve collisions for every entity
	for (auto entity : entityList) entity.second->endUpdate();	// End updates for every entity
	
}

void Game::render() {
	if (debug) {
		window->render(cGrid, player->gridPos);							// Render collision grid positions of player (debug)
		window->render(cGrid);											// Render collision grid lines (debug)
	}
	window->render(spr_renderer);										// Render all animations and sprite effects
	if (debug) {
		for (auto object : objectList) window->render(object.second);	// Render every static collidable (debug)
		for (auto entity : entityList) window->renderDO(entity.second);	// Render all entity collision boxes (debug)
		for (auto att : at_master->attackList)							// Render all attack collision lines (debug)
			for (auto line : att.second->attackLines) 
				window->render(line);
	}
}

/*
 *	Perform all necessary functions to have a newly created Entity interact in the game world.
 */
void Game::addEntity(Entity *entity) {
	entityList.insert(std::pair<unsigned short int, Entity *>(eID, entity));
	entity->ID = eID++;
	cGrid->initEntity(entity);
	entity->setAttackManager(at_master);
}

/*
 *	Delete an Entity from all lists related to the Entity.
 */
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
