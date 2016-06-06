#ifndef COLLISIONGRID_H
#define COLLISIONGRID_H

#include "Entity.h"

#define GRID_WIDTH 160
#define GRID_HEIGHT 160

using namespace sf;

class CollisionGrid {
public:
	unsigned int width, height, size;

	~CollisionGrid();
	CollisionGrid();
	CollisionGrid(int worldWidth, int worldHeight);

	int getGrid(unsigned int x, unsigned int y);
	Vector2i getCoords(unsigned int gridPos);

	void initEntity(Entity *entity);
	void updateEntity(Entity *entity);
	void addObject(Collidable *object);

	std::multimap<unsigned short int, Entity *> *getEntityList();
	std::multimap<unsigned short int, Collidable *> *getObjectList();

	void printList();
	void render(RenderWindow *window);
	void render(RenderWindow *window, short int gridPos[]);
private:
	std::multimap<unsigned short int, Entity *> entityList;
	std::multimap<unsigned short int, Collidable *> objectList;

	void addEntity(int gridPos[], Entity *entity);
	void removeEntity(int gridPos[], Entity *entity);
	void addObject(int gridPos, Collidable *object);
};
#endif