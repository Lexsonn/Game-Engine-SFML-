#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include <SFML/System.hpp>
#include "Entity.h"

using namespace sf;

struct Attackmanager;
struct CollisionGrid;

struct CollisionManager {
public:
	void initialize(std::map<unsigned short int, Entity *> *eList);
	void update();
private:
	static std::map<unsigned short int, Entity *> *entityList;

	void resolveEntitiyAttackCollision(Entity *entity);
	void moveEntityOutsideCollision(Entity *entity);
	void moveEntityOutsideEntity(Entity *entity, Entity *other);
	bool willEntityCollide(Entity *entity, unsigned short int _ID, int _dx, int _dy);
};
#endif
