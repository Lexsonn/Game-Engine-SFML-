#ifndef COLLISIONGRID_H
#define COLLISIONGRID_H

#include "Entity.h"

using namespace sf;

class CollisionGrid {
public:
	unsigned int width, height, size;

	~CollisionGrid();
	CollisionGrid();

	void setAttackManager(AttackManager *manager);

	void build();
	//int getGrid(unsigned int x, unsigned int y);
	//Vector2i getCoords(unsigned int gridPos);

	void initEntity(Entity *entity);
	void updateEntity(Entity *entity);
	void deleteEntity(Entity *entity);
	void addObject(Collidable *object);

	void resolveAttackCollision();
	void resolveEntityCollision(Entity *entity);

	std::multimap<unsigned short int, Entity *> *getEntityList();
	std::multimap<unsigned short int, Collidable *> *getObjectList();

	void printList();
	void render(RenderWindow *window);
	void render(RenderWindow *window, short int gridPos[]);
	void render(RenderWindow *window, std::map<short int, unsigned short int> gridPos);
private:
	std::multimap<unsigned short int, Entity *> entityList;
	std::multimap<unsigned short int, Collidable *> objectList;
	AttackManager *at_master;

	void setGridPos(int gridPos[], Entity *entity);
	void addEntity(int gridPos[], Entity *entity);
	void removeEntity(int gridPos[], Entity *entity);
	void addObject(int gridPos, Collidable *object);
};
#endif
