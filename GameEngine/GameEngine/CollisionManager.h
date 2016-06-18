#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include <SFML/System.hpp>
#include "Entity.h"

using namespace sf;

class CollisionManager {
public:
	~CollisionManager();
	CollisionManager();
	
	void setAttackManager(AttackManager *manager);
	void setEntityList(std::map<unsigned short int, Entity *> *list);
	void setObjectList(std::map<unsigned short int, Collidable *> *list);
	void setEntityPosList(std::multimap<unsigned short int, Entity *> *list);
	void setObjectPosList(std::multimap<unsigned short int, Collidable *> *list);

	void resolveAttackCollisions();
	void resolveEntityCollisions();
private:
	std::map<unsigned short int, Entity *> *entityList;
	std::map<unsigned short int, Collidable *> *objectList;
	std::multimap<unsigned short int, Entity *> *entityPosList;
	std::multimap<unsigned short int, Collidable *> *objectPosList;
	AttackManager *at_master;
};

#endif
