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

void CollisionManager::resolveEntityCollisions() {
	for (std::map<unsigned short int, Entity *>::iterator it = entityList->begin(); it != entityList->end(); it++) {
		// Resolve Entity collisions with Attacks
		resolveEntitiyAttackCollision(it->second);
		// Resolve Entity collisions with other Entities and static Collidables
		moveEntityOutsideCollision(it->second);
	}
}

void CollisionManager::resolveEntitiyAttackCollision(Entity * entity) {
	for (auto attack : at_master->attackList) {
		if (entity->ID != attack.second->parent) {
			for (auto line : attack.second->attackLines) {
				if (entity->intersectsLine(line)) {
					entity->damage(attack.second->strength);
					entity->applyForce(attack.second->force);
					return;
				}
			}
		}
	}
}

void CollisionManager::moveEntityOutsideCollision(Entity *entity) {
	for (int i = 0; i < 4; i++) {
		if (entity->gridPos[i] >= 0) {
			if (!entity->phased) {
				std::pair<std::multimap<unsigned short int, Entity *>::iterator, std::multimap<unsigned short int, Entity *>::iterator> range;
				range = entityPosList->equal_range(entity->gridPos[i]);
				// Cycle through Entities first, since it is permissable to be partially inside one.
				for (std::multimap<unsigned short int, Entity *>::iterator it = range.first; it != range.second; it++) {
					if (it->second->ID != entity->ID) {
						moveEntityOutsideEntity(entity, it->second);
					}
				}
			}
			std::pair<std::multimap<unsigned short int, Collidable *>::iterator, std::multimap<unsigned short int, Collidable *>::iterator> cRange;
			cRange = objectPosList->equal_range(entity->gridPos[i]);
			// Cycle through Collidable objects last, since those can not move. Entities cannot pass through.
			for (std::multimap<unsigned short int, Collidable *>::iterator it = cRange.first; it != cRange.second; it++)
				entity->moveOutsideCollidable(it->second);
		}
	}
}

void CollisionManager::moveEntityOutsideEntity(Entity *entity, Entity *other) {
	if (other == nullptr)
		return;
	if (other->phased)
		return;
	Vector2f vec;
	if (entity->insideCollidable(other)) {
		if (entity->weight > other->weight) {//|| (weight == other->weight && abs(other->dx) < abs(dx) && abs(other->dy) < abs(dy) )) {
			vec = other->getEntityOverlap(entity);
			if (!willEntityCollide(other, entity->ID, int(vec.x), int(vec.y))) {
				moveEntityOutsideCollision(other);
				return;
			}
		}
		vec = entity->getEntityOverlap(other);
		entity->updatePosition(vec);
	}
}

bool CollisionManager::willEntityCollide(Entity *entity, unsigned short int _ID, int _dx, int _dy) {
	for (int i = 0; i < 4; i++) {
		if (entity->gridPos[i] >= 0) {
			std::pair<std::multimap<unsigned short int, Collidable *>::iterator, std::multimap<unsigned short int, Collidable *>::iterator> cRange;
			cRange = objectPosList->equal_range(entity->gridPos[i]);

			for (std::multimap<unsigned short int, Collidable *>::iterator it = cRange.first; it != cRange.second; it++) {
				if (entity->willCollide(it->second, _dx, _dy))
					return true;
			}

			std::pair<std::multimap<unsigned short int, Entity *>::iterator, std::multimap<unsigned short int, Entity *>::iterator> range;
			range = entityPosList->equal_range(entity->gridPos[i]);

			for (std::multimap<unsigned short int, Entity *>::iterator it = range.first; it != range.second; it++) {
				if (it->second->ID != entity->ID && it->second->ID != _ID) {
					if (!it->second->phased)
						if (entity->willCollide(it->second, _dx, _dy))
							return true;
				}
			}
		}
	}
	return false;
}
