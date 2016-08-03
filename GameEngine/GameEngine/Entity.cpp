#include "Entity.h"
#include "Game.h"
#include <iostream>

extern int WWIDTH;
extern int WHEIGHT;
extern Game *game;

const unsigned int Entity::entityType = 0x00000000;

void Entity::init() { 
	for (unsigned short int i = 0; i < 4; i++)
		gridPos[i] = -1;
}

Entity::~Entity() {
	for (std::map<animType, Animation *>::iterator it = animationList.begin(); it != animationList.end(); it++)
		delete it->second;
	
	animationList.clear();
}

Entity::Entity() : life(100), maxLife(100), invulnerable(false) { init(); }
Entity::Entity(ResourceManager *rm) : life(100), maxLife(100) { rm_master = rm; init();  }
Entity::Entity(float startX, float startY, ResourceManager *rm) : life(100), maxLife(100) {
	rm_master = rm;
	x = startX;
	y = startY;
	init();
}

unsigned int Entity::getType() {
	return Entity::entityType;
}

float Entity::getSpeed() {
	return ENTITY_SPEED;
}

float Entity::getFlashTimer() {
	return ENTITY_FLASHTIMER;
}

/*
 *	Check for the given animation name in the animation list. False if not in the list, true otherwise.
 */
bool Entity::isInAnimList(animType name) {
	return animationList.count(name) != 0;
}

/*
 *	Add an animation to the animation list. Does not add if the animation animType is already set.
 */
void Entity::addAnimation(Animation *anim, animType name) {
	animationList.insert(std::pair<animType, Animation*>(name, anim));
}

Animation *Entity::getCurrentAnimation() {
	return animationList[currentAnimation];
}

/*
 *	Flashes the current sprite. The old animation animList type is passed in to reset any animations whose
 *	color has been changed while the Entity is changing animations.
 */
void Entity::flashCurrentSprite(animType oldAnimation) {
	if (!hit)
		return;
	flashDmg += FLASHTIMER_SPEED;
	if (flashDmg > getFlashTimer()) { hit = false; setInvulFalse(); }
	if (int(flashDmg) % 2 == 1) animationList[currentAnimation]->setColor(Color(240, 50, 0));
	else animationList[currentAnimation]->setColor(Color(255, 255, 255));
	// Checking if sprite changed, and resetting the old sprite back to its original color:
	if (oldAnimation != currentAnimation) animationList[oldAnimation]->setColor(Color(255, 255, 255));
}

Sprite &Entity::getSprite() {
	if (isInAnimList(currentAnimation))
		return animationList[currentAnimation]->sprite;
	return emptySprite;
}

void Entity::beginUpdate() {
	if (isInAnimList(currentAnimation))
		animationList[currentAnimation]->beginUpdate();
}

void Entity::endUpdate() {
	if (!isInAnimList(currentAnimation))
		return;

	animationList[currentAnimation]->updatePosition(x, y);
	animationList[currentAnimation]->endUpdate();
	
	if (!isVisible())
		return;
	
	addToRenderer(int(y));
}

void Entity::damage(int dmg) {
	if (invulnerable || hit)
		return;

	if (isInAnimList(currentAnimation))
		animationList[currentAnimation]->restart();

	life -= dmg;
	if (life <= 0) {
		setState(DEAD);
		life = 0;
	} 
	else {
		hit = true;
		invulnerable = true;
		flashDmg = 0;
		setState(DAMAGED);
	}
}

void Entity::recover(int heal) {
	life += heal;
	if (life > maxLife)
		life = maxLife;
}

bool Entity::issuedDash() {
	return (dashU || dashL || dashD || dashR);
}

