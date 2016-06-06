#include "Entity.h"

#define DO_TYPE_ENTITY 1;

void Entity::init() { 
	for (int i = 0; i < 4; i++)
		gridPos[i] = -1;
	visible = true;
	direction = EAST;
	state = IDLE;

	cX = x - cWidth / 2;
	cY = y - cHeight / 2;
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
	if (animationList[name])
		return true;
	return false;
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
				rm_master->addSprite(spr->sprite.getPosition().y, spr->sprite);
			}
		}
	}
	// Allow the entity to be drawn on top of its own sprite effects on same level by inserting last.
	rm_master->addSprite(y, animationList[currentAnimation]->sprite);
}

void Entity::render(RenderWindow *window) {
	// RENDER COLLISION BOX
	RectangleShape sh(Vector2f(cWidth, cHeight));
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
	cX = x - cWidth / 2;
	cY = y - cHeight / 2;
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
	Vector2i vec;
	if (insideCollidable(other)) {
		vec = getOverlap(other);
		x += vec.x;
		y += vec.y;
		cX = x - cWidth / 2;
		cY = y - cHeight / 2;
	}
}

void Entity::moveOutsideEntity(Entity *other) {
	if (other == nullptr)
		return;
	Vector2i vec;
	if (insideCollidable(other)) {
		if (weight > other->weight ){//|| (weight == other->weight && abs(other->dx) < abs(dx) && abs(other->dy) < abs(dy) )) {
			vec = other->getOverlap(this);
			if (!other->willCollide(ID, vec.x, vec.y) ) {
				other->moveOutsideCollidable();
				return;
			}
		}
		vec = getOverlap(other);
		x += vec.x;
		y += vec.y;
		cX = x - cWidth / 2;
		cY = y - cHeight / 2;
	}
}

// TO BE DEFINED IN CHILD CLASSES ////////////////////////////////////////////////////////////////////////////

void Entity::update() {}
void Entity::updateState() {}

// COLLIDABLE INHERITANCE ////////////////////////////////////////////////////////////////////////////////////

bool Entity::isEntity() {
	return true;
}

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
 *	Returns a Vector2i of which direction the Entity should move in order to be touching 
 *	the Collidable object's edge with its own collision box edge.
 */
Vector2i Entity::getOverlap(Entity* other) {
	int x = 0, y = 0;
	int otherLeft = other->cX - 1;						// Left line of other rectangle
	int otherRight = other->cX + other->cWidth + 1;		// Right line of other rectangle
	int otherTop = other->cY - 1;						// Top line of other rectangle
	int otherBottom = other->cY + +other->cHeight + 1;	// Bottom line of other rectangle

	Vector2i center = Vector2i(other->cX + other->cWidth / 2, other->cY + other->cHeight / 2);
	Vector2i myCenter = Vector2i(cX + cWidth / 2, cY + cWidth / 2);
	
	float angle = atan2(center.y - myCenter.y, center.x - myCenter.x) * 180/3.1415;
	
	if (angle <= -45 && angle >= -135) y += 1;	// NORTH
	if (angle <= -135 || angle >= 135) x += 1;	// WEST
	if (angle >= 45 && angle <= 135) y -= 1;	// SOUTH
	if (angle >= -45 && angle <= 45) x -= 1;	// EAST

	return Vector2i(x, y);
}
/*
*	To be called after checking if the Entity is inside a static non-Entity Collidable object.
*	Returns a Vector2i of the distance needed to move the Entity outside the Collidable object.
*/
Vector2i Entity::getOverlap(Collidable* other) {
	int x = 0, y = 0;
	int otherLeft = other->cX - 1;						// Left line of rectangle
	int otherRight = other->cX + other->cWidth + 1;		// Right line of rectangle
	int otherTop = other->cY - 1;						// Top line of rectangle
	int otherBottom = other->cY + +other->cHeight + 1;	// Bottom line of rectangle
	
	// Quick, dirty checks for which side the Entity has collided on. Doesn't work near corners
	if (hasCollidedN(other)) { y -= cY + dy - otherBottom;  return Vector2i(x, y); }
	if (hasCollidedW(other)) { x -= cX + dx - otherRight;  return Vector2i(x, y); }
	if (hasCollidedS(other)) { y -= cY + dy + cHeight - otherTop; return Vector2i(x, y); }
	if (hasCollidedE(other)) { x -= cX + dx + cWidth - otherLeft; return Vector2i(x, y); }
	
	// Doesn't often get through here, but if an Entity is pushed past the edge of the collidable this is used.
	Vector2i center = Vector2i(cX + cWidth / 2, cY + cHeight / 2);
	int dist[4];
	dist[0] = findDistance(Vector2i(otherLeft, otherTop), Vector2i(otherRight, otherTop), center);
	dist[1] = findDistance(Vector2i(otherLeft, otherTop), Vector2i(otherLeft, otherBottom), center);
	dist[2] = findDistance(Vector2i(otherLeft, otherBottom), Vector2i(otherRight, otherBottom), center);
	dist[3] = findDistance(Vector2i(otherRight, otherTop), Vector2i(otherRight, otherBottom), center);

	int smallest = std::min(std::min(abs(dist[0]), abs(dist[1])), std::min(abs(dist[2]), abs(dist[3])));
	
	if (smallest == abs(dist[2])) y -= cY + dy - otherBottom;
	if (smallest == abs(dist[3])) x -= cX + dx - otherRight;
	if (smallest == abs(dist[0])) y -= cY + dy + cHeight - otherTop;
	if (smallest == abs(dist[1])) x -= cX + dx + cWidth - otherLeft;
	
	return Vector2i(x, y);
}