#include "Entity.h"

extern int WWIDTH;
extern int WHEIGHT;

void Entity::init() { 
	for (int i = 0; i < 4; i++)
		gridPos[i] = -1;
	visible = true;
	direction = EAST;
	state = IDLE;

	cX = int(x) - cWidth / 2;
	cY = int(y) - cHeight / 2;
}
Entity::~Entity() { // Might have to revisit this
	for (unsigned int i = 0; i < spriteEffectList.size(); i++)
		delete spriteEffectList.at(i);
	
	spriteEffectList.clear();
}
Entity::Entity() { }
Entity::Entity(ResourceManager *rm) { rm_master = rm; }
Entity::Entity(float startX, float startY, ResourceManager *rm) { 
	life = 100; 
	rm_master = rm;
	x = startX;
	y = startY;
	init();
}

/*
 *	Check for the given animation name in the animation list. False if not in the list, true otherwise.
 */
bool Entity::isInAnimList(animList name) {
	return animationList.count(name) != 0;
}

/*
 *	Add an animation to the animation list. Does not add if the animation animList is already set.
 */
void Entity::addAnimation(Animation *anim, animList name) {
	animationList.insert(std::pair<animList, Animation*>(name, anim));
}

Animation *Entity::getCurrentAnimation() {
	return animationList[currentAnimation];
}

void Entity::beginUpdate() {
	if (isInAnimList(currentAnimation))
		animationList[currentAnimation]->beginUpdate();
}

void Entity::endUpdate() {
	// Resolve all collisions resulting from the update() function.
	moveOutsideCollidable();

	if (!isInAnimList(currentAnimation))
		return;

	animationList[currentAnimation]->updatePosition(x, y);
	animationList[currentAnimation]->endUpdate();
	
	if (!isVisible())
		return;
	if (!spriteEffectList.empty()) {
		std::vector<SpriteEffect *>::iterator it;
		for (it = spriteEffectList.begin(); it < spriteEffectList.end(); ) {
			SpriteEffect *spr = *it;
			if (!spr->update()) {
				delete spr;
				it = spriteEffectList.erase(it);
			}
			else {
				rm_master->addSprite(int(spr->sprite.getPosition().y), spr->sprite);
				it++;
			}
		}
	}
	// Allow the entity to be drawn on top of its own sprite effects on same level by inserting last.
	rm_master->addSprite(int(y), animationList[currentAnimation]->sprite);
}

int Entity::getDrawableType() {
	return DO_ENTITY;
}

void Entity::render(RenderWindow *window) {
	// RENDER COLLISION BOX
	RectangleShape sh(Vector2f(cWidth * 1.f, cHeight * 1.f));
	sh.setFillColor(Color(128, 0, 0, 160));
	sh.setOutlineColor(Color::Red);
	sh.setOutlineThickness(1.0f);
	sh.setPosition((float)cX, (float)cY);
	window->draw(sh);
}

/*
 *	Update the direction the Entity is facing based on its up/down/left/right bool values
 *  Returns false if the Entity is not traveling in any direction.
 */
bool Entity::updateDirection() {
	if (!left && right) {	// EAST/NORTHEAST/SOUTHEAST
		if (!up && down) { direction = SOUTHEAST; return true; }
		if (up && !down) { direction = NORTHEAST; return true; }
		direction = EAST; 
		return true; 
	}
	if (left && !right) {	// WEST/NORTHWEST/SOUTHWEST
		if (!up && down) { direction = SOUTHWEST; return true; }
		if (up && !down) { direction = NORTHWEST; return true; }
		direction = WEST; 
		return true;
	}
	if (up && !down) { direction = NORTH; return true; }
	if (!up && down) { direction = SOUTH; return true; }
	
	return false; // No direction is being held right now.
}

/*
 *	Create short line normal to the direction the Entity is facing. The line will be positioned 
 *	shortly in front of the Entity. Useful for interacting with Entities directly in front of the 
 *	current Entity.
 */