bool Entity::issuedMove() {
	return (up || left || down || right);
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
 *	Update the direction the Entity is dashing based on its dashU/dashL/dashD/dashR bool 
 *	values.
 *  Returns false if the Entity is not dashing in any direction.
 */
bool Entity::updateDashDirection() {
	if (!dashL && dashR) {	// EAST/NORTHEAST/SOUTHEAST
		if (!dashU && dashD) { direction = SOUTHEAST; return true; }
		if (dashU && !dashD) { direction = NORTHEAST; return true; }
		direction = EAST;
		return true;
	}
	if (dashL && !dashR) {	// WEST/NORTHWEST/SOUTHWEST
		if (!dashU && dashD) { direction = SOUTHWEST; return true; }
		if (dashU && !dashD) { direction = NORTHWEST; return true; }
		direction = WEST;
		return true;
	}
	if (dashU && !dashD) { direction = NORTH; return true; }
	if (!dashU && dashD) { direction = SOUTH; return true; }

	return false; // No dash being issued.
}

void Entity::updatePosition() {
	x += v.x;
	y += v.y;
	cX = int(x) - cWidth / 2;
	cY = int(y) - cHeight / 2;
}

void Entity::updatePosition(Vector2f v) {
	x += v.x;
	y += v.y;
	cX = int(x) - cWidth / 2;
	cY = int(y) - cHeight / 2;
}

void Entity::applyForce(Vector2f f) {
	v = f;
}

void Entity::createNewEntity(std::string entityName, Vector2f pos) {
	if (game != nullptr)
		game->createEntity(entityName, pos);
}

void Entity::createSpriteEffect(SpriteEffect *sprEffect) {
	if (game == nullptr)
		return;
	game->addDrawable(sprEffect);
}

void Entity::moveOutsideCollidable(Collidable *other) {
	if (insideCollidable(other)) {
		Vector2f vec = getStaticOverlap(other);
		updatePosition(vec);
	}
}

/*
 *	To be called after checking if the Entity is inside another Entity object.
 *	Returns a Vector2f of which direction the Entity should move in order to resolve Collision,
 *	but does so only in the smallest increment necessary.
 */
Vector2f Entity::getEntityOverlap(Entity *other) {
	int _x = 0, _y = 0;
	int otherLeft = other->cX - 1;						// Left line of other rectangle
	int otherRight = other->cX + other->cWidth + 1;		// Right line of other rectangle
	int otherTop = other->cY - 1;						// Top line of other rectangle
	int otherBottom = other->cY + +other->cHeight + 1;	// Bottom line of other rectangle

	Vector2f center = Vector2f((other->cX + other->cWidth / 2)*1.f, (other->cY + other->cHeight / 2)*1.f);
	Vector2f myCenter = Vector2f((cX + cWidth / 2)*1.f, (cY + cWidth / 2)*1.f);

	float angle = atan2(center.y - myCenter.y, center.x - myCenter.x) * 180 / 3.1415f;

	if (angle >= -48.f && angle <= 42.f) _x -= std::max(1, int(std::abs(other->v.x)));	// EAST
	if (angle <= -42.f && angle >= -138.f) _y += std::max(1, int(std::abs(other->v.y)));	// NORTH
	if (angle <= -132.f || angle >= 132.f) _x += std::max(1, int(std::abs(other->v.x)));	// WEST
	if (angle >= 42.f && angle <= 138.f) _y -= std::max(1, int(std::abs(other->v.y)));	// SOUTH

	return Vector2f(_x*1.f, _y*1.f);
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

void Entity::update() { }
void Entity::updateState() { }
void Entity::setState(stateType newState) { }

void Entity::setInvulFalse() {
	invulnerable = false;
}

int Entity::createAttack(Vector2f pos, int type, int life, int str, Vector2f force, std::vector<std::pair<Vector2f, Vector2f>> attackLines, Animation *anim) {
	Attack *newAttack = new Attack(ID, type, life, str, attackLines, anim);
	newAttack->setForce(force);
	newAttack->setPosition(pos);
	return AttackManager::addAttack(newAttack);
}

Vector2f Entity::generateForceFromDirection(float strength) {
	switch (direction) {
	case EAST: return Vector2f(strength, 0);
	case NORTHEAST: return Vector2f(strength * DIAG_MOD, -strength * DIAG_MOD);
	case NORTH: return Vector2f(0, -strength);
	case NORTHWEST: return Vector2f(-strength * DIAG_MOD, -strength * DIAG_MOD);
	case WEST: return Vector2f(-strength, 0);
	case SOUTHWEST: return Vector2f(-strength * DIAG_MOD, strength * DIAG_MOD);
	case SOUTH: return Vector2f(0, strength);
	case SOUTHEAST: return Vector2f(strength * DIAG_MOD, strength * DIAG_MOD);
	default: return Vector2f(0, 0);
	}
}

/*
 *	Returns a line of specified length, normal to the direction of the Entity, at a specified 
 *	distance away from the Entity's direction.
 */
std::pair<Vector2f, Vector2f> Entity::createNormalLine(float length, float distance) {
	std::pair<Vector2f, Vector2f> line;
	line.first = Vector2f(x + distance, y - length / 2);
	line.second = Vector2f(x + distance, y + length / 2);
	if (direction != EAST)
		line = rotateLineAboutPoint(line, Vector2f(x, y), 45.f * float(direction) * PI / 180.f);
	
	return line;
}

/*
 *	Returns a line of specified length, normal to the specified direction, at a specified
 *	distance away from the direction. The angle entered is in degrees.
 */
std::pair<Vector2f, Vector2f> Entity::createNormalLineFromAngle(float length, float distance, float angle) {
	std::pair<Vector2f, Vector2f> line;
	line.first = Vector2f(x + distance, y - length / 2);
	line.second = Vector2f(x + distance, y + length / 2);
	line = rotateLineAboutPoint(line, Vector2f(x, y), angle * PI / 180.f);
	return line;
}

Entity* Entity::getEntityAt(std::pair<Vector2f, Vector2f> line) {
	Vector2f mid = findMidpointOfLine(line);
	int gridPosition = getGrid(int(mid.x), int(mid.y));
	if (gridPosition >= 0) {
		std::pair<std::multimap<unsigned short int, Entity *>::iterator, std::multimap<unsigned short int, Entity *>::iterator> range;
		range = CollisionGrid::entityPosList.equal_range(gridPosition);

		for (std::multimap<unsigned short int, Entity *>::iterator it = range.first; it != range.second; it++) {
			if (it->second->ID != ID)
				if (it->second->intersectsLine(line))
					return it->second;
		}
	}
	return nullptr;
}

Entity *Entity::getEntityById(unsigned short int id) {
	return game->getEntityById(id);
}

void Entity::idle() { }
void Entity::walk() { 
	if (updateDirection()) {
		switch (direction) {
		case EAST: v = Vector2f(getSpeed() / 2, 0); break;
		case NORTHEAST: v = Vector2f(getSpeed() / 2 * DIAG_MOD, -getSpeed() / 2 * DIAG_MOD); break;
		case NORTH: v = Vector2f(0, -getSpeed() / 2); break;
		case NORTHWEST: v = Vector2f(-getSpeed() / 2 * DIAG_MOD, -getSpeed() / 2 * DIAG_MOD); break;
		case WEST: v = Vector2f(-getSpeed() / 2, 0); break;
		case SOUTHWEST: v = Vector2f(-getSpeed() / 2 * DIAG_MOD, getSpeed() / 2 * DIAG_MOD); break;
		case SOUTH: v = Vector2f(0, getSpeed() / 2); break;
		case SOUTHEAST: v = Vector2f(getSpeed() / 2 * DIAG_MOD, getSpeed() / 2 * DIAG_MOD); break;
		default: std::cout << "You've done the impossible... You're facing a direction I've never seen before!\n";
		}
		currentAnimation = animType(direction + WALK_ANIM);
	}
	else { // Idle animation if currently not moving.
		currentAnimation = animType(direction);
		v = Vector2f(0.f, 0.f);
	}
}

void Entity::run() { 
	if (updateDirection()) {
		switch (direction) {
		case EAST: v = Vector2f(getSpeed(), 0); break;
		case NORTHEAST: v = Vector2f(getSpeed() * DIAG_MOD, -getSpeed() * DIAG_MOD); break;
		case NORTH: v = Vector2f(0, -getSpeed()); break;
		case NORTHWEST: v = Vector2f(-getSpeed() * DIAG_MOD, -getSpeed() * DIAG_MOD); break;
		case WEST: v = Vector2f(-getSpeed(), 0); break;
		case SOUTHWEST: v = Vector2f(-getSpeed() * DIAG_MOD, getSpeed() * DIAG_MOD); break;
		case SOUTH: v = Vector2f(0, getSpeed()); break;
		case SOUTHEAST: v = Vector2f(getSpeed() * DIAG_MOD, getSpeed() * DIAG_MOD); break;
		default: std::cout << "You've done the impossible... You're facing a direction I've never seen before!\n";
		}
		currentAnimation = animType(direction + RUN_ANIM);
	}
	else { // Idle animation if currently not moving.
		currentAnimation = animType(direction);
		v = Vector2f(0.f, 0.f);
	}
}

void Entity::abs() { 
	animFinished = animationList[currentAnimation]->isLastFrame();
}

void Entity::attack() { 
	animFinished = animationList[currentAnimation]->isLastFrame();
}

void Entity::attRec() { 
	animFinished = animationList[currentAnimation]->isLastFrame();
}

void Entity::damaged() { 
	v *= 0.95f;
	animFinished = animationList[currentAnimation]->isLastFrame();
}

void Entity::dash() { }

void Entity::dead() {
	v *= 0.95f;
	animFinished = animationList[currentAnimation]->isLastFrame();
	if (animFinished) {
		v = Vector2f(0.f, 0.f);
		invulnerable = false; // Die here
	}
}
