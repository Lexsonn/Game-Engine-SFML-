#include "CollisionGrid.h"

extern int WWIDTH;
extern int WHEIGHT;

CollisionGrid::~CollisionGrid() { }
CollisionGrid::CollisionGrid() {
	build();
}

/*
 *	Create bounds for the CollisionGrid. Called whenever the game world has changed.
 */
void CollisionGrid::build() {
	width = (WWIDTH - 1) / GRID_WIDTH;
	height = (WHEIGHT - 1) / GRID_HEIGHT;
	size = width*(height + 2) + 1;

	std::cout << "Grid list size: " << size << " (" << width << ", " << height << ")\n";
}

/*
 *	Format a grid position array of size 4 such that it contains the grid positions of an entity,
 *	setting any duplicate values to -1.
 */
void CollisionGrid::setGridPos(int gridPos[], Entity *entity) {
	gridPos[0] = getGrid(entity->cX, entity->cY);
	gridPos[1] = getGrid(entity->cX + entity->cWidth, entity->cY);
	gridPos[2] = getGrid(entity->cX + entity->cWidth, entity->cY + entity->cHeight);
	gridPos[3] = getGrid(entity->cX, entity->cY + entity->cHeight);

	for (int i = 0; i < 3; i++) {
		for (int j = i + 1; j < 4; j++) {
			if (gridPos[i] == gridPos[j])
				gridPos[j] = -1;
		}
	}
}

/*
 *	Set entity's grid position arrays based on where it is currently located, and add the entity
 *	to the multimap ordered by grid position.
 */
void CollisionGrid::initEntity(Entity *entity) {
	int gridPos[4];
	setGridPos(gridPos, entity);

	for (int i = 0; i < 4; i++) {
		if (gridPos[i] >= 0)
			entityList.insert(std::pair<unsigned short int, Entity *>(gridPos[i], entity));
		entity->gridPos[i] = gridPos[i];
	}
}

/*
 *	Update an entity's grid position array, whilst simutaneously updating current multimap of grid
 *	positions with the entity's new positions, if it has changed.
 */
void CollisionGrid::updateEntity(Entity *entity) {
	int gridPos[4];
	setGridPos(gridPos, entity);

	// If no changes made in grid position, no need to update multimap with new grid positions.
	if (gridPos[0] == entity->gridPos[0] && gridPos[1] == entity->gridPos[1] && gridPos[2] == entity->gridPos[2] && gridPos[3] == entity->gridPos[3])
		return;

	removeEntity(gridPos, entity);
	addEntity(gridPos, entity);
}

/*
 *	Delete an Entity from all CollisionGrid positions.
 */
void CollisionGrid::deleteEntity(Entity *entity) {
	for (int i = 0; i < 4; i++) {
		if (entity->gridPos[i] >= 0) {
			std::pair<std::multimap<unsigned short int, Entity *>::iterator, std::multimap<unsigned short int, Entity *>::iterator> range;
			range = entityList.equal_range(entity->gridPos[i]);

			for (std::multimap<unsigned short int, Entity *>::iterator it = range.first; it != range.second; it++) {
				if (it->second->ID == entity->ID) {
					entityList.erase(it);
					break;
				}
			}
		}
	}
}

std::multimap<unsigned short int, Entity *> *CollisionGrid::getEntityList() {
	return &entityList;
}

std::multimap<unsigned short int, Collidable *> *CollisionGrid::getObjectList() {
	return &objectList;
}

/*
 *	Update entity grid positions with new grid positions, being careful not to add duplicate
 *	entires to any one grid position.
 */
void CollisionGrid::addEntity(int gridPos[], Entity *entity) {
	for (int i = 0; i < 4; i++) {
		if (gridPos[i] >= 0 && gridPos[i] != entity->gridPos[i]) 
			entityList.insert(std::pair<unsigned short int, Entity *>(gridPos[i], entity));
		entity->gridPos[i] = gridPos[i];
	}
}

/*
 *	Remove entity from grid positions not included in the new grid positions.
 */
void CollisionGrid::removeEntity(int gridPos[], Entity *entity) {
	for (int i = 0; i < 4; i++) {
		if (entity->gridPos[i] >= 0 && gridPos[i] != entity->gridPos[i]) {
			//std::cout << "Removing " << entity->gridPos[i] << "... ";
			std::pair<std::multimap<unsigned short int, Entity *>::iterator, std::multimap<unsigned short int, Entity *>::iterator> range;
			range = entityList.equal_range(entity->gridPos[i]);

			for (std::multimap<unsigned short int, Entity *>::iterator it = range.first; it != range.second; it++) {
				if (it->second->ID == entity->ID) {
					//std::cout << "ERASE " << entity->ID << "\n";
					entityList.erase(it);
					break;
				}
			}
		}
	}
}

/*
 *	Add the static Collidable object to every grid position it touches with its collision box.
 */