std::pair<Vector2f, Vector2f> Entity::getAccessorLineFromDirection() {
	std::pair<Vector2f, Vector2f> line;
	line.first = line.second = Vector2f(-1.f, -1.f);
	
	switch (direction) {
	case EAST: 
		line.first = Vector2f(x + cWidth / 2 + 4, y - cHeight / 4); 
		line.second = Vector2f(x + cWidth / 2 + 4, y + cHeight / 4); 
		break;
	case NORTHEAST: 
		line.first = Vector2f(x + cWidth / 2 - 4, y - cHeight / 2 + 4); 
		line.second = Vector2f(x + cWidth / 2 + 4, y - cHeight / 2 - 4); 
		break;
	case NORTH: 
		line.first = Vector2f(x - cWidth / 4, y - cHeight / 2 - 4);
		line.second = Vector2f(x + cWidth / 4, y - cHeight / 2 - 4); 
		break;
	case NORTHWEST:
		line.first = Vector2f(x - cWidth / 2 - 4, y - cHeight / 2 - 4);
		line.second = Vector2f(x - cWidth / 2 + 4, y - cHeight / 2 + 4);
		break;
	case WEST:
		line.first = Vector2f(x - cWidth / 2 - 4, y - cHeight / 4);
		line.second = Vector2f(x - cWidth / 2 - 4, y + cHeight / 4);
		break;
	case SOUTHWEST:
		line.first = Vector2f(x - cWidth / 2 - 4, y + cHeight / 2 - 4);
		line.second = Vector2f(x - cWidth / 2 + 4, y + cHeight / 2 + 4);
		break;
	case SOUTH:
		line.first = Vector2f(x - cWidth / 4, y + cHeight / 2 + 4);
		line.second = Vector2f(x + cWidth / 4, y + cHeight / 2 + 4);
		break;
	case SOUTHEAST:
		line.first = Vector2f(x + cWidth / 2 - 4, y + cHeight / 2 + 4);
		line.second = Vector2f(x + cWidth / 2 + 4, y + cHeight / 2 - 4);
		break;
	}

	return line;
}

Entity* Entity::getEntityAt(std::pair<Vector2f, Vector2f> line) {
	for (int i = 0; i < 4; i++) {
		if (gridPos[i] >= 0) {
			std::pair<std::multimap<unsigned short int, Entity *>::iterator, std::multimap<unsigned short int, Entity *>::iterator> range;
			range = entityList->equal_range(gridPos[i]);
			for (std::multimap<unsigned short int, Entity *>::iterator it = range.first; it != range.second; it++) {
				if (it->second->ID != ID) {
					if (it->second->intersectsLine(line))
						return it->second;
				}
			}
		}
	}
	return nullptr;
}

void Entity::updatePosition() {
	x += dx;
	y += dy;
	cX = int(x) - cWidth / 2;
	cY = int(y) - cHeight / 2;
}

void Entity::updatePosition(Vector2f v) {
	x += v.x;
	y += v.y;
	cX = int(x) - cWidth / 2;
	cY = int(y) - cHeight / 2;
}

void Entity::moveOutsideCollidable() {
	for (int i = 0; i < 4; i++) {
		if (gridPos[i] >= 0) {
			if (!phased) {
				std::pair<std::multimap<unsigned short int, Entity *>::iterator, std::multimap<unsigned short int, Entity *>::iterator> range;
				range = entityList->equal_range(gridPos[i]);
				// Cycle through Entities first, since it is permissable to be partially inside one.
				for (std::multimap<unsigned short int, Entity *>::iterator it = range.first; it != range.second; it++) {
					if (it->second->ID != ID) {
						moveOutsideEntity(it->second);
					}
				}
			}
			std::pair<std::multimap<unsigned short int, Collidable *>::iterator, std::multimap<unsigned short int, Collidable *>::iterator> cRange;
			cRange = objectList->equal_range(gridPos[i]);
			// Cycle through Collidable objects last, since those can not move. Entities cannot pass through.
			for (std::multimap<unsigned short int, Collidable *>::iterator it = cRange.first; it != cRange.second; it++)
				moveOutsideCollidable(it->second);
		}
	}
}

