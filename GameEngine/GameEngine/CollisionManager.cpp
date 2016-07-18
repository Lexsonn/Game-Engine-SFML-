#include "CollisionManager.h"
#include "AttackManager.h"
#include "CollisionGrid.h"

std::map<unsigned short int, Entity *> *CollisionManager::entityList;

void CollisionManager::initialize(std::map<unsigned short int, Entity *> *eList) {
	entityList = eList;
}

/*
 *	Resolve all entity collisions with other entities, static collidables, and attacks.
 */
void CollisionManager::update() {
	for (std::map<unsigned short int, Entity *>::iterator it = entityList->begin(); it != entityList->end(); it++) {
		resolveEntitiyAttackCollision(it->second);
		moveEntityOutsideCollision(it->second);
	}
}

/*
 *	Resolve all entity collisions with attacks if Entity is not invulnerable
 */
void CollisionManager::resolveEntitiyAttackCollision(Entity * entity) {
	if (entity->invulnerable)
		return;
	for (auto attack : AttackManager::attackList) {
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

/*
 *	Resolve Entity collisions with other Entities and static Collidables
 */
void CollisionManager::moveEntityOutsideCollision(Entity *entity) {
	for (int i = 0; i < 4; i++) {
		if (entity->gridPos[i] >= 0) {
			if (!entity->phased) {
				std::pair<std::multimap<unsigned short int, Entity *>::iterator, std::multimap<unsigned short int, Entity *>::iterator> range;
				range = CollisionGrid::entityPosList.equal_range(entity->gridPos[i]);
				// Cycle through Entities first, because it is permissable to be partially inside one.
				for (std::multimap<unsigned short int, Entity *>::iterator it = range.first; it != range.second; it++) {
					if (it->second->ID != entity->ID) {
						moveEntityOutsideEntity(entity, it->second);
					}
				}
			}
			std::pair<std::multimap<unsigned short int, Collidable *>::iterator, std::multimap<unsigned short int, Collidable *>::iterator> cRange;
			cRange = CollisionGrid::objectPosList.equal_range(entity->gridPos[i]);
			// Cycle through Collidable objects last, since static collidables can not move. Entities cannot pass through.
			for (std::multimap<unsigned short int, Collidable *>::iterator it = cRange.first; it != cRange.second; it++)
				entity->moveOutsideCollidable(it->second);
		}
	}
}

/*
 *	Resolve collision with another entity, taking  phased and weight into account
 */
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

/*
 *	Only called if being pushed by another Entity. Retuns true if a Collidable object is in the current
 *	coordinates + _dx and _dy. Returns false otherwise.
 */
bool CollisionManager::willEntityCollide(Entity *entity, unsigned short int _ID, int _dx, int _dy) {
	for (int i = 0; i < 4; i++) {
		if (entity->gridPos[i] >= 0) {
			std::pair<std::multimap<unsigned short int, Collidable *>::iterator, std::multimap<unsigned short int, Collidable *>::iterator> cRange;
			cRange = CollisionGrid::objectPosList.equal_range(entity->gridPos[i]);

			for (std::multimap<unsigned short int, Collidable *>::iterator it = cRange.first; it != cRange.second; it++) {
				if (entity->willCollide(it->second, _dx, _dy))
					return true;
			}
			
			std::pair<std::multimap<unsigned short int, Entity *>::iterator, std::multimap<unsigned short int, Entity *>::iterator> range;
			range = CollisionGrid::entityPosList.equal_range(entity->gridPos[i]);

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
