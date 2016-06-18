#include "CollisionManager.h"

CollisionManager::~CollisionManager() { }
CollisionManager::CollisionManager() { }

void CollisionManager::setAttackManager(AttackManager *manager) {
	at_master = manager;
}

void CollisionManager::setEntityList(std::map<unsigned short int, Entity *> *list) {
	entityList = list;
}

void CollisionManager::setObjectList(std::map<unsigned short int, Collidable *> *list) {
	objectList = list;
}

void CollisionManager::setEntityPosList(std::multimap<unsigned short int, Entity *> *list) {
	entityPosList = list;
}
void CollisionManager::setObjectPosList(std::multimap<unsigned short int, Collidable *> *list) {
	objectPosList = list;
}

void CollisionManager::resolveAttackCollisions() {
	for (auto attack : at_master->attackList) {
		for (auto pos : attack.second->gridPos) {
			std::pair<std::multimap<unsigned short int, Entity *>::iterator, std::multimap<unsigned short int, Entity *>::iterator> range;
			range = entityPosList->equal_range(pos.first);

			for (std::multimap<unsigned short int, Entity *>::iterator it = range.first; it != range.second; it++) {
				for (auto line : attack.second->attackLines)
					if (it->second->intersectsLine(line))
						it->second->damage(attack.second->strength);
			}
		}
	}
}

void CollisionManager::resolveEntityCollisions() {
	for (std::map<unsigned short int, Entity *>::iterator it = entityList->begin(); it != entityList->end(); it++) 
		it->second->moveOutsideCollidable();
}