void Entity::moveOutsideCollidable(Collidable *other) {
	if (other == nullptr)
		return;
	Vector2f vec;
	if (insideCollidable(other)) {
		vec = getStaticOverlap(other);
		updatePosition(vec);
	}
}

void Entity::moveOutsideEntity(Entity *other) {
	if (other == nullptr)
		return;
	if (other->phased)
		return;
	Vector2f vec;
	if (insideCollidable(other)) {
		if (weight > other->weight) {//|| (weight == other->weight && abs(other->dx) < abs(dx) && abs(other->dy) < abs(dy) )) {
			vec = other->getOverlap(this);
			if (!other->willCollide(ID, int(vec.x), int(vec.y))) {
				other->moveOutsideCollidable();
				return;
			}
		}
		vec = getOverlap(other);
		updatePosition(vec);
	}
}

void Entity::update() { }
void Entity::updateState() {}

// COLLIDABLE INHERITANCE ////////////////////////////////////////////////////////////////////////////////////

/*
 *	Only called if being pushed by another Entity. Retuns true if a Collidable object is in the current
 *	coordinates + _dx and _dy. Returns false otherwise.
 */
bool Entity::willCollide(unsigned short int _ID, int _dx, int _dy) {
	bool c = false;
	for (int i = 0; i < 4; i++) {
		if (gridPos[i] >= 0) {
			std::pair<std::multimap<unsigned short int, Collidable *>::iterator, std::multimap<unsigned short int, Collidable *>::iterator> cRange;
			cRange = objectList->equal_range(gridPos[i]);

			for (std::multimap<unsigned short int, Collidable *>::iterator it = cRange.first; it != cRange.second; it++) {
				c = c || willCollide(it->second, _dx, _dy);
				if (c) return true;
			}
			
			std::pair<std::multimap<unsigned short int, Entity *>::iterator, std::multimap<unsigned short int, Entity *>::iterator> range;
			range = entityList->equal_range(gridPos[i]);

			for (std::multimap<unsigned short int, Entity *>::iterator it = range.first; it != range.second; it++) {
				if (it->second->ID != ID && it->second->ID != _ID) {
					if (!it->second->phased)
						c = c || willCollide(it->second, _dx, _dy);
					if (c) return true;
				}
			}
		}
	}
	return false;
}

/*
 *	Checks if a Collidable object is in the direction dx, dy of the Entity.
 *	Returns true if a Collidable object is in the current Collidable object's path. False otherwise.
 */
bool Entity::willCollide(Collidable * other, int _dx, int _dy) {
	if (other == nullptr) return false;
	int otherLeft = other->cX - _dx;						// Left line of rectangle
	int otherRight = other->cX + other->cWidth + _dx;		// Right line of rectangle
	int otherTop = other->cY - _dy;							// Top line of rectangle
	int otherBottom = other->cY + +other->cHeight + _dx;	// Bottom line of rectangle

	return !((cY + dy > otherBottom) || (cX + dx > otherRight) || (cY + dy + cHeight < otherTop) || (cX + dx + cWidth < otherLeft));
}

/*
 *	Returns true if the Entity with its current speed is inside the Collidable object. False otherwise.
 *	This method doesn't use a buffer in order to prevent jittering.
 */
bool Entity::insideCollidable(Collidable *other) {
	if (other == nullptr) return false;
	int otherLeft = other->cX;						// Left line of rectangle
	int otherRight = other->cX + other->cWidth;		// Right line of rectangle
	int otherTop = other->cY;						// Top line of rectangle
	int otherBottom = other->cY + +other->cHeight;	// Bottom line of rectangle

	return !((cY + dy > otherBottom) || (cX + dx > otherRight) || (cY + dy + cHeight < otherTop) || (cX + dx + cWidth < otherLeft));
}

