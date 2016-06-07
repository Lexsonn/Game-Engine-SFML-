#include "Entity.h"

#define DO_TYPE_ENTITY 1;

void Entity::init() { 
	for (int i = 0; i < 4; i++)
		gridPos[i] = -1;
	visible = true;
	direction = EAST;
	state = IDLE;

	cX = int(x) - cWidth / 2;
	cY = int(y) - cHeight / 2;
}
Entity::~Entity() { }
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
 *	Add an animation to the animation list.
 */
void Entity::addAnimation(Animation *anim, animList name) {
	if (!isInAnimList(name)) 
		animationList.insert(std::pair<animList, Animation*>(name, anim));
}

int Entity::getDrawableType() {
	return DO_ENTITY;
}

Animation *Entity::getCurrentAnimation() {
	return animationList[currentAnimation];
}

void Entity::beginUpdate() {
	//dx = 0;
	//dy = 0;
	if (isInAnimList(currentAnimation))
		animationList[currentAnimation]->beginUpdate();
}

void Entity::endUpdate() {
	moveOutsideCollidable();

	if (!isInAnimList(currentAnimation))
		return;

	animationList[currentAnimation]->endUpdate();
	// If the Entity is not in view, do not draw.
	if (!isVisible())
		return;
	if (!spriteEffectList.empty()) {
		std::vector<SpriteEffect*>::iterator it;
		for (it = spriteEffectList.begin(); it < spriteEffectList.end(); ) {
			SpriteEffect * spr = *it;
			if (!spr->update())
				it = spriteEffectList.erase(it);
			else {
				it++;
				rm_master->addSprite(int(spr->sprite.getPosition().y), spr->sprite);
			}
		}
	}
	// Allow the entity to be drawn on top of its own sprite effects on same level by inserting last.
	rm_master->addSprite(int(y), animationList[currentAnimation]->sprite);
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
			std::pair<std::multimap<unsigned short int, Entity *>::iterator, std::multimap<unsigned short int, Entity *>::iterator> range;
			range = entityList->equal_range(gridPos[i]);
			// Cycle through Entities first, since it is permissable to be partially inside one.
			for (std::multimap<unsigned short int, Entity *>::iterator it = range.first; it != range.second; it++) {
				if (it->second->ID != ID) {
					moveOutsideEntity(it->second);
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

// TO BE DEFINED IN CHILD CLASSES ////////////////////////////////////////////////////////////////////////////

void Entity::update() {}
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
	
	// Quick, dirty checks for which side the Entity has collided on. Doesn't work near corners
	if (hasCollidedN(other)) { _y -= cY + int(dy) - otherBottom;  return Vector2f(_x*1.f, _y*1.f); }
	if (hasCollidedW(other)) { _x -= cX + int(dx) - otherRight;  return Vector2f(_x*1.f, _y*1.f); }
	if (hasCollidedS(other)) { _y -= cY + int(dy) + cHeight - otherTop; return Vector2f(_x*1.f, _y*1.f); }
	if (hasCollidedE(other)) { _x -= cX + int(dx) + cWidth - otherLeft; return Vector2f(_x*1.f, _y*1.f); }
	
	// Doesn't often get through here, but if an Entity is pushed past the edge of the collidable this is used.
	Vector2f center = Vector2f((cX + cWidth / 2)*1.f, (cY + cHeight / 2)*1.f);
	int dist[4];
	dist[0] = int(findDistance(Vector2f(otherLeft*1.f, otherTop*1.f), Vector2f(otherRight*1.f, otherTop*1.f), center));
	dist[1] = int(findDistance(Vector2f(otherLeft*1.f, otherTop*1.f), Vector2f(otherLeft*1.f, otherBottom*1.f), center));
	dist[2] = int(findDistance(Vector2f(otherLeft*1.f, otherBottom*1.f), Vector2f(otherRight*1.f, otherBottom*1.f), center));
	dist[3] = int(findDistance(Vector2f(otherRight*1.f, otherTop*1.f), Vector2f(otherRight*1.f, otherBottom*1.f), center));

	int smallest = std::min(std::min(abs(dist[0]), abs(dist[1])), std::min(abs(dist[2]), abs(dist[3])));
	
	if (smallest == abs(dist[2])) _y -= cY + int(dy) - otherBottom;
	if (smallest == abs(dist[3])) _x -= cX + int(dx) - otherRight;
	if (smallest == abs(dist[0])) _y -= cY + int(dy) + cHeight - otherTop;
	if (smallest == abs(dist[1])) _x -= cX + int(dx) + cWidth - otherLeft;
	
	return Vector2f(_x*1.f, _y*1.f);
}