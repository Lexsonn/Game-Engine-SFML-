#include "Game.h"
#include "Slime.h" // Eventually make a header with all Enemy types
#include "BabySlime.h"

#define _DEBUG_MODE true
#define _CHECK_CONTROLLABLE_FLAG if (newEntity->getType() & 1) controller->addControllable(dynamic_cast<Controllable *>(newEntity));

int WWIDTH(800);
int WHEIGHT(800);
Game *game(nullptr);

Game::~Game() { }
Game::Game(RenderWindow* rWindow) {
	game = this;
	eID = 0;
	oID = 0;
	debug = _DEBUG_MODE;

	const int l[] = { 25, 25, // load dis from txt file pls
		0,  4,  8,  4,  4,  4,  8,  12, 0,  4,  4,  4,  8,  0,  4,  8,  3,  3,  3,  3,  3,  3,  3,  3,  1,
		1,  5,  9,  5,  5,  5,  9,  12, 1,  5,  5,  5,  9,  1,  5,  9,  3,  3,  3,  3,  3,  3,  3,  3,  1,
		2,  6,  10, 5,  5,  5,  9,  12, 1,  5,  5,  5,  9,  1,  5,  9,  3,  3,  3,  3,  3,  3,  3,  3,  1,
		1,  5,  5,  5,  5,  5,  9,  12, 1,  5,  5,  5,  9,  1,  5,  9,  3,  3,  3,  3,  3,  3,  3,  3,  1,
		1,  5,  5,  5,  5,  6,  10, 12, 2,  6,  6,  6,  10, 2,  5,  9,  3,  3,  3,  3,  3,  3,  3,  3,  1,
		1,  5,  5,  5,  9,  12, 12, 12, 13, 13, 13, 13, 13, 14, 2,  10, 3,  3,  3,  3,  3,  3,  3,  3,  1,
		2,  6,  6,  6,  10, 12, 12, 13, 13, 13, 13, 14, 14, 14, 14, 14, 3,  3,  3,  3,  3,  3,  3,  3,  1,
		12, 12, 12, 12, 12, 12, 12, 13, 13, 13, 13, 14, 14, 14, 14, 14, 3,  3,  3,  3,  3,  3,  3,  3,  1,
		12, 12, 12, 12, 12, 12, 12, 12, 13, 13, 13, 13, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 1,
		12, 12, 12, 12, 12, 12, 12, 12, 13, 13, 13, 13, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 1,
		12, 12, 12, 12, 12, 12, 12, 12, 13, 13, 13, 13, 13, 13, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 1,
		12, 12, 12, 12, 12, 12, 12, 12, 13, 13, 13, 13, 13, 13, 13, 14, 14, 14, 14, 14, 14, 14, 14, 14, 1,
		12, 12, 12, 12, 12, 12, 12, 12, 13, 13, 13, 13, 13, 13, 13, 13, 14, 14, 14, 14, 14, 14, 14, 14, 1,
		12, 12, 12, 12, 12, 12, 12, 12, 13, 13, 13, 13, 13, 13, 13, 13, 14, 14, 14, 14, 14, 14, 14, 14, 1,
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
	//*
	std::vector<std::pair<Vector2f, Vector2f>> lines;
	lines.push_back(std::pair<Vector2f, Vector2f>(Vector2f(130, 250), Vector2f(420, 110)));
	lines.push_back(std::pair<Vector2f, Vector2f>(Vector2f(330, 150), Vector2f(330, 410)));
	Animation *anim = new Animation(rm_master->getTexture("playerAtt1.png"), 0, 0, 50, 50, 5, 0.4f, true);
	//Attack * att = new Attack(0, 0, 1, 60, 23, lines);
	at_master->addAttack(1, 1, 320, 23, lines, anim);
	at_master->attackList.at(0)->setPosition(210, 190);
	at_master->attackList.at(0)->setForce(2, 2);
	//*/
	/* QUICK CHECKS FOR CLASS SIZES (empty lists)
	std::cout << "ResourceManager : " << sizeof(ResourceManager) << "\tCollisionGrid: " << sizeof(CollisionGrid) << "\n";
	std::cout << "GameWindow : " << sizeof(GameWindow) << "\tInputController: " << sizeof(InputController) << "\n";
	std::cout << "AttackManager : " << sizeof(AttackManager) << "\tAttack: " << sizeof(Attack) << "\n";
	std::cout << "Player : " << sizeof(Player) << "\t\tEntity: " << sizeof(Entity) << "\n";
	//*/
}

void Game::initEntityMap() {
	entityMap["Entity"] = ENTITY;
	entityMap["Player"] = PLAYER;
	entityMap["Slime"] = SLIME;
	entityMap["BabySlime"] = BABYSLIME;
}

void Game::initManagers(RenderWindow *rWindow) {
	rm_master = new ResourceManager();
	spr_renderer = new SpriteRenderer();
	controller = new InputController();
	cGrid = new CollisionGrid();
	cMaster = new CollisionManager();
	at_master = new AttackManager();
	window = new GameWindow(rWindow, 640.f, 480.f, true);
	player = new Player(200, 200, rm_master);
	// Manager/player setup
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
	// All dis gon b loaded in txt file <3 <3 <3
	for (int i = 0; i <= level[0] / SSX; i++) {
		for (int j = 0; j <= level[1] / SSY; j++) {
			Vector2u offset = Vector2u(i, j);
			tileMap.push_back(TileMap("Tilesets/tileset1.png", Vector2u(TILESIZE_X, TILESIZE_Y), level, offset, rm_master));
		}
	}

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

void Game::createEntity(std::string entityName, Vector2f pos) {
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
	}
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
	for (auto entity : entityList) {
		entity.second->update();								// Update every entity
		cGrid->updateEntity(entity.second);						// Update CollisionGrid position
	}
	cMaster->resolveEntityCollisions();							// Resolve collisions for every entity
	window->updateView(player);									// Update view to follow player
	for (auto entity : entityList) entity.second->endUpdate();	// End updates for every entity
	at_master->updateAttacks();									// Update all Attacks
}

void Game::render() {
	for (int i = 0; i < tileMap.size(); i++) window->render(tileMap.at(i));
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
	entity->setAttackManager(at_master);
	cGrid->initEntity(entity);
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
	object->ID = oID;
	objectList.insert(std::pair<unsigned short int, Collidable *>(oID++, object));
	cGrid->addObject(object);
}

/*
*	Delete a static Collidable from all lists related to the Collidable.
*/
void Game::deleteObject(unsigned short int _ID) {
	std::map<unsigned short int, Collidable *>::iterator it = objectList.find(_ID);
	if (it == objectList.end())
		return;
	cGrid->deleteObject(it->second);
	delete it->second;
	objectList.erase(it);
}
//*/