/*
 *	To be called after checking if the Entity is inside another Entity object.
 *	Returns a Vector2f of which direction the Entity should move in order to be touching 
 *	the Collidable object's edge with its own collision box edge.
 */
Vector2f Entity::getOverlap(Entity* other) {
	int _x = 0, _y = 0;
	int otherLeft = other->cX - 1;						// Left line of other rectangle
	int otherRight = other->cX + other->cWidth + 1;		// Right line of other rectangle
	int otherTop = other->cY - 1;						// Top line of other rectangle
	int otherBottom = other->cY + +other->cHeight + 1;	// Bottom line of other rectangle

	Vector2f center = Vector2f((other->cX + other->cWidth / 2)*1.f, (other->cY + other->cHeight / 2)*1.f);
	Vector2f myCenter = Vector2f((cX + cWidth / 2)*1.f, (cY + cWidth / 2)*1.f);
	
	float angle = atan2(center.y - myCenter.y, center.x - myCenter.x) * 180/3.1415f;
	
	if (angle <= -45.f && angle >= -135.f) _y += std::max(1, int(abs(other->dy)));	// NORTH
	if (angle <= -135.f || angle >= 135.f) _x += std::max(1, int(abs(other->dx)));	// WEST
	if (angle >= 45.f && angle <= 135.f) _y -= std::max(1, int(abs(other->dy)));	// SOUTH
	if (angle >= -45.f && angle <= 45.f) _x -= std::max(1, int(abs(other->dx)));	// EAST

	return Vector2f(_x*1.f, _y*1.f);
}

/*
 *	To be called after checking if the Entity is inside a static non-Entity Collidable object.
 *	Returns a Vector2f of the distance needed to move the Entity outside the Collidable object.
 */
Vector2f Entity::getStaticOverlap(Collidable* other) {
	int _x = 0, _y = 0;
	int otherLeft = other->cX - 1;						// Left line of rectangle
	int otherRight = other->cX + other->cWidth + 1;		// Right line of rectangle
	int otherTop = other->cY - 1;						// Top line of rectangle
	int otherBottom = other->cY + +other->cHeight + 1;	// Bottom line of rectangle
	/*
	// Quick, dirty checks for which side the Entity has collided on. Doesn't work near corners
	if (hasCollidedN(other)) { _y -= cY - otherBottom;  return Vector2f(_x*1.f, _y*1.f); }
	if (hasCollidedW(other)) { _x -= cX - otherRight;  return Vector2f(_x*1.f, _y*1.f); }
	if (hasCollidedS(other)) { _y -= cY + cHeight - otherTop; return Vector2f(_x*1.f, _y*1.f); }
	if (hasCollidedE(other)) { _x -= cX + cWidth - otherLeft; return Vector2f(_x*1.f, _y*1.f); }
	//*/
	// Doesn't often get through here, but if an Entity is pushed past the edge of the collidable this is used.
	Vector2f center = Vector2f((cX + cWidth / 2)*1.f, (cY + cHeight / 2)*1.f);
	Vector2f otherCenter = Vector2f((other->cX + other->cWidth / 2)*1.f, (other->cY + other->cHeight / 2)*1.f);
	Vector2f diff = center - otherCenter;

	float xOverlap = cWidth/2 + other->cWidth/2 - abs(diff.x);
	float yOverlap = cHeight/2 + other->cHeight/2 - abs(diff.y);

	if (xOverlap < yOverlap) {
		if (diff.x > 0) _x -= cX - otherRight;
		else _x -= cX + cWidth - otherLeft;
	}
	else {
		if (diff.y > 0) _y -= cY - otherBottom;
		else _y -= cY + cHeight - otherTop;
	}
	
	
	return Vector2f(_x*1.f, _y*1.f);
}