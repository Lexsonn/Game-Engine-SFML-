#include "Entity.h"
#include "Game.h"

extern int WWIDTH;
extern int WHEIGHT;
extern Game *game;

int Entity::entityType = 0;

void Entity::init() { 
	for (int i = 0; i < 4; i++)
		gridPos[i] = -1;
	visible = true;
	direction = EAST;
	state = IDLE;

	cX = int(x) - cWidth / 2;
	cY = int(y) - cHeight / 2;
}

Entity::~Entity() {
	for (unsigned int i = 0; i < spriteEffectList.size(); i++)
		delete spriteEffectList.at(i);
	for (std::map<animType, Animation *>::iterator it = animationList.begin(); it != animationList.end(); it++)
		delete it->second;

	spriteEffectList.clear();
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

void Entity::setAttackManager(AttackManager *manager) {
	at_master = manager;
}

int Entity::getType() {
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
	if (flashDmg > getFlashTimer()) { hit = false; flashDmg = 0; invulnerable = false; }
	if (int(flashDmg) % 2 == 1) animationList[currentAnimation]->setColor(Color(240, 50, 0));
	else animationList[currentAnimation]->setColor(Color(255, 255, 255));
	// Checking if sprite changed, and resetting the old sprite back to its original color:
	if (oldAnimation != currentAnimation) animationList[oldAnimation]->setColor(Color(255, 255, 255));
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

void Entity::damage(int dmg) {
	if (invulnerable)
		return;
	setState(DAMAGED);
	if (isInAnimList(currentAnimation))
		animationList[currentAnimation]->restart();
	life -= dmg;
	if (life < 0)
		life = 0;
}

void Entity::recover(int heal) {
	life += heal;
	if (life > maxLife)
		life = maxLife;
}

int Entity::getDrawableType() {
	return DO_ENTITY;
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

void Entity::applyForce(Vector2f f) {
	dx = f.x;
	dy = f.y;
}

void Entity::createNewEntity(std::string entityName, Vector2f pos) {
	if (game != nullptr)
		game->createEntity(entityName, pos);
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

	if (angle >= -45.f && angle <= 45.f) _x -= std::max(1, int(std::abs(other->dx)));	// EAST
	if (angle <= -45.f && angle >= -135.f) _y += std::max(1, int(std::abs(other->dy)));	// NORTH
	if (angle <= -135.f || angle >= 135.f) _x += std::max(1, int(std::abs(other->dx)));	// WEST
	if (angle >= 45.f && angle <= 135.f) _y -= std::max(1, int(std::abs(other->dy)));	// SOUTH

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

int Entity::createAttack(Vector2f pos, int type, int life, int str, Vector2f force, std::vector<std::pair<Vector2f, Vector2f>> attackLines, Animation *anim) {
	Attack *newAttack;
	newAttack = new Attack(ID, type, life, str, attackLines, anim);
	newAttack->setForce(force.x, force.y);
	newAttack->setPosition(pos);
	return at_master->addAttack(newAttack);
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
std::pair<Vector2f, Vector2f> Entity::createNormalAttackLine(float length, float distance) {
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
std::pair<Vector2f, Vector2f> Entity::createNormalAttackLineFromAngle(float length, float distance, float angle) {
	std::pair<Vector2f, Vector2f> line;
	line.first = Vector2f(x + distance, y - length / 2);
	line.second = Vector2f(x + distance, y + length / 2);
	line = rotateLineAboutPoint(line, Vector2f(x, y), angle * PI / 180.f);
	return line;
}

void Entity::idle() { }
void Entity::walk() { 
	if (updateDirection()) {
		switch (direction) {
		case EAST: dx = getSpeed() / 2; dy = 0; break;
		case NORTHEAST: dx = getSpeed() / 2 * DIAG_MOD; dy = -getSpeed() / 2 * DIAG_MOD; break;
		case NORTH: dx = 0; dy = -getSpeed() / 2; break;
		case NORTHWEST: dx = -getSpeed() / 2 * DIAG_MOD; dy = -getSpeed() / 2 * DIAG_MOD; break;
		case WEST: dx = -getSpeed() / 2; dy = 0; break;
		case SOUTHWEST: dx = -getSpeed() / 2 * DIAG_MOD; dy = getSpeed() / 2 * DIAG_MOD; break;
		case SOUTH: dx = 0; dy = getSpeed() / 2; break;
		case SOUTHEAST: dx = getSpeed() / 2 * DIAG_MOD; dy = getSpeed() / 2 * DIAG_MOD; break;
		default: std::cout << "You've done the impossible... You're facing a direction I've never seen before!\n";
		}
		currentAnimation = animType(direction + WALK_ANIM);
	}
	else setState(IDLE); // Idle animation if currently not moving.
}
void Entity::run() { 
	if (updateDirection()) {
		switch (direction) {
		case EAST: dx = getSpeed(); dy = 0; break;
		case NORTHEAST: dx = getSpeed() * DIAG_MOD; dy = -getSpeed() * DIAG_MOD; break;
		case NORTH: dx = 0; dy = -getSpeed(); break;
		case NORTHWEST: dx = -getSpeed() * DIAG_MOD; dy = -getSpeed() * DIAG_MOD; break;
		case WEST: dx = -getSpeed(); dy = 0; break;
		case SOUTHWEST: dx = -getSpeed() * DIAG_MOD; dy = getSpeed() * DIAG_MOD; break;
		case SOUTH: dx = 0; dy = getSpeed(); break;
		case SOUTHEAST: dx = getSpeed() * DIAG_MOD; dy = getSpeed() * DIAG_MOD; break;
		default: std::cout << "You've done the impossible... You're facing a direction I've never seen before!\n";
		}
		currentAnimation = animType(direction + RUN_ANIM);
	}
	else setState(IDLE); // Idle animation if currently not moving.
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
	dx *= 0.95f;
	dy *= 0.95f;
	animFinished = animationList[currentAnimation]->isLastFrame();
}

void Entity::dash() { }
