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
	at_master->addAttack(0, 1, 120, 23, lines, anim);
	at_master->attackList.at(0)->setPosition(210, 190);

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
	window = new GameWindow(rWindow, 640.f, 480.f, false);
	player = new Player(200, 200, rm_master);
	controller = new InputController();
	
	at_master->setResourceManager(rm_master);
	rm_master->setSpriteRenderer(spr_renderer);
	rm_master->setView(window->getView());
	cGrid->setAttackManager(at_master);
	controller->addControllable(player);
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
	at_master->updateAttacks();
	for (auto entity : entityList) {
		entity.second->update();								// Update every entity
		cGrid->updateEntity(entity.second);						// Update CollisionGrid position
	}
	window->updateView(player);									// Update view to follow player
	cGrid->resolveAttackCollision();							// Resolve collision for each attack
	for (auto entity : entityList) {
		cGrid->resolveEntityCollision(entity.second);			// Resolve collisions for every entity
		entity.second->endUpdate();								// End updates for every entity
	}
}

void Game::render() {
	if (debug) {
		window->render(cGrid, player->gridPos);							// Render collision grid first (debug)
		for (auto att : at_master->attackList) window->render(cGrid, att.second->gridPos);
	}
	window->render(spr_renderer);										// Render all animations and sprite effects
	if (debug) {
		for (auto object : objectList) window->render(object.second);	// Render every static collidable (debug)
		for (auto entity : entityList) window->renderDO(entity.second);	// Render all entity collision boxes (debug)
		for (auto att : at_master->attackList)
			for (auto line : att.second->attackLines) window->render(line);
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
	entity->setEntityList(cGrid->getEntityList());
	entity->setObjectList(cGrid->getObjectList());
	entity->setAttackManager(at_master);
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
