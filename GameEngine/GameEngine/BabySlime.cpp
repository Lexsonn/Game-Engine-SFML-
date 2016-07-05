#include "BabySlime.h"

#define SPEED 0.5f

void BabySlime::init() {
	// AI vars
	generateRND(int(time(NULL)), 99);
	destination.x = int(x);
	destination.y = int(y);
	setBounds(120, 120, 240, 240);	// Temporary
	decisionMake = 0;
	decisionSpeed = 0.05f;
	// Entity vars
	name = "Baby Slime";
	cWidth = 10;
	cHeight = 10;
	life = 40;
	currentAnimation = idleE;
	weight = 2;
	Entity::init();

	Texture *tx0 = rm_master->getTexture("playerIdle.png");
	Texture *tx1 = rm_master->getTexture("playerAttRec.png");

	animationList[idleE] = new Animation(tx0, 0.f, 0.f, 50, 50, 4, 0.2f, true); animationList[idleE]->setScale(0.35f, 0.35f);
	animationList[damageE] = new Animation(tx1, 0.f, 0.f, 50, 50, 6, 0.1f, true); animationList[damageE]->setScale(0.35f, 0.35f);
}

BabySlime::~BabySlime() { }
BabySlime::BabySlime(ResourceManager *rm) {
	rm_master = rm;
	init();
}

BabySlime::BabySlime(float startX, float startY, ResourceManager *rm) {
	rm_master = rm;
	x = startX;
	y = startY;
	init();
}

float BabySlime::getSpeed() {
	return SPEED;
}

void BabySlime::update() {
	// AI decision making
	decisionMake += decisionSpeed;
	if (decisionMake >= 1) {
		decisionMake -= 1;
		if (getDecision() <= 8)
			setDestination();
	}
	decideDirection();

	// Typical Entity update
	animType oldAnimation = currentAnimation;

	updateState();
	switch (state) {
	case IDLE: idle(); break;
	case WALK: walk(); break;
	case RUN: run(); break;
	case DAMAGED: damaged(); break;
	}

	// If the Slime has been hit, flash the current sprite.
	flashCurrentSprite(oldAnimation);

	updatePosition();
}

void BabySlime::updateState() {
	switch (state) {
	case IDLE:
	case WALK:
	case RUN:
		if (issuedMove()) {
			if (running) setState(RUN);
			else setState(WALK);
		}
		else
			setState(IDLE);
		break;
	case DAMAGED:
		if (animFinished)
			setState(IDLE);
		break;
	default: std::cout << "What did you do now?\n";
	}
}
void BabySlime::setState(stateType newState) {
	if (state == newState)
		return;

	animationList[currentAnimation]->restart();

	switch (newState) {
	case IDLE:
		dx = 0;
		dy = 0;
		currentAnimation = idleE;
		break;
	case DAMAGED:
		animFinished = false;
		invulnerable = true;
		hit = true;
		currentAnimation = damageE;
		break;
	}
	state = newState;
}

void BabySlime::decideDirection() {
	left = false;
	right = false;
	up = false;
	down = false;

	if (std::abs(int(x - destination.x)) > std::max(SPEED / 2, std::abs(dx))) {
		if (x < destination.x) right = true;
		else left = true;
	}

	if (std::abs(y - destination.y) > std::max(SPEED / 2, std::abs(dy))) {
		if (y < destination.y) down = true;
		else up = true;
	}
}

void BabySlime::walk() {
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
		// currentAnimation = animType(direction + WALK_ANIM);
	}
	else setState(IDLE); // Idle animation if currently not moving.
}

void BabySlime::run() {
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
		// currentAnimation = animType(direction + RUN_ANIM);
	}
	else setState(IDLE); // Idle animation if currently not moving.
}