void CollisionGrid::addObject(Collidable *object) {
	int cX, cW, cY, cH;
	cX = object->cX / GRID_WIDTH;
	cW = (object->cX + object->cWidth) / GRID_WIDTH;
	cY = object->cY / GRID_WIDTH;
	cH = (object->cY + object->cHeight) / GRID_HEIGHT;

	for (int i = cX; i <= cW; i++) {
		for (int j = cY; j <= cH; j++) {
			int gridPos = i * (height + 1) + j;
			addObject(gridPos, object);
		}
	}
}

/*
 *	Delete a static Collidable from all its CollisionGrid positions.
 */
void CollisionGrid::deleteObject(Collidable *object) {
	int cX, cW, cY, cH;
	cX = object->cX / GRID_WIDTH;
	cW = (object->cX + object->cWidth) / GRID_WIDTH;
	cY = object->cY / GRID_WIDTH;
	cH = (object->cY + object->cHeight) / GRID_HEIGHT;

	for (int i = cX; i <= cW; i++) {
		for (int j = cY; j <= cH; j++) {
			int gridPos = i * (height + 1) + j;
			if (gridPos < 0 || gridPos >= size)
				break;
			std::pair<std::multimap<unsigned short int, Collidable *>::iterator, std::multimap<unsigned short int, Collidable *>::iterator> range;
			range = objectList.equal_range(gridPos);

			for (std::multimap<unsigned short int, Collidable *>::iterator it = range.first; it != range.second; it++) {
				if (it->second->ID == object->ID) {
					objectList.erase(it);
					break;
				}
			}
		}
	}
}

/*
 *	Add a static Collidable object to the multimap of Collidables ordered by grid position.
 */
void CollisionGrid::addObject(int gridPos, Collidable *object) {
	if (gridPos >= 0 && gridPos < size)
		objectList.insert(std::pair<unsigned short int, Collidable *>(gridPos, object));
}

/*
 *	Prints a list of current Entities and Collidables by ID and their corresponding grid positions.
 */
void CollisionGrid::printLists() {
	std::cout << "Entity IDs: ";
	for (auto entity : entityList) {
		std::cout << entity.first  << "(" << entity.second->ID << ") ";
	}
	std::cout << "\nObject IDs: ";
	for (auto object : objectList) {
		std::cout << object.first << "(" << object.second->ID << ") ";
	}
	std::cout << std::endl;
}

/*
 *	Clear the lists of Entity and Collidable grid positions. 
 */
void CollisionGrid::clearLists() {
	// Simply clear the reference list of Entities and Collidables, no need to delete.
	entityList.clear();
	objectList.clear();
}

/*
 *	(DEBUG) Draw CollisionGrid grid
 */
void CollisionGrid::render(RenderWindow *window) {
	for (unsigned int i = 0; i <= width + 1; i++) {
		Vertex line[] = { Vertex(Vector2f(GRID_WIDTH * i * 1.f, 0.f)), Vertex(Vector2f(GRID_WIDTH * i * 1.f, (height + 1) * GRID_HEIGHT * 1.f)) };
		line[0].color = Color(0, 255, 64); line[1].color = Color(0, 64, 255);
		window->draw(line, 2, Lines);
	}
	for (unsigned int i = 0; i <= height + 1; i++) {
		Vertex line[] = { Vertex(Vector2f(0.f, GRID_HEIGHT * i * 1.f)), Vertex(Vector2f((width + 1) * GRID_WIDTH * 1.f, GRID_HEIGHT * i * 1.f)) };
		line[0].color = Color(0, 255, 64); line[1].color = Color(0, 64, 255);
		window->draw(line, 2, Lines);
	}
}

/*
 *	(DEBUG) Draw CollisionGrid positions for Entities
 */
void CollisionGrid::render(RenderWindow *window, short int gridPos[]) {
	for (int i = 0; i < 4; i++) {
		if (gridPos[i] >= 0) {
			Vector2i v = getCoords(gridPos[i]);
			RectangleShape sh(Vector2f(GRID_WIDTH, GRID_HEIGHT));
			sh.setFillColor(Color(0, 255, 24, 128));
			sh.setPosition((float)v.x*GRID_WIDTH, (float)v.y*GRID_HEIGHT);
			window->draw(sh);
		}
	}
}

/*
 *	(DEBUG) Draw CollisionGrid positions for Attacks
 */
void CollisionGrid::render(RenderWindow *window, std::map<short int, unsigned short int> gridPos) {
	for (auto pos : gridPos) {
		Vector2i v = getCoords(pos.first);
		RectangleShape sh(Vector2f(GRID_WIDTH, GRID_HEIGHT));
		sh.setFillColor(Color(255, 24, 24, 128));
		sh.setPosition((float)v.x*GRID_WIDTH, (float)v.y*GRID_HEIGHT);
		window->draw(sh);
	}
}
