#include "CollisionGrid.h"

CollisionGrid::~CollisionGrid() { }
CollisionGrid::CollisionGrid() : width(0), height(0), size(0) { }
CollisionGrid::CollisionGrid(int worldWidth, int worldHeight) {
	width = worldWidth / GRID_WIDTH;
	height = worldHeight / GRID_HEIGHT;
	size = width*(height + 2) + 1;

	std::cout << "Grid list size: " << size << "\n";
}

int CollisionGrid::getGrid(unsigned int x, unsigned int y) {
	int posX = x / GRID_WIDTH;
	int posY = y / GRID_HEIGHT;

	int i = -1;
	if (posX <= width && posY <= height)
		i = posX * (height + 1) + posY;
	
	return i;
}

Vector2i CollisionGrid::getCoords(unsigned int gridPos) {
	int x = gridPos / (height + 1);
	int y = gridPos % (height + 1);

	return Vector2i(x, y);
}

void CollisionGrid::initEntity(Entity *entity) {
	int gridPos[4];
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

	for (int i = 0; i < 4; i++) {
		if (gridPos[i] >= 0)
			entityList.insert(std::pair<unsigned short int, Entity *>(gridPos[i], entity));
		entity->gridPos[i] = gridPos[i];
	}
}

void CollisionGrid::updateEntity(Entity *entity) {
	int gridPos[4];
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

	if (gridPos[0] == entity->gridPos[0] && gridPos[1] == entity->gridPos[1] && gridPos[2] == entity->gridPos[2] && gridPos[3] == entity->gridPos[3])
		return;

	removeEntity(gridPos, entity);
	addEntity(gridPos, entity);
}

std::multimap<unsigned short int, Entity *> *CollisionGrid::getEntityList() {
	return &entityList;
}

std::multimap<unsigned short int, Collidable *> *CollisionGrid::getObjectList() {
	return &objectList;
}

void CollisionGrid::addEntity(int gridPos[], Entity *entity) {
	for (int i = 0; i < 4; i++) {
		if (gridPos[i] >= 0 && gridPos[i] != entity->gridPos[i]) 
			entityList.insert(std::pair<unsigned short int, Entity *>(gridPos[i], entity));
		entity->gridPos[i] = gridPos[i];
	}
}

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

void CollisionGrid::addObject(int gridPos, Collidable *object) {
	if (gridPos >= 0 && gridPos < size)
		objectList.insert(std::pair<unsigned short int, Collidable *>(gridPos, object));
}

void CollisionGrid::printList() {
	std::cout << "IDs: ";
	for (auto entity : entityList) {
		std::cout << entity.first  << "(" << entity.second->ID << ") ";
	}
	std::cout << std::endl;
}

void CollisionGrid::render(RenderWindow *window) {
	for (unsigned int i = 0; i < width; i++) {
		Vertex line[] = { Vertex(Vector2f(GRID_WIDTH * i * 1.f, 0.f)), Vertex(Vector2f(GRID_WIDTH * i * 1.f, height * GRID_HEIGHT * 1.f)) };
		line[0].color = Color(0, 255, 64); line[1].color = Color(0, 64, 255);
		window->draw(line, 2, Lines);
	}
	for (unsigned int i = 0; i < height; i++) {
		Vertex line[] = { Vertex(Vector2f(0.f, GRID_HEIGHT * i * 1.f)), Vertex(Vector2f(width * GRID_WIDTH * 1.f, GRID_HEIGHT * i * 1.f)) };
		line[0].color = Color(0, 255, 64); line[1].color = Color(0, 64, 255);
		window->draw(line, 2, Lines);
	}
}

void CollisionGrid::render(RenderWindow *window, short int gridPos[]) {
	render(window);

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