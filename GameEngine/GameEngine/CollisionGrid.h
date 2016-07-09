#ifndef COLLISIONGRID_H
#define COLLISIONGRID_H

#include "Entity.h"

using namespace sf;

class CollisionGrid {
public:
	unsigned int width, height, size;

	~CollisionGrid();
	CollisionGrid();

	void build();

	void initEntity(Entity *entity);
	void updateEntity(Entity *entity);
	void deleteEntity(Entity *entity);
	void addObject(Collidable *object);
	void deleteObject(Collidable *object);

	std::multimap<unsigned short int, Entity *> *getEntityList();
	std::multimap<unsigned short int, Collidable *> *getObjectList();

	void printList();
	void render(RenderWindow *window);
	void render(RenderWindow *window, short int gridPos[]);
	void render(RenderWindow *window, std::map<short int, unsigned short int> gridPos);
private:
	std::multimap<unsigned short int, Entity *> entityList;		// multimap containing the grid positions of Entities
	std::multimap<unsigned short int, Collidable *> objectList; // multimap containing the grid positions of static Collidables

	void setGridPos(int gridPos[], Entity *entity);
	void addEntity(int gridPos[], Entity *entity);
	void removeEntity(int gridPos[], Entity *entity);
	void addObject(int gridPos, Collidable *object);
};
#endif
