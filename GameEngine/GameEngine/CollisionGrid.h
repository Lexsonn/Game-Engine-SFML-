#ifndef COLLISIONGRID_H
#define COLLISIONGRID_H

#include "Entity.h"

using namespace sf;

struct CollisionGrid {
public:
	static unsigned int width, height, size;
	static std::multimap<unsigned short int, Entity *> entityPosList;	  // multimap containing the grid positions of Entities
	static std::multimap<unsigned short int, Collidable *> objectPosList; // multimap containing the grid positions of static Collidables

	void build();

	void initEntity(Entity *entity);
	void updateEntity(Entity *entity);
	void deleteEntity(Entity *entity);
	void addObject(Collidable *object);
	void deleteObject(Collidable *object);

	void printLists();
	void clearLists();

	void render(RenderWindow *window) const;
	void render(RenderWindow *window, short int gridPos[]) const;
	void render(RenderWindow *window, std::map<short int, unsigned short int> gridPos) const;
private:
	void setGridPos(int gridPos[], Entity *entity);
	void addEntity(int gridPos[], Entity *entity);
	void removeEntity(int gridPos[], Entity *entity);
	void addObject(int gridPos, Collidable *object);
};
#endif
