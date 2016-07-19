#include "BabySlime.h"
#include <iostream>

#define SPEED 0.5f

void BabySlime::init() {
	// AI vars
	generateRND(int(time(NULL)), 99);
	destination.x = int(x);
	destination.y = int(y);
	setBounds(120, 120, 120, 120);	// Temporary
	decisionMake = 0;
	// Entity vars
	name = "Baby Slime";
	cWidth = 10;
	cHeight = 10;
	life = 40;
	maxLife = 40;
	currentAnimation = idleE;
	weight = 2;

	Texture *tx0 = rm_master->getTexture("playerIdle.png");
	Texture *tx1 = rm_master->getTexture("playerAttRec.png");
	Texture *tx2 = rm_master->getTexture("playerDeath.png");

	animationList[idleE] = new Animation(tx0, 0.f, 0.f, 50, 50, 4, 0.2f, true); animationList[idleE]->setScale(0.35f, 0.35f);
	animationList[damageE] = new Animation(tx1, 0.f, 0.f, 50, 50, 6, 0.1f, true); animationList[damageE]->setScale(0.35f, 0.35f);
	animationList[deathE] = new Animation(tx2, 0.f, 0.f, 50, 50, 8, 0.1f, true); animationList[deathE]->setScale(0.35f, 0.35f);
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
	case DEAD: dead(); break;
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
	case DEAD:
		if (animFinished && !isDead)
			isDead = true;
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
		v = Vector2f(0.f, 0.f);
		currentAnimation = idleE;
		break;
	case DAMAGED:
		animFinished = false;
		hit = true;
		currentAnimation = damageE;
		break;
	case DEAD:
		animFinished = false;
		phased = true;
		invulnerable = true;
		hit = false;
		currentAnimation = deathE;
		break;
	}
	state = newState;
}

void BabySlime::decideDirection() {
	left = false;
	right = false;
	up = false;
	down = false;

	if (std::abs(int(x - destination.x)) > std::max(SPEED / 2, std::abs(v.x))) {
		if (x < destination.x) right = true;
		else left = true;
	}

	if (std::abs(y - destination.y) > std::max(SPEED / 2, std::abs(v.y))) {
		if (y < destination.y) down = true;
		else up = true;
	}
}

void BabySlime::walk() {
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
		// currentAnimation = animType(direction + WALK_ANIM);
	}
	else setState(IDLE); // Idle animation if currently not moving.
}

void BabySlime::run() {
	if (updateDirection()) {
		switch (direction) {
		case EAST: v = Vector2f(getSpeed(), 0); break;
		case NORTHEAST: v = Vector2f(getSpeed() * DIAG_MOD, -getSpeed() * DIAG_MOD); break;
		case NORTH: v = Vector2f(0, -getSpeed()); break;
		case NORTHWEST: v = Vector2f(-getSpeed() * DIAG_MOD, -getSpeed() * DIAG_MOD); break;
		case WEST: v = Vector2f(-getSpeed(), 0); break;
		case SOUTHWEST: v = Vector2f(-getSpeed() * DIAG_MOD, getSpeed() * DIAG_MOD); break;
		case SOUTH: Vector2f(0, getSpeed()); break;
		case SOUTHEAST: Vector2f(getSpeed() * DIAG_MOD, getSpeed() * DIAG_MOD); break;
		default: std::cout << "You've done the impossible... You're facing a direction I've never seen before!\n";
		}
		// currentAnimation = animType(direction + RUN_ANIM);
	}
	else setState(IDLE); // Idle animation if currently not moving.
}

void BabySlime::dead() {
	v *= 0.95f;
	animFinished = animationList[currentAnimation]->isLastFrame();
}
